#include "opcode.h"
#include <cstdint>
#include <cstdlib>

const uint32_t OPCODE_DECODER();
const uint32_t EXTRACT_INSTR(uint32_t B, uint32_t W, uint32_t L)
{
	return(B >> (32 - 1 - L)) & ((1 << (L - W + 1)) - 1);
}

inline void OPCODE::LOOKUP_OPCODE(uint32_t CODE)
{
	switch (EXTRACT_INSTR(CODE, 0, 5))
	{
	case 0x000000: OPCODE_DECODER();
		break;
	}
}
