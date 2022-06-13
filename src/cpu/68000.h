#include <vector>
#include <string>
#include <map>

#ifdef LOG
#include <stdio.h>
#endif

class Bus;

class 68000
{

public:
	68000();
	~68000();

	/// CPU Core Registers
	/// Displayed as Public so this library can be accessed by other scripts

public: 
	uint16_t a = 0x0000; /// Address Register
	uint8_t x = 0x00;  /// X Register
	uint8_t n = 0x00;  /// N Register
	uint8_t z = 0x00;  /// Z Register
	uint8_t v = 0x00;  /// V Register
	uint8_t c = 0x00;  /// C Register
	uint32_t pc = 0x000000; /// Program Counter
}
