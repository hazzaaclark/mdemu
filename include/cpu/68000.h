#pragma once
#ifndef M68K_H
#define M68K_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

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

#define ADDRESS_WIDTH 0xFFFFFF

struct OPCODE;
struct CPU;
struct DECODED_OPCODE;
struct MD;
extern struct OPCODE** OPCODE_TABLE{};

/* CPU STRUCTURE */
/* JUST BASIC IMPLEMENTATION OF THE M68K's FUNCTIONS */

typedef struct
{
	struct MD* MD;
	const uint32_t PROGRAM_COUNTER;
	const uint16_t STATUS_REGISTER;
	const uint32_t DATA_REG[8];
	const uint32_t ADDRESS_REG[8];

	/* DEPEDANT ON THE TYPE OF OPERATION */
	/* THE CPU USES DIFFERENT STACK POINTERS VIA DEBUGGING */
	/* THIS CAN LEAD TO VARIOUS EXCEPTION HANDLES BEING USED TO DISCERN BETWEEN STATES */
	/* FOR THE DEMONSTRATION OF THE MEGA DRIVE, ONLY THE USER STACK POIINTER WILL BE USED */

	const uint32_t USER_STACK;

} CPU;

#endif
