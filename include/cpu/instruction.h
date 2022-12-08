#pragma once

#ifndef _INSTRUCTION_
#define _INSTRUCTION_
#else
#endif

#include <stdbool.h>
#include <stdint.h>
#include "cpu.h"

typedef struct
{
	struct CONDITION;
	struct INSTRUCTION;
	struct CPU;
	struct OPERAND;

} INSTR_SET;

typedef uint8_t INSTR_FUNCTION(struct INSTRUCTION*, struct CPU*);

typedef struct
{

} INSTRUCTION;

