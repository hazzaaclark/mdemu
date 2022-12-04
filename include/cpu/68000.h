#pragma once
#ifndef M68K_H
#define M68K_H

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef BIT_LOGIC
#define MASTER_BIT_LOGIC

#define FULL_MASK_INTERRUPT ((uint64_t) 0xFFFFFFFF) /* AN 8 BYTE INTERRUPT FOR HANDLING INSTRUCTIONS */
#define BIT(REG_X, REG_NTH_X) 
#define BIT_CHANGE

#define REGISTER_BIT_LOGIC

#define CARRY_BIT 0
#define OVERFLOW_BIT 1
#define ZERO_BIT 2
#define NEGATIVE_BIT 3
#define EXTENDED_BIT 4

#endif

/* REGISTER TABLE */
/* A REFACTOR TABLE TO INITIALISE THE STATUS OF EACH FLAG */
/* RELATIVE TO THEIR DESIGNATED BIT */

#ifndef REGISTERS
#define REGISTERS

#define CARRY(context) BIT(context->status, CARRY_BIT)
#define OVERFLOW(context) BIT(context->status, OVERFLOW_BIT)
#define ZERO(context) BIT(context->status, ZERO_BIT)
#define NEGATIVE(context) BIT(context->status, NEGATIVE_BIT)
#define EXTENDED(context) BIT(context->status, EXTENDED_BIT)

#endif

/* RE-FACTOR TABLE IN ORDER TO CHANGE THE BYTES ALLOCATED AT DIFFERENT REGISTERS */
/* CREATED IN ORDER TO DISCERN WHICH CONDITION CODE IS BEING TARGETTED */

#ifndef REGISTER_SETS
#define REGISTER_SETS

#define CARRY_SET(context, byte) context->status = BIT_CHANGE(context->status, CARRY_BIT, byte)
#define OVERFLOW_SET(context, byte) context->status = BIT_CHANGE(context->status, OVERFLOW_BIT, byte)

#endif 

#define ADDRESS_WIDTH 0xFFFFFFFF

#ifndef _INSTR
#define INSTR

struct OPCODE;
struct CPU;
struct DECODED_OPCODE;
struct MD;
extern struct OPCODE** OPCODE_TABLE{};

#endif 

/* CPU STRUCTURE */
/* JUST BASIC IMPLEMENTATION OF THE M68K's FUNCTIONS */

typedef struct
{
	MD* MD;
	uint32_t PROGRAM_COUNTER;
	uint16_t STATUS_REGISTER;
	uint32_t DATA_REG[8];
	uint32_t ADDRESS_REG[8];

	/* DEPEDANT ON THE TYPE OF OPERATION */
	/* THE CPU USES DIFFERENT STACK POINTERS VIA DEBUGGING */
	/* THIS CAN LEAD TO VARIOUS EXCEPTION HANDLES BEING USED TO DISCERN BETWEEN STATES */
	/*
	/* http://alanclements.org/68kusersupervisor.html
	/*
	/* FOR THE DEMONSTRATION OF THE MEGA DRIVE, ONLY THE USER STACK POIINTER WILL BE USED */

	/* AS WELL AS BEING DEMONSTRATED ON THE DOCUMENTATION FOR THE CPU */
	/* https://www.nxp.com/files-static/archives/doc/ref_manual/M68000PRM.pdf */

	unsigned int PENDING_INTERRUPT;
	uint32_t USER_STACK;
	uint64_t CYCLES;
	int32_t REMAINING_CYCLES;
	bool CYCLES_STOPPED;

	uint32_t INSTRUCTION_COUNT{};
	uint32_t INSTRUCTION_ADDRESS;
	uint16_t INSTRUCTION_REGISTER;
	uint32_t CURRENT_DECODED_INSTRUCTION;

} CPU;

/* ARBITRARY READ AND WRITE FUNCTIONS FOR THE 68000 */

struct IO
{
	static uint32_t CPU_READ(CPU*, size_t SIZE, uint32_t ADDRESS); /* PARENT READ FUNCTION TO DISCERN THE DATA TYPES AND ADDRESSING MODE */
	static uint8_t CPU_READ_BYTE(CPU*, uint32_t ADDRESS);
	static uint16_t CPU_READ_WORD(CPU*, uint32_t ADDRESS);
	static uint32_t CPU_READ_LONG(CPU*, uint32_t ADDRESS);

	static void CPU_WRITE(CPU*, size_t SIZE, uint32_t ADDRESS, uint32_t VALUE); /* PARENT WRITE FUNCTION TO DISCERN THE DATA TYPES AND ADDRESSING MODE */
	static void CPU_WRITE_BYTE(CPU*, uint32_t ADDRESS);
	static void CPU_WRITE_WORD(CPU*, uint32_t ADDRESS);
	static void CPU_WRITE_LONG(CPU*, uint32_t ADDRESS);
};

static uint16_t CPU_FETCH_ADDR(CPU* CPU);
static const uint32_t MAX_CYCLES_PER_COREFREQ = 7;
static void CPU_FREE(CPU*);
static void CPU_INIT(CPU*);
CPU* CREATE_CPU(struct MD*);

#endif
