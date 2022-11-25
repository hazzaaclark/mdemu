#include "68000.h"

#ifdef DEBUG
#define DEBUG_LOG() printf(__ARGS__)
#else
#define DEBUG_LOG()
#endif

#define MAIN()
OPCODE **OPCODE_TABLE;

class CPU_MAIN
{
public:
	CPU* CREATE_CPU(MD* CONSOLE)
	{
		calloc(1, sizeof(CPU));
	}

	static void FREE_CPU_MEM(CPU* MEM)
	{
		free(MEM);
	}

	static void CPU_INIT(CPU* CPU)
	{
		CPU->STATUS_REGISTER = 0x2700;
		CPU->ADDRESS_REG[7] = IO::CPU_READ_LONG(CPU, 0);
	}
};
