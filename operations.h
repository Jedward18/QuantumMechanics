#ifndef OP_H
#define OP_H

/**
 * Applies a sequence of quantum gate matrices to an initial state vector.
 * 
 * param ordineArray      Array of gate identifiers (characters) representing the circuit sequence.
 * param initArray        Array of compNumber structs representing the input state vector (modified in place).
 * param numVelem         Number of elements in the state vector (and matrix size).
 * param ordineArrayLen   Length of the ordineArray (number of gates to apply).
 */
void matrixVector(char *ordineArray, compNumber *initArray, int numVelem, int ordineArrayLen);

#endif