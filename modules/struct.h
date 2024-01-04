#ifndef STRUCT_H
#define STRUCT_H
#define MAX_SIZE 100

typedef struct{
    wchar_t content;
    char color;
}cell;


#define LINE_VERTICAL L'│'
#define LINE_HORIZONTAL L'─'
#define LINE_DOWN_RIGHT L'┌'
#define LINE_DOWN_LEFT L'┐'
#define LINE_UP_RIGHT L'└'
#define LINE_UP_LEFT L'┘'
#define SQUARE_WHITE L' '
#define SQUARE_BLACK L'█'
#define ARROW_NORTH_WHITE L'△'
#define ARROW_NORTH_BLACK L'▲'
#define ARROW_EAST_WHITE L'▷'
#define ARROW_EAST_BLACK L'▶'
#define ARROW_SOUTH_WHITE L'▽'
#define ARROW_SOUTH_BLACK L'▼'
#define ARROW_WEST_WHITE L'◁'
#define ARROW_WEST_BLACK L'◀'

#endif