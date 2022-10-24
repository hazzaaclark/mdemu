#pragma once
#ifndef M68K_H
#define M68K_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef BIT_LOGIC
#define MASTER_BIT_LOGIC

#define FULL_MASK_INTERRUPT ((uint64_t) 0xFFFFFFFF) /* AN 8 BYTE */
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

#endif
