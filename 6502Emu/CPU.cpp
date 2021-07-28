#include "CPU.h"
#include <iostream>
#include <fstream>

emu6502::CPU::CPU()
{
	// Make some kind of CSV thing to store all this shit.
	instructions =
	{

	};
	reset();

	using a = CPU;
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




// Opcode Implementations


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