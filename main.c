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

    int percentage = 0;

    cell map[MAX_SIZE][MAX_SIZE];

    //mapAllWhite(map, rows, columns);
    mapBlackByPercentage(map, rows, columns, percentage);

    setColorParameter(map, rows, columns);
    placeAntInTheMiddle(map, rows, columns, direction);
    
    int help = iterations;
    while(iterations>0){
        printMap(map, rows, columns, out, help - iterations);

        if(moveAnt(map, rows, columns) == 1){
            break;
        }
        
        iterations--;
    }

    return 0;
}