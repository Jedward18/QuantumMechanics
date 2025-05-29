#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "parsers.h"
#include "structs.h"
#include "swap.h"
#define BUFFER_SIZE 256


int main(){

    FILE *readInit; //dichiarazione puntatore per il file
    readInit = fopen("init-ex.txt","r"); //fopen ritorna un FILE pointer se il file `e stato aperto correttamente
    char *line = NULL; //variabile per la memorizzazione/lettura di ogni riga

    FILE *readCirc;
    readCirc = fopen("circ-ex.txt","r");
    
    while((line = readLine(readInit)) != NULL){
        
        //printf("Line: %s", line);
        //initLine(line);
        int qubits, numVelem;
        

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

    int i = 0;
    while((line = readLine(readCirc)) != NULL){
        //printf("Linea %d: %s", i,line);

        char *pretoken = strchr(line, '(');  // start of the matrix part
        char *currChar = NULL;
        char *gateArray = NULL;
        int size = 0;
        int index = 0;
        int qubits = 2;

        if ((currChar = strstr(line, "#define")) != NULL) {
            printf("\n\nSubstring '#define' was found in the line.\n");

            // Allocate space for gateArray (1 character in this case)
            size++;
            gateArray = realloc(gateArray, size);

            if (gateArray == NULL) {
                perror("realloc failed");
                return 1;
            }

            // Move to the gate character (e.g., X)
            while (!isupper(*currChar)) {
                currChar++;
            }

            gateArray[index] = *currChar;
            printf("Gate: %c\n", *currChar);

            // Start parsing the matrix content
            if (pretoken != NULL) {
                char *token = strtok(pretoken, "()]");  // Split on ')' or ']'
                char *copyToken = NULL;
                char *tokenArray[qubits];

                int index = 0;

                while (token != NULL) {

                    //token += strspn(token, "( ");
                    if(token != NULL && strlen(token) > 0 && !isspace(token[0])) {

                        //printf("Iterazione....\n");
                        //printf("Token: %s\n", token);

                        tokenArray[index] = token;
                        index++;
                    }

                    token = strtok(NULL, "()]");
                }
                subToken(tokenArray, qubits);
            } else {

                printf("Substring '#define' wasn't found in the line.\n");
            }
            free(gateArray);
        }
        i++;
    }

    fclose(readInit);
    fclose(readCirc);

    return 0;
}







