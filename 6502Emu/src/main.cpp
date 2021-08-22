#include <iostream>
#include <sstream>
#include "emulator.h"
#include "emuUI.h"

void loadObjCode(emu6502::RAM *ram, std::string objString);

int main()
{
	using namespace std;

	emu6502::RAM ram;
	emu6502::CPU cpu;
	emu6502::emuUI ui(&cpu);

	cpu.connectRam(&ram);
	// Load object code into RAM
	loadObjCode(&ram, "A2 01");
	cpu.reset();
	printf("PC: %X\n", cpu.getP());
	ui.initUI();

	return 0;
}

void loadObjCode(emu6502::RAM *ram, std::string objString)
{
	uint16_t memOffset = 0x8000;
	std::stringstream ss;
	ss << objString;
	while(!ss.eof())
	{
		std::string byte;
		ss >> byte;
		ram->mem_write(memOffset++, uint8_t(std::stoul(byte, nullptr, 16)));
	}
	ram->mem_write(0xFFFC, 0x00);
	ram->mem_write(0xFFFD, 0x80);
}