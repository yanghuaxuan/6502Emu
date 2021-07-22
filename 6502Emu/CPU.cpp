#include "CPU.h"

emu6502::CPU::CPU()
{
	reset();
}

emu6502::CPU::~CPU() {}

void emu6502::CPU::connectBus(Bus &bus)
{
	bus = bus;
}

void emu6502::CPU::reset()
{
	// 0xFFFC Sets us to a location that we can immediately use in memory
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
	return bus->read(pc);
}

// TODO
void emu6502::CPU::execute(uint8_t instruction)
{

}

void emu6502::CPU::doInstruction(int cyclesNeeded)
{
	uint8_t instruction = fetch();
	execute(instruction);
	cyclesNeeded--;
}


