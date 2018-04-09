
all:bin/alarm

bin/alarm:src/main.c src/setTime.c src/multiTimer.c lib/libev.a
	gcc -std=c99 -o bin/alarm -I ./lib src/main.c src/setTime.c src/multiTimer.c lib/libev.a -lm

.PHONY: clean
clean:
	rm -rf bin/alarm
	@echo "clean done!"
