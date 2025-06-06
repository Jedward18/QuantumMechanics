#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include "parsers.h"
#include "structs.h"
#include "swap.h"
#include "hashing.h"
#include "operations.h"

char **convertToStr(compNumber *initArray, int numVelem)
{

    char **output = malloc(numVelem * sizeof(char *));

    for (int i = 0; i < numVelem; i++)
    {
        output[i] = malloc(128 * sizeof(char));

        if (initArray[i].cImag < 0)
        {
            sprintf(output[i], "%g-i%g", initArray[i].cReal, -initArray[i].cImag);
        }
        else
        {
            sprintf(output[i], "%g+i%g", initArray[i].cReal, initArray[i].cImag);
        }
    }

    return output;
}

int main(int argc, char *argv[])
{

    int opt;

    char *initfilename = NULL;
    char *circfilename = NULL;

    while ((opt = getopt(argc, argv, "i:c:")) != -1)
    {

        switch (opt)
        {

        case 'i':
            initfilename = optarg;
            break;

        case 'c':
            circfilename = optarg;
            break;

        case '?':
            if (optopt == 'i')
                fprintf(stderr, "Option -%c requires an argument <Init Filename>\n", optopt);
            else if (optopt == 'c')
                fprintf(stderr, "Option -%c requires an argument <Circ Filename>\n", optopt);

            else if (isprint(optopt))
                fprintf(stderr, "Unknown option -%c\n", optopt);

            exit(EXIT_FAILURE);

        default:
            break;
        }
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
    for (int i = 0; i < ordineArrayLen; i++)
    {
        printf(" %c ", ordineArray[i]);
    }

    printf("\n#INIT CONTENT: \n");
    for (int i = 0; i < numVelem; i++)
    {
        printf("Real: %g, Imaginary: %g\n\n", initArray[i].cReal, initArray[i].cImag);
    }

    matrixVector(ordineArray, initArray, numVelem, ordineArrayLen);

    outStrArr = convertToStr(initArray, numVelem);

    printf("\nVFIN OUTPUT: \n");
    for (int i = 0; i < numVelem; i++)
    {
        printf("%s", outStrArr[i]);
        printf("\n");
    }
    return 0;
}
