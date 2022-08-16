#include "ym2612.h"

static void WRITE_REG(uint16_t PORT, uint8_t REG, uint8_t CHANNEL)
{
	YM2612::YM_WRITE((PORT * 2) + 0, REG | (CHANNEL * 4));
}

inline void YM2612::YM2612_RESET()
{
	return YM2612_RESET();
}
