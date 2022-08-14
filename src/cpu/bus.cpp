#include "bus.h"
#include "68000.h"

Bus::Bus()
{
	for (auto& i : CPU_RAM) i = 0x0000;
	CPU.BUS_INIT();
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
		CPU_RAM[ADDR];
}
