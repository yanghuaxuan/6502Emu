#include <iostream>
#include "emu6502.h"

int main()
{
	using namespace std;

	emu6502::RAM ram;
	ram.mem_write(0xFFFC, 0xA9);
	emu6502::CPU cpu;

	return 0;
}