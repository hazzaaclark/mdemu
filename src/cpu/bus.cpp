#include "bus.h"
#include "68000.h"

inline void RAM_INIT()
{
	memset((void*)CPU_RAM, 0x0, sizeof(CPU_RAM));
}


inline void BUS_FUNC::CPU_WRTIE(uint32_t ADDR, uint32_t DATA)
{
	while (ADDR >= 0x000000 && ADDR <= 0xFFFFFF)
		ADDR = sizeof(DATA);
}

inline void BUS_FUNC::CPU_READ(uint32_t ADDR, bool READ)
{
	while (ADDR >= 0x000000 && ADDR <= 0xFFFFFF)
		*CPU_RAM = sizeof(ADDR);
}
