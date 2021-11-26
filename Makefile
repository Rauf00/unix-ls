all: build

build:
	gcc -g UnixLs.c main.c -o ls
	
run: build
	./ls

valgrind: build
	valgrind --leak-check=full ./ls

clean:
	rm -f ls
