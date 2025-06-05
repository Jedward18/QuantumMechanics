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

void convertToStr(char ***outStrArr, compNumber *initArray, int numVelem){
    

    *outStrArr = realloc(*outStrArr, numVelem * (sizeof(char*)));
    for(int i = 0; i < numVelem; i++){
        (*outStrArr)[i] = malloc(15);
        if(initArray[i].cImag < 0){
            sprintf((*outStrArr)[i], "%g-i%g", initArray[i].cReal, -initArray[i].cImag);
        }else{
            sprintf((*outStrArr)[i], "%g+i%g\n", initArray[i].cReal, initArray[i].cImag);
        }
        
    }

}

int main(){

    char *initfilename = "init-ex.txt";
    char *circfilename = "circ-ex.txt";
    char *ordineArray = NULL;
    char **outStrArr = NULL;
    int qubits, numVelem, ordineArrayLen;
    compNumber *initArray = NULL;

    read_InitFile(initfilename, &qubits, &numVelem, &initArray);
    init_hashtable();
    //printHashTable();
    read_CircFile(circfilename, numVelem, &ordineArray, &ordineArrayLen);   
    printHashTable();

    printf("ORDINE MATRICI: ");
    for(int i = 0; i < ordineArrayLen; i++){
        printf(" %c ",ordineArray[i]);
    }

    printf("\n#INIT CONTENT: \n");
    for(int i = 0; i < numVelem; i++){
        printf("Real: %g, Imaginary: %g\n\n", initArray[i].cReal, initArray[i].cImag);
    }


    matrixVector(ordineArray, initArray, numVelem, ordineArrayLen);
    convertToStr(&outStrArr, initArray, numVelem);
    printf("\nVFIN OUTPUT: \n");
    /*
    for(int i = 0; i < numVelem; i++){
        printf("Real: %g, Imaginary: %g\n\n", initArray[i].cReal, initArray[i].cImag);
    */
    for(int i = 0; i < numVelem; i++){
        printf("%s\n",outStrArr[i]);
    }
    return 0;


}
