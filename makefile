# COPYRIGHT (C) HARRY CLARK 2024
# SEGA MEGA DRIVE EMULATOR

CC = gcc
CFLAGS = -std=c90 -Wall -Wextra

SRCS = 68000.c instruction.c vdp.c psg.c
OBJS = $(SRCS:.c=.o)

TARGET = mdemu

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
