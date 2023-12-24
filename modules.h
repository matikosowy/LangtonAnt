#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100

typedef struct{
    char content;
    char color;
}cell;

char rotate(int turn, char ant);
int directionChange(char ant);
void printMap(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, FILE *out, int iterations);
int moveAnt(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);
void setColorParameter(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);
void placeAntInTheMiddle(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, int direction);
void mapAllWhite(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);
double checkBlackPercentage(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns);
void mapBlackByPercentage(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, int percentage);