/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

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
#include <stdbool.h>

#if defined(USE_PSG)
#define USE_PSG
#else
#define USE_PSG

#define     PSG_TYPE_PERIODIC       0
#define     PSG_TYPE_WHITE          1
#define     PSG_VOLUME              0x10
#define     PSG_LOOKUP_LENGTH       0x0F
#define     PSG_CHANNEL_VOLUME      4.0 * 8.0
#define     PSG_CLOCKS              240       
#define     PSG_STATE_COUNT(VALUE)      (sizeof(VALUE) / sizeof(VALUE)[0])  

typedef struct PSG_BASE
{
    bool TONE_DISABLED[3];
    bool NOISE_DISABLED;
    bool VOLUME_CONTROL;
    S16 VOLUME[PSG_VOLUME][2];
    S16 SAMPLE_BUFFER;
    UNK TOTAL_SAMPLES;

    union PSG_STATE
    {
        U16* PHASE_COUNT;
        U16* PHASE_COUNT_MASTER;
        U8* ATTENUATION;
        U8* OUTPUT;
        U16* POLARITY;
        U32* TIMESTAMP;

        U8* CHANNEL;
        U8* FAKE_OUTPUT_LO;
        U8* FAKE_OUTPUT_HI;
        U8 FREQUENCEY;
        U16* SHIFT;

        U16* COUNTDOWN;
        U16* COUNTDOWN_MASTER_CONTROL;

    } PSG_STATE;

} PSG_BASE;

void PSG_CONST_INIT(PSG_BASE* PSG_BASE);
void PSG_STATE_INIT(PSG_BASE* PSG_BASE);
void PSG_UPDATE(PSG_BASE* PSG_BASE);
void PSG_UPDATE_INSTR(PSG_BASE* PSG_BASE, U8* INSTRUCTION);
void PSG_FREE(PSG_BASE* PSG_BASE);

#endif

#endif
