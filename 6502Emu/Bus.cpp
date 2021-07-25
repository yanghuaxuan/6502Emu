#include "Bus.h"

emu6502::Bus::Bus()
{
	cpu.connectBus(this);
	ram.connectBus(this);
}

emu6502::Bus::~Bus() {}

uint8_t emu6502::Bus::read(uint16_t addr)
{
	return ram.mem_read(addr);
}

void emu6502::Bus::write()
{

}
