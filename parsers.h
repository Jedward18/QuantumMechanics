#ifndef PARSERS_H
#define PARSERS_H

#include <stdio.h>
#include "structs.h"

compNumber *parseInit(char *line, int qubits);
int isqubitLine(char *line);
int isinitLine(char *line);
int parseQubits(char *line);
char *readLine(FILE *toRead);
compNumber **subToken(char **tokenArray, int size);

#endif