#include "68000.h"

#ifdef DEBUG
#define DEBUG_LOG() (__ARGS__)
#else
#define DEBUG_LOG()
#endif

#define MAIN()
OPCODE **OPCODE_TABLE;

class CPU_MAIN
{
public:

	/* ALLOCATE THE REQUESTED MEMORY */
	/* USING THE CALLOC FUNCTION TO CREATE A POINTER */

	static CPU* CREATE_CPU(MD* CONSOLE)
	{
		calloc(1, sizeof(CPU));
	}

	/* BASE CASE FOR DEALLOCATING OR REALLOCATING MEMORY */

	static void FREE_CPU_MEM(CPU* MEM)
	{
		free(MEM);
	}

	/* A REFACTOR FUNCTION TO DECLARE THE CPU'S QUINTESSENTIAL FUNCTIONS */
	/* ALL OF WHICH ARE CITED FROM https://www.nxp.com/files-static/archives/doc/ref_manual/M68000PRM.pdf */

	static void CPU_INIT(CPU* CPU)
	{
		CPU->STATUS_REGISTER = 0x2700;
		CPU->ADDRESS_REG[7] = IO::CPU_READ_LONG(CPU, 0); 
		CPU->PROGRAM_COUNTER = IO::CPU_READ_LONG(CPU, 4);
		CPU->CYCLES = 0;
		CPU->CYCLES_STOPPED = false;

	}
};
