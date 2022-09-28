#ifndef CPU_MAPPER_H 
#define CPU_MAPPER_H

#include <cstdint>
#include <array>
#include "68000.h"

#define BUS_REGISTERS
uint16_t BUS_POINTER{};
uint16_t BUS_RAM[16 * 1000000]{};
uint16_t CPU_RAM[64 * 1000]; 

#define BUS_FUNC
inline void CPU_WRTIE(uint32_t ADDRESS_REG, uint32_t DATA_REG);
inline void CPU_READ(uint32_t ADDRESS_REG, bool READ_ONLY = false);
static void BUS_RESET();
static void BUS_POWER();

#endif 
