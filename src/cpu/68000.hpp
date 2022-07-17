#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <stdio.h>

class Bus;

class 68000
{

public:
	68000();
	~68000();

	/// CPU Core Registers
	/// Displayed as Public so this library can be accessed by other scripts

public:
	uint32_t a = 0x000000; /// Address Register
	uint8_t indexRegister = 0x00;  /// X Register
	uint8_t negativeFlag = 0x00;  /// N Register
	uint8_t zeroFlag = 0x00;  /// Z Register
	uint8_t overflowFlag = 0x00;  /// V Register
	uint8_t carryOp = 0x00;  /// C Register
	uint32_t pc = 0x000000; /// Program Counter

	
};
