#pragma once
#include <vector>
#include <map>
#include <string>
#include <stdio.h>

#ifndef M68K_H
#define M68K_H

#define CPU_BYTE 0
#define CPU_WORD 1
#define CPU_LONG 2
#define CPU_SINGLE 3
#define CPU_DOUBLE   4
#define CPU_EXTENDED 5
#define CPU_PACKED   6
#define CPU_UNSIZED  7

class M68K
{
public:
	M68K();
	~M68K();

public:
	uint32_t DATA_REG[8];
	uint32_t ADDRESS_REG[8];
	uint32_t PROGRAM_COUNTER;
	uint32_t STATUS_REG;
	uint8_t INDEX_REGISTER;
	uint8_t NEGATIVE_REG;
	uint8_t ZERO_REG;
	uint8_t OVERFLOW_REG;
	uint8_t CARRY_OP_REG;

	int CURRENT_STACK_POINTER;
	uint32_t STACK_POINTER[3];

	static void BUS_INIT();
	static void CPU_RESET();
	static void REG_INTERRUPT();
	static void NON_MASKABLE_RI();
	static void TIMER();
	bool CYCLECOMPLETE();

	struct M68KFLAGS
	{
		const char C = (1 << 0);
		const char X = (1 << 1);
		const char Z = (1 << 2);
		const char V = (1 << 3);
		const char N = (1 << 4);
	};	

private:
	struct OPCODE_INSTRUCTION
	{
		std::string OPCODE;
		uint32_t(M68K::* OPERATE)(void*) = nullptr;
		uint32_t(M68K::* ADDR_MODE)(void*) = nullptr;
	};

	std::vector<OPCODE_INSTRUCTION> OPCODE_LOOKUP;

	static void SET_FLAG(M68KFLAGS FLAGS, bool STATUS_);
	uint32_t CPU_READ(uint32_t ADDR, uint32_t DATA);
	uint16_t GETFLAGS(M68KFLAGS FLAGS);
	uint32_t FETCH_LOCATION();

private:

	/** OPCODES **/
	uint32_t ADDA(); uint32_t ADDA_W(); uint32_t ADDA_L();
	uint32_t ADDI(); uint32_t ADDI_B(); uint32_t ADDI_W();
	uint32_t ADDI_L(); uint32_t ADDQ(); uint32_t ADDQ_B();

#endif
};
