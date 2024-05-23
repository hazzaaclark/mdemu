# COPYRIGHT (C) HARRY CLARK 2024
# SEGA MEGA DRIVE EMULATOR

68000FILES 			=		68000.c opcode.c
MDFILES 			=		main.c md.c psg.c vdp.c ym2612.c
TARGET 				= 		mdemu

EXE					=
EXEPATH				=		./

.CFILES				= 		$(68000FILES) $(MDFILES)
.OFILES				=		$(.CFILES:%.c=%.o)

CC 					= 		gcc
WARNINGS 			= 		-std=c99 -Wall -Wextra -Wno-int-conversion
CFLAGS				=		$(WARNINGS)

all: $(EXEPATH)$(EXE)

$(EXEPATH)$(EXE): $(OFILES)
	$(CC) $(OFILES) -o $(EXEPATH)$(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES) $(EXEPATH)$(EXE)
