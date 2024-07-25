/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY SURROUNDING THE YM2612 */
/* AND THE CORRESPODENCE ASSOCIATED WITH FM AUDIO INTEGRATION */ 

#ifndef YM2612_H
#define YM2612_H

/* NESTED INCLUDES */

#include "common.h"
#include "md.h"

/* SYSTEM INCLUDES */

#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(USE_FM_CHANNELS)
#define USE_FM_CHANNELS
#else
#define USE_FM_CHANNELS

#define         FM_SR_DIV       (6 * 6 * 4)

typedef struct YM2612
{
    struct MD* MD_CONSOLE;

    bool MASTER_CHANNEL_DISABLED[6];
    bool DAC_CHANNEL_DISABLED;
    U8 PORT;
    U32* FM_CHANNEL; 


    union STATE
    {
        S16 DAC;

        U32 STEP;
        U32 STEP_POSITION;

        U16 PHASE_BLOCK;
        U16 PHASE_KEY;
        U16 PHASE_DETUNE;
        U16 PHASE_MULTI;

    } STATE;

    union CHANNEL
    {
        bool PAN_LEFT;
        bool PAN_RIGHT;
        U16 CACHE_FREQUENCY:11;

    } CHANNEL;

    union TIMER
    {
        U32 VALUE;
        U32 COUNTER;
        bool ENABLED;

    } TIMER[];

} YM2612;

typedef struct FM_OPERATOR
{
    bool FM_AMPLIFY:1;
    U8 FM_RATE_SCALING:2;
    U8 FM_DETUNE:3;
    U8 FM_MULTI:4;
    U8 FM_SUSTAIN_LVL:4;
    U8 FM_SUSTAIN_RATE:5;
    U8 FM_ATTACK_RATE:6;
    U8 FM_TOTAL_RATE:7;

    U16 FM_ATTENUATION:10;
    U32 FM_PHASE:20;

    bool FM_POLARITY;

    union FREQUENCY
    {
        U8 BASE;
        U8 BLOCK;

    } FREQUENCY;

} FM_OPERATOR;

void YM2612_INIT(struct YM2612* YM2612);
void YM2612_PARAM_INIT(struct YM2612* YM2612);

#endif
#endif
