
CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c11

all: sync_car

sync_car: sync_car.c sync_car.h sync_car-runner.c
	$(CC) $(CFLAGS) -o sync_car sync_car.c sync_car-runner.c

clean:
	rm -f sync_car

.PHONY: all clean
