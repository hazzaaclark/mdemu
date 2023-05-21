/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONALITY OF THE VIDEO DISPLAY PORT OF THE MEGA DRIVE */
/* TAKING INTO ACCOUNT THE INTRICACIES OF THE SYSTEM THROUGH VARIOUS PIECES OF DOCUMENTATION */

/* DOCUMENTATION INCLUDES: */

/* https://wiki.megadrive.org/index.php?title=VDP */
/* http://md.railgun.works/index.php?title=VDP */

/* NESTED INCLUDES */

#include "68000.h"
#include "vdp.h"
#include "common.h"

/* SYSTEM INCLUDES */

#include <assert.h>
#include <stdlib.h>

/* CREATE AN INSTANCE OF THE VDP BY ALLOCING THE SCREEN BUFFER */
/* THIS WILL CREATE VIRTUAL MEMORY ASSOCIATED WITH THE BYTEWISE SIZE */
/* OF THE UNIT */

static inline VDP* VDP_INSTANCE(CPU* CPU, VDP* VDP, VDP_IMAGE* IMAGE)
{

    #ifdef USE_VDP

	calloc(1, sizeof(VDP));
	VDP->CPU += 1, sizeof(CPU);
	IMAGE->OUTPUT += VDP_SCREEN, sizeof(U8);

    #endif
}
