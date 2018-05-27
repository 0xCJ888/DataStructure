CC = gcc
SRC = src/main.c src/card.c src/player.c
HEADER = src/card.h src/player.h
OUTPUT = bin/test
CFLAG = -std=c99 -Wall
LIBDIR = hiredis


all:build bin

build:${OUTPUT}

${OUTPUT}:${SRC} ${HEADER}
	$(CC) $(CFLAG) $(SRC) -o ${OUTPUT} -I${LIBDIR} -L${LIBDIR} -lhiredis -D _BSD_SOURCE

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/test