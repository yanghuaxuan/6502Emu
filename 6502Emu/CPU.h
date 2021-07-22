#pragma once
#include <cstdint>
#include "Bus.h"

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
		void reset();
	private:
		uint16_t pc;
		uint8_t stkp, acc;
		uint8_t x, y;

		uint8_t status;
		enum flags { C, Z, I, D, B, U, V, N };

		// "Wire" our bus to CPU
		Bus bus;
	};
}

