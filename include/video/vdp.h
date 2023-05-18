/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONALITY OF THE VIDEO DISPLAY PORT OF THE MEGA DRIVE */
/* TAKING INTO ACCOUNT THE INTRICACIES OF THE SYSTEM THROUGH VARIOUS PIECES OF DOCUMENTATION */

/* DOCUMENTATION INCLUDES: */

/* https://wiki.megadrive.org/index.php?title=VDP */

#ifndef VISUAL_DISPLAY_PORT
#define VISUAL_DISPLAY_PORT

/* NESTED INCLUDES */

#include "common.h"

/* SYSTEM INCLUDES */

#include <stdbool.h>
#include <stdio.h>

/* DEFINED DIRECTIVE FOR THE VDP'S INTERLACE FREQUENCY */
/* FOR BEING ABLE TO COMPUTE ENOUGH PIXELS PER REFRESH RATE */

#if defined(VDP_MASTER_FREQ)
#define VDP_MASTER_FREQ
#else
#define VDP_MASTER_FREQ_NTSC        53693175
#define VDP_MASTER_FREQ_PAL         53203424

#define VDP_CYCLES_PER_LINE         4096
#define VDP_FREQ_DIV                   7

#endif

/* CONSTRUCTOR FOR THE VDP'S MAIN FUNCTIONALITY */
/* THIS DEFINED DIRECTIVE INCLUDES ALL OF THE FUNCTIONALITY PERTAINING */
/* TO THE VDP'S READ AND WRITE, MEMORY, BUFFERS, ETC */

#if defined(USE_VDP)
#define USE_VDP
#else
#define USE_VDP

typedef struct VDP
{
	GRAPHICS* VDP_GRAPHICS;
	static bool LOAD_STATE(const char* LOAD);
	static bool SAVE_STATE(const char* SAVE);
};

typedef struct GRAPHICS;

typedef struct VDP_ARCHITECTURE
{
	static U8* VRAM[0x10000];
	static U16* CRAM[0x40];
};

#endif
#endif
