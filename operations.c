#include "structs.h"
#include "hashing.h"
#include <stdio.h>
#include <string.h>

/**
 * Applies a sequence of quantum gate matrices to an initial state vector.
 *
 * param ordineArray    -> Array of gate identifiers (characters) representing the circuit sequence.
 * param initArray      -> Array of compNumber structs representing the input state vector (modified in place).
 * param numVelem       -> Number of elements in the state vector (and matrix size).
 * param ordineArrayLen -> Length of the ordineArray (number of gates to apply).
 *
 * The function looks up each gate matrix by its character, applies the matrix to the current state vector,
 * and updates the state vector after each operation.
 */
void matrixVector(char *ordineArray, compNumber *initArray, int numVelem, int ordineArrayLen) {

    int last_index = ordineArrayLen - 1; // Index of the last gate to apply
    char letter;                         // Current gate identifier
    mapGates *gateStruct = NULL;         // Pointer to the gate structure from the hash table
    compNumber temp[numVelem];           // Temporary array to store intermediate results
    compNumber **gateMatrix;             // Pointer to the current gate matrix

    // Apply gates in reverse order (from last to first in the sequence)
    for (int k = last_index; k >= 0; k--) {
        letter = ordineArray[k]; // Get the current gate identifier

        gateStruct = hashtable_lookup(letter); // Look up the gate matrix by its identifier

        if (gateStruct == NULL) {
            // If the gate is not found, skip this iteration (could also handle as error)
            continue;
        }
        gateMatrix = gateStruct->matrix; // Get the matrix for the current gate

        // Matrix-vector multiplication: temp = gateMatrix * initArray
        for (int i = 0; i < numVelem; i++) {
            temp[i].cReal = 0.0;
            temp[i].cImag = 0.0;

            for (int j = 0; j < numVelem; j++) {
                // Complex multiplication and accumulation for each element
                temp[i].cReal += (gateMatrix[i][j].cReal * initArray[j].cReal) - (gateMatrix[i][j].cImag * initArray[j].cImag);
                temp[i].cImag += (gateMatrix[i][j].cReal * initArray[j].cImag) + (gateMatrix[i][j].cImag * initArray[j].cReal);
            }
        }
        // Copy the result back to initArray for the next gate application
        memcpy(initArray, temp, sizeof(compNumber) * numVelem);
    }
}