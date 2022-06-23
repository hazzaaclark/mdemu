#include "config.h"
#include "types.h"
#include "tools.h"
#include "mapper.h"

#define	NUM_BANK 8
static uint16_t banks[NUM_BANK] = { 0, 1, 2, 3, 4, 5, 6,  7 };
static uint16 registration = 0;
