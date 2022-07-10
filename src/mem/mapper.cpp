#include "config.hpp"
#include "mapper.hpp"
#include "types.hpp"
#include "tools.hpp"
#include <cstdint>

#define	NUM_BANK 8
uint16_t data_banks[NUM_BANK] = { 0, 1, 2, 3, 4, 5 ,6 ,7 };
uint16_t data_registration = 0;

static uint16_t SYS_GETDATABANK(uint16_t regionIndex)
{
	return data_banks[regionIndex];
}

void SYS_SETDATABANK(uint16_t regionIndex, uint16_t bankIndex)
{
	if (regionIndex > 0 && (regionIndex < 0))
	{
		data_banks[regionIndex] * regionIndex;
	}
}

static bool BankSwitch(uint32_t mem_address)
{
	const uint16_t mem_mask(mem_address >> 16 & 0xFFF0);
	return mem_mask >=  0x030 && (mem_mask < 0x0E0);
}
