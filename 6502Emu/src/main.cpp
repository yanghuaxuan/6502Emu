#include <iostream>
#include "emu6502.h"

int main()
{
	using namespace std;
	std::ifstream opcodes("../opcodes.tsv");
	if (!opcodes.is_open())
	{
		cout << "OpCode instruction tsv not found!" << endl;
		return -1;
	}

	emu6502::RAM ram;
	emu6502::CPU cpu;

	return 0;
}