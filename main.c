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
            sprintf((*outStrArr)[i], "%g+i%g", initArray[i].cReal, initArray[i].cImag);
        }
        
    }

}

int getValidFilename(char *prompt, char *filename, size_t size) {
    printf("%s", prompt);
    if (fgets(filename, size, stdin) == NULL) {
        fprintf(stderr, "Errore nella lettura del nome del file.\n");
        return 1;
    }
    // Remove newline character if present
    if (strlen(filename) > 0 && filename[strlen(filename) - 1] == '\n') {
        filename[strlen(filename) - 1] = '\0';
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Errore: il file \"%s\" non esiste o non può essere aperto.\n", filename);
        return 1;
    }
    fclose(fp);
    return 0;
}

int main(){

    char initfilename[20];
    char circfilename[20];

    //read the name of the init file
    if (getValidFilename("Inserisci il nome del primo file: (ex. init-ex.txt) ", initfilename, sizeof(initfilename))) {
        return 1;
    }
    if (getValidFilename("Inserisci il nome del secondo file: (ex. circ-ex.txt) ", circfilename, sizeof(circfilename))) {
        return 1;
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
        printf("%s",outStrArr[i]);
        printf("\n");
    }
    return 0;


}
