#include "CPU.h"
#include <iostream>

emu6502::CPU::CPU()
{
	instructions =
	{
		{ "BRK", &CPU::BRK, &CPU::IMM, 7 },{ "ORA", &CPU::ORA, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::ZP0, 3 },{ "ASL", &CPU::ASL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "BIT", &CPU::BIT, &CPU::ZP0, 3 },{ "AND", &CPU::AND, &CPU::ZP0, 3 },{ "ROL", &CPU::ROL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::ZP0, 3 },{ "LSR", &CPU::LSR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ADC", &CPU::ADC, &CPU::ZP0, 3 },{ "ROR", &CPU::ROR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZP0, 3 },{ "STA", &CPU::STA, &CPU::ZP0, 3 },{ "STX", &CPU::STX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IZY, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::NOP, &CPU::IMP, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IZX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "LDY", &CPU::LDY, &CPU::ZP0, 3 },{ "LDA", &CPU::LDA, &CPU::ZP0, 3 },{ "LDX", &CPU::LDX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPY", &CPU::CPY, &CPU::ZP0, 3 },{ "CMP", &CPU::CMP, &CPU::ZP0, 3 },{ "DEC", &CPU::DEC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPX", &CPU::CPX, &CPU::ZP0, 3 },{ "SBC", &CPU::SBC, &CPU::ZP0, 3 },{ "INC", &CPU::INC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::SBC, &CPU::IMP, 2 },{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
	};

	reset();
}

emu6502::CPU::~CPU() {}

void emu6502::CPU::connectRam(RAM& ram)
{
	ram = ram;
}

void emu6502::CPU::reset()
{
	// 0xFFFC Sets us to a location that we contains an absolute address to jump to
	pc = 0xFFFC;
	// Stack pointer starts at memory address 0x01000 
	stkp = 0x0100;

	// Clear registers
	A = 0x00;
	x = 0x00; 
	y = 0x00;
	status = 0x00;

	// Clear helper variables
	temp = 0x0000; 
	abs_addr = 0x0000; 
	rel_addr = 0x00;
	ir = 0x00;
}

/*
* Fetch data from pc, or by argument
* @param void or addr
* @return Single byte of data
*/
uint8_t emu6502::CPU::fetch()
{
	return ram.mem_read(pc++);
}

uint8_t emu6502::CPU::fetch(uint16_t addr)
{
	return ram.mem_read(addr);
}

/*
* Same as fetch but skip if implied IMP addressing mode is specified
* @param void (always fetch from pc)
* @return Single byte of data
*/
uint8_t emu6502::CPU::fetch_noIMP()
{
	return 0;
}
 
void emu6502::CPU::execute()
{
	while (clock.clockCycles != 0)
	{
		uint8_t instruction = fetch();
		// Function that will execute instruction
		clock.cycle();
	}
}


// Addressing Mode implementations


uint8_t emu6502::CPU::IMP()
{
	ir = A;
	return 0;
}

uint8_t emu6502::CPU::IMM()
{
	abs_addr = pc++;
	return 0;
}

uint8_t emu6502::CPU::ZP0()
{
	// Allows us to store the first 256-bytes of data into zero-page,
	// reducing the amount of cycles needed
	abs_addr = fetch();
	abs_addr &= 0x00FF;
	return 0;
}

uint8_t emu6502::CPU::ZPX()
{
	abs_addr = (fetch() + x);

	return 0;
}

uint8_t emu6502::CPU::ZPY()
{
	abs_addr = (fetch() + y);
	abs_addr &= 0x00FF;

	return 0;
}

// Fetch absolute address
uint8_t emu6502::CPU::ABS()
{
	uint16_t low = fetch();
	uint16_t high = fetch();

	abs_addr = (high << 8) | low;

	return 0;
}

// ABS but with X offset
uint8_t emu6502::CPU::ABX()
{
	uint16_t lo = fetch();
	uint16_t hi = fetch();

	abs_addr = (hi << 8) | lo;
	abs_addr += x;
	
	// Check if page has changed
	return ((abs_addr & 0xFF00) != (hi << 8)) ? 1 : 0;
}

uint8_t emu6502::CPU::ABY()
{
	uint16_t lo = fetch();
	uint16_t hi = fetch();

	abs_addr = (hi << 8) | lo;
	abs_addr += y;

	// Check if page has changed
	return ((abs_addr & 0xFF00) != (hi << 8)) ? 1 : 0;
}

// 6502 pointer implementation
uint8_t emu6502::CPU::IND()
{
	// Get the actual address where data resides (aka pointer)
	uint16_t ptr_low = fetch();
	uint16_t ptr_high = fetch();
	uint16_t ptr = (ptr_high << 8) | ptr_low;

	/*
	 * See https ://www.nesdev.com/6502bugs.txt
	 * Calculating high byte will fail because 
	 * adding a high byte by 1 changes the page
	*/ 
	if (ptr_low == 0x00FF) // This will simulate the bug
	{
		abs_addr = (fetch(ptr & 0xFF00) << 8 | fetch(ptr + 0));	
	}
	else
	{
		abs_addr = (fetch(ptr + 1) << 8) | fetch(ptr + 0);
	} 

	return 0;
}

// IND but with X offset
uint8_t emu6502::CPU::IZX()
{
	// Somewhere in the zero page...
	uint16_t zp_addr = fetch();

	// X offset
	uint16_t low = fetch((uint16_t)(zp_addr + (uint16_t)x) & 0x00FF);
	uint16_t high = fetch((uint16_t)(zp_addr + (uint16_t)x + 1) & 0x00FF);

	abs_addr = (high << 8) | low;

	return ((abs_addr & 0xFF00) != (high << 8)) ? 1 : 0;
}

uint8_t emu6502::CPU::IZY()
{
	// Somewhere in the zero page...
	uint16_t zp_addr = fetch();

	// X offset
	uint16_t low = fetch((uint16_t)(zp_addr + (uint16_t)y) & 0x00FF);
	uint16_t high = fetch((uint16_t)(zp_addr + (uint16_t)y + 1) & 0x00FF);

	abs_addr = (high << 8) | low;

	return ((abs_addr & 0xFF00) != (high << 8)) ? 1 : 0;
}

// Allow branching instructions to jump (at 128 signed bit limit)
uint8_t emu6502::CPU::REL()
{
	abs_addr = fetch();
	// Checks the most significant bit to see if it's signed or not
	if (rel_addr & 0x80)
	{
		rel_addr |= 0xFF00;
	}

	return 0;
}


// Instruction implementations


uint8_t emu6502::CPU::ADC()
{
	return 0;
}

/*
* Performs bitwise AND operation
* @param void
* @return 1 to specify this requires additional clock cycles
*/ 
uint8_t emu6502::CPU::AND()
{
	A = A & fetch();
	if (A == 0x00)
	{
		status |= (1 << Z);
	}
	if (A & 0x80)
	{
		status |= (1 << N);
	}

	return 1;
}

/*
* Branche if Carry Set 
* Address is pc added by relative addr if carry mode is ON
*/
uint8_t emu6502::CPU::BCS()
{
	if (status & (1 << C))
	{
		clock.cycle();
		abs_addr = pc + rel_addr;
		if ((abs_addr & 0xFF00) != (pc & 0xFF00))
		{
			clock.cycle();
		}
		// Set program counter to new counter
		pc = abs_addr;
	}
	return 0;
}

uint8_t emu6502::CPU::BCC()
{
	clock.cycle();
	abs_addr = pc + abs_addr;
	if ((abs_addr & 0xFF00) != (pc & 0xFF00))
	{
		clock.cycle();
	}
	pc = abs_addr;

	return 0;
}

uint8_t emu6502::CPU::BEQ()
{
	if (status & (1 << Z))
	{
		clock.cycle();
		abs_addr = pc + rel_addr;
		if ((abs_addr & 0xFF00) != (pc & 0xFF00))
		{
			clock.cycle();
		}
		pc = abs_addr;

	}
	return 0;
}

uint8_t emu6502::CPU::BMI()
{
	if (status & (1 << N))
	{
		clock.cycle();
		abs_addr = pc + rel_addr;
		if ((abs_addr & 0xFF00) != (pc & 0xFF00))
		{
			clock.cycle();
		}
		pc = abs_addr;
	}
	return 0;
}

uint8_t emu6502::CPU::BNE()
{
	if (!(status & (1 << Z)))
	{
		clock.cycle();
		abs_addr = pc + rel_addr;
		if ((abs_addr & 0xFF00) != (pc & 0xFF00))
		{
			clock.cycle();
		}
		pc = abs_addr;
	}
	return 0;
}

uint8_t emu6502::CPU::BPL()
{
	if (!(status & (1 << N)))
	{
		clock.cycle();
		abs_addr = pc + rel_addr;
		if ((abs_addr & 0xFF00) != (pc & 0xFF00))
		{
			clock.cycle();
		}
		pc = abs_addr;
	}
	return 0;
}

uint8_t emu6502::CPU::BVC()
{
	if (!(status & (1 << V)))
	{
		clock.cycle();
		abs_addr = pc + rel_addr;
		if ((abs_addr & 0xFF00) != (pc & 0xFF00))
		{
			clock.cycle();
		}
		pc = abs_addr;
	}
	return 0;
}

uint8_t emu6502::CPU::BVS()
{
	if (status & (1 << V))
	{
		clock.cycle();
		abs_addr = pc + rel_addr;
		if ((abs_addr & 0xFF00) != (pc & 0xFF00))
		{
			clock.cycle();
		}
		pc = abs_addr;
	}
	return 0;
}

uint8_t emu6502::CPU::CLC()
{
	status &= ~(1 << C);
	return 0;
}

uint8_t emu6502::CPU::CLD()
{
	status &= ~(1 << D);
	return 0;
}

uint8_t emu6502::CPU::CLI()
{
	status &= ~(1 << I);
	return 0;
}

uint8_t emu6502::CPU::CLV()
{
	status &= ~(1 << V);
	return 0;
}


uint8_t emu6502::CPU::LDA()
{
	uint8_t val = fetch();
	A = val;
	// Sets zero flag if A=0
	status |= (A == 0) ? (1 << Z) : 0;
	// Set negative flag if bit 7 of A is set
	status |= (A & 0b1000000) ? (1 << N) : 0;

	return 0;
}