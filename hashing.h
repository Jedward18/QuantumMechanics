#ifndef HASHING_H
#define HASHING_H

#include "structs.h"

/**
 * Hash function for gate letters.
 * param letter Character representing the gate.
 * return Hash value (index in the table).
 */
unsigned int hash(char letter);

/**
 * Initializes the hash table by setting all entries to NULL.
 */
void init_hashtable();

/**
 * Inserts a gate into the hash table.
 * param gate Pointer to the mapGates struct to insert.
 * return 1 on success, 0 if gate is NULL.
 */
unsigned int hashtable_insert(mapGates *gate);

/**
 * Looks up a gate in the hash table by its letter.
 * param letter Character representing the gate.
 * return Pointer to the mapGates struct if found, NULL otherwise.
 */
mapGates *hashtable_lookup(char letter);

/**
 * Prints the contents of the hash table for debugging.
 */
void printHashTable();

#endif