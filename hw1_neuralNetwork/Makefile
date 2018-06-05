CC = gcc
CFLAG = -std=c99 -Wall
SRC = src/main.c src/NN.c
HEADER = src/NN.h
OUTPUT = bin/BP

all: bin build

build:${OUTPUT}

${OUTPUT}:${SRC} ${HEADER}
	$(CC) $(CFLAG) $(SRC) -o ${OUTPUT} -lm

bin:
	mkdir bin

.PHONY: clean 
clean:
	rm -r ${OUTPUT}