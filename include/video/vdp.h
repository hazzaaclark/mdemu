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

#define VDP_PAL 1
#define VDP_NTSC

#define REGS U8[0x20]
#define REG5_H40_MODE               U32
#define REG0_HV_LATCH               BIT(REGS[0], 1) 1
#define REG0_LINE_IRQ               BIT(REGS[0], 4) 4
#define REG1_PAL_MODE               BIT(REGS[1], 3) 3
#define REG1_DMA_ENABLED            BIT(REGS[1], 4) 4
#define REG1_VBLANK_IRQ             BIT(REGS[1], 5) 5
#define REG1_DISP_ENABLED           BIT(REGS[1], 6) 6
#define REG2_NAMETABLE_A            BIT(REGS[2], 3, 3) << 13 13
#define REG3_NAMETABLE_W            BIT(REGS[3], 1, 5) << 11 11
#define REG4_NAMETABLE_B            BIT(REGS[4], 0, 3) << 13 13
#define REG5_SAT_ADDRESS            BIT(REGS[5] & REG5_H40_MODE ? 0x7E : 0x7F)) 0x7E : 0x7F
#define REG5_SAT_SIZE               BIT(REGS[5], REG5_H40_MODE ? (1 << 10) : (1 << 9)) 1 << 10 : 1 << 9
#define REG10_LINE_COUNTER          BIT(REGS[10], 0, 8) 8 
#define REG12_H40_MODE              BIT(REGS[12], 0) 12 
#define REG15_DMA_INCREMENT         BIT(REGS[15]) 15
#define REG19_DMA_LENGTH            BIT(REGS[19] || (REGS[20] << 8)) 8
#define REG23_DMA_TYPE              BIT(REGS[23], 6, 2) 2

#endif

#if defined(VDP_MASTER)
#define VDP_MASTER
#else
#define VDP_MASTER

typedef struct VDP
{
	GRAPHICS* VDP_GRAPHICS;
	static bool LOAD_STATE(const char* LOAD);
	static bool SAVE_STATE(const char* SAVE);
};

typedef struct VDP_ARC
{
	static U8* VRAM[0x10000];
	static U16* VSRAM[0x40];
	static U16* CRAM[0x40];
	static U16* REGISTER_ADDR;
	static bool HORIZONTAL_INTERUPT();

	static U32 SPRITE_OVERFLOW;
	static U32 LINE_INTERRUPT;
	static U32 VERTICAL_COUNTER;
	typedef U32 HORIZONTAL_COUNTER;
	static bool DMA_FILL();
	typedef bool HV_COUNTER();
	static bool VBLANK();

	static U16* STATUS_REGISTER_READ();
	static U16* DATA_PORT_READ(void);
	static U16* HV_COUNTER_READ(void);
	static U32* IRQ(U32 IRQ_LEVEL);
	typedef U32 VDP_CYCLES;
	typedef U32 VDP_PIXEL_CLOCK;
};

typedef struct GRAPHICS{};

#endif

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
