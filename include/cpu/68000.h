/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONALITY OF THE CPU */
/* USING DOCUMENTATION, THE AMBITION IS TO FASHION THE BASE ARCHITECURE OF THE CONSOLES' */
/* FUNCTIONS WHICH WILL CORRESPOND WITH THE ACTIONS CARRIED OUT BY THE RESPECTIVE CPP FILE */

#ifndef M68K
#define M68K

/* SYSTEM INCLUDES */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* NESTED INCLUDES */

#include "common.h"
#include "instruction.h"

#ifdef DEBUG
#define DEBUG_LOG(...) (__VA_ARGS__)
#else
#define DEBUG_LOG(MESSAGE, SIZE) printf("%s %p\n", MESSAGE, (void*)SIZE)
#endif

#define MODE_MASK(MODE) (1 << MODE)

#define CARRY_BIT 0
#define OVERFLOW_BIT 1
#define ZERO_BIT 2
#define NEGATIVE_BIT 3
#define EXTENDED_BIT 4

/* AS OF THIS CODE REFACTOR, I AM NOT SURE IF I WILL NEED */
/* THESE STATIC TYPES */

/* I WILL KEEP THEM HERE JUST IN CASE */

#define CARRY() BIT(REGS[0], CARRY_BIT)
#define OVERFLOW() BIT(REGS[1], OVERFLOW_BIT)
#define ZERO() BIT(REGS[2], ZERO_BIT)
#define NEGATIVE() BIT(REGS[3], NEGATIVE_BIT)
#define EXTENDED() BIT(REGS[4], EXTENDED_BIT)

#define         ADDRESS_WIDTH_8             0xFF
#define         ADDRESS_WIDTH_16            0xFFFF
#define         ADDRESS_WIDTH_32            0xFFFFFFFF
#define         SYMBOL_WIDTH                ''

#if defined(USE_CPU)
#define USE_CPU
#else
#define USE_CPU

/* ARBITARY MACROS TO ALLOW FOR READING AND WRITING DATA */
/* THIS RETURNS A STATIC CAST OF A SPECIFIC DATA TYPE */

/* DATA AND ADDRESS ARE PARSED AS PER THE STATUS QUO OF ARCHITECURE */
/* PTR IS DISCERNED TO OUTPUT A BITWISE AND OPERAND */

#define     M68K_READ_8(DATA, ADDRESS)              (DATA)[(ADDRESS) ^ 1] 
#define     M68K_WRITE_8(DATA, ADDRESS, PTR)        (DATA)[(ADDRESS) ^ 1] = (PTR & ADDRESS_WIDTH_8)

#define     M68K_READ_16(DATA, ADDRESS)             (((BASE)[ADDRESS]<<8) | (DATA)[(ADDRESS) +1])
#define     M68K_WRITE_16(DATA, ADDRESS, PTR)       *(U16*)((DATA + (ADDRESS)) = PTR & ADDRESS_WIDTH_16)

#define     M68K_READ_32(DATA, ADDRESS)             (((BASE)[ADDRESS + 1] <<24 | (((BASE)[ADDRESS + 3] >> 8))))
#define     M68K_WRITE_32(DATA, ADDRESS, PTR)       *(U32*)((DATA + (ADDRESS)) = PTR & ADDRESS_WIDTH_32)

typedef struct CPU_68K
{
    unsigned int* PC;
    unsigned int* INSTRUCTION_CYCLES;
    unsigned int* INSTRUCTION_CYCLES_NULL;

    U32* REGISTER_BASE[16];
    U32* PREVIOUS_PC;
    U32* STACK_POINTER[5];
    U32* INSTRUCTION_REGISTER;

    char* INSTRUCTION_MODE;
    char* TRACE_FLAG;

    unsigned int* PREVIOUS_DATA;
    unsigned int* PREVIOUS_ADDRESS;
    unsigned char* ERROR_ADDRESS;
    unsigned char* ERROR_WRITE_MODE;
    unsigned char* ERROR_PC;
    UNK* ERROR_JUMP;

    union MEMORY_MAP
    {
        char* MEMORY_BASE;
        void(*WRITE_8_BIT)(S32 ADDRESS, S32 DATA);
        void(*READ_8_BIT)(S32 ADDRESS);
        void(*WRITE_16_BIT)(S32 ADDRESS, S32 DATA);
        void(*READ_16_BIT)(S32 ADDRESS);

    } MEMORY_MAP[256];

    S32(*INTERRUPT_CALLBACK)(unsigned INTERRUPT);
    S32(*RESET_INTERRUPT)(void);
    S32(*CPU_FUNC_CALLBACK)(unsigned FUNCTION);

} CPU_68K;

#endif

#endif
