#include "structs.h"
#include <stdio.h> 

#define TABLE_SIZE 100
mapGates *hashtable[TABLE_SIZE];


unsigned int hash(char *letter){
    
    unsigned int hashvalue =  *letter;
    hashvalue = (hashvalue + 10) % TABLE_SIZE;

    return hashvalue;

}

void init_hashtable(){ 

    //TABLE IS EMPTY
    for(int i = 0; i < TABLE_SIZE; i++){
        hashtable[i] = NULL;
    }

}

unsigned int hashtable_insert(mapGates *gate){

    if(gate = NULL) return 0;
    int index = hash(gate->letter);
    gate->next = hashtable[index]; //we are taking the gate in the table and assigning it as next for the new element
    hashtable[index] = gate; //assigning the new element (gate)



    return 1;

}


mapGates *hashtable_lookup(char *letter){
    int index = hash(letter);
    mapGates *temp = hashtable[index];

    while(temp != NULL && strcmp(temp->letter, letter) != 0){
         //until not NULL or not equals continue the iteration
         temp = temp->next;

    }

    return temp;
}


