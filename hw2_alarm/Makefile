
all:bin/alarm

bin/alarm:src/main.c src/setTime.c src/multiTimer.c libev/ev.o libev/event.o 
	gcc -std=c99 -o bin/alarm -I ./libev src/main.c src/setTime.c src/multiTimer.c libev/ev.o libev/event.o -lm

.PHONY: clean
clean:
	rm -rf bin/alarm
	@echo "clean done!"
