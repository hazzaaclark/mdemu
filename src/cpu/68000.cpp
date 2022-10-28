#include "68000.h"

#ifdef DEBUG
#define DEBUG_LOG() printf(__ARGS__)
#else
#define DEBUG_LOG()
#endif

#define MAIN()
OPCODE **OPCODE_TABLE;

namespace M68K
{
	class MAIN_CPU
	{
		CPU* CREATE_CPU(MD* CONSOLE)
		{
			calloc(1, sizeof(CPU));
		}

		static void FREE_CPU_MEM(CPU* MEM)
		{
			free(MEM);
		}

		inline void CPU_INIT(CPU* CPU)
		{
			CPU->ADDRESS_REG[7];
		}
	};
}
