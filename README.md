# A Simple Quantum Circuit

> This is a simple program (Quantum Circuit in ANSI C) that simulates the behaviour of a simple Quantum Circuit. It reads definitions of Gates (square matrices) and an initial vector from text files. It prints the final state of the vector on stdout.

## File Included
- 'main.c' - Entry point of arguments (name of the two .txt files), produce an array of string (complex numbers format) for the final vector and print it

- 'parsers.c', 'parsers.h' - Functions for parsing input files and extracting circuit/state data

- 'hashing.c', 'hashing.h' - Hash table implementation for storing and retrieving gate definitions

- 'operations.c', 'operations.h' - Matrix-vector multiplication for applying gates and vector

- 'swap.c', 'swap.h' - Utility for swapping values (called in parsers.c)

- 'structs.h' - Data Structures for complex numbers and gate rappresentations

- 'Makefile' - Used for building instructions

- Example Text Files for input: 'init-ex.txt', 'circ-ex.txt', 'randominit.txt', 'randomcirc.txt'

## Features
-Uses hash table for efficient gate lookup
-Handles the product of square matrices of complex numbers by a vector of complex numbers
-Parses quantum circuit definitions and initial state vector from text files

## Input Files

- **Initial Vector State File** -> 'init-ex.txt' or 'randominit.txt' for larger input

- **Circuit Definition File** -> 'circ-ex.txt' or 'randomcirc.txt' for larger input


## User Manual

    Input parameters are provided in command line through options

    *Options*: 
    -i for 'init-ex.txt' or 'randominit.txt' for larger input
    -c for 'circ-ex.txt' or 'randomcirc.txt' for larger input

**To build:**
    make

**To Run**
    ./app -i <init_file> -c <circ_file> 
    Example: ./app -i init-ex.txt -c circ-ex.txt

**Output**
    The program prints the final state vector after doing all the operations

**Output Example**
    Vout OUTPUT:
    0.5-i0.5
    0.5+i0.5    

## Needs
- A compiler (GCC -> compatible compiler)
- Make Utility -> Build Automation Tool uses a file called Makefile


