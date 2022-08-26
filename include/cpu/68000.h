#ifndef M68K_H
#define M68K_H

#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>


class M68K
{
public:
	M68K();
	~M68K();

public:
	uint32_t DATA_REG[8];
	uint32_t ADDRESS_REG[8];
	uint32_t PROGRAM_COUNTER;
	uint32_t STATUS_REG;
	uint8_t INDEX_REGISTER;
	uint8_t NEGATIVE_REG;
	uint8_t ZERO_REG;
	uint8_t OVERFLOW_REG;
	uint8_t CARRY_OP_REG;

	int CURRENT_STACK_POINTER;
	uint32_t STACK_POINTER[3];

	static void BUS_INIT();
	static void CPU_RESET();
	static void REG_INTERRUPT();
	static void NON_MASKABLE_RI();
	static void TIMER();
	bool CYCLECOMPLETE();

public:
	uint32_t CPU_READ(uint32_t ADDR, uint32_t DATA);
	uint32_t FETCH_LOCATION();

public:
	struct M68KFLAGS
	{
		const char C = (1 << 0);
		const char X = (1 << 1);
		const char Z = (1 << 2);
		const char V = (1 << 3);
		const char N = (1 << 4);
	};

};
#endif
