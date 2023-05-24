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

#include "68000.h"
#include "common.h"
#include "instruction.h"

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
#define VDP_MASTER_CYCLES                  4

#define VDP_CYCLES_PER_LINE             4096
#define VDP_FREQ_DIV                       7

#endif

/* CONSTRUCTOR FOR THE VDP'S MAIN FUNCTIONALITY */
/* THIS DEFINED DIRECTIVE INCLUDES ALL OF THE FUNCTIONALITY PERTAINING */
/* TO THE VDP'S READ AND WRITE, MEMORY, BUFFERS, ETC */

#if defined(USE_VDP)
#define USE_VDP
#else
#define USE_VDP

#define VDP_PAL                            0
#define VDP_NTSC                           1

#define VDP_HBLANK_IRQ                     4
#define VDP_VBLANK_IRQ                     6

#define VDP_SCREEN_WIDTH                 320
#define VDP_SCREEN_HEIGHT                240
#define VDP_SCREEN (VDP_SCREEN_WIDTH * VDP_SCREEN_HEIGHT * 3)

#define VDP_HORIZONTAL_SCROLL
#define VDP_VERTICAL_SCROLL

#define VDP_NAMETABLE_A                    0 
#define VDP_NAMETABLE_W                    1
#define VDP_NAMETABLE_B                    2

#define VDP_HORIZONTAL_SCROLL
#define VDP_VERTICAL_SCROLL

#define VDP_H_COUNTER
#define VDP_V_COUNTER 
#define VDP_HBLANK_COUNTER 
#define VDP_VBLANK_COUNTER 

typedef struct VDP
{
	static S32 REMAINING_CYCLES;
	static U32 CLOCK_SPEED;
	static U8 VRAM[0x10000];
	static U8 VSRAM[0x40];
	static U8 CRAM[0x40];
	static U32 RW_ACCESS;
	static U16 RW_ACCESS_ADDR;
	static U16 DMA_LENGTH;
	static U16 DMA_SOURCE_LOW;
	static U8 DMA_SOURCE_HIGH;
	static U32 DMA_TYPE;
	static U8 REG_VALUES[0x18];
	static U32 AUTO_INCREMENT;

	CPU* CPU;
};

typedef struct VDP_ARGS : VDP
{
	static bool PENDING_INSTR;
	static bool DMA_ENABLED;
	static bool DMA_FILL;
	static bool DMA_PROG;
	static bool HBLANK_IRQ;
	static bool VBLANK_IRQ;
	static bool HBLANK_PROG;
	static bool VBLANK_PROG;
	static bool VBLANK_PENDING;
	static bool HV_COUNTER;
};

typedef struct VDP_IMAGE
{
	static U8* DISPLAY_HEIGHT;
	static U8* DISPLAY_WIDTH;
	static U8* PLANE_WIDTH;
	static U8* PLANE_HEIGHT;
	static U32 SPRITE_TABLE;
	static U8 HBLANK_INTERLACE;
	static U8* OUTPUT;
};

#endif

#if defined(USE_DMA)
#define USE_DMA
#else
#define USE_DMA_READ

#define VDP_READ_VRAM 0
#define VDP_READ_VSRAM 4
#define VDP_READ_CRAM 8

#define USE_DMA_WRITE

#define VDP_WRITE_VRAM 1
#define VDP_WRITE_VSRAM 3
#define VDP_WRITE_CRAM 5

#define USE_DMA_FILL

#define VDP_FILL_VRAM 1
#define VDP_FILL_VSRAM 3
#define VDP_FILL_CRAM 5

#endif

/* EXTERNAL ARGS FOR DISPLAY VALUES */

#if defined(USE_DISPLAY_ARGS)
#define USE_DISPLAY_ARGS
#else
#define USE_DISPLAY_ARGS

extern "C"
{
	extern U8 HEIGHT_VALUES[] = { 28, 30 };
	extern U8 WIDTH_VALUES[] = { 32, 40 };
}

#endif


VOID_FUNCTION(VDP_INIT);
VOID_FUNCTION(VDP_FREE);
VOID_FUNCTION(VDP_SCANLINE);
VOID_FUNCTION(VDP_DMA_INIT);
VOID_FUNCTION(VDP_DMA_FILL);
VOID_FUNCTION(VDP_DMA_COPY);
VOID_FUNCTION(VDP_RESET);
VOID_FUNCTION(VDP_CONTROL_PORT);
VOID_FUNCTION(VDP_DATA_PORT);
VOID_FUNCTION(VDP_WRITE);


#endif
