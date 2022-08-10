#include "68000.h"
#include "bus.h"

class Bus;

/** CPU CONSTRUCTOR **/
// Assembles the Operation Code table and the bulk of the CPU's main functions

M68K::M68K()
{
	using a = M68K;
	OPCODE_LOOKUP =
	{
		{ "ADDA", }
	};
}

M68K::~M68K()
{

}

void M68K::BUS_INIT()
{
	Bus* BUS_POINTER(void** (CPU_READ));
}

void CPU_READ(uint32_t ADDR)
{
	return CPU_READ(ADDR);
}
