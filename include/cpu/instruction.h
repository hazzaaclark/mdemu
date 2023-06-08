/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE FUNCTIONALITY OF THE INSTRUCTION SET IN ACCORDANCE */
/* WITH THE INSTRUCTIONS PERTAINING TO THE ARCHITECTURE OF THE CPU */

#ifndef INSTRUCTION_SET
#define INSTRUCTION_SET

/* NESTED INCLUDES */

#include "68000.h"
#include "common.h"

/* SYSTEM INCLUDES */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#if defined(USE_M68K_MEM)
#define USE_M68K_MEM
#else
#define USE_M68K_MEM

#define BIT (VALUE, INDEX)            ((VALUE) >> (INDEX))
#define BITS (VALUE, INDEX, RESULT)   ((VALUE) >> (INDEX)) & ((1 << (RESULT)) - 1)) 
#define BYTE_LO 0
#define BYTE_HI 0

#endif

#if defined(USE_ISA)
#define USE_ISA
#else
#define USE_ISA

/* CREATES A STATIC OBJECT FROM WHICH A DESIGNATED OPCODE */
/* CAN BE CONSTRUCTED FROM */

/* USING A STRUCTURE METHOD TO CONCATENATE THE STRUCTURE */
/* WITH THE OPCODE VALUE PROVIDED */

/* THE FOLLOWING ALLOWS FOR SEAMLESS INTEGRATION OF OPCODE */
/* WRITING AND ANY OTHER STATIC OBJECT DECLARATIONS */

#define INSTRUCTION_FUNCTION(VALUE) \
static INSTRUCTION* TYPE ## VALUE(U16 OPCODE);

#define INSTRUCTION_MAKE(VALUE) \
static INSTRUCTION* TYPE ## VALUE(char* NAME);

#define INSTRUCTION_GENERATE(VALUE) \
static INSTRUCTION* TYPE ## VALUE(U16 OPCODE);

#define INSTRUCTION_EXEC(VALUE) \
static INSTRUCTION* TYPE ## VALUE(U8 INSTR, CPU* CPU);

#define INSTRUCTION_NON_IMPL(VALUE) \
static INSTRUCTION* TYPE ## VALUE(CPU* CPU);

typedef struct INSTRUCTION
{
	static char* NAME;
	static U16* OPCODE;
	static U8* CYCLES;
};

typedef struct CONDITION;

#define CONDITION_FUNCTION(VALUE) \
static CONDITION* FUNCTION ## VALUE(bool CONDITION_MET);

#define CONDITION_GET(VALUE) \
static CONDITION* GET_SET ## VALUE(U32 PATTERN);

#define CONDITION_MNEMONICS(VALUE) \
static CONDITION* MNEMOMIC ## VALUE(char* TYPE);

#endif

#if defined(USE_ISA_MODE)
#define USE_ISA_MODE
#else
#define USE_ISA_MODE

#define ISA_MODE(VALUE) \
static MODE_PATTERN* MODE ## VALUE(U32 MODE);

#define MODE_DATA          (ISA_MODE(DATA_REG))
#define MODE_ADDR          (ISA_MODE(ADDRESS_REG))
#define MODE_ADDR_INDEX    (ISA_MODE(ADDRESS_INDEX))
#define MODE_ADDR_OFFSET   (ISA_MODE(ADDRESS_OFFSET))
#define MODE_PC            (ISA_MODE(PROGRAM_COUNTER))
#define MODE_IMM           (ISA_MODE(IMMEDIATE_ACCESS))
#define MODE_ALL           (MODE_DATA | MODE_ADDR | MODE_ADDR_INDEX | MODE_ADDR_OFFSET | MODE_PC | MODE_IMM)
#define MODE_NONE          0


typedef struct MODE_PATTERN
{
	INSTRUCTION_GENERATE();
	static char* MODE_BITS;
	static U16* LEGAL_MODE;
	static MODE_PATTERN* PATTERN[];
};

#endif

extern "C"
{
	extern void MEM_INIT();
	extern U32 LOAD_BIN();
}

#endif
