#ifndef STRUCTS_H
#define STRUCTS_H

/**
 * Structure representing a complex number.
 * variable cReal Real part of the complex number.
 * variable cImag Imaginary part of the complex number.
 */
typedef struct compNumberTag{
    double cReal;
    double cImag;
} compNumber;

/**
 * Structure representing a quantum gate mapping.
 * variable field letter Character identifier for the gate.
 * variable matrix Pointer to a 2D array (matrix) of compNumber structs.
 * variable next Pointer to the next mapGates struct (for hash table chaining).
 */
typedef struct mapGatesTag{
    char letter;
    compNumber **matrix;
    struct mapGatesTag *next;
} mapGates;

#endif