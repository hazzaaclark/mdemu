#pragma once
#include <cstdint>
#include <array>
#include "68000.h"

class Bus
{
public:
	Bus();
	~Bus();

public:
	uint16_t CPU_RAM[4096];
	M68K CPU;

public:
	void CPU_WRTIE(uint32_t ADDRESS_REG, uint32_t DATA_REG);
	void CPU_READ(uint32_t ADDRESS_REG, bool READ_ONLY = false);
};
