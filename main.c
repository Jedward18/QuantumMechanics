#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "parsers.h"
#include "structs.h"
#include "swap.h"
#include "hashing.h"
#include "operations.h"



int main(){

    char *initfilename = "init-ex.txt";
    char *circfilename = "circ-ex.txt";
    char *ordineArray = NULL;
    int qubits, numVelem, ordineArrayLen;
    compNumber *initArray = NULL;

    read_InitFile(initfilename, &qubits, &numVelem, &initArray);
    init_hashtable();
    //printHashTable();
    read_CircFile(circfilename, numVelem, &ordineArray, &ordineArrayLen);   
    printHashTable();

    for(int i = 0; i < ordineArrayLen; i++){
        printf("Ordine array: %c\n",ordineArray[i]);
    }

    for(int i = 0; i < numVelem; i++){
        printf("Real: %g, Imaginary: %g\n\n", initArray[i].cReal, initArray[i].cImag);
    }
    matrixVector(ordineArray, initArray, numVelem, ordineArrayLen);
    
    return 0;

    // to make the multiplications
    /*
    i need the list of the letters
    i need vin
    i need functions for addition and moltiplication
    */

}
