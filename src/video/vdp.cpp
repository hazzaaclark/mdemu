/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONALITY OF THE VIDEO DISPLAY PORT OF THE MEGA DRIVE */
/* TAKING INTO ACCOUNT THE INTRICACIES OF THE SYSTEM THROUGH VARIOUS PIECES OF DOCUMENTATION */

/* DOCUMENTATION INCLUDES: */

/* https://wiki.megadrive.org/index.php?title=VDP */

/* NESTED INCLUDES */

#include "68000.h"
#include "vdp.h"
#include "common.h"

/* CREATE AND ALLOCATE MEMORY ON THE HEAP FOR THE VDP */

static VDP* VDP_MAKE_INSTANCE(MD* MD)
{
	calloc(1, sizeof(VDP));
}

static void VDP_INIT(VDP* VDP)
{
	VDP_REGISTERS::DISPLAY_HEIGHT* HEIGHT;
	HEIGHT += VDP_DISPLAY_HEIGHT[0];
}
