#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "modules/ant.h"
#include "modules/map.h"

int main(int argc, char** argv){
    setlocale(LC_ALL, "en_US.UTF-8");
    
    // Wartości domyślne dla zmiennych parametrycznych
    int rows = 50;
    int columns = 50;
    int iterations = 500;
    int direction = 0;
    int percentage = 0;
    char *readFileName = "";
    char writeFileName[50];

    // Flagi dla getopt()
    int mflag = 0; // m - liczba wierszy
    int nflag = 0; // n - liczba kolumn
    int iflag = 0; // i - liczba iteracji
    int fflag = 0; // f - nazwa pliku out (kolejne iteracje)
    int dflag = 0; // d - kierunek poczatkowy mrowki
    int gflag = 0; // g - opcja generowania procentowo zapelnionej mapy
    int rflag = 0; // r - nazwa pliku in (gotowa mapa do wczytania)

    // Wektor 2d, przechowujący komorki mapy
    cell map[MAX_SIZE][MAX_SIZE];
    
    // Przetwarzanie argumentow wywolania poprzez funkcję getopt()
    int opt;
    while ((opt = getopt(argc, argv, "m:n:i:f:d:g:r:")) != -1) {
        switch (opt) {
            case 'm':
                rows = atoi(optarg);
                if(rows<1){
                    fprintf(stderr, "Nieprawidlowa liczba wierszy!\n");
                    return 1;
                }
                mflag = 1;
                break;
            case 'n':
                columns = atoi(optarg);
                if(columns<1){
                    fprintf(stderr, "Nieprawidlowa liczba kolumn!\n");
                    return 1;
                }
                nflag = 1;
                break;
            case 'i':
                iterations = atoi(optarg);
                if(iterations<1){
                    fprintf(stderr, "Nieprawidlowa liczba iteracji!\n");
                    return 1;
                }
                iflag = 1;
                break;
            case 'f':
                strcpy(writeFileName, optarg);
                fflag = 1;
                break;
            case 'd':
                direction = atoi(optarg);
                if(direction<0 || direction >4){
                    fprintf(stderr, "Nieprawidlowy kierunek poczatkowy mrowki!\n");
                    return 1;
                }
                dflag = 1;
                break;
            case 'g':
                percentage = atoi(optarg);
                if(percentage < 0 || percentage > 100){
                    fprintf(stderr, "Nieprawidlowy stosunek pol czarnych!\n");
                }
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

    // Obsługa flag, przetworzonych przez getopt()
    if(!rflag){
        if(!mflag){
            fprintf(stderr, "Nie wprowadzono parametru liczby wierszy!\n  Wartość domyślna = 50\n");
        }
        if(!nflag){
            fprintf(stderr, "Nie wprowadzono parametru liczby kolumn!\n  Wartość domyślna = 50\n");
        }
        if(!iflag){
            fprintf(stderr, "Nie wprowadzono parametru liczby iteracji!\n  Wartość domyślna = 500\n");
        }
        if(!fflag){
            fprintf(stderr, "Nie wprowadzono parametru pliku wyjsciowego!\n  Domyślnie: wyjście standardowe\n");
        }
        if(!dflag){
            fprintf(stderr, "Nie wprowadzono parametru kierunku poczatkowego mrowki!\n  Wartość domyślna = 0\n");
        }
    }
    // Przypadek, kiedy wczytujemy siatkę z pliku
    if(rflag == 1){
        FILE *in = fopen(readFileName, "r");
        columns = countColumns(in) - 2;
        rows = countRows(in) - 2;
        
        wchar_t *vector = insertMapToVector(in, rows, columns);
        vectorToMap(vector, rows, columns, map);
        readFileMapAdjustment(map, rows, columns);
    }
    else{
        mapBlackByPercentage(map, rows, columns, percentage);
        setColorParameter(map, rows, columns);
        placeAntInTheMiddle(map, rows, columns, direction);
    }

    // Folder na pliki wyjściowe
    char name[50];
    strcpy(name, writeFileName);

    char *folderName = "out";
    char filePath[100];

    #ifdef _WIN32
        CreateDirectory(folderName, NULL);
    #else 
        mkdir(folderName, 0777);
    #endif

    // Poruszanie się mrowki i zapis poszczegolnych iteracji do plikow
    int help = iterations;
    while(iterations>0){
        
        if(fflag){
            sprintf(name, "%s/%s_%d", folderName, writeFileName, help - iterations + 1);
            FILE *out = fopen(name, "w");
            printMap(map, rows, columns, out, help - iterations);
            fclose(out);
        }else{
            FILE *out = stdout;
            printMap(map, rows, columns, out, help - iterations);
        }
        int result = moveAnt(map, rows, columns);

        if(result == 1){
            break;
        }
        iterations--;
    }

    return 0;
}