#ifndef YM2612_H
#define YM2612_H
#define YM2612_B_ADDR 0xA04000

#include <iostream>
#include <stdio.h>

class YM2612
{
public:
	YM2612();
	~YM2612();

public:
	uint8_t YM_READ(const uint16_t PORT);

public:
	static void YM_WRITE(const uint16_t PORT, const uint8_t DATA);
	static void YM_WRITE_SAFE(const uint16_t PORT, const uint8_t DATA);
	static void YM_RESET();

};

#endif 
