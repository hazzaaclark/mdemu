#include "68000.h"
#include <cstdint>
#include <stdio.h>

static void SET_CPU(CPU_STATE *state)
{
	CPU_STATE* cpu = state;
	cpu->PROGRAM_COUNTER;
}

void CPU_FUNCTIONS::RESET()
{
	uint32_t ABS_ADDR = 0xFFFFFC;
	uint32_t READ;
	void WRITE(uint32_t ADDR_REG, uint32_t DATA_REG);
}
