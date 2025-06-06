#ifndef PARSERS_H
#define PARSERS_H

#include <stdio.h>
#include "structs.h"

/**
 * Parses a line containing the initial state vector.
 * param line Input string containing the vector.
 * param qubits Number of qubits (used to determine vector size).
 * return Pointer to an array of compNumber structs.
 */
compNumber *parseInit(char *line, int qubits);

/**
 * Checks if a line contains the "#qubits" keyword.
 * param line Input string to check.
 * return 1 if "#qubits" is found, 0 otherwise.
 */
int isqubitLine(char *line);

/**
 * Checks if a line contains the "#init" keyword.
 * param line Input string to check.
 * return 1 if "#init" is found, 0 otherwise.
 */
int isinitLine(char *line);

/**
 * Parses the number of qubits from a line.
 * param line Input string containing "#qubits <number>".
 * return The number of qubits if found, 0 otherwise.
 */
int parseQubits(char *line);

/**
 * Reads the initialization file and fills the qubits, numVelem, and initArray variables.
 * param filename Name of the initialization file.
 * param qubits Pointer to store the number of qubits.
 * param numVelem Pointer to store the number of vector elements.
 * param initArray Pointer to the array of compNumber structs.
 */
void read_InitFile(char *filename, int *qubits, int *numVelem, compNumber **initArray);

/**
 * Reads the circuit file, fills the ordineArray and ordineArrayLen, and parses gate definitions.
 * param filename Name of the circuit file.
 * param numVelem Number of vector elements (matrix size).
 * param ordineArray Pointer to the array storing the sequence of operations.
 * param ordineArrayLen Pointer to the length of ordineArray.
 */
void read_CircFile(char *filename, int numVelem, char **ordineArray, int *ordineArrayLen);

/**
 * Reads a line from a file, dynamically allocating memory as needed.
 * param toRead File pointer to read from.
 * return Pointer to the read line (must be freed by caller), or NULL on EOF.
 */
char *readLine(FILE *toRead);

/**
 * Converts an array of string tokens to a 2D array of compNumber structs.
 * param tokenArray Array of string tokens.
 * param size Number of tokens (matrix size).
 * return Pointer to a 2D array of compNumber structs.
 */
compNumber **subToken(char **tokenArray, int size);

#endif