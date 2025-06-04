#ifndef HASHING_H
#define HASHING_H

#include "structs.h"

unsigned int hash(char letter);
void init_hashtable();
unsigned int hashtable_insert(mapGates *gate);
mapGates *hashtable_lookup(char *letter);
void printHashTable();

#endif