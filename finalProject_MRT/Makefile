CC = gcc
SRC = src/main.c src/dataProcess.c
HEADER = src/dataProcess.h
OUTPUT = bin/MRT
CFLAG = -std=c99 -Wall

all:bin build 

build:${OUTPUT}

${OUTPUT}:${SRC} ${HEADER}
	$(CC) $(CFLAG) $(SRC) -o ${OUTPUT}

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf ${OUTPUT}