/***
* This Header file is just here to carry out simple Assembly Methods and Instructions
* This might come in handy for allocating memory, rom-management, etc
*/

#ifndef ASM_H
#define ASM_H

#define VARREG_BYTE(VAR, REG)   asm("move.b, %0, %/"REG"" :: "a" (VAR) : ""REG"")
#define VARREG_WORD(VAR, REG)   asm("move.w, %0, %/"REG"" :: "a" (VAR) : ""REG"")
#define VARREG_LONG(VAR, REG)   asm("move.l, %0, %/"REG"" :: "a" (VAR) : ""REG""))

#define REGVAR_BYTE(REG, VAR)   asm("move.b, %0, %/"REG", %0" : "=a" (VAR))
#define REGVAR_WORD(REG, VAR)   asm("move.w, %0, %/"REG", %0" : "=a" (VAR)) 
#define REGVAR_LONG(REG, VAR)   asm("move.l, %0, %/"REG", %0" : "=a" (VAR))

#endif 
