#pragma once

#ifndef _INSTRUCTION_
#define _INSTRUCTION_
#endif

#include <stdbool.h>
#include <stdint.h>
#include "68000.h"

#define INSTRUCTION_FUNCTION typedef uint8_t
#define INSTRUCTION_NAME typedef char
#define OPCODE typedef uint16_t

struct CONDITION;
struct INSTRUCTION;
struct CPU;
struct OPERAND;

typedef struct
{
	INSTRUCTION_NAME NAME;
	INSTRUCTION_FUNCTION FUNCTION;
	INSTRUCTION_SIZE SIZE;
	OPCODE OP;
	
} INSTRUCTION;

