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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* DEFINED DIRECTIVE FOR THE VDP'S INTERLACE FREQUENCY */
/* FOR BEING ABLE TO COMPUTE ENOUGH PIXELS PER REFRESH RATE */

#if defined(VDP_MASTER_FREQ)
#define VDP_MASTER_FREQ
#else

#define		VDP_MAX_SCANLINE_FREQ	320
#define		VDP_MAX_SCANLINES		(240 * 2)

#endif

/* CONSTRUCTOR FOR THE VDP'S MAIN FUNCTIONALITY */
/* THIS DEFINED DIRECTIVE INCLUDES ALL OF THE FUNCTIONALITY PERTAINING */
/* TO THE VDP'S READ AND WRITE, MEMORY, BUFFERS, ETC */

#if defined(USE_VDP)
#define USE_VDP
#else
#define USE_VDP

#define		VDP_VRAM					0x10000
#define		VDP_CRAM					(4 * 16)
#define		VDP_VSRAM					[64]

#define		VDP_SPRITE_LOOKUP			1 << 1 + 2 | 1 << 1 + 1 + 2 + 4 | 1 << 4 
#define		VDP_SPRITE_DETAIL_LOOKUP	1 << 1 + 2 | 1 << 1 + 1 + 2 + 4 | 1 << 4

#define		VDP_PALETTE_MASK			0x0F
#define		VDP_COLOUR_MASK				0x3F
#define		VDP_PRIORITY_MASK			0x40
#define		VDP_NULL_MASK				0x80

#define		VDP_SHADOW_NRM				(0 << 6)
#define		VDP_SHADOW_BASE				(1 << 6)
#define		VDP_SHADOW_HIGH				(2 << 6)


#define		VDP_DMA_MODE_MEM_TO_VRAM		
#define		VDP_DMA_MODE_FILL			
#define		VDP_DMA_MODE_COPY			

#define		VDP_HSCROLL_MODE_FULL		
#define		VDP_HSCROLL_MODE_1CELL		
#define		VDP_HSCROLL_MODE_1LINE		

#define		VDP_VSCROLL_MODE_FULL
#define		VDP_VSCROLL_MODE_2CELL

#define		VDP_ACCESS_VRAM				
#define		VDP_ACCESS_VSRAM
#define		VDP_ACCESS_CRAM


typedef struct VDP_CONFIG
{
	bool SPRITES_DISABLE;
	bool WINDOW_DISABLE;
	bool SPRITE_PLANES_DISABLED[2];
};

typedef struct VDP_STATE
{
	union
	{
		bool ENABLED;
		bool PENDING;
		U8 ADDRESS_MODE_HIGH;
		U8 ADDRESS_MODE_LOW;
		U16 ADDRESS_LENGTH;

	} DMA;

	union 
	{
		bool WRITE_PENDING;
		bool READ_MODE;
		enum BUFFER;
		S16 CACHE;
		S16 INDEXING;
		S16 INCREMENT;

	} ACCESS_MODE;

	U16 PLANE_A_ADDRESS;
	U16 PLANE_B_ADDRESS;
	U16 WINDOW_ADDRESS;
	U16 SPRITE_TABLE;
	U16 HSCROLL_ADDRESS;

	bool WINDOW_ALIGN_RIGHT;
	bool WINDOW_ALIGN_BOTTOM;
	U8 WINDOW_HORI;
	U8 WINDOW_VERT;

	U16 PLANE_WIDTH;
	U16 PLANE_HEIGHT;
	U16 PLANE_WIDTH_BITMASK;
	U16 PLANE_HEIGHT_BITMASK;

	bool DISPLAY_ENABLED;
	bool VERTICAL_PLANE_ENABLED;
	bool HORI_PLANE_ENABLED;
	bool H40_ENABLED;
	bool V30_ENABLED;
	bool SHADOW_ENABLED;
	bool SUPER_SAMPLING;

	U8 BG_COLOUR;
	U8 HORI_INTERVAL;
	bool VBLANK;
};

typedef struct VDP
{
	static VDP_CONFIG* CONFIG;
	static VDP_STATE* STATE;
	static struct LOOKUP{};
};


void VDP_CONST_INIT(VDP* VDP);
void VDP_STATE_INIT(VDP* VDP);
void VDP_RENDER_SCANLINE(const VDP* VDP, U16* SCANLINE);
void SCANLINE_CALLBACK(const void* USER_DATA, U16 SCANLINE, U8* PIXELS, U16 WIDTH, U16 HEIGHT);

U16 VDP_READ(VDP* VDP);
U16 VDP_WRITE(VDP* VDP);


#endif

#endif
