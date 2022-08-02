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

typedef struct CPU_STATE
{
	uint32_t DATA_REG;
	uint32_t ADDRESS_REG;
	uint32_t PROGRAM_COUNTER;

} STATE;

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
	virtual void RESET();
	virtual void INTERRUPT();
	virtual void TIMER();

} FUNC;

