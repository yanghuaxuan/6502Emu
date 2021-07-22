#pragma once
#include "CPU.h"
#include "RAM.h"

// Prevent circular inclusion
class CPU;
class RAM;

namespace emu6502
{
	class Bus
	{
	public:
		uint8_t read(uint16_t addr);
		void write();
	private:
		// Get access to devices
		CPU *cpu = nullptr;
		RAM *ram = nullptr;
	};
}
