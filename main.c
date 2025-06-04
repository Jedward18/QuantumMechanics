#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "parsers.h"
#include "structs.h"
#include "swap.h"
#include "hashing.h"



int main(){

    char *initfilename = "init-ex.txt";
    char *circfilename = "circ-ex.txt";

    int qubits, numVelem;

    read_InitFile(initfilename, &qubits, &numVelem);
    init_hashtable();
    printHashTable();
    read_CircFile(circfilename, numVelem);
    
    printHashTable();
    
    return 0;
}