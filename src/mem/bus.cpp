#include "bus.h"
#include <vector>

Bus:Bus()
{
	cpu.ConnectBus(this);
}

Bus:~Bus()
{
}

static void Bus::cpuWrite(uint16_t bus_addr, uint16_t, bus_data)
{

}
