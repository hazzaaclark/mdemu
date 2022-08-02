#pragma once
#include <vector>
#include <map>
#include <string>

#define CPU_MAIN_PARENT(obj);
#define CPU_MAIN_CLASS;
#define CPU_MAIN_GET_CLASS;

#define CPU_BYTE 0
#define CPU_WORD 1
#define CPU_LONG 2
#define CPU_SINGLE 3
#define CPU_DOUBLE   4
#define CPU_EXTENDED 5
#define CPU_PACKED   6
#define CPU_UNSIZED  7

typedef struct CPU_MAIN
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

} MAIN;

struct CPU_INIT
{
	MAIN MASTER_INIT;
	CPU_MAIN env;
	typedef struct CPUCLASS cc;
};


typedef struct CPU_REGISTERS
{
	uint32_t ADDRESS_REGISTER;
	uint32_t PROGRAM_COUNTER;
	uint8_t INDEX_REGISTER;
	uint8_t NEGATIVE_REG;
	uint8_t ZERO_REG;
	uint8_t OVERFLOW_REG;
	uint8_t CARRY_OP_REG;

} REG;

typedef struct CPU_FUNCTIONS
{
	virtual void BUS_INIT();
	virtual void RESET();
	virtual void INTERRUPT();
	virtual void TIMER();
	bool COMPLETE();

} FUNC;
