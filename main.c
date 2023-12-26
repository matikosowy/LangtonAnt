#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "modules.h"

int main(int argc, char** argv){

    int rows = 50;
    int columns = 50;
    int iterations = 500;
    int direction = 0;
    int percentage = 0;
    FILE *out = stdout;

    int mflag = 0; // m - liczba wierszy
    int nflag = 0; // n - liczba kolumn
    int iflag = 0; // i - liczba iteracji
    int fflag = 0; // f - nazwa pliku out (kolejne iteracje)
    int dflag = 0; // d - kierunek poczatkowy mrowki
    int gflag = 0; // g - opcja generowania procentowo zapelnionej mapy
    int rflag = 0; // r - nazwa pliku in (gotowa mapa do wczytania)

    int opt;
    while ((opt = getopt(argc, argv, "m:n:i:f:d:g:r:")) != -1) {
        switch (opt) {
            case 'm':
                printf("Wiersze: %s\n", optarg);
                rows = atoi(optarg);
                mflag = 1;
                break;
            case 'n':
                printf("Kolumny: %s\n", optarg);
                columns = atoi(optarg);
                nflag = 1;
                break;
            case 'i':
                printf("Iteracje: %s\n", optarg);
                iterations = atoi(optarg);
                iflag = 1;
                break;
            case 'f':
                printf("Nazwa pliku: %s\n", optarg);
                out = fopen(optarg, "w");
                fflag = 1;
                break;
            case 'd':
                printf("Kierunek: %s\n", optarg);
                direction = atoi(optarg);
                dflag = 1;
                break;
            case 'g':
                printf("Generuj: %s\n", optarg);
                percentage = atoi(optarg);
                gflag = 1;
                break;
            case 'r':
                printf("Czytaj: %s\n", optarg);
                FILE *in = fopen(optarg, "r");
                // readMapFromFile();
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
        fprintf(stderr, "Nie wprowadzono parametru liczby wierszy!\n");
        return 1;
    }
    if(!nflag){
        fprintf(stderr, "Nie wprowadzono parametru liczby kolumn!\n");
        return 1;
    }
    if(!iflag){
        fprintf(stderr, "Nie wprowadzono parametru liczby iteracji!\n");

        return 1;
    }
    if(!fflag){
        fprintf(stderr, "Nie wprowadzono parametru pliku wyjsciowego!\n");
        return 1;
    }
    if(!dflag){
        fprintf(stderr, "Nie wprowadzono parametru kierunku poczatkowego mrowki!\n");
        return 1;
    }


    cell map[MAX_SIZE][MAX_SIZE];

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