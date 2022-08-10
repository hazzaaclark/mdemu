#pragma once

#ifndef YM2612_H
#define YM2612_H
#define YM2612_B_ADDR 0xA04000

class YM2612
{
public:
	YM2612();
	~YM2612();
	static void YM2612_RESET(void);
};


#endif 
