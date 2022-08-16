#include "ym2612.h"

static void WRITE_REG(uint16_t PORT, uint8_t REG, uint8_t CHANNEL, uint8_t VALUE)
{
	YM2612::YM_WRITE((PORT * 2) + 0, REG | (CHANNEL * 4));
	YM2612::YM_WRITE((PORT * 2) + 1, VALUE);
}

inline void YM2612::YM_RESET()
{
	return YM_RESET();
}

