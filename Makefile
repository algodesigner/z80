build:
	gcc -g -o main console.c z80.c main.c
clean:
	rm -rf main
all: clean build
