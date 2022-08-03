#pragma once
#include <vector>
#include <map>
#include <string>

#define CPU_BYTE 0
#define CPU_WORD 1
#define CPU_LONG 2
#define CPU_SINGLE 3
#define CPU_DOUBLE   4
#define CPU_EXTENDED 5
#define CPU_PACKED   6
#define CPU_UNSIZED  7

struct CPU_STATE
{
	/** REGISTERS **/

	uint32_t DATA_REG[8];
	uint32_t ADDRESS_REG[8];
	uint32_t PROGRAM_COUNTER;
	uint32_t STATUS_REGISTER;

	/** POINTERS **/

	int CURRENT_STACK_POINTER;
	uint32_t STACK_POINTER[3];

	/** FLAGS **/

	uint32_t CONDITION_OP;
	uint32_t CONDITION_X;
	uint32_t CONDITION_N;
	uint32_t CONDITION_V;
	uint32_t CONDITION_C;
	uint32_t CONDITION_Z;

};

struct CPU_REGISTERS
{
	uint32_t ADDRESS_REGISTER;
	uint32_t PROGRAM_COUNTER;
	uint8_t INDEX_REGISTER;
	uint8_t NEGATIVE_REG;
	uint8_t ZERO_REG;
	uint8_t OVERFLOW_REG;
	uint8_t CARRY_OP_REG;

};

struct CPU_FUNCTIONS
{
	void BUS_INIT();
	void RESET();
	void INTERRUPT();
	void NM_INTERRUPT();
	void TIMER();
	bool COMPLETE();

};

class
{
public:
	struct MEM_MAP
	{
		std::map <uint16_t, std::string> DISASM(uint16_t DIS_START, uint16_t DIS_STOP);
	};
};
