#ifndef ANT_H
#define ANT_H

#include <stdlib.h>
#include <stdio.h>
#include "struct.h"

char rotate(int turn, char ant);
int directionChange(char ant);
int moveAnt(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);

#endif