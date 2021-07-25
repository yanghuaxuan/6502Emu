#pragma once
#include "CPU.h"
#include "RAM.h"
namespace emu6502
{
	class Bus
	{
	public:
		Bus();
		~Bus();
		uint8_t read(uint16_t addr);
		void write();
	private:
		// Get access to devices
		// Prevent circular inclusion
		CPU cpu;
		RAM ram;
	};
}
