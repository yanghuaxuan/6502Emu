/*
* http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
*/

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "RAM.h"

namespace emu6502
{

    class CPU
    {
    public:
        CPU(RAM *_ram);
        ~CPU();

        void reset();
        void execute();

        uint8_t getx();
        uint8_t gety();
        uint8_t getA();
        uint8_t getS();
        uint16_t getP();

    private:
        RAM *ram = nullptr;
        // Program counter
        uint16_t pc;
        // Our accumulator for arithmetic and logical opreations
        uint8_t A;
        // Registers x and y
        uint8_t x, y;
        // Stack pointer
        uint8_t stkp;

        // This is to store values modified by addressing modes
        uint8_t fetched;
        uint16_t abs_addr; // Store absolute (full) memory address
        uint16_t rel_addr; // Store branch instructions to jump
        uint8_t  ir; // Store current instruction

        struct instruction
        {
            std::string name;
            uint8_t (CPU::* op)();
            uint8_t (CPU::* mode)();
            int cycles = 0;
        };
        std::vector<instruction> instructions;

        // Fetch an instruction from program counter or a specified address
        uint8_t fetch();

        // Interrupts
        void irq();
        void nmi();

        // 6502 clock emulation
        struct Clock
        {
            int  clockCycles = 0; // Counts how many cycles the instruction has remaining
            int clockCounter = 0; // A global accumulation of the number of clocks
            /*
            * Go through one cycle
            * @param void
            * @return void
            */
            void cycle()
            {
                clockCycles--;
                clockCounter++;
            }
            void addCycles(uint8_t cycles)
            {
                clockCycles += cycles;
            }
        } clock;


        uint8_t status;
        enum flags { C, Z, I, D, B, U, V, N };

        // Addressing Modes
        uint8_t IMP();	uint8_t IMM();	uint8_t ZP0();	uint8_t ZPX();
        uint8_t ZPY();	uint8_t REL();	uint8_t ABS();	uint8_t ABX();
        uint8_t ABY();	uint8_t IND();	uint8_t IZX();	uint8_t IZY();

        // Opcode function declaration
        uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
        uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
        uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
        uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
        uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
        uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
        uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
        uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
        uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
        uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
        uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
        uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
        uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
        uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();
        uint8_t XXX();
    };
}
