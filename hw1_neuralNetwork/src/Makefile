CC = gcc 
INC = NN.h
OBJ = NN.o main.o

all: BP

BP: ${OBJ} 
	$(CC) -o $@ ${OBJ} -lm
%.o: %.c 
	${CC} $< ${INC} -c 

.PHONY: clean 
clean:
	rm -r ${OBJ} ${INC}.gch