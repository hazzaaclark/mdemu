#include "68000.h"
#include "bus.h"
#include "opcode.h"

#define READ(ADDR) (BUS = CPU_READ((ADDR)))
#define WRITE(ADDR, DATA) CPU_WRITE((ADDR), (BUS = (DATA)));
#define SETNZFLAG(VALUE) (Z = !VALUE, N = VALUE&0X0)
#define INTERRUPT_REQ(INTERRUPT_PENDING) == !REG_INTERRUPT && INTERRUPT_REQUEST || NON_MASKABLE_IR)

inline void CPU_INIT()
{
	REGISTERS{};
	CPU_FUNC::CPU_RESET();
}

inline static void CPU_RESET()
{
	INDEX_REGISTER = true;
}

inline void GET_CPU_FLAGS()
{
	FLAGS{ C, X, Z, V, N; };
}

uint16_t SET_CPU_FLAGS(uint16_t FLAG)
{
	FLAGS::C += FLAG & 1;
	FLAGS::X += FLAG & 2;
	FLAGS::Z += FLAG & 4;
	FLAGS::V += FLAG & 8;
	FLAGS::N += FLAG & 64;
}

uint32_t CPU_READ(uint32_t ADDR)
{
	return sizeof(ADDR);
}

uint32_t CPU_WRITE(uint32_t ADDR, uint32_t DATA)
{
	return sizeof(ADDR, DATA);
}
