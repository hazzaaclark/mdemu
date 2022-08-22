#include "bus.h"
#include "68000.h"

Bus::Bus()
{
	memset((void*)CPU_RAM, 0x0, sizeof(CPU_RAM));
}


Bus::~Bus()
{

}

void Bus::CPU_WRTIE(uint32_t ADDR, uint32_t DATA)
{
	if (ADDR >= 0x000000 && ADDR <= 0xFFFFFF)
		ADDR = DATA;
}

void Bus::CPU_READ(uint32_t ADDR, bool READ)
{
	if (ADDR >= 0x000000 && ADDR <= 0xFFFFFF)
		*CPU_RAM = sizeof(ADDR);
}
