CC = gcc
SRC = src/main.c src/card.c src/player.c
HEADER = src/card.h src/player.h
OUTPUT = bin/big2
CFLAG = -std=c99 -Wall
LIBDIR = lib/hiredis


all:bin build 

build:${OUTPUT}

${OUTPUT}:${SRC} ${HEADER}
	$(CC) $(CFLAG) $(SRC) -o ${OUTPUT} -I${LIBDIR} -L${LIBDIR} -lhiredis -D _BSD_SOURCE

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf ${OUTPUT}