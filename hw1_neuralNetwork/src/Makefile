CC = gcc 
INC = NN.h
OBJ = NN.o main.o

all: test clean

BP: ${OBJ} 
	$(CC) -o $@ ${OBJ} 
%.o: %.c 
	${CC} $< ${INC} -c -lm

.PHONY: clean 
clean:
	rm -r ${OBJ}