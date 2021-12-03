all: build

build:
	gcc -g UnixLs.c main.c -o UnixLs
	
run: build
	./UnixLs

valgrind: build
	valgrind --leak-check=full ./UnixLs

clean:
	rm -f UnixLs
