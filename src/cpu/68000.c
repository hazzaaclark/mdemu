/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONS OF THE CPU */

#include "68000.h"

#undef USE_CPU

#if defined(M68K_CPU_ARGS)
#define	M68K_CPU_ARGS
#else
#define M68K_CPU_ARGS

#define		M68K_CALLBACK_RESET			1
#define		M68K_CALLBACK_FUNC			2

#endif

/*===============================================================================*/
/*							68000 MAIN CPU FUNCTIONALIY							 */
/*===============================================================================*/

/* DISCERN THE EXCEPTION HANDLER TABLE WHICH ENCOMPASSES THE */
/* MASTER LOGIC FROM THE VECTOR TABLE OF THE HEADER OF 68K ASSEMBLY */

U8 M68K_EXECEPTION_TABLE[4][256] =
{
	{ 	  0, /* 	NULL	 										 	*/
		  4, /*  0: RESET - STACK POINTER 		                     	*/
		  4, /*  1: RESET - PROGRAM COUNTER                    			*/
		 50, /*  2: BUS ERROR                             				*/
		 50, /*  3: ADDRESS ERROR 										*/
		 34, /*  4: ILLEGAL OP/INSTR                                	*/
		 38, /*  5: ZERO DIV							             	*/
		 40, /*  6: CHECK REGISTER AGAINST UB/LB (1'S, 2'S COMP)		*/
		 34, /*  7: TRAPV                                              	*/
		 34, /*  8: PRIVILEGE VIOLATION                                 */
		 34, /*  9: TRACE EXEC                                          */
		  4, /* 10: 1010                                                */
		  4, /* 11: 1111                                                */
		  4, /* 12: RESERVED                                            */
		  4, /* 13: COPROCESSOR VIOLATION (SCD, 32X)  					*/
		  4, /* 14: FORMAT ERROR                                       	*/
		 44, /* 15: UNIITIALISED INTERRUPT                            	*/
		  4, /* 16: RESERVED                                           	*/
		  4, /* 17: RESERVED                                           	*/
		  4, /* 18: RESERVED                                           	*/
		  4, /* 19: RESERVED                                           	*/
		  4, /* 20: RESERVED                                           	*/
		  4, /* 21: RESERVED                                           	*/
		  4, /* 22: RESERVED                                           	*/
		  4, /* 23: RESERVED                                           	*/
		 44, /* 24: SP INTERRUPT		                                */
		 44, /* 25: LEVEL 1 IRQ                       					*/
		 44, /* 26: LEVEL 2 IRQ                       					*/
		 44, /* 27: LEVEL 3 IRQ                        					*/
		 44, /* 28: LEVEL 4 IRQ                        					*/
		 44, /* 29: LEVEL 5 IRQ                        					*/
		 44, /* 30: LEVEL 6 IRQ                        					*/
		 44, /* 31: LEVEL 7 IRQ                        					*/
		 34, /* 32: TRAP #0                   							*/
		 34, /* 33: TRAP #1                                            	*/
		 34, /* 34: TRAP #2                                            	*/
		 34, /* 35: TRAP #3                                            	*/
		 34, /* 36: TRAP #4                                            	*/
		 34, /* 37: TRAP #5                                            	*/
		 34, /* 38: TRAP #6                                            	*/
		 34, /* 39: TRAP #7                                            	*/
		 34, /* 40: TRAP #8                                            	*/
		 34, /* 41: TRAP #9                                            	*/
		 34, /* 42: TRAP #10                                           	*/
		 34, /* 43: TRAP #11                                           	*/
		 34, /* 44: TRAP #12                                           	*/
		 34, /* 45: TRAP #13                                           	*/
		 34, /* 46: TRAP #14                                           	*/
		 34, /* 47: TRAP #15                                           	*/
		  4, /* 48: FP BRAS 											*/
		  4, /* 49: FP INEAXCT 											*/
		  4, /* 50: FP ZERO DIVIDE 										*/
		  4, /* 51: FP UNDERFLOW										*/
		  4, /* 52: FP OPERNAD                      					*/
		  4, /* 53: FP OVERFLOW                           				*/
		  4, /* 54: FP SIGNAL NAN                       				*/
		  4, /* 55: FP UNUSED DATA TYPE            						*/
		  4, /* 56: MMU CONFIG ERROR               						*/
		  4, /* 57: MMU ILLEGAL OP ERROR           						*/
		  4, /* 58: MMU ACCESS LEVEL VIOLATION      					*/
		  4, /* 59: RESERVED                                           	*/
		  4, /* 60: RESERVED                                           	*/
		  4, /* 61: RESERVED                                           	*/
		  4, /* 62: RESERVED                                           	*/
		  4, /* 63: RESERVED                                           	*/
		     /* 64-255: USER DEFINED                                   	*/
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	}
};



/* FOLLOWING THE INITIAL DECLARATION OF THE VECTOR TABLE */
/* DISCERN THE RUDIMENTARY AMOUNT OF CPU CYCLES */
/* THE CPU WILL GOVERN OVER THE COURSE OF IT'S RUN TIME */

/* THIS WILL ENCOMPASS THE WIDE BITWISE VARIETY */
/* THROUGH THE MEANS OF EVALUATING THE SIZE OF THE DESIGNATED MEMORY */

/* SEE 1.1 USER PROGRAMMING MODEL https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#page=13 */

void INITIALISE_68K_CYCLES()
{
	char* CPU_68K_CYCLES;
	CPU_68K_CYCLES = malloc(sizeof(CPU_68K_CYCLES));

	/* THIS LOOP WILL CHECK FOR EVERY SUBSEQUENT BITWISE */
	/* OPERATION AND EVALUATE IT'S DESIGNATED MEMORY */

	/* THE FIRST CO-EFFICIENT REPRESENTS THE BITWISE LENGTH OF THE OPERATION */
	/* THE SECOND CO-EFFICIENT REPRESENTS THE SIZE OF THE REGISTER */

	for (size_t INDEX = 0; INDEX < sizeof(CPU_68K_CYCLES); INDEX++)
	{
		switch (INDEX / 16)
		{
		case 0:
			CPU_68K_CYCLES[INDEX] = 8*7;
			break;

		case 1:
			CPU_68K_CYCLES[INDEX] = 16*7;
			break;

		case 2:
			CPU_68K_CYCLES[INDEX] = 24*7;

		default:
			CPU_68K_CYCLES[INDEX] = 32*7;
			break;
		}
	}
}

/* ACCESS EACH RESPECTIVE REGISTER FROM THE ENUMERATION */
/* RETURN THE CORRESPONDENCE IN RELATION TO THE SIZE */

/* FOR EASE OF USE WHEN ACCESSING METHODS, I HAVE CREATED A MACRO */
/* TO BE ABLE TO RETURN THE CORRESPONDING ADDRESS VALUE IN RELATION */
/* TO THE INDEXXING OF THE REGISTER ARRAY */

U32* CPU_ACCESS_REGISTERS(CPU_68K_REGS REGISTER, unsigned VALUE)
{
	struct CPU_68K* CPU_68K = malloc(sizeof(CPU_68K));

	/* IF THERE IS NO ACCESSIBLE METHODS */
	/* WE SPECIFICALLY ALLOCATE MEMORY SAID ACCESSING OF REGISTERS */

	/* THE REASON AS TO WHY THERE ARE TWO SEPERATE CASTS IS DUE TO THE FACT */
	/* THAT THE UINTPTR WILL HOUSE THE CORRESPONDING POINTER OF THE RESPECTIVE 32 BIT INTEGER */

	/* IT HAS NOW BEEN UPDATED TO ACCOMODATE FOR THE ACTUAL RETURN OF A 32 BIT INT */
	/* AKIN TO THE MAX SIZE OF THE REGISTERS */

	switch(REGISTER)
	{
		case M68K_REG_D0: return CPU_68K->REGISTER_BASE[0];
		case M68K_REG_D1: return CPU_68K->REGISTER_BASE[1];
		case M68K_REG_D2: return CPU_68K->REGISTER_BASE[2];
		case M68K_REG_D3: return CPU_68K->REGISTER_BASE[3];
		case M68K_REG_D4: return CPU_68K->REGISTER_BASE[4];
		case M68K_REG_D5: return CPU_68K->REGISTER_BASE[5];
		case M68K_REG_D6: return CPU_68K->REGISTER_BASE[6];
		case M68K_REG_D7: return CPU_68K->REGISTER_BASE[7];
		
		case M68K_REG_A0: return CPU_68K->REGISTER_BASE[8];
		case M68K_REG_A1: return CPU_68K->REGISTER_BASE[9];
		case M68K_REG_A2: return CPU_68K->REGISTER_BASE[10];
		case M68K_REG_A3: return CPU_68K->REGISTER_BASE[11];
		case M68K_REG_A4: return CPU_68K->REGISTER_BASE[12];
		case M68K_REG_A5: return CPU_68K->REGISTER_BASE[13];
		case M68K_REG_A6: return CPU_68K->REGISTER_BASE[14];
		case M68K_REG_A7: return CPU_68K->REGISTER_BASE[15];

		case M68K_REG_PC: return (U32*)(uintptr_t)M68K_RETURN_ADDRESS(CPU_68K->PC);

		case M68K_REG_USP:
			return CPU_68K->S_FLAG;

		case M68K_REG_ISP:
			return CPU_68K->S_FLAG ? CPU_68K->STACK_POINTER[0] : CPU_68K->REGISTER_BASE[15];

		case M68K_REG_SP:
			return CPU_68K->REGISTER_BASE[15];

		case M68K_REG_SFC:
			return CPU_68K->SOURCE_FUNCTION_COUNTER;

		case M68K_REG_DFC:
			return CPU_68K->DEST_FUNCTION_COUNTER;

		case M68K_REG_VBR:
			return CPU_68K->VBR;

		case M68K_REG_CACR:
			return CPU_68K->CACHE_CONTROL;

		case M68K_REG_CAAR:
			return CPU_68K->CACHE_ADDRESS;

		case M68K_REG_IR:
			return CPU_68K->INDEX_REGISTER;

		default:
			free(CPU_68K);
			return 0;
	}
}

/* IN A SIMILAR VEIN TO THE FUNCTION ABOVE, THIS FUNCTION WILL FOCUS MOREOVER */
/* ON THE SETTING OF THESE VALUES */

/* THIS IS POSSIBLE DUE TO THE WAY IN WHICH THE ENUM VALUES ARE ASSIGNED TO THE SPECIFIC */
/* MACRO WITH AN ALLOCATED SIZE */

void CPU_SET_REGISTERS(CPU_68K_REGS REGISTER, unsigned VALUE)
{
	struct CPU_68K* CPU_68K = malloc(sizeof(struct CPU_68K));

	switch (REGISTER)
	{
		case M68K_REG_D0: CPU_68K->REGISTER_BASE[0] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_D1: CPU_68K->REGISTER_BASE[1] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_D2: CPU_68K->REGISTER_BASE[2] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_D3: CPU_68K->REGISTER_BASE[3] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_D4: CPU_68K->REGISTER_BASE[4] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_D5: CPU_68K->REGISTER_BASE[5] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_D6: CPU_68K->REGISTER_BASE[6] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_D7: CPU_68K->REGISTER_BASE[7] += M68K_MASK_OUT_ABOVE_32(VALUE); return;

		case M68K_REG_A0: CPU_68K->REGISTER_BASE[8] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_A1: CPU_68K->REGISTER_BASE[9] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_A2: CPU_68K->REGISTER_BASE[10] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_A3: CPU_68K->REGISTER_BASE[11] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_A4: CPU_68K->REGISTER_BASE[12] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_A5: CPU_68K->REGISTER_BASE[13] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_A6: CPU_68K->REGISTER_BASE[14] += M68K_MASK_OUT_ABOVE_32(VALUE); return;
		case M68K_REG_A7: CPU_68K->REGISTER_BASE[15] += M68K_MASK_OUT_ABOVE_32(VALUE); return;

		case M68K_REG_PC: M68K_JUMP(M68K_MASK_OUT_ABOVE_32(VALUE)); return;
		case M68K_REG_SR: M68K_SET_SR_IRQ(VALUE); return;
		case M68K_REG_SP: CPU_68K->STACK_POINTER[7] = M68K_MASK_OUT_ABOVE_32(VALUE); return;

		default:
			if(CPU_68K == NULL)
				free(CPU_68K);
			return;
	}
}

/* INTIALISE THE INTEGER TYPE CALLBACK */
/* THIS CALLBACK REFERS TO THE WAY IN WHICH THE DESIGNATED TYPE */
/* IS ABLE TO COMMUNICATE BETWEEN ALL AREAS OF EACH RESPECTIVE REGISTER */

/* SEE: https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#page=14 */

/* ALLOCATE A DESIGNATED CHUNK OF MEMORY ASSUMING THE NOTION */
/* THAT THE RESPECTIVE REGISTER NEEDS TO ACCESS VALUES OF THIS ASSOCIATION */

#undef M68K_CPU_ARGS

int M68K_SET_INT_CALLBACK(int* CALLBACK, int* LEVEL)
{
	return M68K_CALLBACK_INT(CALLBACK ? CALLBACK : (int*)sizeof(*LEVEL), LEVEL);
}

/* FOLLOWING ON FROM THE SAME PRINCIPLES AS ABOVE */
/* INITIALISE THE REMAINING CALLBACKS */

void M68K_SET_FUNC_CALLBACK(int* CALLBACK, int* LEVEL)
{
	M68K_FUNC_CALLBACK(CALLBACK ? CALLBACK : (int*)sizeof(*LEVEL), LEVEL);
}

/* DETERMINE THE STEP LATENCY OF RELEVANT MOVE BASED INSTRUCTIONS */
/* THIS CHECKS THE MASK TO PROCESS SAID IRQ */

void M68K_SET_MOVE_IRQ_INT()
{
	struct CPU_68K* CPU_68K;

	/* FIRSTLY, WE BEGIN TO EVALUATE THE SIZE OF THE CURRENTLY EXECUTED INSTRUCTION */
	/* THIS IS SO THAT WHEN CHECKING THE MASK, WE DON'T RUN INTO BUFFER OVERFLOWS */

	assert(CPU_68K->PC <= ADDRESS_WIDTH_32);
	assert(CPU_68K->MEMORY_ADDRESS[7] % 2 == 0);

	/* SECONDLY, EVALUATE WHICH INSTRUCTION IS BEING EXECUTED */
	/* CREATE A CAST TO EVALUATE THE SIZE OF THE RELEVANT INSTRUCTION */

	CPU_68K->INSTRUCTION_REGISTER = (U16*)malloc(M68K_FETCH_INSTR(&CPU_68K));

	/* THIRDLY, EVALUATE THE STEP LATENCY TO DETERMINE THE EXECUTION TIME */	
	/* THIS IS BY ASSUMING THAT THE CORRESPONDING INSTRUCTION HAS A RELATIVE SIZE */

	/* FROM THERE, DETERMINE IF THE INSTRUCTION CAN BE OR IS HOUSED IN THE INDEX REGISTER */
	/* IF NOT, MAKE ROOM FOR THE CURRENT INDEX */

	int IRQ_LATENCY;
	int INT_LEVEL;

	if(!IRQ_LATENCY && M68K_REG_IR & 0xF000 != 0x2000) 
	{
		M68K_CYCLE_CLOCK_SHIFT(CPU_68K->INSTRUCTION_CYCLES[M68K_REG_IR]);
	}

	INT_LEVEL <= 8;
}

void M68K_RUN(void)
{
	struct CPU_68K* CPU_68K;
	int CYCLES;

	/* WHILE WORKING, CHECK IF THE INSTRUCTION CYCLES */
	/* MATCHES THE CORRESPONDNECE IN THE CYCLE CACHE */

	if(CPU_68K->INSTRUCTION_CYCLES >= CYCLES)
	{
		return;
	}

	do
	{
		INITIALISE_68K_CYCLES();
		M68K_FETCH_INSTR(&CPU_68K);

	} while (CYCLES > 0);
	

	/* EXECUTE RELEVANT INSTRUCTION */

	CPU_68K->INSTRUCTION_REGISTER[M68K_REG_IR];
	M68K_CYCLE_CLOCK_SHIFT(CPU_68K->INSTRUCTION_CYCLES[M68K_REG_IR]);

	return CYCLES;

}

/* BASED ON THE FUNCTIONALITY ABOVE, WE CAN BEGIN TO EVALUATE WHICH INSTRUCTIONS ARE BEING FETCHED */
/* THIS IS BASED ON THEIR PRIORITY LEVEL IN RELATION TO WHICH INSTRUCTION IS BEING FETCHED FROM THE PC */

U16* M68K_FETCH_INSTR(struct CPU_68K* CPU_68K)
{
	unsigned WORD;

	/* IF THE PROGRAM COUNTER HAS JUMPED TO ANOTHER SUBROUTINE */
	/* OR INSTRUCTION, SHIFT LOGICAL TO THE NEXT PROBABLE INSTRUCTION */

	if(CPU_68K->PC != CPU_68K->PREVIOUS_ADDRESS)
	{
		WORD = M68K_READ_16(CPU_68K->MEMORY_ADDRESS, CPU_68K->MEMORY_DATA);
		CPU_68K->PC = CPU_68K->PREVIOUS_ADDRESS, sizeof(CPU_68K->PC + 2);
	}

	return WORD;
}

/* PARSE THE CONTENTS OF THE PULSE RESET ADDRESS LINE ON THE CPU */

void M68K_PULSE_RESET(void)
{
	struct CPU_68K* CPU_68K;
	unsigned PREV_INT_LEVEL = M68K_INT_LEVEL(*CPU_68K->INSTRUCTION_CYCLES);

	if(!PREV_INT_LEVEL)
	{
		M68K_INIT_OPCODE();
	}
}

/* INITIALISE THE MAIN CONSTRUCTOR OF THE CPU INSTANCE */
/* WITH ALL OF THE PRE-REQUISITIES ABOVE ESTABLISHED */

void M68K_INIT(void)
{
	/* ASSUMES THE ROLE THAT ONCE THE EMU HAS STARTED */
	/* THE LINKER WILL ESTABLISH THE CORRESPONDING FUNCTIONS AND TYPES */

	unsigned INIT_EMU = 0;

	if(!INIT_EMU)
	{
		M68K_BUILD_OPCODE_TABLE();
	}

	M68K_SET_MOVE_IRQ_INT(NULL);
	M68K_SET_FUNC_CALLBACK(NULL, NULL);
	M68K_SET_INT_CALLBACK(NULL, NULL);
	M68K_FETCH_INSTR(NULL);
}

/* THIS FUNCTION HOUSES FUNCTIONALITY TO BE ABLE TO SAVE REGISTER TYPES */
/* AND STATES BASED ON THEIR BYTEWISE LENGTH */

/* IN ASSOCIATION WITH THEIR STRING LITERAL TO BE */ 
/* ABLE TO COMMUNICATE WITH OTHER FUNCTIONS */

void M68K_STATE_REGISTER(const char* TYPE, int* CPU_BASE)
{
	CPU_68K_REGS REGISTER;
	struct CPU_68K* CPU_68K;

	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "D", M68K_REG_D0, 8);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "A", M68K_REG_A0, 8);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "PC", M68K_REG_PC, 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "USP", M68K_REG_USP, 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "ISP", M68K_REG_ISP, 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "VBR", M68K_REG_VBR, 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "SFC", M68K_REG_SFC, 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "DFC", M68K_REG_DFC, 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "CACR", M68K_REG_CACR, 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "INT_LVL", M68K_INT_LEVEL(*CPU_68K->INT_LEVEL), 1);
	M68K_SAVE_REGISTER(TYPE, CPU_BASE, "INT_CYC", M68K_INT_LEVEL(*CPU_68K->INSTRUCTION_CYCLES), 1);
}

/* FINALLY, ESTABLISH AN EXECUTION ENTRY POINTER FOR THE MASTER CPU LOGIC */
/* THIS ASSUMES THE ROLE OF WHEN THE CPU IS NOT HALTED AND OR STOPPED */

/* IT WILL LOOK INTO THE PREVIOUS PROGRAM COUNTER STATE TO DETERMINE */
/* WHICH INSTRUCTION TO COMPUTE */

int M68K_EXEC(int CYCLES)
{
	struct CPU_68K* CPU_68K;
	int INITIAL_CYCLES;

	if(!CPU_68K->STOPPED)
	{
		while(M68K_REMAINING_CYCLES > 0)
		{
			/* TO-DO: */
			/* INITIALISE M68K MEMORY MAP   					*/
			/* CREATE EXTERNAL CPU HOOK							*/
			/* DETERMINE TRACE MODE FOR EXCEPTION HANDLES		 */

			CPU_68K->PREVIOUS_PC = M68K_REG_PC;
		}

		return INITIAL_CYCLES;
	}

	return CYCLES;
}

/*===============================================================================*/
/*							68000 MEMORY FUNCTIONALIY							 */
/*===============================================================================*/

/* LOAD THE TMSS ROM HEADER SUCH THAT THE MEMORY MAP IS ABLE TO DISCERN */
/* IF THE PROVIDED ROM HAS TMSS SUPPORT */

unsigned int* LOAD_TMSS_ROM(void)
{
	struct CPU_68K* CPU_68K;
	unsigned char* TMSS_BUFFER;

	/* THIS FUNCTION WILL ASSUME THAT THE TMSS CORRESPONDENCE WILL */
	/* BE NULL TO BEGIN WITH */

	CLEAR_TMSS_ROM();

	/* DISCERN IF TMSS IS NOT ENABLED WITHIN THE ROM HEADER */

	if(!IS_TMSS_ENABLED())
		return -1;

	/* DEFINE THE TMSS ROM FILESIZE, THIS IS BASED ON THE SIZE */
	/* OF A TRADITIONAL MD ROM */

	if(sizeof(CPU_68K->TMSS.ROM < 0) || CPU_68K->TMSS.ROM > (int)M68K_MAX_TMSS_SIZE)
		return -2;

	/* ASSUMING NOW THAT THE ROM FITS WITHIN THE REALMS OF THE SIZE OF THE BUFFER */
	/* WE CAN BEGIN TO ALLOCATE MEMORY ONTO THE STACK TO STORE THE TMSS */

	TMSS_BUFFER = (char*)malloc(sizeof(CPU_68K->TMSS.ROM()));

	if(TMSS_BUFFER == NULL)
	{
		fprintf("Could not allocate relative memory to TMSS Rom Header %x", stderr);
		free(CPU_68K->TMSS.ROM);
		return -3;
	}

	/* CLEAR THE EMPTY STACK MEMORY OF THE ROM BUFFER ASSUMING WHEN */
	/* IT ISN'T BEING USED */

	memset(&CPU_68K->TMSS.ROM, 0xFF, 0);
	free(CPU_68K->TMSS.ROM);
	return 0;

}

/* INITIALISE THE MEMORY MAPPER FOR THE CPU */
/* THIS WILL BE THE INTIAL FOUNDATION BY WHICH THE CPU WILL COMMUNICATE WITH THE SUB CPU */
/* TO INITIALISE THE CASTING TO THE CYCLE TABLE */

void M68K_MEM_INIT(void)
{
	int INDEX;
	int CYCLE_TAB[256];
	
	/* WHEN THE INDEX FOR THE TABLE IS LESS THAN THE MAX BUFFER */
	/* ALLOCATE MEMORY FOR EACH RESEPECTIVE REGISTER */

	for(INDEX = 0; INDEX < 512; ++INDEX)
	{
		CYCLE_TAB[INDEX] = (int)malloc(INDEX * 7 / 15);
	}
}

/* FROM HERE, IMPLEMENT CYCLE ACCURATE MEMORY READING METHODS */
/* SUCH THAT THE DESIGNATED MEMORY IS ABLE TO COMMUNICATE BETWEEN COMPONENTS */

/* SUCH IS THE CASE WITH COMMUNICATING WITH THE SUB-CPU (Z80) */

/* BEGIN EACH OF THESE FUNCTIONS BY DISCERNING THE RELATIVE SIZE OF THE RAM IN MEMORY */ 

U8 M68K_READ_RAM_BYTE(U32* ADDRESS)
{
	memset(ADDRESS, 0, 0xFFFF);
	return M68K_RAM_BYTE[ADDRESS];
}

/* READ RELATIVE DATA FROM THE Z80 BUS */
/* THIS ENCOMPASSES DATA REGISTER $A00000 - $A7FFFF */
/* WHICH REVOLVES AROUND MEMORY, CONTROL PORTS, AND IO */

U8 M68K_READ_BUS_BYTE(U32* ADDRESS)
{
	memset(ADDRESS, 0, 0xFFFF);
	unsigned int ADDRESS_MODE;

	/* DIFFERENTIATE BETWEEN THE VARIOUS ADDRESSABLE MODES */

	switch(ADDRESS_MODE)
	{

		/* ENTRY POINT FOR Z80 BUS COMMUNICATION */
		/* NOTHING REALLY HAPPENS AT THIS ADDRESS SO */
		/* WE WILL JUST RETURN THE READ DATA COUROUTINE */

		case 0xA0FFFF:
			return Z80_READ(ADDRESS, 0xFFFF);
		break;

		/* THIS ADDRESS IS THE MAX VALUE AND DOESN'T */
		/* CHECK FOR ANYTHING, SO WE CAN USE THIS TO DISCERN */
		/* A FETCH COUROUTINE */

		case 0xA20000:
			if(*ADDRESS < 0xFFFF)
				memset((void*)sizeof(ADDRESS), 0, sizeof(unsigned int));

			else
				assert(0);
			break;

		default:
			return 0xFF;
	}
}

/*===============================================================================*/
/*							68000 MISC FUNCTIONALIY								 */
/*===============================================================================*/

/* SMALL INDEPENDANT FUNCTIONS THAT FOLLOW THE SCHEMA OF PROVIDING */
/* BASE FUNCTIONALITY FOR THE M68000'S FUNCTIONS SUCH AS MEMORY FLOW, MEMORY ALLOCATION, ETC */

/* THESE FUNCTIONS WILL BE USED FURTHER UP IN THE PROGRAM FOR ACCESSING RELEVANT REGISTERS */
/* IN RELATION TO THEIR CONDITION */

INLINE void M68K_JUMP(unsigned NEW_PC)
{
	struct CPU_68K* CPU_68K = malloc(sizeof(CPU_68K));

	CPU_68K->PC = NEW_PC;
}

/* IN A SIMILAR VEIN FOR THE ABOVE FUNCTION, DECLARE THE JUMP VECTOR */
/* THE JUMP VECTOR ENCOMPASSES THE POSITION BY WHICH THE JMP COUROUTINE TRANSFERS */
/* DATA TO AND FROM THE PC */

INLINE void M68K_JUMP_VECTOR(unsigned VECTOR)
{
	struct CPU_68K* CPU_68K = malloc(sizeof(CPU_68K));

	/* READ THE RELEVANT CONTENTS OF THE COROUTINE */
	/* FROM THERE, DISCERN THE  OFFSET OF THE JMP VECTOR */

	M68K_READ_32(CPU_68K->PC, CPU_68K->PREVIOUS_PC);
	CPU_68K->PC = (VECTOR << 2) + CPU_68K->VBR;
}

/* DETERMINE THE STATUS REGISTER FOR RELEVANT INTERRUPTS AND STACK POINTER */
/* INITIALISE THE RELEVANT FLAG FOR EACH */

INLINE void M68K_SET_SR_IRQ(unsigned VALUE)
{
	struct CPU_68K* CPU_68K = malloc(sizeof(CPU_68K));

	/* EVALUATE THE MASKABLE BITS FROM THE SR */
	VALUE &= CPU_68K->STATUS_REGISTER[7]; 

	if(CPU_68K == NULL && !VALUE) free(CPU_68K);
}
