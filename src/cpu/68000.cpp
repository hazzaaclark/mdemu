#include "68000.h"
#include "bus.h"

class Bus;

/** CPU CONSTRUCTOR **/
// Assembles the Operation Code table

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

uint32_t CPU_READ(uint32_t ADDR)
{
	return CPU_READ(ADDR);
}
