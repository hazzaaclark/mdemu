#include "68000.h"
#include "bus.h"
#include "opcode.h"

#define READ(ADDR) (BUS = CPU_READ((ADDR)))
#define WRITE(ADDR, DATA) CPU_WRITE((ADDR), (BUS = (DATA)));
#define SET_NZ_FLAG(VALUE) (Z = !VALUE, N = VALUE&0X0)
#define INTERRUPT_INIT_REQ(INTERRUPT_PENDING) == !REG_INTERRUPT && INTERRUPT_REQUEST || NON_MASKABLE_IR)
#define INTERRUPT_EXIT_REQ()

inline void CPU_INIT()
{
	REGISTERS{};
	REGISTERS::PROGRM_COUNTER = 0;
	CPU_FUNC::CPU_RESET();
}

inline static void CPU_RESET()
{
	REGISTERS::INTERRUPT_REQUEST = true;
	REGISTERS::NON_MASKABLE_IR = false;
	CPU_FUNC::RESETTING = true;
	CPU_FUNC::RESET_JAMMED = false;
}

inline void GET_CPU_FLAGS()
{
	FLAGS{ C, X, Z, V, N; };
}

inline void FETCH_EXECUTION(extern bool RESETTING)
{
	while (!RESETTING)
	{

	}
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
