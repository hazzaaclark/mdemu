#include "bus.h"
#include <vector>

Bus:Bus()
{
	cpu.ConnectBus(this);
}

Bus:~Bus()
{
}

static void Bus::cpuWrite(uint16_t bus_addr, uint16_t bus_data)
{
	if (cart->cpuWrite(bus_addr, bus_data))
	{

	}
	else if (bus_addr >= 0x0000)
	{

	}
}
