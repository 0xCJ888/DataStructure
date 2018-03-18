CC = gcc 
INC = NN.h
OBJ = main.o NN.o 
test: ${OBJ} 
	$(CC) -o $@ ${OBJ} 
%.o: %.c 
	${CC} $< ${INC} -c 
.PHONY: clean 
clean: 
	rm -f test ${OBJ}