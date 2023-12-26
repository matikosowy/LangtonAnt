#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "modules.h"

int main(int argc, char** argv){

    int rows = 50;
    int columns = 50;
    int iterations = 500;
    int direction = 0;
    int percentage = 0;
    char *readFileName = "";
    char writeFileName[50];

    int mflag = 0; // m - liczba wierszy
    int nflag = 0; // n - liczba kolumn
    int iflag = 0; // i - liczba iteracji
    int fflag = 0; // f - nazwa pliku out (kolejne iteracje)
    int dflag = 0; // d - kierunek poczatkowy mrowki
    int gflag = 0; // g - opcja generowania procentowo zapelnionej mapy
    int rflag = 0; // r - nazwa pliku in (gotowa mapa do wczytania)

    cell map[MAX_SIZE][MAX_SIZE];
    
    int opt;
    while ((opt = getopt(argc, argv, "m:n:i:f:d:g:r:")) != -1) {
        switch (opt) {
            case 'm':
                rows = atoi(optarg);
                mflag = 1;
                break;
            case 'n':
                columns = atoi(optarg);
                nflag = 1;
                break;
            case 'i':
                iterations = atoi(optarg);
                iflag = 1;
                break;
            case 'f':
                //out = fopen(optarg, "w");
                strcpy(writeFileName, optarg);
                fflag = 1;
                break;
            case 'd':
                direction = atoi(optarg);
                dflag = 1;
                break;
            case 'g':
                percentage = atoi(optarg);
                gflag = 1;
                break;
            case 'r':
                readFileName = optarg;
                rflag = 1;
                break;
            case '?':
                fprintf(stderr, "Nieznany parametr: -%c\n", optopt);
                return 1;
            default:
                return 1;
        }
    }

    if(!mflag){
        fprintf(stderr, "Nie wprowadzono parametru liczby wierszy!\n  Wartość domyślna = 50\n");
        //return 1;
    }
    if(!nflag){
        fprintf(stderr, "Nie wprowadzono parametru liczby kolumn!\n  Wartość domyślna = 50\n");
       //return 1;
    }
    if(!iflag){
        fprintf(stderr, "Nie wprowadzono parametru liczby iteracji!\n  Wartość domyślna = 500\n");
        //return 1;
    }
    if(!fflag){
        fprintf(stderr, "Nie wprowadzono parametru pliku wyjsciowego!\n  Domyślnie: wyjście standardowe\n");
        //return 1;
    }
    if(!dflag){
        fprintf(stderr, "Nie wprowadzono parametru kierunku poczatkowego mrowki!\n  Wartość domyślna = 0\n");
        //return 1;
    }

    if(rflag == 1){
        FILE *in = fopen(readFileName, "r");
        columns = countColumns(in);
        rows = countRows(in);
        
        char *vector = insertMapToVector(in, rows, columns);
        vectorToMap(vector, rows, columns, map);
        
        setColorParameter(map, rows, columns);

    }else{
        mapBlackByPercentage(map, rows, columns, percentage);
        setColorParameter(map, rows, columns);
        placeAntInTheMiddle(map, rows, columns, direction);
    }

    char name[50];
    strcpy(name, writeFileName);

    char *folderName = "files";
    char filePath[100];

    #ifdef _WIN32
        CreateDirectory(folderName, NULL);
    #else 
        mkdir(folderName, 0777);
    #endif

    int help = iterations;
    while(iterations>0){
        if(iterations<200){
            if(fflag){
            sprintf(name, "%s/%s_%d", folderName, writeFileName, help - iterations + 1);
            FILE *out = fopen(name, "w");
            printMap(map, rows, columns, out, help - iterations);
            fclose(out);
        }else{
            FILE *out = stdout;
            printMap(map, rows, columns, out, help - iterations);
        }
        }

        if(moveAnt(map, rows, columns) == 1){
            break;
        }
        iterations--;
    }

    return 0;
}