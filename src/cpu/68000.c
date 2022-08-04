#pragma once
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <stdbool.h>

struct REGISTERS
{
	uint32_t DATA_REG[8];
	uint32_t ADDRESS_REG[8];
	uint32_t PROGRAM_COUNTER;
	uint32_t STATUS_REGISTER;
	uint8_t INDEX_REGISTER;
	uint8_t NEGATIVE_REG;
	uint8_t ZERO_REG;
	uint8_t OVERFLOW_REG;
	uint8_t CARRY_OP_REG;
};

struct POINTERS
{

	int CURRENT_STACK_POINTER;
	uint32_t STACK_POINTER[3];

};

static void BUS_INIT();
static void CPU_RESET();
static void REG_INTERRUPT();
static void NON_MASKABLE_RI();
static void TIMER();
bool CYCLECOMPLETE();
