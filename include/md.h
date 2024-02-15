/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

/* THIS FILE PERTAINS TOWARDS THE MAIN FUNCTIONALITY OF THE CONSOLE */
/* IN CONJUNCTION WITH THE METHODS ESTABLISHED IN THE CPU'S HEADER FILE */

#ifndef MEGA_DRIVE
#define MEGA_DRIVE

/* NESTED INCLUDES */

#include "68000.h"
#include "common.h"

/* SYSTEM INCLUDES */

#include <stdio.h>
#include <stdbool.h>

#if defined(USE_MD)
#define USE_MD
#else
#define USE_MD

#define     SYSTEM_MD           0x80        // THE TYPICAL ENTRY POINT OF A MD CART
#define     SYSTEM_MISC         0x81
#define     ZBUFFER_MAX         256
#define     ZBANK_MAX_RAM       4096

typedef struct MD_CART
{
    U8* ROM_BASE;
    U8* ROM_ADDON;
    U8 CARTRIDGE_REGS[4];
    U16 CARTRIDGE_RESET;
    U32 CARTRIDGE_MASK[4];
    U32 CARTRIDGE_ADDRESS[4];
    U32 ROM_SIZE;

    unsigned(*TICK_TIMER)(unsigned ADRRESS);
    unsigned(*REGISTER_READ)(unsigned ADDRESS);
    void(*REGISTER_WRITE)(unsigned ADDRESS, unsigned DATA);

} MD_CART;

typedef struct MD
{
    MD_CART* MD_CART;
    U8* BOOT_ROM[0x800];
    U8* BOOT_RAM[0X10000];
    U8 ZRAM[0x2000];
    U8 ZSTATE;
    U8 SYSTEM_BIOS;
    U32* ZBANK[ZBANK_MAX_RAM];
    U8 MEMORY_CUR_PAGE;
    U8 TMSS[4];
    U8* SYSTEM_TYPE;

} MD; 

typedef enum MD_RESET_MODE
{
    MODE_SOFT,
    MODE_HARD,
    NONE,

} MD_RESET_MODE;



void MD_INIT(void);
void MD_RESET(void);
void MD_ADDRESS_BANK_WRITE(unsigned DATA);
void MD_ADDRESS_BANK_READ(void);
U32(*MD_BANKSWITCH(unsigned int VALUE));
void MD_BUS_REQ(unsigned STATE, unsigned CYCLES);
void MD_CART_INIT(void);
void MD_CARD_RESET(int const RESET_TYPE);
S32(*MD_CART_CONTEXT(U8* STATE))(void);

#endif

#endif
