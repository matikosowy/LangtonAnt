#include "map.h"

// Wyświetlanie mapy w formie graficznej, po sformatowaniu (obramowania, pola i strzałki)
void printMap(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, FILE *out, int iterations){
    
    cell cells[rows*columns];
    int idx = 0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            cells[idx].content = map[i][j].content;
            cells[idx].color = map[i][j].color;
            idx++;
        }
    }

    int newRows = rows+2;
    int newColumns = columns+2;

    wchar_t mapBeautified[newRows][newColumns];

    idx = 0;
    for(int i=0; i<newRows; i++){
        for(int j=0; j<newColumns; j++){
            if((i == 0 || i == newRows-1) && j>0 && j<newColumns-1){
                mapBeautified[i][j] = LINE_HORIZONTAL;
            }else if(i == 0 && j == 0){
                mapBeautified[i][j] = LINE_DOWN_RIGHT;
            }else if(i == 0 && j == newColumns-1){
                mapBeautified[i][j] = LINE_DOWN_LEFT;
            }else if(i == newRows-1 && j == 0){
                mapBeautified[i][j] = LINE_UP_RIGHT;
            }else if(i == newRows-1 && j == newColumns-1){
                mapBeautified[i][j] = LINE_UP_LEFT;
            }else if(j == 0 || j == newColumns-1){
                mapBeautified[i][j] = LINE_VERTICAL;
            }else{
                switch(cells[idx].content){
                    case '#':
                        mapBeautified[i][j] = SQUARE_BLACK;
                        break;
                    case ' ':
                        mapBeautified[i][j] = SQUARE_WHITE;
                        break;
                    case '^':
                        if(cells[idx].color == 'b'){
                            mapBeautified[i][j] = ARROW_NORTH_BLACK;
                        }else{
                            mapBeautified[i][j] = ARROW_NORTH_WHITE;
                        }
                        break;
                    case '>':
                        if(cells[idx].color == 'b'){
                            mapBeautified[i][j] = ARROW_EAST_BLACK;
                        }else{
                            mapBeautified[i][j] = ARROW_EAST_WHITE;
                        }
                        break;
                    case 'v':
                        if(cells[idx].color == 'b'){
                            mapBeautified[i][j] = ARROW_SOUTH_BLACK;
                        }else{
                            mapBeautified[i][j] = ARROW_SOUTH_WHITE;
                        }
                        break;
                    case '<':
                        if(cells[idx].color == 'b'){
                            mapBeautified[i][j] = ARROW_WEST_BLACK;
                        }else{
                            mapBeautified[i][j] = ARROW_WEST_WHITE;
                        }
                        break;
                }
                if(cells[idx].content == '#'){
                    mapBeautified[i][j] = SQUARE_BLACK;
                }else if(cells[idx].content == ' '){
                    mapBeautified[i][j] = SQUARE_WHITE;
                }
                idx++;
            }
        }
    }

    for(int i=0; i<newRows; i++){
            for(int j=0; j<newColumns; j++){
                
                fwprintf(out, L"%lc", mapBeautified[i][j]);
            }
            fprintf(out, "\n");
        }
    fprintf(out, "\n");
}

// Ustawienie koloru komorki według jej zawartości
void setColorParameter(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(map[i][j].content == ' '){
                map[i][j].color = 'w';
            }
            if(map[i][j].content == '#'){
                map[i][j].color = 'b';
            }
            if(map[i][j].content != ' ' && map[i][j].content != '#'){
                map[i][j].color = 'w';
            }
        }
    }
}

// Ustawienie mrowki na środku mapy
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

// Ustawienie wszystkich komorek mapy na białe
void mapAllWhite(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            map[i][j].content = ' ';
        }
    }
}

// Sprawdzenie pokrycia mapy czarnymi polami (%)
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

// Zamalowanie na czarno komorek według zapełnienia procentowego oraz losowo
void mapBlackByPercentage(cell map[MAX_SIZE][MAX_SIZE], int rows, int columns, int percentage){
    srand(time(NULL));

    mapAllWhite(map, rows, columns);

    while(checkBlackPercentage(map, rows, columns) < percentage){
        int row = rand()%rows;
        int column = rand()%columns;

        map[row][column].content = '#';
    }
}

// Liczy kolumny w pliku z gotową mapą wprowadzoną przez uzytkownika w pliku
int countColumns(FILE *file) {
  int count = 0;
  int ch;

  if (file == NULL) {
    printf("Nie udało się otworzyć pliku.\n");
    return -1;
  }

  rewind(file);

  while ((ch = fgetc(file)) != '\n' && ch != EOF) {
    count++;
  }

  return count;
}

// Liczy wiersze w pliku z gotową mapą wprowadzoną przez uzytkownika w pliku
int countRows(FILE *file) {
  int count = 0;
  char ch;

  if (file == NULL) {
    printf("Nie udało się otworzyć pliku.\n");
    return -1;
  }

  rewind(file);

  fseek(file, 0, SEEK_END);
  if (ftell(file) == 0) {
    printf("Pusty plik wejsciowy z mapa!r\n");
    return -1;
  }
  fseek(file, 0, SEEK_SET);

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      count++;
    }
  }

  count++;

  return count;
}

// Wczytanie znakow z pliku z gotową mapą od uzytkownika
char *insertMapToVector(FILE *file, int rows, int columns) {
  char *vector = malloc(rows * columns * sizeof(char));

  if (file == NULL) {
    printf("Nie udało się otworzyć pliku.\n");
    return NULL;
  }

  rewind(file);

  int index = 0;
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\t' || ch == '\n' || ch == '\r') {
      continue;
    }
    vector[index++] = ch;
  }

  return vector;
}

// Przetworzenie znakow gotowej mapy od uzytkownika na mapę dla programu
void vectorToMap(char *vector, int rows, int columns, cell map[MAX_SIZE][MAX_SIZE]) {
  int idx = 0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      map[i][j].content = vector[idx++];
    }
  }
}