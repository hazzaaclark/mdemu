#pragma once
#include <vector>
#include <cstdint>

#ifndef CPU_MAPPER_H 
#define CPU_MAPPER_H

class M68K_MAPPER
{
public:
	M68K_MAPPER(uint32_t MAP_SUPERVISOR_FUNCTION, uint32_t MAP_DATA_FUNCTION);
	~M68K_MAPPER();

public:
	virtual bool CPU_MAP_READ(uint32_t ADDR, uint32_t& MAPPED_ADDR, uint32_t& DATA) = 0;
	virtual bool CPU_MAP_WRTIE(uint32_t ADDR, uint32_t& MAPPED_ADDR, uint32_t DATA = 0) = 0;
};

#endif 

