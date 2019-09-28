build:
	gcc -o main console.c cpu.c main.c
clean:
	rm -rf main
all: clean build
