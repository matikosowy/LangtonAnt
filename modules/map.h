#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "struct.h"

void printMap(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, FILE *out, int iterations);
void setColorParameter(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);
void placeAntInTheMiddle(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, int direction);
void mapAllWhite(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);
double checkBlackPercentage(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);
void mapBlackByPercentage(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, int percentage);
int countRows(FILE *file);
int countColumns(FILE *file);
char* insertMapToVector(FILE *file, int rows, int columns);
void vectorToMap(char *vector, int rows, int columns, cell map[MAX_SIZE][MAX_SIZE]);

#endif