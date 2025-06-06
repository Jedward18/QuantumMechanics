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

    char initfilename[20];
    char circfilename[20];

    //read the name of the init file
    printf("Inserisci il nome del primo file: (ex. init-ex.txt) ");
    if(fgets(initfilename, sizeof(initfilename), stdin) == NULL){
        fprintf(stderr, "Errore nella lettura del nome del init file.\n");
        return 1;
    }
    //remove any non necessary characters
    if(strlen(initfilename) > 0 && initfilename[strlen(initfilename)-1] == '\n'){
        initfilename[strlen(initfilename)-1] = '\0';
    }

    //read the name of the circ file
    printf("Inserisci il nome del primo file: (ex. circ-ext.txt) ");
    if(fgets(circfilename, sizeof(circfilename), stdin) == NULL){
        fprintf(stderr, "Errore nella lettura del nome del init file.\n");
        return 1;
    }
    //remove any non necessary characters
    if(strlen(circfilename) > 0 && circfilename[strlen(circfilename)-1] == '\n'){
        circfilename[strlen(circfilename)-1] = '\0';
    }


    char *ordineArray = NULL;
    char **outStrArr = NULL;
    int qubits, numVelem, ordineArrayLen;
    compNumber *initArray = NULL;

    read_InitFile(initfilename, &qubits, &numVelem, &initArray);
    init_hashtable();
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
    for(int i = 0; i < numVelem; i++){
        printf("%s\n",outStrArr[i]);
    }
    return 0;


}
