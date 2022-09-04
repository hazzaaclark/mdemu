#include "68000.h"
#include "bus.h"
#include "opcode.h"

#define READ(ADDR) (BUS = CPU_READ((ADDR)))
#define WRITE(ADDR, DATA) CPU_WRITE((ADDR), (BUS = (DATA)));

inline void CPU_FLAGS()
{
	FLAGS{ C, X, Z, V, N; }
}

uint32_t CPU_READ(uint32_t ADDR)
{
	return sizeof(ADDR);
}

uint32_t CPU_WRITE(uint32_t ADDR, uint32_t DATA)
{
	return CPU_WRITE(ADDR, DATA);
}
