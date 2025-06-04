#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "parsers.h"
#include "structs.h"
#include "swap.h"
#include "hashing.h"
#define BUFFER_SIZE 256


int main(){

    FILE *readInit; //dichiarazione puntatore per il file
    readInit = fopen("init-ex.txt","r"); //fopen ritorna un FILE pointer se il file `e stato aperto correttamente
    char *line = NULL; //variabile per la memorizzazione/lettura di ogni riga

    FILE *readCirc;
    readCirc = fopen("circ-ex.txt","r");
    int qubits, numVelem;

    while((line = readLine(readInit)) != NULL){       
        

        if(isqubitLine(line)){
            qubits = parseQubits(line);
            numVelem = pow(2, qubits);
            
        }else if(isinitLine(line)){
            printf("Numero di qubits: %d\n\n",qubits);
            compNumber *arrayCompNum = parseInit(line, numVelem);

            for(int i = 0; i < numVelem; i++){
                printf("Real: %g, Imaginary: %g\n\n", arrayCompNum[i].cReal, arrayCompNum[i].cImag);
            }   

        }
    }




    init_hashtable();
    printHashTable();
    int i = 0;
    while((line = readLine(readCirc)) != NULL){

        char *pretoken = strchr(line, '(');  // start of the matrix part
        char *currLine = NULL;
        char *gateArray = NULL;
        int size = 0;
        int index = 0;

        if ((currLine = strstr(line, "#define")) != NULL) {
            printf("\n\nSubstring '#define' was found in the line.\n");
            printf("\nNumber of qubits: %d\n", numVelem);

            // Allocate space for gateArray (1 character in this case)
            size++;
            gateArray = realloc(gateArray, size);

            if (gateArray == NULL) {
                perror("realloc failed");
                return 1;
            }


            // Move to the gate character (e.g., X)
            while (!isupper(*currLine)) {
                currLine++;
            }

            gateArray[index] = *currLine;
            printf("Gate: %c\n", *currLine);

            // Start parsing the matrix content
            if (pretoken != NULL) {
                char *token = strtok(pretoken, "()]");  // Split on ')' or ']'
                char *tokenArray[numVelem];

                int index = 0;

                while (token != NULL) {

                    //token += strspn(token, "( ");
                    if(token != NULL && strlen(token) > 0 && !isspace(token[0])) {


                        tokenArray[index] = token;
                        index++;
                    }

                    token = strtok(NULL, "()]");
                }
                
                compNumber **gateRow = subToken(tokenArray, numVelem);
                mapGates *currMapGate = malloc(sizeof(mapGates));
                currMapGate->letter = *currLine;
                currMapGate->matrix = gateRow;
                hashtable_insert(currMapGate);
            
            } else {

                printf("Substring '#define' wasn't found in the line.\n");
            }
            free(gateArray);

        } else if((currLine = strstr(line, "#circ")) != NULL){
            printf("\n\nSubstring '#circ' was found in the line.\n");

            char *ordineArray = NULL;
            int size = 0, index = 0;

            while(*currLine != '\n'){
                
                if(isupper(*currLine)){
                    size++;
                    ordineArray = realloc(ordineArray,size);

                    if (ordineArray == NULL) {
                        perror("realloc failed");
                        return 1;
                    }

                    ordineArray[index] = *currLine;
                    index++;

                }
                currLine++;
            }

            printf("Ordine degli gates: \n");

            for(int i = 0; i < size; i++){

                printf("%c\n", ordineArray[i]);

            }

        }
        
    }

    
    printHashTable();

    fclose(readInit);
    fclose(readCirc);

    return 0;
}