#include "structs.h"
#include <stdio.h> 
#include <string.h>

#define TABLE_SIZE 50
mapGates *hashtable[TABLE_SIZE];

/**
 * Hash function for gate letters.
 * param letter Character representing the gate.
 * return Hash value (index in the table).
 */
unsigned int hash(char letter){
    unsigned int hashvalue = letter;
    hashvalue = (hashvalue + 1) % TABLE_SIZE; // Simple hash: ASCII value + 1, modulo table size
    return hashvalue;
}

/**
 * Initializes the hash table by setting all entries to NULL.
 */
void init_hashtable(){ 
    // Set all table entries to NULL (empty)
    for(int i = 0; i < TABLE_SIZE; i++){
        hashtable[i] = NULL;
    }
}

/**
 * Inserts a gate into the hash table.
 * param gate Pointer to the mapGates struct to insert.
 * return 1 on success, 0 if gate is NULL.
 */
unsigned int hashtable_insert(mapGates *gate){
    if(gate == NULL) return 0;
    int index = hash(gate->letter);
    // Insert at the beginning of the linked list for this index
    gate->next = hashtable[index];
    hashtable[index] = gate;
    return 1;
}

/**
 * Looks up a gate in the hash table by its letter.
 * param letter Character representing the gate.
 * return Pointer to the mapGates struct if found, NULL otherwise.
 */
mapGates *hashtable_lookup(char letter){
    int index = hash(letter);
    mapGates *temp = hashtable[index];
    // Traverse the linked list at this index
    while(temp != NULL && temp->letter != letter){
         temp = temp->next;
    }
    return temp;
}

/**
 * Prints the contents of the hash table for debugging.
 */
void printHashTable(){
    printf("--START--\n");
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hashtable[i] == NULL){
            printf("\t%i\t--\n",i);
        }else {
            printf("\t%i\t ",i);
            mapGates *temp = hashtable[i];
            // Print all gates in the linked list at this index
            while(temp != NULL){
                printf("%c - ", temp->letter);
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("--END---\n");
}
