#include "RAM.h"
#include <iostream>

emu6502::RAM::RAM()
{
	init();
}

emu6502::RAM::~RAM() {}

void emu6502::RAM::init()
{
	// Clear RAM
	for (int i = 0; i < MEM_SIZE; i++)
	{
		ram[i] = 0x00;
	}
}

uint8_t emu6502::RAM::mem_read(uint16_t addr)
{
	// Check if address is legal
	if (addr >= 0x0000 && addr < 0x10000)
	{
		return ram[addr];
	}
	return 0x00;
}

void emu6502::RAM::mem_write(uint16_t addr, uint8_t data)
{
	ram[addr] = data;
}