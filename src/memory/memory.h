#pragma once
#include <cstdint>
#include <memory.h>

#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

class MEM
{
public:
	MEM();
	~MEM();

private:
	uint32_t ROM;
	uint32_t STATIC_RAM;
	uint32_t STACK_SIZE;
};


#endif 
