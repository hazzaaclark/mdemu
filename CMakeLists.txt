## COPYRIGHT (C) HARRY CLARK
## 
## SEGA MEGA DRIVE EMULATOR

cmake_minimum_required(VERSION 3.18)

project(mdemu LANGAUGES C)

add_library(mdemu STATIC
        "68000.c"
        "68000.h"
        "instruction.c"
        "instruction.h"
        "opcode.h"
        "vdp.c"
        "vdp.h"
)

set_target_properties(mdemu PROPERTIES
            C_STANDARD 90
            C_STANDARD_REQUIRED NO
            C_EXTENSIONS OFF
)