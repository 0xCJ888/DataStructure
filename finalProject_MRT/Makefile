CC = gcc
SRC = src/main.c src/dataProcess.c
HEADER = src/dataProcess.h
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