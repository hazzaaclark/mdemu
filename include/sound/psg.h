/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY OF THE PSG */
/* THE PSG GOVERNS THE ARRANGEMENT OF SOUND EFFECTS IN CONJUNCTION */
/* WITH THE FUNCTIONALITY OF THE YM2612 TO COMPOSE SOUNDS AND MUSIC */

#ifndef PSG
#define PSG

/* NESETD INCLUDES */

#include "common.h"

/* SYSTEM INCLUDES */

#include <math.h>
#include <malloc.h>
#include <stddef.h>

#if defined(USE_PSG)
#define USE_PSG
#else
#define USE_PSG

#define     PSG_TYPE_PERIODIC       0
#define     PSG_TYPE_WHITE          1
#define     PSG_VOLUME              0x10

typedef struct PSG_BASE
{
    bool TONE_DISABLED[3];
    bool NOISE_DISABLED;
    bool VOLUME_CONTROL;
    S16 VOLUME[PSG_VOLUME][2];

    union STATE
    {
        U16* PHASE_COUNT;
        U16* PHASE_COUNT_MASTER;
        U8* ATTENUATION;
        U8* OUTPUT;

        U8* CHANNEL;
        U8* FAKE_OUTPUT_LO;
        U8* FAKE_OUTPUT_HI;
        U8* FREQUENCEY;
        U16* SHIFT;

    } STATE;

    struct PSG_TONE* TONES[3];

} PSG_BASE;

void PSG_CONST_INIT(const PSG_BASE* PSG_BASE);
void PSG_STATE_INIT(const PSG_BASE* PSG_BASE, S16* BUFFER, size_t* TOTAL_SAMPLES);
void PSG_UPDATE(const PSG_BASE* PSG_BASE);
void PSG_UPDATE_INSTR(PSG_BASE* PSG_BASE, U8* INSTRUCTION);

#endif

#endif