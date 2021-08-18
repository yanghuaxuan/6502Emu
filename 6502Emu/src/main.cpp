#include <iostream>
#include "emulator.h"
#include "emuUI.h"

int main()
{
	using namespace std;

	emu6502::emuUI ui;
	emu6502::RAM ram;
	emu6502::CPU cpu;

	ui.initUI();

	return 0;
}
