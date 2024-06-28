# COPYRIGHT (C) HARRY CLARK 2024
# SEGA MEGA DRIVE EMULATOR

68000FILES          =       68000.c opcode.c
MDFILES             =       main.c md.c psg.c vdp.c ym2612.c
TARGET              =       mdemu

EXE                 =       mdemu
EXEPATH             =       ./

CFILES              =       $(68000FILES) $(MDFILES)
OFILES              =       $(CFILES:.c=.o)

CC                  =       gcc

WARNINGS            =       -std=c99 -Wall -Wextra -Wno-int-conversion -Wno-incompatible-pointer-types 
CFLAGS              =       $(WARNINGS)

all: run

$(EXEPATH)$(EXE): $(OFILES)
	$(CC) $(OFILES) -o $(EXEPATH)$(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEPATH)$(EXE)

clean:
	rm -f $(OFILES) $(EXEPATH)$(EXE)
