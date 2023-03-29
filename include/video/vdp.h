/* Copyright(C) 2023 Harry Clark * /

/* SEGA Mega Drive Emulator */

/* THIS FILE PERTAINS TO THE MAIN FUNCTIONALITY OF THE VIDEO DISPLAY PORT OF THE MEGA DRIVE */
/* TAKING INTO ACCOUNT THE INTRICACIES OF THE SYSTEM THROUGH VARIOUS PIECES OF DOCUMENTATION */

/* DOCUMENTATION INCLUDES: */

/* https://wiki.megadrive.org/index.php?title=VDP */

#ifndef VDP
#define VDP

/* NESTED INCLUDES */

#include "common.h"

/* SYSTEM INCLUDES */

#include <stdbool.h>
#include <stdio.h>

#ifdef DEBUG
#define DEBUG_LOG(...)(__VA_ARGS__)
#else
#define DEBUG_LOG()
#endif

/* USING THE RULE OF THE NTH VALUE + 4 */
/* THIS HELPS TO CREATE THE CORRESPONDING COLOURS CHANNELS */
/* TO CREATE AN 11 BIT COLOUR VALUE */

/* DOCUMENTATION PERTAINING TO THIS */
/* https://wiki.megadrive.org/index.php?title=VDP_Palette */

#ifndef COLOUR_CHANNELS
#define COLOUR_CHANNELS

#define RED_CHANNEL(COLOUR) FRAGMENT((COLOUR), 3, 1)
#define GREEN_CHANNEL(COLOUR) FRAGMENT((COLOUR), 7, 5)
#define BLUE_CHANNEL(COLOUR) FRAGMENT((COLOUR), 11, 9)

#endif
#endif