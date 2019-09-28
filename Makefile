build:
	gcc -o main console.c cpu.c main.c
clean:
	rm -rf main sl
all: clean build
