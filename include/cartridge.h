/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY SURROUDNING THE LOADING AND READING OF THE CARTRIDGE */

#ifndef MEGA_DRIVE_CARTRIDGE
#define MEGA_DRIVE_CARTRIDGE

/* NESTED INCLUDES */

#include "common.h"
#include "68000.h"
#include "md.h"

/* SYSTEM INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(LOAD_MD_ROM)
#define LOAD_MD_ROM
#else
#define LOAD_MD_ROM

typedef struct ROM_INFO
{
    char TYPE[18];
    char COPYRIGHT[18];
    char DOMESTIC[50];
    char INTERNATIONAL[50];
    char ROM_TYPE[4];
    char SERIAL[14];
    
    unsigned short CHECKSUM;
    unsigned int ROM_START;
    unsigned int ROM_END;
    unsigned char REGION[18];

    S16* PERIPHERALS;

} ROM_INFO;

#define             ROM_CONSOLE_TYPE            ROM_INFO_BASE->TYPE
#define             ROM_COPYRIGHT               ROM_INFO_BASE->COPYRIGHT
#define             ROM_DOMESTIC_NAME           ROM_INFO_BASE->DOMESTIC
#define             ROM_INTERNATIONAL_NAME      ROM_INFO_BASE->INTERNATIONAL
#define             ROM_TYPE                    ROM_INFO_BASE->ROM_TYPE
#define             ROM_SERIAL_NO               ROM_INFO_BASE->SERIAL
#define             ROM_CHECKSUM                ROM_INFO_BASE->CHECKSUM
#define             ROM_START                   ROM_INFO_BASE->ROM_START
#define             ROM_END                     ROM_INFO_BASE->ROM_END
#define             ROM_REGION                  ROM_INFO_BASE->REGION
#define             ROM_EXT                     ROM_INFO_BASE->PERIPHERALS

ROM_INFO* ROM_INFO_BASE;

#endif
#endif