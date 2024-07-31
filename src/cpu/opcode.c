/* COPYRIGHT (C) HARRY CLARK 2024 */

/* SEGA MEGA DRIVE EMULATOR */

/* THIS FILE PERTAINS TOWARDS THE CONJUNCTIVE FUNCTIONALITY */
/* BETWEEN THE 68000 AND Z80 - PERTAINING TOWARDS OPCODES */
/* THAT ARE USED TO DETERMINE INSTRUCTION AND EXECUTION METHODS */

/* NESTED INCLUDES */

#include "opcode.h"

#undef USE_OPCODE_DEFS

/* FINALLY, WE CAN BEGIN TO BUILD THE OPCODE TABLE BASED ON THE CORRESPONDENCE ESTABLISHED */
/* IN THE GENERATOR FUNCTION */

/* THIS DIFFERENCE BETWEEN THE TWO IS THAT THIS ONE ENCOMPASSES THE INSTRUCTION TYPES AND METHODS */
/* WHEREAS THE GENERATOR FOCUSSES MORESO ON THE INDEXXING OF SAID OPCODES */

void M68K_BUILD_OPCODE_TABLE(void)
{
    unsigned MASK_MODE = 0;
    struct OPCODE* OPCODE_HANDLER = malloc(sizeof(struct OPCODE));
    int INDEX;

    /* FOR EVERY SUBSEQUENT MASK MODE OF THE OPCODE TABLE */
    /* SORT BETWEEN THE RESPECTIVE ELEMENTS AND DISCERN THEIR CORRESPONDENCE */
    /* IN RELATION TO WHICH INSTRUCTION IS BEING USED */

    /* THIS EMPOSES THE ASSUMPTION THAT THE OPCODE'S WILL BE ALLOCATED */
    /* TO A RESPECTIVE REGISTER TO GOVERN A SPECIFIC AREA */

    switch (MASK_MODE)
    {
        case OPCODE_MASK_ILLEGAL:
            if((INDEX = 0) && INDEX < M68K_MAX_INSTR_LENGTH)
            {
                M68K_CYC_INSTRUCTION = INDEX;
            }
            break;

        case OPCODE_MASK_LOG_BIT:
            for (INDEX = 0; INDEX < 8; INDEX++)
            {
                M68K_OPCODE_INSTRUCTION = M68K_OPCODE_HANDLER;

                if(!OPCODE_HANDLER->INSTRUCTION && M68K_MAX_INSTR_LENGTH == 0)
                {
                    M68K_CYC_INSTRUCTION[0] = (M68K_CYC_INSTRUCTION[1] || M68K_OPCODE_INSTRUCTION + INDEX);
                }
            }

            break;

        case OPCODE_MASK_LOG_OR:
            for (INDEX = 0; INDEX < 0xF; INDEX++)
            {
                M68K_OPCODE_INSTRUCTION = M68K_OPCODE_HANDLER;
                M68K_CYC_INSTRUCTION[INDEX] = M68K_OPCODE_PATTERN[INDEX] | M68K_CYC_INSTRUCTION[INDEX];
            }

            break;
            
        
    default:
        for (INDEX = 0; INDEX < M68K_MAX_INSTR_LENGTH; INDEX++)
        {
            return;
        }
        break;
    }

    free(OPCODE_HANDLER);
}

/* ALL OF THE FOLLOWING OPCODE DIRECTIVES ARE A PSEUDO BITWISE REPRESENTTION */
/* BY WHICH THEY OPERATE WITH ONE ANOTHER */

/* OPCODE WORKS UNDER THE GUISE OF EVOKING A SOURCE OFFSET, THE DESITINATION OFFSET */
/* AS WELL AS THE RESULT OF THE FINAL OPERAND */

/* ALL OF THESE FUNCTIONS SERVE TO PROVIDE A BARE METAL REPRESENTATION OF THE FLAGS AND CASTING */
/* USED TO DEMONSTRATE THEIR RESPECTIVE FUNCTION */

/* SEE: https://web.njit.edu/~rosensta/classes/architecture/252software/code.pdf */

M68K_MAKE_EXCE_OP(1010, 0, _, _)
{
    M68K_EXCEPTION_1010();
}

M68K_MAKE_EXCE_OP(1111, 0, _, _)
{
    M68K_EXCEPTION_1111();
}

M68K_MAKE_OPCODE(ABCD, 8, RR, 0)
{
    int* DST = 0;
    int SRC = M68K_REG_D;
    int RES = (int)SRC + (int*)DST;

    RES = FLAG_V;

    if(FLAG_C) RES -= 0xA0;

    RES &= FLAG_V;
    RES = FLAG_N;

    RES = M68K_MASK_OUT_ABOVE_8(RES);
    RES |= FLAG_Z;
} 

M68K_MAKE_OPCODE(ABCD, 8, MM, AX7)
{
    unsigned* SRC = 0;
    unsigned* EA = 0;           
    unsigned* DST = M68K_READ_8(EA);
    unsigned RES = (int*)SRC + *(int*)DST;

    RES += *(int*)SRC + *(int*)DST;
    RES = *(unsigned*)FLAG_X = *(unsigned*)FLAG_C = (RES > 0x99) << 8;

    if(FLAG_C)
        RES -= 0xA0;

    RES = FLAG_V;
    RES = FLAG_N;

    RES = M68K_MASK_OUT_ABOVE_8(RES);
    RES |= FLAG_Z;
    
}

M68K_MAKE_OPCODE(ADD, 8, ER, D)
{
    unsigned* REG_DST = &M68K_REG_D;
    unsigned SRC = 0;
    unsigned DST = 0;
    unsigned RES = SRC + DST;

    RES = M68K_FLAG_N;
    RES = M68K_FLAG_V;
    RES = M68K_FLAG_X + *(unsigned*)M68K_FLAG_C;
    RES = *(unsigned*)M68K_FLAG_Z = M68K_MASK_OUT_ABOVE_8(RES);

    REG_DST = M68K_MASK_OUT_ABOVE_8(*REG_DST) | FLAG_Z;
}
