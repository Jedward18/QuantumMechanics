
# Makefile for the project
# This Makefile compiles the source files and links them into an executable named 'app'
all: app

app: main.o parsers.o hashing.o swap.o
	gcc -o app main.o parsers.o hashing.o swap.o

main.o: main.c
	gcc -c main.c

parsers.o: parsers.c
	gcc -c parsers.c

hashing.o: hashing.c
	gcc -c hashing.c

swap.o: swap.c
	gcc -c swap.c

clean:
	rm -rf *o app


