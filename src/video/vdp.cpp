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

/* INITALISE THE MAIN COMPONENT OF THE VDP AND ALL OF THE REQUISITIES THAT */
/* FOLLOW WITH IT */

/* THIS IS THROUGH ALLOCATING MEMORY PROPORTIONAL TO THE SIZE FO THE VARIABLE */
/* INSIDE OF THE STRUCTURE AMONGST OTHER MEANS OF CALCULATING THE SIZEOF THE */
/* INSTANCE BY SETTING THEIR CORRESPONDING ARGS */

static inline void VDP_INIT(VDP* VDP, VDP_ARGS* VDP_ARGS, VDP_IMAGE* IMAGE)
{

    #ifdef USE_DISPLAY_ARGS

	calloc(1, sizeof(VDP->VRAM, 0, 0x10000 * sizeof(U8)));
	calloc(1, sizeof(VDP->VSRAM, 0, 0x40 * sizeof(U16)));
	calloc(1, sizeof(VDP->CRAM, 0, 0x40 * sizeof(U8)));

	IMAGE += 1, sizeof(IMAGE->DISPLAY_WIDTH) * WIDTH_VALUES[0];
	IMAGE += 1, sizeof(IMAGE->DISPLAY_HEIGHT) * HEIGHT_VALUES[0];

	VDP_ARGS->PENDING_INSTR = false;
	VDP_ARGS->DMA_FILL = false;
	VDP_ARGS->DMA_PROG = false;
	VDP_ARGS->HBLANK_PROG = false;
	VDP_ARGS->VBLANK_PROG = false;
	VDP_ARGS->VBLANK_PENDING = false;

	VDP_H_COUNTER(0);
	VDP_V_COUNTER(0);
	VDP_HBLANK_COUNTER(0);
	VDP_VBLANK_COUNTER(2);

    #endif

}

/* CREATE AN INSTANCE OF THE DMA READ DATA SCHEMA */
/* TAKING INTO L0-L7 AND H0-H7 BITS WHICH DETERMINE THE BIT SOURCE */

/* SEE DMA LENGTH: https://md.railgun.works/index.php?title=VDP#DMA */

static const U16* VDP_READ_DATA(VDP* VDP, VDP_ARGS* VDP_ARGS, U16* ACCESS_VALUE)
{
	VDP_ARGS->PENDING_INSTR = false;

	/* THIS SWITCH CASE WILL TAKE INTO ACCOUNT THE 16 BITWISE LENGTH */
	/* OF THE DMA LENGTH REGISTER AND DETERMINE WHICH INSTANCE OF THE VDP */
	/* THE DMA WILL ACCESS; FROM THE PROVIDED HIGH AND LOW BITS */

    #ifdef USE_DMA_READ

	switch (VDP->RW_ACCESS & 0xF)
	{

	case VDP_READ_VRAM:
		ACCESS_VALUE += VDP->VRAM[VDP->RW_ACCESS_ADDR] << 8 | VDP->VRAM[VDP->RW_ACCESS_ADDR + 1];
		break;

	case VDP_READ_VSRAM:
		ACCESS_VALUE += VDP->VSRAM[VDP->RW_ACCESS_ADDR >> 1 & 0x3F];
		break;

	case VDP_READ_CRAM:
		ACCESS_VALUE += VDP->CRAM[VDP->RW_ACCESS_ADDR >> 1 & 0x3F];
		break;

	default:
		printf("Inapplicable Access Mode\n");
		break;
	}

	VDP->RW_ACCESS_ADDR += VDP->AUTO_INCREMENT;
	return ACCESS_VALUE;

    #endif
}

/* CREATE AN INSTANCE OF THE DMA WRITE DATA SCHEMA */
/* THROUGH THE DMA'S LENGTH AND FILL FUNCTIONS TO DETERMINE */
/* THE LOW (L0-L7) TO HIGH (H0-H7) BITS ON THE DMA REGISTER */

static inline void VDP_WRITE(VDP* VDP, VDP_ARGS* VDP_ARGS, U16* ACCESS_VALUE)
{
	switch (VDP->RW_ACCESS & 0xF)
	{

	case VDP_WRITE_VRAM:
		VDP->VRAM[VDP->RW_ACCESS_ADDR] += 1, sizeof(BYTE_HI(ACCESS_VALUE));
		VDP->VRAM[VDP->RW_ACCESS_ADDR ^ 1] = 1, sizeof(BYTE_LO(ACCESS_VALUE));
		VDP->RW_ACCESS_ADDR += VDP->AUTO_INCREMENT;
		break;


	case VDP_WRITE_VSRAM:
		VDP->VSRAM[VDP->RW_ACCESS_ADDR >> 1 & 0x3F] += 1, sizeof(BYTE_HI(ACCESS_VALUE));
		VDP->RW_ACCESS_ADDR += VDP->AUTO_INCREMENT;
		break;


	case VDP_WRITE_CRAM:
		VDP->CRAM[VDP->RW_ACCESS_ADDR >> 1 & 0x3F];
		VDP->RW_ACCESS_ADDR += VDP->AUTO_INCREMENT;
		break;

	default:
		printf("Inapplicable Access Mode\n");
		break;
	}

	if (VDP_ARGS->DMA_ENABLED && VDP_ARGS->DMA_PROG)
	{
		VDP_ARGS->DMA_PROG = false;

		switch (VDP->RW_ACCESS & 0xF)
		{

		case VDP_WRITE_VRAM:
			VDP->VRAM[VDP->RW_ACCESS_ADDR] = 1, sizeof(BYTE_HI(ACCESS_VALUE));
		}
	}
}

#endif
