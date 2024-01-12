/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONALITY OF THE CPU */
/* USING DOCUMENTATION, THE AMBITION IS TO FASHION THE BASE ARCHITECURE OF THE CONSOLES' */
/* FUNCTIONS WHICH WILL CORRESPOND WITH THE ACTIONS CARRIED OUT BY THE RESPECTIVE CPP FILE */

#ifndef M68K
#define M68K

/* SYSTEM INCLUDES */

#include <assert.h>
#include <malloc.h>
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

#define         CARRY() BIT(REGS[0], CARRY_BIT)
#define         OVERFLOW() BIT(REGS[1], OVERFLOW_BIT)
#define         ZERO() BIT(REGS[2], ZERO_BIT)
#define         NEGATIVE() BIT(REGS[3], NEGATIVE_BIT)
#define         EXTENDED() BIT(REGS[4], EXTENDED_BIT)

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

#define     M68K_RETURN_ADDRESS(ADDRESS)            ((ADDRESS) & 0xFFFFFFFFFF)                       

typedef struct CPU_68K
{
    unsigned int PC;
    unsigned int* INSTRUCTION_CYCLES;
    unsigned int* INSTRUCTION_CYCLES_NULL;
    unsigned char* MEMORY_BASE;
    unsigned char* MEMORY_MAP[256];

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

    S32(*INTERRUPT_CALLBACK)(unsigned INTERRUPT);
    S32(*RESET_INTERRUPT)(void);
    S32(*CPU_FUNC_CALLBACK)(unsigned FUNCTION);

} CPU_68K;

typedef enum CPU_68K_REGS
{
    M68K_REG_D0,    
    M68K_REG_D1,
    M68K_REG_D2,
    M68K_REG_D3,
    M68K_REG_D4,
    M68K_REG_D5,
    M68K_REG_D6,
    M68K_REG_D7,
    M68K_REG_A0,    
    M68K_REG_A1,
    M68K_REG_A2,
    M68K_REG_A3,
    M68K_REG_A4,
    M68K_REG_A5,
    M68K_REG_A6,
    M68K_REG_A7,
    M68K_REG_PC,    
    M68K_REG_SR,    
    M68K_REG_SP,    
    M68K_REG_USP,   
    M68K_REG_ISP, 

} CPU_68K_REGS;

typedef enum CPU_68K_FLAGS 
{
    FLAG_S,
    FLAG_X,
    FLAG_Z,
    FLAG_N,
    FLAG_C,
    FLAG_V,
    FLAG_T1,

} CPU_68K_FLAGS;

#ifndef BUILD_68K_TABLES
void(*INITIALISE_68K_CYCLES)(char* CPU_68K_CYCLES[0x10000]);
#endif

STATIC
unsigned CPU_ACCESS_REGISTERS(CPU_68K_REGS REGISTER,
                              CPU_68K_FLAGS FLAGS, unsigned VALUE);

void M68K_INIT(void);
void M68K_INIT_OPCODE(unsigned CALLBACK(void));
void M68K_SET_INT_CALLBACK(unsigned CALLBACK(void));
void M68K_SET_FUNC_CALLBACK(unsigned CALLBACK(void));

#endif
#endif
