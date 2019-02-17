#ifndef MAJOR_FUNCTIONS_H_INCLUDED
#define MAJOR_FUNCTIONS_H_INCLUDED
#include "settings.h"

typedef struct{
    int x,y;
}tailSec;
typedef struct{
    char name[100];
    int score;
}User;
int gameover;
char *optionsList[NUMBER_OF_OPTIONS];
char *optionsForwardArrow[NUMBER_OF_OPTIONS];
int arrowY;
int state;
int enter;
int xPos,yPos,prevXPos,prevYPos,prev2XPos,prev2YPos;
int direction;
int start;
int tailNumber;
int fruitXPos,fruitYPos;
int score;
tailSec tailSections[100];
void set_option_arrow();
void printForwardArrow(int optionNumber);
void hidecursor();
void gotoxy_m(int x, int y);
void settings();
void print_rectangle(int x,int y , int width, int height,int color);
void intro();
void menu();
void input();
void show();
void logic();
void new_game();
void load_game();
void set_console_dimensions(int width,int height);
void reset();

#endif // MAJOR_FUNCTIONS_H_INCLUDED
