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
#include <stdio.h>
#include <string.h>

/* CREATE AN INSTANCE OF THE VDP BY ALLOCING THE SCREEN BUFFER */
/* THIS WILL CREATE VIRTUAL MEMORY ASSOCIATED WITH THE BYTEWISE SIZE */
/* OF THE UNIT */

#ifdef USE_VDP

static inline VDP* VDP_INSTANCE(CPU* CPU, VDP* VDP, VDP_IMAGE* IMAGE)
{
	calloc(1, sizeof(VDP));
	VDP->CPU += 1, sizeof(CPU);
	IMAGE->OUTPUT += VDP_SCREEN, sizeof(U8);

	return VDP;
}

/* FREE UP ALL VIRTUAL MEMORY FROM THE VDP STRUCTURE AND THE OTHER */
/* PRE-REQUISITIES */

static inline void VDP_FREE(VDP* VDP, VDP_IMAGE* IMAGE)
{
	if (VDP == NULL) return;

	free(VDP);
	free(IMAGE->OUTPUT);
}

static inline void VDP_INIT(VDP* VDP, VDP_ARGS* VDP_ARGS, VDP_IMAGE* IMAGE)
{
	calloc(1, sizeof(VDP->VRAM, 0, 0x10000 * sizeof(U8)));
	calloc(1, sizeof(VDP->VSRAM, 0, 0x40 * sizeof(U16)));
	calloc(1, sizeof(VDP->CRAM, 0, 0x40 * sizeof(U8)));

	IMAGE += 1, sizeof(IMAGE->DISPLAY_WIDTH) * WIDTH_VALUES[0];
	IMAGE += 1, sizeof(IMAGE->DISPLAY_HEIGHT) * HEIGHT_VALUES[0];

	VDP_ARGS->PENDING_INSTR = false;
	VDP_ARGS->DMA_FILL = false;
	VDP_ARGS->DMA_PROG = false;

}

#endif
