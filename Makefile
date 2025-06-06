# Makefile for the project
# This Makefile compiles the source files and links them into an executable named 'app'

CC := gcc

all: app

app: main.o parsers.o hashing.o swap.o operations.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *o app


