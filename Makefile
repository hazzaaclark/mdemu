# COPYRIGHT (C) HARRY CLARK 2024
# SEGA MEGA DRIVE EMULATOR

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

SRCS = 68000.c md.c vdp.c psg.c ym2612.c
OBJS = $(SRCS:.c=.o)

TARGET = mdemu

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
