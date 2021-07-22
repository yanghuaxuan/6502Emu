#include "RAM.h"

emu6502::RAM::RAM()
{
	init();
}

emu6502::RAM::~RAM() {}

void emu6502::RAM::init()
{
	// Clear RAM
	for (uint8_t i : ram)
	{
		i = 0x00;
	}
}

void emu6502::RAM::connectBus(Bus &bus)
{
	bus = bus;
}

uint8_t emu6502::RAM::mem_read(uint16_t addr)
{
	// Check if address is legal
	return addr < MEM_SIZE ? ram[addr] : 0x00;
}

void emu6502::RAM::mem_write(uint16_t addr, uint8_t data)
{
	ram[addr] = data;
}