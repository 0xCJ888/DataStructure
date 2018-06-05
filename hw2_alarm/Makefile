
all:bin bin/alarm

bin/alarm:src/main.c src/setTime.c src/multiTimer.c lib/libev.a bin
	gcc -std=c99 -Werror -g -o bin/alarm -DDEBUG -I ./lib src/main.c src/setTime.c src/multiTimer.c lib/libev.a -lm
bin:
	mkdir bin
	
.PHONY: clean
clean:
	rm -rf bin/alarm
	@echo "clean done!"
