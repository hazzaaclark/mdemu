#include "68000.h"
#include = "bus.h"

/// Initiator

68000::68000()
{
	using cpu = 68000;

	/// This is the Initialiser Table
	mem_lookup =
	{
		{ "ORI", &cpu::ORI, &cpu::CCR, 4 },{ "ORI", &cpu::ORI, &cpu::SR, 5 },
	};
}

uint8_t 68000::read(uint16_t cpu)
{
	return this.bus->read(cpu, false);
}

void 68000::write(uint16_t a, uint8_t b)
{
	this.bus->write(a, b);
}