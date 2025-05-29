#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct compNumberTag{
    double cReal;
    double cImag;
} compNumber;

typedef struct mapGatesTag{
    char name;
    compNumber **matrix;

} mapGates;

#endif