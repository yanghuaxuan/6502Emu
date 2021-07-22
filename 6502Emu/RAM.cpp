#include "RAM.h"

using namespace emu6502;

const int MEM_SIZE = 0x10000;

RAM::RAM()
{
	init();
}

RAM::~RAM() {}

void RAM::init()
{
	// Clear RAM
	for (uint8_t i : ram)
	{
		i = 0x00;
	}
}