#include "CPU.h"
#include "Bus.h"
#include <iostream>

emu6502::CPU::CPU()
{
	reset();

	using a = CPU;
}

emu6502::CPU::~CPU() {}

void emu6502::CPU::connectRam(RAM& ram)
{
	ram = ram;
}

void emu6502::CPU::reset()
{
	// 0xFFFC Sets us to a location that we contains an absolute address to jump to
	pc = 0xFFFC;
	// Stack pointer starts at memory address 0x01000 
	stkp = 0x0100;

	// Clear registers
	acc = 0x00;
	x = 0x00; 
	y = 0x00;
	status = 0x00;
}

uint8_t emu6502::CPU::fetch()
{
	pc++;
	return ram.mem_read(pc);
}
 
void emu6502::CPU::execute(std::string opCode, int cyclesNeeded)
{
	// Black magic methods accessing function pointers
	auto instruction = opCodes.find(opCode);
	if (instruction == opCodes.end())
	{
		std::cout << "Error finding OpCode!" << std::endl;
	}
	else
	{
		// De-reference function pointer
		(this->*instruction->second)();
	}
	cyclesNeeded--;
}

// Opcode Implementation
uint8_t emu6502::CPU::ADC()
{
	return 0;
}

uint8_t emu6502::CPU::LDA()
{
	uint8_t val = fetch();
	acc = val;
	// Temporary testing, plz remove
	std::cout << int(acc) << std::endl;
	return 0;
}