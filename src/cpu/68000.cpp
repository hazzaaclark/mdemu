#include "68000.h"
#include <cstdint>
#include <stdio.h>

static void CPU_INIT(CPU_MAIN* main)
{
	main->PROGRAM_COUNTER = 0x000000;
}
