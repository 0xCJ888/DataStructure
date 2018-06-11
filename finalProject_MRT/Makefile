CC = gcc
SRC = src/main.c src/dataProcess.c
HEADER = src/dataProcess.h
OUTPUT = build/MRT
CFLAG = -std=gnu99 -Wall -g 

all:${OUTPUT} build 

${OUTPUT}:${SRC} ${HEADER}
	$(CC) $(CFLAG) $(SRC) -o ${OUTPUT} 

build:
	mkdir build

.PHONY: clean
clean:
	rm -rf ${OUTPUT}