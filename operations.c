#include "structs.h"
#include "hashing.h"
#include <stdio.h>
#include <string.h>



void matrixVector(char *ordineArray, compNumber *initArray, int numVelem, int ordineArrayLen) {
    //have the vin
    /*
    1) get the first gate in the vicinity of vin
    2) look it up in the hashtable
    3) get the gate
    4) do the algorithm
    */
    printf("START OPERATIONS!!!!\n");
    int last_index = ordineArrayLen-1;
    char letter;
    mapGates *gateStruct = NULL;
    compNumber temp[numVelem];
    compNumber **gateMatrix;

    printf("PRE FOR LOOP, LAST INDEX: %d\n", last_index);
    for(int k = last_index; k >= 0; k--){
        printf("Inniest Loop\n");
        letter = ordineArray[k];
        
        gateStruct = hashtable_lookup(letter);
             
        if (gateStruct == NULL) {
            printf("Gate for letter '%c' not found!\n", letter);
            continue; // or handle the error as needed
        }
        gateMatrix = gateStruct->matrix;
        printf("Letter: %c\n", letter);
        
        //row of the matrix is the row of the result in our case is i
        //column of tha matrix is the row of the vin in our case is j
        for(int i = 0; i < numVelem; i++){
            temp[i].cReal = 0.0;
            temp[i].cImag = 0.0;

            for(int j = 0; j < numVelem; j++){
                temp[i].cReal += (gateMatrix[i][j].cReal * initArray[j].cReal) - (gateMatrix[i][j].cImag * initArray[j].cImag);
                temp[i].cImag += (gateMatrix[i][j].cReal * initArray[j].cImag) + (gateMatrix[i][j].cImag * initArray[j].cReal);
                
            }
            
        }
        printf("I AM HERE\n");
        //copy the result in the initArray
        memcpy(initArray, temp, sizeof(compNumber) * numVelem);

    }

    printf("OPERATIONS FINISHEDD!!!!!!!!");
    
    

}