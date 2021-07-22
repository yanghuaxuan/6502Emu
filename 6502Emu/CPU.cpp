#include "CPU.h"

using namespace emu6502;

CPU::CPU() 
{
	reset();
}

CPU::~CPU() {}

void CPU::reset()
{
	// 0xFFFC Sets us to a location that we can immediately use in memory
	pc = 0xFFFC;
	stkp = 0x0100;

	acc = 0x00;
	x = 0x00; 
	y = 0x00;
	status = 0x00;

}

uint8_t CPU::fetch()
{
	pc++;
	return bus.read(pc);

}

void CPU::execute(uint8_t instruction)
{

}

void CPU::doInstruction(int cyclesNeeded)
{
	uint8_t instruction = fetch();
	execute(instruction);
}


