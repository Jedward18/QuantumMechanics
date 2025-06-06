#include "structs.h"
#include "hashing.h"
#include <stdio.h>
#include <string.h>



void matrixVector(char *ordineArray, compNumber *initArray, int numVelem, int ordineArrayLen) {


    int last_index = ordineArrayLen-1;
    char letter;
    mapGates *gateStruct = NULL;
    compNumber temp[numVelem];
    compNumber **gateMatrix;


    for(int k = last_index; k >= 0; k--){
        letter = ordineArray[k];
        
        gateStruct = hashtable_lookup(letter);
             
        if (gateStruct == NULL) {
     
            continue; // or handle the error as needed
        }
        gateMatrix = gateStruct->matrix;
   
        
        //row of the matrix is the row of the result in our case is i
        //column of tha matrix is the row of the vin in our case is j
        for(int i = 0; i < numVelem; i++){
            temp[i].cReal = 0.0;
            temp[i].cImag = 0.0;

            for(int j = 0; j < numVelem; j++){
                temp[i].cReal += (gateMatrix[i][j].cReal * initArray[j].cReal) - (gateMatrix[i][j].cImag * initArray[j].cImag);
                temp[i].cImag += (gateMatrix[i][j].cReal * initArray[j].cImag) + (gateMatrix[i][j].cImag * initArray[j].cReal);
                
            }
       
            
            
            //printf("Real: %g, Imaginary: %g\n\n", initArray[i].cReal, initArray[i].cImag);
            
        }
        memcpy(initArray, temp, sizeof(compNumber) * numVelem);
        
        
    }


    
    

}