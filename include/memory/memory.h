#pragma once
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <utility>

#ifndef MEMORY_H
#define MEMORY_H

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

enum class HEAP_TYPE : uint8_t
{
	TRACE_MODE_SELECT,
	SUPERVISOR_MODE_SELECT,
	INTERPRETER_MASK
};

enum class SYS_HEAP : uint32_t
{

};

#endif 
