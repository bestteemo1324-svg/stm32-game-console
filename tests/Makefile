# Unit test chay tren PC (x86), khong can kit.
# Dev 2 so huu.  Chay:  make test   (tu thu muc goc)

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g -I. -I../app/inc -I../bsp/inc -Istubs
TARGET  = build/test_game

SRC = test_game.c

all: run

build:
	mkdir -p build

$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean
