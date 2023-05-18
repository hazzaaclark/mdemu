/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONALITY OF THE VIDEO DISPLAY PORT OF THE MEGA DRIVE */
/* TAKING INTO ACCOUNT THE INTRICACIES OF THE SYSTEM THROUGH VARIOUS PIECES OF DOCUMENTATION */

/* DOCUMENTATION INCLUDES: */

/* https://wiki.megadrive.org/index.php?title=VDP */
/* http://md.railgun.works/index.php?title=VDP */

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

typedef struct VDP_ARCHITECTURE
{
	static U8* VRAM[0x10000];
	static U16* VSRAM[0x40];
	static U16* CRAM[0x40];
	static U8* REGS[0x20];
	static U16* REGISTER_ADDR;
	static bool HORIZONTAL_INTERUPT();

	static U32 SPRITE_OVERFLOW;
	static U32 LINE_INTERRUPT;
	static U32 VERTICAL_COUNTER;
	static U32 HORIZONTAL_COUNTER;
	static bool DMA_FILL();
	static bool HV_COUNTER();
	static bool VBLANK();

	static U16* STATUS_REGISTER_READ();
	static U16* DATA_PORT_READ(void);
	static U16* HV_COUNTER_READ(void);
	static U32* IRQ(U32 IRQ_LEVEL);
};

typedef struct GRAPHICS{};

VOID_FUNCTION(VDP_INIT);
VOID_FUNCTION(VDP_SCANLINE);
VOID_FUNCTION(VDP_DMA_INIT);
VOID_FUNCTION(VDP_DMA_FILL);
VOID_FUNCTION(VDP_DMA_COPY);
VOID_FUNCTION(VDP_RESET);
VOID_FUNCTION(VDP_CONTROL_PORT);
VOID_FUNCTION(VDP_DATA_PORT);
VOID_FUNCTION(VDP_WRITE_REGISTER);


#endif
#endif
