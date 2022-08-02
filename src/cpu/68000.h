#pragma once
#include <vector>
#include <map>
#include <string>
#ifndef STDLIB
#include <stdio.h>
#endif 

class CPU_HEADER
{
public:
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

	typedef struct CPU_FUNC
	{
		virtual void RESET();
		virtual void INTERRUPT();
		virtual void TIMER();

	} FUNCTIONS;
};
