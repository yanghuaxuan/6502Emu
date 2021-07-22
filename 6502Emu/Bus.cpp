#include "Bus.h"
#include <cstdint>

using namespace emu6502;

uint8_t Bus::read(uint16_t addr)
{
	return ram.mem_read(addr);
}
void Bus::write()
{

}