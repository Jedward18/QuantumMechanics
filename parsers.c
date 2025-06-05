#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "swap.h"
#include "structs.h"
#include "hashing.h"

int isqubitLine(char *line){

    char word[] = "#qubits";

    if(strstr(line,word) != NULL){
        return 1;
    }else{
        return 0;
    }
}


int isinitLine(char *line){

    char word[] = "#init";

    if(strstr(line,word) != NULL){
        return 1;
    }else{
        return 0;
    }

}


int parseQubits(char *line){

    char word[strlen("#qubits")];
    int qubits;

    if(sscanf(line, "%s %d", word, &qubits) == 2)
        return qubits;


    return 0;


}

compNumber *parseInit(char *line, int numVelem){

    char *pretoken = strchr(line, '[');
    double real, imaginary;
    compNumber *cnumbers = malloc(numVelem * sizeof(compNumber));
    int index = 0;

    if(pretoken != NULL){
        pretoken++;

        char *token = strtok(pretoken, " ,");

        while(token && isdigit(*token)){

            char *i = strchr(token, 'i');

            if(i != NULL){

                char *j = i+1;
                while(isdigit(*j) || *j == '.'){
                    swap(i,j);
                    i++;
                    j++;
                }

            }

            sscanf(token, "%lf%lf", &real, &imaginary);
            printf("Real: %g\n", real);
            printf("Imaginary: %gi\n\n", imaginary);
            cnumbers[index].cReal = real;
            cnumbers[index].cImag = imaginary;


            //printf("%g%c%c%g\n",   a, op, im, b );
            token = strtok(NULL, " ,]");
            index++;
        }

        printf("N elem in vector: %d\n", numVelem );

    }else{

        printf("Character '[' not found in line.\n");
        
    }

    return cnumbers;

}


char *readLine(FILE *toRead){

    char *buffer = NULL;
    size_t size = 0;

    char *newLine_Found = NULL;

    do{
        //reallocate the buffer to accomodate more characters (initial allocation is 0)
        if((buffer = realloc(buffer, (size + BUFSIZ) * sizeof(char))) == NULL){
            perror("Error (message): ");
            exit(EXIT_FAILURE);         // Exit on realloc failure
        }

        //check for end-for-file (fgets == NULL return value indicates an error or an end-of-file conditionL)
        if(fgets(buffer + size, BUFSIZ, toRead) == NULL){
            return NULL;
        }

        //Search for newline character within the recent read portion
        newLine_Found = strchr(buffer + size, '\n');

    }while(!newLine_Found && (size += BUFSIZ));

    return buffer;



}


compNumber **subToken(char **tokenArray, int size) {

	compNumber **gateRow = NULL;
	char *subToken = NULL;

    gateRow = realloc(gateRow, size *sizeof(compNumber));
    for (int i = 0; i < size; ++i){
        gateRow[i] = malloc(size * sizeof(compNumber));
    }

	if (gateRow == NULL) {
		perror("malloc failed");
	}

	//print all token in the array
	for(int i = 0; i < size; i++) {
		printf("\nToken n.%d: %s\n", i+1, tokenArray[i]);


		subToken = strtok(tokenArray[i], " ,");
		int index = 0;

		while (subToken != NULL) {
			char *end;
			long intValue = strtol(subToken, &end, 10);
			printf("SubToken: %s\n", subToken);

			if (subToken) {
			    
				if (strchr(subToken, 'i') != NULL) {
					//printf("i TROVATO nel token\n");
					gateRow[i][index].cReal = 0.0;
					
					if(strcmp(subToken,"i") == 0) {
						gateRow[i][index].cImag = 1.0;
					} else if(strcmp(subToken,"-i") == 0) {
						gateRow[i][index].cImag = -1.0;
					}
					
					printf("Numero reale: %.1lf\n", gateRow[i][index].cReal);
					printf("Numero imaginaria: %.1lf\n", gateRow[i][index].cImag);
					
				} else {
				    
					//printf("i NON TROVATO nel token\n");
					gateRow[i][index].cReal = (double)intValue;
					gateRow[i][index].cImag = 0.0;
					printf("Numero reale: %.1lf\n", gateRow[i][index].cReal);
					printf("Numero imaginaria: %.1lf\n", gateRow[i][index].cImag);
				}
				
				index++;
			}
			
			subToken = strtok(NULL, " ,");
			
		}
	}

    return gateRow;
}



void read_InitFile(char *filename, int *qubits, int *numVelem, compNumber **initArray){
    FILE *readInit; //dichiarazione puntatore per il file
    readInit = fopen(filename, "r"); //fopen ritorna un FILE pointer se il file `e stato aperto correttamente
    char *line = NULL; //variabile per la memorizzazione/lettura di ogni riga

    while((line = readLine(readInit)) != NULL){       
        

        if(isqubitLine(line)){
            *qubits = parseQubits(line);
            *numVelem = pow(2, *qubits);
            
        }else if(isinitLine(line)){
            printf("Numero di qubits: %d\n\n",*qubits);
            *initArray = realloc(*initArray, *numVelem * sizeof(compNumber));
            *initArray = parseInit(line, *numVelem);
            /*
            for(int i = 0; i < *numVelem; i++){
                printf("Real: %g, Imaginary: %g\n\n", (*initArray)[i].cReal, (*initArray)[i].cImag);
            }   
            */

        }
    }
    free(line); //libero la memoria allocata per la riga
    fclose(readInit); //chiusura del file
}



void read_CircFile(char *filename, int numVelem, char **ordineArray, int *ordineArrayLen){
    FILE *readCirc;
    readCirc = fopen(filename, "r");
    char *line = NULL;

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
                break; // Exit the loop if realloc fails
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
            int size = 0;
            *ordineArrayLen = 0;

            while(*currLine != '\n'){
                
                if(isupper(*currLine)){
                    size++;
                    *ordineArray = realloc(*ordineArray,size);

                    if (ordineArray == NULL) {
                        perror("realloc failed");
                        break; // Exit the loop if realloc fails
                    }

                    (*ordineArray)[*ordineArrayLen] = *currLine;
                    (*ordineArrayLen)++;

                }
                currLine++;
            }
        /*
            printf("OrdineArrayLen: %d\n", *ordineArrayLen);
            printf("Ordine degli gates: \n");
            

            for(int i = 0; i < size; i++){

                printf("%c\n", (*ordineArray)[i]);

            }
        */

        }
        
    }
    fclose(readCirc);
    free(line); //libero la memoria allocata per la riga


}


