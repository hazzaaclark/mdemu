#include "ym2612.h"

YM2612::YM2612()
{

}

static void WRITE_REG(uint16_t PORT, uint8_t REG, uint8_t CHANNEL, uint8_t VALUE)
{
	YM2612::YM_WRITE((PORT * 2) + 0, REG | (CHANNEL * 4));
	YM2612::YM_WRITE((PORT * 2) + 1, VALUE);
}

static void WRITE_CHANNEL_REG(uint16_t PORT, uint8_t REG, uint8_t CHANNEL, uint8_t VALUE)
{
	YM2612::YM_WRITE((PORT * 2) + 0, REG | CHANNEL);
	YM2612::YM_WRITE((PORT * 2) + 1, VALUE);
}

inline void YM2612::YM_RESET()
{
	uint16_t PORT{}; 
	uint16_t CHANNEL{};
	uint16_t BUS;


	/* DISABLE TIMER INTERRUPT */
	
	YM_WRITE(0, 0x22);
	YM_WRITE(1, 0X00);

	/* DISBALE DAC ARCHITECTURE */

	YM_WRITE(0, 0x2B);
	YM_WRITE(1, 0x00);

	/* FOR LOOPS TO GO THROUGH EACH ITERATION OF THE IO */
	/* TO CARRY OUT SPECIFIC AUDIO OPERATIONS */

	for (int p = 0; p < 1; p++)
	{
		for (int c = 0; c < 3; c++)
		{
			WRITE_REG(PORT, CHANNEL, 0X30, 0X00);
			WRITE_REG(PORT, CHANNEL, 0X40, 0X7F);
		}
	}
}
