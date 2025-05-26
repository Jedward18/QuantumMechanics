#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define BUFFER_SIZE 256


typedef struct Complex {
    double cReal;
    double cImag;
}complex;

int isinitLine(char *line);
int parseQubits(char *line);
void formatStandard();
complex *parseInit(char *line, int qubits);
char *readLine(FILE *toRead);
void swap(char *a, char *b);


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

    if(sscanf(line, "%s %d", word, &qubits) ==2)
        return qubits;


    return 0;


}

void formatStandard(){

}

complex *parseInit(char *line, int numVelem){

    char *pretoken = strchr(line, '[');
    double real, imaginary;
    complex *cnumbers = malloc(numVelem * sizeof(complex));
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

void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}


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
            complex *arrayCompNum = parseInit(line, numVelem);

            for(int i = 0; i < numVelem; i++){
                printf("Real: %g, Imaginary: %g\n\n", arrayCompNum[i].cReal, arrayCompNum[i].cImag);
            }   

        }
    }

    int i = 0;
    while((line = readLine(readCirc)) != NULL){
        printf("Linea %d: %s", i,line);

        i++;
    }

    fclose(readInit);
    fclose(readCirc);

    return 0;
}