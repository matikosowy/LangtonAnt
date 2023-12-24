#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "modules.h"


char rotate(int turn, char ant){
    switch (ant)
    {
    case '^':
        if(turn == 0){
            ant = '<';
        }else{
            ant = '>';
        }
        break;
    
    case '>':
        if(turn == 0){
            ant = '^';
        }else{
            ant = 'v';
        }
        break;
    
    case 'v':
        if(turn == 0){
            ant = '>';
        }else{
            ant = '<';
        }
        break;
    
    case '<':
        if(turn == 0){
            ant = 'v';
        }else{
            ant = '^';
        }
        break;
    
    default:
        break;
    }

    return ant;
}

int directionChange(char ant){
    switch(ant){
        case '^':
            return 0;
        case '>':
            return 1;
        case 'v':
            return 2;
        case '<':
            return 3;
    }
    printf("Wrong direction error!\n");
    return -1;
}

void printMap(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, FILE *out, int iterations){
    fprintf(out, "%d: \n", iterations);
    for(int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){
                
                fprintf(out, "%c ", map[i][j].content);
            }
            fprintf(out, "\n");
        }
    fprintf(out, "\n");
}

int moveAnt(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns){

    for(int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){
                if(map[i][j].content != ' ' && map[i][j].content != '#'){
                    if(map[i][j].color == 'w'){
                        map[i][j].color = 'b';
                        map[i][j].content = rotate(1, map[i][j].content);
                        int direction = directionChange(map[i][j].content);
                        
                        switch (direction){
                            case 0:
                                if(i-1 < 0){
                                    printf("Sciana!\n");
                                    return 1;
                                    break;
                                }
                                map[i-1][j].content = map[i][j].content;
                                if(map[i][j].color == 'b'){
                                    map[i][j].content = '#';
                                }else{
                                    map[i][j].content = ' ';
                                }
                                break;
                            
                            case 1:
                                if(j+1 >= columns){
                                    printf("Sciana!\n");
                                    return 1;
                                    break;
                                }
                                map[i][j+1].content = map[i][j].content;
                                if(map[i][j].color == 'b'){
                                    map[i][j].content = '#';
                                }else{
                                    map[i][j].content = ' ';
                                }
                                break;

                            case 2:
                                if(i+1 >= rows){
                                    printf("Sciana!\n");
                                    return 1;
                                    break;
                                }
                                map[i+1][j].content = map[i][j].content;
                                if(map[i][j].color == 'b'){
                                    map[i][j].content = '#';
                                }else{
                                    map[i][j].content = ' ';
                                }
                                break;

                            case 3:
                                if(j-1 < 0){
                                    printf("Sciana!\n");
                                    return 1;
                                    break;
                                }
                                map[i][j-1].content = map[i][j].content;
                                if(map[i][j].color == 'b'){
                                    map[i][j].content = '#';
                                }else{
                                    map[i][j].content = ' ';
                                }
                                break;

                            default:
                                break;
                            }
                        return 0;
                    }

                    if(map[i][j].color == 'b'){
                        map[i][j].color = 'w';
                        map[i][j].content = rotate(0, map[i][j].content);
                        int direction = directionChange(map[i][j].content);
                        
                        switch (direction)
                        {
                        case 0:
                            if(i-1 < 0){
                                printf("Sciana!\n");
                                return 1;
                                break;
                            }
                            map[i-1][j].content = map[i][j].content;
                            if(map[i][j].color == 'b'){
                                map[i][j].content = '#';
                            }else{
                                map[i][j].content = ' ';
                            }
                            break;
                        
                        case 1:
                            if(j+1 >= columns){
                                printf("Sciana!\n");
                                return 1;
                                break;
                            }
                            map[i][j+1].content = map[i][j].content;
                            if(map[i][j].color == 'b'){
                                map[i][j].content = '#';
                            }else{
                                map[i][j].content = ' ';
                            }
                            break;

                        case 2:
                            if(i+1 >= rows){
                                printf("Sciana!\n");
                                return 1;
                                break;
                            }
                            map[i+1][j].content = map[i][j].content;
                            if(map[i][j].color == 'b'){
                                map[i][j].content = '#';
                            }else{
                                map[i][j].content = ' ';
                            }
                            break;

                        case 3:
                            if(j-1 < 0){
                                printf("Sciana!\n");
                                return 1;
                                break;
                            }
                            map[i][j-1].content = map[i][j].content;
                            if(map[i][j].color == 'b'){
                                map[i][j].content = '#';
                            }else{
                                map[i][j].content = ' ';
                            }
                            break;

                        default:
                            break;
                        }
                        return 0;
                    }
                
                }
            }
        }
    return 0;
}

void setColorParameter(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(map[i][j].content == ' '){
                map[i][j].color = 'w';
            }
            if(map[i][j].content == '#'){
                map[i][j].color = 'b';
            }
        }
    }
}

void placeAntInTheMiddle(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, int direction){
    map[rows/2][columns/2].content = 't';

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(map[i][j].content == 't'){
                switch(direction){
                    case 0:
                        map[i][j].content = '^';
                        break;
                    case 1:
                        map[i][j].content = '>';
                        break;
                    case 2:
                        map[i][j].content = 'v';
                        break;
                    case 3: 
                        map[i][j].content = '<';
                        break;
                    default:
                        break;
                }
            }
        }
    }

}

void mapAllWhite(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            map[i][j].content = ' ';
        }
    }
}

double checkBlackPercentage(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns){
    int blackCount = 0;

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(map[i][j].content == '#'){
                blackCount++;
            }
        }
    }
    double result = ((double)blackCount / (rows * columns)) * 100.0;

    return result;
}

void mapBlackByPercentage(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, int percentage){
    srand(time(NULL));

    mapAllWhite(map, rows, columns);

    while(checkBlackPercentage(map, rows, columns) < percentage){
        int row = rand()%rows;
        int column = rand()%columns;

        map[row][column].content = '#';
    }
}