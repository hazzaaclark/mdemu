#ifndef CPU_MAPPER_H 
#define CPU_MAPPER_H

#include <vector>
#include <cstdint>

class M68K_MAPPER
{
public:
	M68K_MAPPER(uint32_t MAP_SUPERVISOR_FUNCTION, uint32_t MAP_DATA_FUNCTION);
	~M68K_MAPPER();

public:
	virtual bool CPU_MAP_READ(uint32_t ADDR, uint32_t& MAPPED_ADDR, uint32_t& DATA) = 0;
	virtual bool CPU_MAP_WRTIE(uint32_t ADDR, uint32_t& MAPPED_ADDR, uint32_t DATA = 0) = 0;

	virtual bool MMU_MAP_READ();
	virtual bool MMU_MAP_WRITE();

private:
	uint32_t pSFC = 0;
	uint32_t pDFC = 0;
};

#endif 
