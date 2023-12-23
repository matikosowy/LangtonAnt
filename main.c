#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "modules.h"

int main(int argc, char** argv){
    
    int rows = argc>1 ? atoi(argv[1]) : 100;
    int columns = argc>2 ? atoi(argv[2]) : 100;
    int iterations = argc>3 ? atoi(argv[3]) : 1000;
    FILE *out = argc>4 ? fopen(argv[4], "w") : stdout;
    int direction = argc>5 ? atoi(argv[5]) : 0;

    cell map[MAX_SIZE][MAX_SIZE];

    // wszedzie biale pola
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            map[i][j].content = ' ';
        }
    }
    // uzupelnienie parametru koloru
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
        // ustawienie mrowki
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

    
    int help = iterations;
    while(iterations>0){
        
        printMap(map, rows, columns, out, help - iterations);

        if(magic(map, rows, columns) == 1){
            break;
        }
        
        iterations--;
    }


    return 0;
}