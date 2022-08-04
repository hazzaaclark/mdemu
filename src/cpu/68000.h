#pragma once
#include <vector>
#include <map>
#include <string>
#include <stdio.h>

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

	/** REGISTERS **/

	uint32_t DATA_REG[8];
	uint32_t ADDRESS_REG[8];
	uint32_t PROGRAM_COUNTER;
	uint32_t STATUS_REGISTER;
	uint8_t INDEX_REGISTER;
	uint8_t NEGATIVE_REG;
	uint8_t ZERO_REG;
	uint8_t OVERFLOW_REG;
	uint8_t CARRY_OP_REG;

	/** POINTERS **/

	int CURRENT_STACK_POINTER;
	uint32_t STACK_POINTER[3];

	void BUS_INIT();
	void RESET();
	void INTERRUPT();
	void NM_INTERRUPT();
	void TIMER();
	bool COMPLETE();

	enum CPUFLAGS 
	{
		CONDITION_OP,
	    CONDITION_X,
	    CONDITION_N,
	    CONDITION_V,
	    CONDITION_C,
	    CONDITION_Z,
	};

private:
	uint16_t ACCESS_FLAG(CPUFLAGS CPUF);
	uint16_t ABS_ADDR;
	uint8_t OPCODE;
	static void SET_FLAG(CPUFLAGS CPUF, bool SR);
};
