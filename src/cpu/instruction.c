/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE FUNCTIONALITY OF THE INSTRUCTION SET IN ACCORDANCE */
/* WITH THE INSTRUCTIONS PERTAINING TO THE ARCHITECTURE OF THE CPU */

/* NESTED INCLUDES */

#include "instruction.h"
#include "opcode.h"

#ifdef USE_ISA

/* A COLLECTION OF ALL OF THE ASSEMBLY INSTRUCTIONS PERTAINING TO THEIR */
/* DESIGNATED FUNCTIONS */

/* THESE FUNCTIONS INCLUDE THE FOLLOWING: */

/* ---------------------------------
MACRO: ADDRESS,
MACRO: DATA,
MACRO: OFFSETS,
MACRO: ALL
MACRO: NULL TERMINATORS
----------------------------------*/

/* ADDRESS AND DATA ARE SELF-EXPLANTORY; PROVIDING READ AND WRITE COROUTINES */
/* TO THEIR RESPECTIVE INSTRUCTION */

/* OFFSET FUNCTIONS SUCH AS JMP AND JSR WORK BY CHANGING WHERE THE DATA WILL */
/* BE SENT IN RELATION TO THE OFFSET PROVIDED BY THE PROGRAM COUNTER */

INSTRUCTION_FUNCTION(ADD);
INSTRUCTION_FUNCTION(ADD_ADDRESS);
INSTRUCTION_FUNCTION(ADD_DECIMAL_EXTEND);
INSTRUCTION_FUNCTION(ADD_EXTENDED);
INSTRUCTION_FUNCTION(ADD_IMMEDIATE);
INSTRUCTION_FUNCTION(ADD_QUICK);
INSTRUCTION_FUNCTION(AND_IMMEDIATE);
INSTRUCTION_FUNCTION(AND_IMMEDIATE_CONDITION);
INSTRUCTION_FUNCTION(AND_IMMEDIATE_STATUS_REG); 
INSTRUCTION_FUNCTION(AND_LOGICAL);;

INSTRUCTION_FUNCTION(ARITHMETIC_SHIFT_LEFT);
INSTRUCTION_FUNCTION(ARITHMETIC_SHIFT_RIGHT);

INSTRUCTION_FUNCTION(BIT_CHANGE);
INSTRUCTION_FUNCTION(BIT_CLEAR);
INSTRUCTION_FUNCTION(BIT_FIELD);
INSTRUCTION_FUNCTION(BIT_FIELD_SET);
INSTRUCTION_FUNCTION(BIT_FIELD_CHANGE);
INSTRUCTION_FUNCTION(BIT_FIELD_CLEAR);
INSTRUCTION_FUNCTION(BIT_FIELD_SIGNED);
INSTRUCTION_FUNCTION(BIT_FIELD_UNSIGNED);
INSTRUCTION_FUNCTION(BIT_FIRST_ONE);
INSTRUCTION_FUNCTION(BIT_TEST);
INSTRUCTION_FUNCTION(BIT_TEST_SET);
INSTRUCTION_FUNCTION(BRANCH_ALWAYS);

INSTRUCTION_FUNCTION(CALL_MODULE);
INSTRUCTION_FUNCTION(COMPARE);
INSTRUCTION_FUNCTION(COMPARE_ADDRESS);
INSTRUCTION_FUNCTION(COMPARE_IMMEDIATE);
INSTRUCTION_FUNCTION(COMPARE_MEMORY);
INSTRUCTION_FUNCTION(COMPARE_REGISTER_AGAINST);

INSTRUCTION_FUNCTION(DECREMENT_BRANCH);
INSTRUCTION_FUNCTION(DIVIDE_SIGNED);
INSTRUCTION_FUNCTION(DIVIDE_UNSIGNED);

INSTRUCTION_FUNCTION(EXCLUSIVE_OR);
INSTRUCTION_FUNCTION(EXCLUSIVE_OR_IMMEDIATE);
INSTRUCTION_FUNCTION(EXCLUSIVE_OR_IMMEDIATE_CONDITION);
INSTRUCTION_FUNCTION(EXCLUSIVE_OR_IMMEDIATE_STATUS_REG);
INSTRUCTION_FUNCTION(EXCHANGE_REGISTERS);
INSTRUCTION_FUNCTION(EXTEND_SIGNED);

INSTRUCTION_FUNCTION(ILLEGAL_TRAP);

INSTRUCTION_FUNCTION(JUMP);
INSTRUCTION_FUNCTION(JUMP_OR_BRANCH);
INSTRUCTION_FUNCTION(JUMP_OR_BRANCH_SHORT);
INSTRUCTION_FUNCTION(JUMP_TO_SUB);

INSTRUCTION_FUNCTION(LOAD_EFFECTIVE_ADDRESS);
INSTRUCTION_FUNCTION(LINK_ALLOCATE);
INSTRUCTION_FUNCTION(LOGICAL_SHIFT_LEFT);
INSTRUCTION_FUNCTION(LOGICAL_SHIFT_RIGHT);

INSTRUCTION_FUNCTION(MOVE);
INSTRUCTION_FUNCTION(MOVE_FROM_SR);
INSTRUCTION_FUNCTION(MOVE_FROM_CC);
INSTRUCTION_FUNCTION(MOVE_TO_CC);
INSTRUCTION_FUNCTION(MOVE_TO_SR);
INSTRUCTION_FUNCTION(MOVE_USP);
INSTRUCTION_FUNCTION(MOVE_CR);
INSTRUCTION_FUNCTION(MOVE_MR);
INSTRUCTION_FUNCTION(MOVE_PERIPHERAL_DATA);
INSTRUCTION_FUNCTION(MOVE_QUICK);
INSTRUCTION_FUNCTION(MOVE_ADDRESS_SPACE);

INSTRUCTION_FUNCTION(NO_OP);
INSTRUCTION_FUNCTION(LOGICAL_COMPLMENT);
INSTRUCTION_FUNCTION(OR_LOGICAL);
INSTRUCTION_FUNCTION(OR_IMMEDIATE);
INSTRUCTION_FUNCTION(OR_IMMEDIATE_TO_CC);
INSTRUCTION_FUNCTION(OR_IMMEDIATE_TO_SR);

INSTRUCTION_FUNCTION(RESET);
INSTRUCTION_FUNCTION(ROTATE_LEFT);
INSTRUCTION_FUNCTION(ROTATE_RIGHT);
INSTRUCTION_FUNCTION(RETURN_DEALLOC);
INSTRUCTION_FUNCTION(RETURN_EXCEPTION);
INSTRUCTION_FUNCTION(RETURN_MODULE);
INSTRUCTION_FUNCTION(RETURN_RESTORE_CC);

INSTRUCTION_FUNCTION(SUBTRACT_DEC);
INSTRUCTION_FUNCTION(SET_CONDITION);
INSTRUCTION_FUNCTION(STOP);
INSTRUCTION_FUNCTION(SUBTRACT_ADDR);
INSTRUCTION_FUNCTION(SUBTRACT_IMMEDIATE);
INSTRUCTION_FUNCTION(SUBTRACT_QUICK);
INSTRUCTION_FUNCTION(SUBTRACT_EXTEND);
INSTRUCTION_FUNCTION(SWAP);

INSTRUCTION_FUNCTION(TRAP);
INSTRUCTION_FUNCTION(TRAP_CONDITION_UNSIGNED);
INSTRUCTION_FUNCTION(TRAP_CONDITION_SIGNED);
INSTRUCTION_FUNCTION(TRAP_OVERFLOW);
INSTRUCTION_FUNCTION(UNLINK);
INSTRUCTION_FUNCTION(UNPACK_BCD);

static U8* INSTRUCTION_NOT_IMPL(INSTRUCTION* INSTR)
{
	printf("Instruction %s not implemented\n", INSTR->NAME);
}

/* CREATE AN INITIAL OBJECT INSTANCE OF THE OPCODE ARRAY */
/* THIS WILL DETERMINE THE EXECUTION OF EACH CONSECTUTIVE OPCODE */
/* AND WILL ACCESS THEM WHEN NECESSSARY */

/* THIS IS DONE THROUGH A MATCHING CORRESPONDENCE THAT DETERMINE IF */
/* THE OPCODE'S EXECUTION LINES UP WITH THE MICRO-PROCESSOR'S ARCHITECURE */

/* SEE M68K OPCODES: http://goldencrystal.free.fr/M68kOpcodes-v2.3.pdf */

static INSTRUCTION* INSTRUCTION_INIT(U16 OPCODE, U8 OPCODE_COUNT)
{
	OPCODE_COUNT = sizeof(MODE_PATTERN::PATTERN[0]);

	for (U8 O = 0; O < OPCODE_COUNT; O++)
	{
		MODE_PATTERN* PATTERN = MODE_PATTERN::PATTERN[O];

		if (PATTERN += OPCODE)
		{
			INSTRUCTION* INSTR = PATTERN->TYPE(OPCODE);
			return INSTR;
		}
	}
}

#undef OPCODE_LOOKUP
#undef OPCODE_ADDRESSING

/* IN TANDEM WITH THE METHOD DECLARE ABOVE, REFER TO THE WHETHER OR NOT */
/* THE RESPECTIVE INSTRUCTION'S OPCODE CORRESPONDS TO ONE ANOTHER */

static bool INSTRUCTION_MATCH(MODE_PATTERN* PATTERN, U16 OPCODE, U8 OPCODE_COUNT)
{
	assert(sizeof(PATTERN->MODE_BITS) == 1);

	PATTERN->ACCESS_MODE = (U16*)malloc(sizeof(OPCODE_COUNT));
	PATTERN->LEGAL_MODE = (U16*)malloc(sizeof(OPCODE_COUNT));

	/* FAILING THE ABOVE MEMORY ALLOCATION, HANDLE ALLOCATION FAILURE */

	if (PATTERN->ACCESS_MODE == NULL || PATTERN->LEGAL_MODE == NULL)
	{
		free(PATTERN->ACCESS_MODE);
		free(PATTERN->LEGAL_MODE);
		return false;
	}

	/* CHECK THE BITWISE LENGTH OF THE SCAN IN ACCORDANCE WITH THE LENGTH */
	/* OF THE STATUS REGISTER */

	U32 ENDIAN_PTR = 0;
	U16 FRAGMENT_OPCODE = 0;

	/* THE NUMBER REPRESENTS THE USER BYTE DATA CORRESPONDING TO THE STATUS REGISTER */
	/* THIS REGISTER ENCOMPASSES THE FUNCTIONS NECESSARY TO DETERMINE THE CONDITION */
	/* OF AN OPERATION */

	/* THE LETTERS REPRESENT THE ANTITHESIS WITH THESE BEING TEH CONDITION FLAGS THAT */
	/* ARE INDICATIVE OF THE CONDITION OF AN OPERATION */

	/* SEE M68K STATUS REGISTER: https://www.nxp.com/docs/en/reference-manual/MC68000UM.pdf#page=17 */

	while (PATTERN->OPCODE_SEARCH < 16)
	{
		switch (PATTERN->MODE_BITS[PATTERN->OPCODE_SEARCH])
		{
		case '0':
			if (BIT(OPCODE, 15 - PATTERN->OPCODE_SEARCH) != 0) return false;
			PATTERN->OPCODE_SEARCH++;
			continue;

		case '1':
			if (BIT(OPCODE, 15 - PATTERN->OPCODE_SEARCH != 1)) return false;
			PATTERN->OPCODE_SEARCH++;
			continue;

		case '5':
			if (PATTERN->MODE_BITS[ENDIAN_PTR], 1 == '2')
			{
				if (FRAGMENT_OPCODE == 0x00 || FRAGMENT_OPCODE == 0x10)
				{
					ENDIAN_PTR += 2;
					continue;
				}

				return false;
			}

			/* EXTEND THE OPCODE FRAGMENTATION BASED ON THE POSITION OF THE ENDIAN POINTER */
			/* THIS CASE WILL EXTEND THE MEMORY ADDRESS TO IT'S DESIGNATED LOCATION */

			/* IT WILL SPLIT THE MEMORY INTO SMALLER CHUNKS IF NEED BE TO CORRESPOND */
			/* WITH THE SIZE OF THE REGISTER */

		case 'X':
			FRAGMENT_OPCODE = (PATTERN->MODE_BITS[ENDIAN_PTR] == 'X') ?
				((FRAGMENT_OPCODE << 3) & 0x000888) | ((FRAGMENT_OPCODE >> 3) & 0x000777) :
				FRAGMENT_OPCODE++;

		default:
			printf("");
			break;
		}
	}

	return true;
}

/* GENERATE AN INSTRUCTION GIVEN AN ARBITARY VALUE FROM THE SIZE OF */
/* THE ARRAY OF THE ASSEMBLY INSTRUCTIONS */

/* PROVIDED THE ARBITARY VALUE OF THE INSTRUCTION */
/* ALLOCATE THAT MEMORY BASED ON THE SIZE OF THE DRIECTIVE */

INSTRUCTION* GENERATE_INSTRUCTION(MODE_PATTERN* PATTERN, U16 OPCODE, U8 PATTERN_COUNT)
{
	for (U8 i = 0; i < PATTERN_COUNT; ++i)
	{
		malloc(sizeof(char(&PATTERN->PATTERN[i])));

		/* IF THE INSTRUCTIONS MATCH THEIR RESPECTIVE MODE */
		/* RETURN THE TYPE IN RELATION TO THEIR OPCODE */

		if (INSTRUCTION_MATCH(PATTERN, OPCODE, PATTERN_COUNT))
		{
			PATTERN->TYPE(OPCODE);
			return;
		}
	}

	return NULL;
}

#endif