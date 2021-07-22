#include "Bus.h"
#include <cstdint>

uint8_t emu6502::Bus::read(uint16_t addr)
{
	return ram->mem_read(addr);
}
void emu6502::Bus::write()
{

}
