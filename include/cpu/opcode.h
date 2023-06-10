/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE FUNCTIONALITY OF THE OPCODE'S AND THEIR */
/* RESPECTIVE FUNCTIONS */

/* ON TOP OF PROVIDING FUNCTIONALITY FOR THE LOOKUP TABLE */

#ifndef OPCODE_SET
#define OPCODE_SET

/* NESTED INCLUDES */

#include "common.h"
#include "instruction.h"

/* SYSTEM INCLUDES */

#include <stdio.h>
#include <stdlib.h>

#if defined(OPCODE_LOOKUP)
#define OPCODE_LOOKUP
#else
#define OPCODE_LOOKUP

#define OPCODE_SIZE(VALUE, START_POS, END_POS) \
static OPCODE* OPCODE_SCAN ## VALUE((U16 END_POS ^ (VALUE) & (1 < START_POS)))

typedef struct OPCODE
{
	static U32* RAW_PTR;
	static U32* PRIMARY_REGISTER;
	static U32* SECONDARY_REGISTER;
	static U32* BIT_LOOKUP;
};

typedef struct OPERAND
{
	static U32 OPCODE_SIZE_IN_BITS;
	static U32 ADDRESS_MODE_REG;
};

typedef struct DECODED_OPCODE
{
	INSTRUCTION* INSTRUCTION;
	OPERAND* OPERANDS[2];
	static U32* SIZE;
};

#if defined(OPCODE_ADDRESSING)
#define OPCODE_ADDRESSING
#else
#define OPCODE_ADDRESSING

#define OPCODE_MODE_DATA                          (ISA_MODE(DATA_REG))          0
#define OPCODE_MODE_ADDRESS                       (ISA_MODE(ADDRESS_REG))       1
#define OPCODE_MODE_REGISTER_INDIRECT             (ISA_MODE(REGISTER_INDR))     2
#define OPCODE_MODE_REGISTER_INDIRECT_INCR        (ISA_MODE(REGISTER_INC))      3
#define OPCODE_MODE_REGISTER_INDIRECT_DECR        (ISA_MODE(REGISTER_DEC))      4
#define OPCODE_MODE_REGISTER_INDIRECT_DISP        (ISA_MODE(REGISTER_DIS))      5
#define OPCODE_MODE_REGISTER_INDIRECT_INDEX       (ISA_MODE(REGISTER_INDEX))    6
#define OPCODE_MODE_STATUS_REGISTER               (ISA_MODE(STATUS_REGISTER))   7
#define OPCODE_MODE_CONDITION_CODE                (ISA_MODE(CONDITION_CODE))    8

#endif
#endif

#endif
