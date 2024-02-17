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
#define         ADDRESS_ILLEGAL_ACCESS      (0x8000000 << 0xDFFFFF)

#if defined(USE_CPU)
#define USE_CPU
#else
#define USE_CPU

/* ARBITARY MACROS TO ALLOW FOR READING AND WRITING DATA */
/* THIS RETURNS A STATIC CAST OF A SPECIFIC DATA TYPE */

/* DATA AND ADDRESS ARE PARSED AS PER THE STATUS QUO OF ARCHITECURE */
/* PTR IS DISCERNED TO OUTPUT A BITWISE AND OPERAND */

#define     M68K_READ_8(DATA, ADDRESS)                  (DATA)[(uintptr_t)(ADDRESS) ^ 1] 
#define     M68K_WRITE_8(DATA, ADDRESS, PTR)            ((DATA)[(*(ADDRESS)) ^ 1] = (*(PTR)) & ADDRESS_WIDTH_8)

#define     M68K_READ_16(DATA, ADDRESS)                 (DATA)[(uintptr_t)(ADDRESS) ^ 2] 
#define     M68K_WRITE_16(DATA, ADDRESS, PTR)           ((DATA)[(*(ADDRESS)) ^ 2] = (*(PTR)) & ADDRESS_WIDTH_16)

#define     M68K_READ_32(DATA, ADDRESS)                 (DATA)[(uintptr_t)(ADDRESS) ^ 4] 
#define     M68K_WRITE_32(DATA, ADDRESS, PTR)           ((DATA)[(*(ADDRESS)) ^ 4] = (*(PTR)) & ADDRESS_WIDTH_32)

#define     M68K_RETURN_ADDRESS(ADDRESS)                ((ADDRESS) & 0xFFFFFFFFFF)                       

#define     Z80_READ(DATA, ADDRESS)                             (DATA)[(uintptr_t)(ADDRESS)]
#define     Z80_WRITE(DATA, ADDRESS, PTR)                       ((DATA)[(*(ADDRESS)) ^ 4] = (*(PTR)) & ADDRESS_WIDTH_32)

#define		CTRL_READ_BYTE(DATA, ADDRESS)				(DATA)[(uintptr_t)(ADDRESS) ^ 1]
#define		CTRL_WRITE_BYTE(DATA, ADDRESS, PTR)			((DATA)[(*(ADDRESS)) ^ 1] = (*(PTR)) & ADDRESS_WIDTH_8)

#define		CTRL_READ_WORD(DATA, ADDRESS)				(DATA)[(uintptr_t)(ADDRESS) ^ 2]
#define		CTRL_WRITE_WORD(DATA, ADDRESS, PTR)			((DATA)[(*(ADDRESS)) ^ 2] = (*(PTR)) & ADDRESS_WIDTH_16)

#ifdef M68K_CYCLE_CLOCK
#define M68K_CYCLE_CLOCK_SHIFT(VALUE) CPU_68K->INSTRUCTION_CYCLES += ((VALUE) * CPU_68K.CYCLE_RATE) >> M68K_CYCLE_CLOCK_SHIFT
#else
#define M68K_CYCLE_CLOCK_SHIFT(VALUE) CPU_68K->INSTRUCTION_CYCLES += ((VALUE))
#endif

typedef struct CPU_68K
{
    unsigned int PC;
    unsigned int* INSTRUCTION_CYCLES;
    unsigned int* CYCLE_RATE;
    unsigned int* INSTRUCTION_CYCLES_NULL;
    unsigned char* MEMORY_BASE;

    unsigned(*MEMORY_DATA);
    unsigned(*MEMORY_ADDRESS);
    unsigned(*MEMORY_POINTER);

	unsigned(*LOW_ADDR);
	unsigned(*HIGH_ADDR);
	void(*USER_DATA);
    
    union MEMORY_MAP
    {
        char* BASE;
        U8 MEMORY_READ_8;
        U16 MEMORY_READ_16;
        U8 MEMORY_WRITE_8;
        U16 MEMORY_WRITE_16;

    } MEMORY_MAP[256];

    /* PUTTING THE Z80 MEMORY BANK FUNCTIONALITY */
    /* IN HERE FOR NOW UNTIL MODULARISATION WOULD BETTER SUIT */

    union Z80_MEM
    {
        unsigned(*READ)(unsigned ADDRESS);
        unsigned(*WRITE)(unsigned ADDRESS);

        unsigned int CYCLES;

    } Z80_MEM[256];


	U16 STATUS_REGISTER;
	U32 INDEX_REGISTER;
    U32* REGISTER_BASE[16];
	U32* DATA_REGISTER[16];
	U32* ADDRESS_REGISTER[16];
    U32* PREVIOUS_PC;
    U32 STACK_POINTER;
	U32 USER_STACK;
	U32 ADDRESS_STACK_POINTER;
    U32* INSTRUCTION_REGISTER;
	U32 SOURCE_FUNCTION_COUNTER;
	U32 DEST_FUNCTION_COUNTER;
	U32 VBR;
	U32 CACHE_CONTROL;
	U32 CACHE_ADDRESS;


    char* INSTRUCTION_MODE;
    char* TRACE_FLAG;

    unsigned int* PREVIOUS_DATA;
    unsigned int* PREVIOUS_ADDRESS;
    unsigned int* ADDRESS_RT_CHECK;
    unsigned char* ERROR_ADDRESS;
    unsigned char* ERROR_WRITE_MODE;
    unsigned char* ERROR_PC;
    UNK* ERROR_JUMP;

    S32(*INTERRUPT_CALLBACK)(unsigned INTERRUPT);
    S32(*RESET_INTERRUPT)(void);
    S32(*CPU_FUNC_CALLBACK)(unsigned FUNCTION);

	U32 TMSS[4];
	unsigned int* INT_LEVEL;

} CPU_68K;

typedef enum CPU_68K_REGS
{
	M68K_REG_TYPE,
    M68K_REG_D0 = 0,    
    M68K_REG_D1 = 1,
    M68K_REG_D2 = 2,
    M68K_REG_D3 = 3,
    M68K_REG_D4 = 4,
    M68K_REG_D5 = 5,
    M68K_REG_D6 = 6,
    M68K_REG_D7 = 7,
    M68K_REG_A0 = 8,    
    M68K_REG_A1 = 9,
    M68K_REG_A2 = 10,
    M68K_REG_A3 = 11,
    M68K_REG_A4 = 12,
    M68K_REG_A5 = 13,
    M68K_REG_A6 = 14,
    M68K_REG_A7 = 15,
    M68K_REG_PC,    
    M68K_REG_SR,    
    M68K_REG_SP,    
    M68K_REG_USP,   
    M68K_REG_ISP,
    M68K_REG_IR, 
	M68K_REG_SFC,
	M68K_REG_VBR,
	M68K_REG_DFC,
	M68K_REG_CACR,
	M68K_REG_CAAR,

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

#define M68K_SAVE_INSTR(IDENTIFIER, VALUE) 					(*((char*)(IDENTIFIER)) = (char)((VALUE)))
#define	M68K_INT_LEVEL(IDENTIFIER) 							CPU_68K->INT_LEVEL += ((IDENTIFIER))
#define	M68K_CYC_INSTRUCTION								CPU_68K->INSTRUCTION_CYCLES

#ifdef 			USE_OPCODE_DEFS
#define 		USE_OPCODE_DEFS
#else
#define			OPERAND_NONE		                                                        0 << 0															 
#define			OPERAND_DATA_REGISTER														1 << 0
#define			OPERAND_ADDRESS_REGISTER													1 << 1
#define			OPERAND_ADDRESS_REGISTER_IND												1 << 2
#define			OPERAND_ADDRESS_REGISTER_IND_POSTINCREMENT									1 << 3
#define			OPERAND_ADDRESS_REGISTER_IND_PREDECREMENT									1 << 4
#define			OPERAND_ADDRESS_REGISTER_IND_W_DISP											1 << 5
#define			OPERAND_ADDRESS_REGISTER_IND_W_DISP_INDEX_REG								1 << 6
#define			OPERAND_ADDRESS_BASE														1 << 7
#define			OPERAND_ADDRESS_ABSOLUTE													1 << 8
#define			OPERAND_LITERAL																1 << 9
#define			OPERAND_PC_W_DISP															1 << 10
#define			OPERAND_PC_W_DISP_INDEX_REG													1 << 11
#define			OPERAND_STATUS_REGISTER_BASE												1 << 12
#define			OPERAND_CONDITION_CODE_REG_BASE												1 << 13
#define			OPERAND_USER_STACK_POINTER_REG_BASE											1 << 14
#define			OPERAND_REGISTER_LIST	

/* THESE MACROS REFER TO THE VARIOUS WAYS BY WHICH OPCODES ENCOMPASSES */
/* MULTIPLE OPERAND MODES OR JUST ONE MODE */

/* BOTH GOVERN THE SAME PROPERTIES OF INCLUDING DIFFERENT ADDRESSES EVOKING THEIR */
/* LENGTH HOWEVER, THEY ONLY ENCOMPASS ONE INSTRUCTION */

/* SUCH AN EXAMPLE WOULD BE COMPARISON OPERANDS WHICH ENCOMPASSES TWO OPERAND MODES */

#define			OPCODE_ADDRESS_OFFSET(VALUE)			((VALUE) << 16)
#define			OPCODE_ADRESSS_OFFSETS(VALUE, OFFSET)	(((VALUE) << 16) + OFFSET)

#endif

typedef struct OPCODE
{
	U16* PATTERN;
	size_t* OPCODE_SIZE;

	union 
	{
		U32 MAIN_REGISTER;
		U32 INDEX_REGISTER;
		size_t* OPERAND_SIZE;
		char LITERAL;
		bool* IR_TO_AR;

	} OPERAND;
	
} OPCODE;

typedef enum CONDITION
{
    CONDITION_TRUE,
	CONDITION_FALSE,
	CONDITION_HIGHER,
	CONDITION_LOWER_OR_SAME,
	CONDITION_CARRY_CLEAR,
	CONDITION_CARRY_SET,
	CONDITION_NOT_EQUAL,
	CONDITION_EQUAL,
	CONDITION_OVERFLOW_CLEAR,
	CONDITION_OVERFLOW_SET,
	CONDITION_PLUS,
	CONDITION_MINUS,
	CONDITION_GREATER_OR_EQUAL,
	CONDITION_LESS_THAN,
	CONDITION_GREATER_THAN,
	CONDITION_LESS_OR_EQUAL,

} CONDITION;

typedef enum OPCODE_TYPE
{
    OPCODE_ORI_TO_CCR,
	OPCODE_ORI_TO_SR,
	OPCODE_ORI,
	OPCODE_ANDI_TO_CCR,
	OPCODE_ANDI_TO_SR,
	OPCODE_ANDI,
	OPCODE_SUBI,
	OPCODE_ADDI,
	OPCODE_EORI_TO_CCR,
	OPCODE_EORI_TO_SR,
	OPCODE_EORI,
	OPCODE_CMPI,
	OPCODE_BTST_STATIC,
	OPCODE_BCHG_STATIC,
	OPCODE_BCLR_STATIC,
	OPCODE_BSET_STATIC,
	OPCODE_BTST_DYNAMIC,
	OPCODE_BCHG_DYNAMIC,
	OPCODE_BCLR_DYNAMIC,
	OPCODE_BSET_DYNAMIC,
	OPCODE_MOVEP_TO_REG,
	OPCODE_MOVEP_FROM_REG,
	OPCODE_MOVEA,
	OPCODE_MOVE,
	OPCODE_MOVE_FROM_SR,
	OPCODE_MOVE_TO_CCR,
	OPCODE_MOVE_TO_SR,
	OPCODE_NEGX,
	OPCODE_CLR,
	OPCODE_NEG,
	OPCODE_NOT,
	OPCODE_EXT,
	OPCODE_NBCD,
	OPCODE_SWAP,
	OPCODE_PEA,
	OPCODE_ILLEGAL,
	OPCODE_TAS,
	OPCODE_TST,
	OPCODE_TRAP,
	OPCODE_LINK,
	OPCODE_UNLK,
	OPCODE_MOVE_TO_USP,
	OPCODE_MOVE_FROM_USP,
	OPCODE_RESET,
	OPCODE_NOP,
	OPCODE_STOP,
	OPCODE_RTE,
	OPCODE_RTS,
	OPCODE_TRAPV,
	OPCODE_RTR,
	OPCODE_JSR,
	OPCODE_JMP,
	OPCODE_MOVEM_TO_REGS,
	OPCODE_MOVEM_FROM_REGS,
	OPCODE_LEA,
	OPCODE_CHK,
	OPCODE_ADDQ,
	OPCODE_SUBQ,
	OPCODE_Scc,
	OPCODE_DBcc,
	OPCODE_BRA,
	OPCODE_BSR,
	OPCODE_BCC,
	OPCODE_MOVEQ,
	OPCODE_DIVU,
	OPCODE_DIVS,
	OPCODE_SBCD_DATA_REGS,
	OPCODE_SBCD_ADDRESS_REGS,
	OPCODE_OR_TO_REG,
	OPCODE_OR_FROM_REG,
	OPCODE_SUB_TO_REG,
	OPCODE_SUB_FROM_REG,
	OPCODE_SUBX_DATA_REGS,
	OPCODE_SUBX_ADDRESS_REGS,
	OPCODE_SUBA,
	OPCODE_EOR,
	OPCODE_CMPM,
	OPCODE_CMP,
	OPCODE_CMPA,
	OPCODE_MULU,
	OPCODE_MULS,
	OPCODE_ABCD,
	OPCODE_EXG,
	OPCODE_AND_TO_REG,
	OPCODE_AND_FROM_REG,
	OPCODE_ADD_TO_REG,
	OPCODE_ADD_FROM_REG,
	OPCODE_ADDX_DATA_REGS,
	OPCODE_ADDX_ADDRESS_REGS,
	OPCODE_ADDA,
	OPCODE_ASL_STATIC,
	OPCODE_ASR_STATIC,
	OPCODE_LSL_STATIC,
	OPCODE_LSR_STATIC,
	OPCODE_ROXL_STATIC,
	OPCODE_ROXR_STATIC,
	OPCODE_ROL_STATIC,
	OPCODE_ROR_STATIC,
	OPCODE_ASL_DYNAMIC,
	OPCODE_ASR_DYNAMIC,
	OPCODE_LSL_DYNAMIC,
	OPCODE_LSR_DYNAMIC,
	OPCODE_ROXL_DYNAMIC,
	OPCODE_ROXR_DYNAMIC,
	OPCODE_ROL_DYNAMIC,
	OPCODE_ROR_DYNAMIC,
	OPCODE_ASL_SINGLE,
	OPCODE_ASR_SINGLE,
	OPCODE_LSL_SINGLE,
	OPCODE_LSR_SINGLE,
	OPCODE_ROXL_SINGLE,
	OPCODE_ROXR_SINGLE,
	OPCODE_ROL_SINGLE,
	OPCODE_ROR_SINGLE,

} OPCODE_TYPE;

void INITIALISE_68K_CYCLES();
U32 CPU_ACCESS_REGISTERS(CPU_68K_REGS REGISTER, unsigned VALUE);

void M68K_INIT(void);
void M68K_INIT_OPCODE(void);
void M68K_RUN(void);
U16(*M68K_FETCH_INSTR(struct CPU_68K* CPU_68K));
void M68K_SET_INT_CALLBACK(int* CALLBACK, int* LEVEL);
void M68K_SET_FUNC_CALLBACK(int* CALLBACK, int* LEVEL);

int M68K_CALLBACK_INT(int* CALLBACK, int* LEVEL);
int M68K_FUNC_CALLBACK(int* CALLBACK, int* LEVEL);

void M68K_SET_MOVE_IRQ_INT();
void M68K_CHECK_IRQ(void);
void M68K_PULSE_RESET(void);

typedef OPCODE* GENERATE_OPCODE(const OPCODE* OPCODE, UNK* MAP);

#endif
#endif
