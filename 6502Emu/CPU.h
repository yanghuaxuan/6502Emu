#pragma once
#include <cstdint>
#include "Bus.h"

// Prevent circular inclusion
class Bus;

namespace emu6502
{
	class CPU
	{
	public:
		CPU();
		~CPU();

		uint8_t fetch();
		void execute(uint8_t instruction);
		void doInstruction(int cyclesNeeded);
		void connectBus(Bus &bus);
		void reset();
	private:
		// Might have to check w/ stack pointer type
		uint16_t pc, stkp;
		uint8_t acc;
		uint8_t x, y;

		uint8_t status;
		enum flags { C, Z, I, D, B, U, V, N };

		// "Wire" our bus to CPU
		Bus *bus = nullptr;
	};
}

