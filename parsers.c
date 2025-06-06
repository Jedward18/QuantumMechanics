#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "swap.h"
#include "structs.h"
#include "hashing.h"

/**
 * Checks if a line contains the "#qubits" keyword.
 * param line Input string to check.
 * return 1 if "#qubits" is found, 0 otherwise.
 */
int isqubitLine(char *line)
{
    char word[] = "#qubits";
    // Search for "#qubits" in the line
    if (strstr(line, word) != NULL)
        return 1;
    else
        return 0;
}

/**
 * Checks if a line contains the "#init" keyword.
 * param line Input string to check.
 * return 1 if "#init" is found, 0 otherwise.
 */
int isinitLine(char *line)
{
    char word[] = "#init";
    // Search for "#init" in the line
    if (strstr(line, word) != NULL)
        return 1;
    else
        return 0;
}

/**
 * Parses the number of qubits from a line.
 * param line Input string containing "#qubits <number>".
 * return The number of qubits if found, 0 otherwise.
 */
int parseQubits(char *line)
{
    char word[strlen("#qubits")];
    int qubits;
    // Extract the number after "#qubits"
    if (sscanf(line, "%s %d", word, &qubits) == 2)
        return qubits;
    return 0;
}

/**
 * Parses a line containing the initial state vector.
 * param line Input string containing the vector.
 * param numVelem Number of elements in the vector.
 * return Pointer to an array of compNumber structs.
 */
compNumber *parseInit(char *line, int numVelem)
{
    char *pretoken = strchr(line, '[');
    double real, imaginary;
    compNumber *cnumbers = malloc(numVelem * sizeof(compNumber));
    int index = 0;

    if (pretoken != NULL)
    {
        pretoken++; // Move past '['
        char *token = strtok(pretoken, " ,");

        // Parse each token representing a complex number
        while (token && isdigit(*token))
        {
            char *i = strchr(token, 'i');
            if (i != NULL)
            {
                // Swap to handle imaginary part if needed
                char *j = i + 1;
                while (isdigit(*j) || *j == '.')
                {
                    swap(i, j);
                    i++;
                    j++;
                }
            }
            // Read real and imaginary parts
            sscanf(token, "%lf%lf", &real, &imaginary);
            cnumbers[index].cReal = real;
            cnumbers[index].cImag = imaginary;
            token = strtok(NULL, " ,]");
            index++;
        }
    }
    else
    {
        printf("Character '[' not found in line.\n");
    }
    return cnumbers;
}

/**
 * Reads a line from a file, dynamically allocating memory as needed.
 * param toRead File pointer to read from.
 * return Pointer to the read line (must be freed by caller), or NULL on EOF.
 */
char *readLine(FILE *toRead)
{
    char *buffer = NULL;
    size_t size = 0;
    char *newLine_Found = NULL;

    do
    {
        // Reallocate buffer to accommodate more characters
        if ((buffer = realloc(buffer, (size + BUFSIZ) * sizeof(char))) == NULL)
        {
            perror("Error (message): ");
            exit(EXIT_FAILURE);
        }
        // Read next chunk of the line
        if (fgets(buffer + size, BUFSIZ, toRead) == NULL)
        {
            return NULL;
        }
        // Check for newline character
        newLine_Found = strchr(buffer + size, '\n');
    } while (!newLine_Found && (size += BUFSIZ));

    return buffer;
}

/**
 * Converts an array of string tokens to a 2D array of compNumber structs.
 * param tokenArray Array of string tokens.
 * param size Number of tokens (matrix size).
 * return Pointer to a 2D array of compNumber structs.
 */
compNumber **subToken(char **tokenArray, int size)
{
    compNumber **gateRow = NULL;
    char *subToken = NULL;

    // Allocate memory for the matrix
    gateRow = realloc(gateRow, size * sizeof(compNumber));
    for (int i = 0; i < size; ++i)
    {
        gateRow[i] = malloc(size * sizeof(compNumber));
    }

    if (gateRow == NULL)
    {
        perror("malloc failed");
    }

    // Parse each token into compNumber structs
    for (int i = 0; i < size; i++)
    {
        subToken = strtok(tokenArray[i], " ,");
        int index = 0;
        while (subToken != NULL)
        {
            char *end;
            long intValue = strtol(subToken, &end, 10);
            if (subToken)
            {
                if (strchr(subToken, 'i') != NULL)
                {
                    gateRow[i][index].cReal = 0.0;
                    if (strcmp(subToken, "i") == 0)
                        gateRow[i][index].cImag = 1.0;
                    else if (strcmp(subToken, "-i") == 0)
                        gateRow[i][index].cImag = -1.0;
                }
                else
                {
                    gateRow[i][index].cReal = (double)intValue;
                    gateRow[i][index].cImag = 0.0;
                }
                index++;
            }
            subToken = strtok(NULL, " ,");
        }
    }
    return gateRow;
}

/**
 * Reads the initialization file and fills the qubits, numVelem, and initArray variables.
 * param filename Name of the initialization file.
 * param qubits Pointer to store the number of qubits.
 * param numVelem Pointer to store the number of vector elements.
 * param initArray Pointer to the array of compNumber structs.
 */
void read_InitFile(char *filename, int *qubits, int *numVelem, compNumber **initArray)
{
    FILE *readInit;
    // Open the file for reading
    if ((readInit = fopen(filename, "r")) == NULL)
    {
        perror("Error apertura file");
        exit(EXIT_FAILURE);
    }
    char *line = NULL;
    // Read each line and process accordingly
    while ((line = readLine(readInit)) != NULL)
    {
        if (isqubitLine(line))
        {
            *qubits = parseQubits(line);
            *numVelem = pow(2, *qubits);
        }
        else if (isinitLine(line))
        {
            *initArray = realloc(*initArray, *numVelem * sizeof(compNumber));
            *initArray = parseInit(line, *numVelem);
        }
    }
    free(line);
    fclose(readInit);
}

/**
 * Reads the circuit file, fills the ordineArray and ordineArrayLen, and parses gate definitions.
 * param filename Name of the circuit file.
 * param numVelem Number of vector elements (matrix size).
 * param ordineArray Pointer to the array storing the sequence of operations.
 * param ordineArrayLen Pointer to the length of ordineArray.
 */
void read_CircFile(char *filename, int numVelem, char **ordineArray, int *ordineArrayLen)
{
    FILE *readCirc;
    // Open the file for reading
    if ((readCirc = fopen(filename, "r")) == NULL)
    {
        perror("Error apertura file");
        exit(EXIT_FAILURE);
    }
    char *line = NULL;
    // Read each line and process accordingly
    while ((line = readLine(readCirc)) != NULL)
    {
        char *pretoken = strchr(line, '(');
        char *currLine = NULL;
        char *gateArray = NULL;
        int size = 0;
        int index = 0;

        // Parse gate definitions
        if ((currLine = strstr(line, "#define")) != NULL)
        {
            size++;
            gateArray = realloc(gateArray, size);
            if (gateArray == NULL)
            {
                perror("realloc failed");
                break;
            }
            // Move to the gate character (e.g., X)
            while (!isupper(*currLine))
            {
                currLine++;
            }
            gateArray[index] = *currLine;

            // Parse the matrix content
            if (pretoken != NULL)
            {
                char *token = strtok(pretoken, "()]");
                char *tokenArray[numVelem];
                int index = 0;
                while (token != NULL)
                {
                    if (token != NULL && strlen(token) > 0 && !isspace(token[0]))
                    {
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
            }
            else
            {
                printf("Substring '#define' wasn't found in the line.\n");
            }
            free(gateArray);
        }
        // Parse the circuit sequence
        else if ((currLine = strstr(line, "#circ")) != NULL)
        {
            int size = 0;
            *ordineArrayLen = 0;
            while (*currLine != '\n')
            {
                if (isupper(*currLine))
                {
                    size++;
                    *ordineArray = realloc(*ordineArray, size);
                    if (ordineArray == NULL)
                    {
                        perror("realloc failed");
                        break;
                    }
                    (*ordineArray)[*ordineArrayLen] = *currLine;
                    (*ordineArrayLen)++;
                }
                currLine++;
            }
        }
    }
    fclose(readCirc);
    free(line);
}
