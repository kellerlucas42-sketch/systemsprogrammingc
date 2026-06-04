CC=gcc
CFLAGS=-Wall -Werror -pthread

HEADERS=lib/buttons.h lib/device.h lib/display.h lib/lcd.h lib/log.h lib/colors.h lib/fonts/fonts.h lib/image.h lib/camera.h lib/client.h
COMMON_SRCS=lib/buttons.c lib/device.c lib/display.c lib/lcd.c lib/log.c lib/fonts/font8.c lib/fonts/font12.c lib/fonts/font16.c lib/fonts/font20.c lib/fonts/font24.c lib/image.c lib/camera.c lib/client.c
COMMON_OBJS=$(COMMON_SRCS:.c=.o)
BINARIES=main test

.PHONY: all clean

all: $(BINARIES)

main: main.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lbcm2835

test: test.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lbcm2835

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINARIES) $(COMMON_OBJS) main.o test.o
