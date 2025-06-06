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

/**
 * Converts an array of complex numbers to an array of strings.
 * 
 * initArray Pointer to the array of compNumber structs (input complex numbers).
 * numVelem Number of elements in the array.
 * Pointer to an array of strings, each representing a complex number.
 */
char **convertToStr(compNumber *initArray, int numVelem)
{
    // Allocate memory for the output array of strings
    char **output = malloc(numVelem * sizeof(char *));

    for (int i = 0; i < numVelem; i++)
    {
        // Allocate memory for each string (128 chars per string)
        output[i] = malloc(128 * sizeof(char));

        // Format the complex number as a string (handle sign of imaginary part)
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

/**
 * Main function: Entry point of the program.
 * Parses command-line arguments, reads input files, processes the quantum circuit,
 * and prints the output vector.
 * 
 * param argc Argument count.
 * param argv Argument vector.
 * return Exit status.
 */
int main(int argc, char *argv[])
{
    int opt;
    char *initfilename = NULL; // Stores the initialization file name
    char *circfilename = NULL; // Stores the circuit file name

    // Parse command-line options for input and circuit file names
    while ((opt = getopt(argc, argv, "i:c:")) != -1)
    {
        switch (opt)
        {
        case 'i':
            initfilename = optarg; // Set initialization file name
            break;

        case 'c':
            circfilename = optarg; // Set circuit file name
            break;

        case '?':
            // Handle missing or unknown options
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

    char *ordineArray = NULL;      // Stores the sequence of operations
    char **outStrArr = NULL;       // Stores the output strings
    int qubits, numVelem, ordineArrayLen;
    compNumber *initArray = NULL;  // Stores the initial state vector

    // Read the initialization file and fill initArray
    read_InitFile(initfilename, &qubits, &numVelem, &initArray);
    // Initialize the hash table for operations
    init_hashtable();
    // Read the circuit file and fill ordineArray
    read_CircFile(circfilename, numVelem, &ordineArray, &ordineArrayLen);

    // Apply the quantum circuit operations to the initial vector
    matrixVector(ordineArray, initArray, numVelem, ordineArrayLen);

    // Convert the resulting vector to strings for output
    outStrArr = convertToStr(initArray, numVelem);

    printf("\nVout OUTPUT: \n");
    // Print each element of the output vector
    for (int i = 0; i < numVelem; i++)
    {
        printf("%s", outStrArr[i]);
        printf("\n");
    }

    return 0;
}
