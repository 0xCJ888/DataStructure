CC = gcc
SRC = src/main.c src/Path.c src/Price.c
HEADER = src/Path.h src/Price.h
OUTPUT = build/MRT
CFLAG = -std=gnu99 -Wall -g
LIBDIR = lib/hiredis

all:${OUTPUT} build 

${OUTPUT}:${SRC} ${HEADER}
	$(CC) $(CFLAG) $(SRC) -o ${OUTPUT} -I${LIBDIR} -L${LIBDIR} -lhiredis

build:
	mkdir build

.PHONY: clean
clean:
	rm -rf ${OUTPUT}