#include "major_functions.h"
#include <windows.h>
#include "settings.h"
#include <stdio.h>
#include <conio.h>

gameover = 1;
char *optionsList[NUMBER_OF_OPTIONS] = {
        "New Game\n",
        "Load Game\n",
        "Exit\n"
};

void set_option_arrow(){
    int i;
    for(i = 0; i < NUMBER_OF_OPTIONS ;i++){
        if(i == arrowY){
            optionsForwardArrow[arrowY] = "-->";
        }else{
            optionsForwardArrow[i] = "\0";
        }
    }
}
void printForwardArrow(int optionNumber){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
    printf("%s",optionsForwardArrow[optionNumber]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void gotoxy_m(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void settings(){
    hidecursor();
    arrowY = 0;
    state = 0; /// this is the menu state.
    enter = 0;
    start = 0;
    xPos = BORDER_X_ZERO + BORDER_WIDTH / 2 + 13;
    yPos = BORDER_Y_ZERO + BORDER_HEIGHT / 2 ;
    set_option_arrow();
    set_console_dimensions(100,100);
    direction = 0;
    prevXPos = xPos;
    prevYPos = yPos;
    prev2XPos = prevXPos;
    prev2YPos = prevYPos;
    tailNumber = 0;
    generateFruitPos();
    score = 0;

}
void print_rectangle(int x,int y,int width,int height,int color){
    gotoxy_m(x,y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    int i;
    // upper
    for(i = 0; i < width+1; i++){
        if(i == width){
            printf("*");
        }else{
            printf("* ");
        }
    }
    // left
    for(i = 1 ; i < height ; i++){
        gotoxy_m(x,y+i);
        printf("*");
    }
    // right
    for(i = 1; i < height ; i++){
        gotoxy_m(x+width * 2,y+i);
        printf("*");
    }
    // lower
    gotoxy_m(x,y+height);
    for(i = 0; i < width+1; i++){
        if(i == width){
            printf("*");
        }else{
            printf("* ");
        }
    }
}
void print_xy(int x,int y,char *str,int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    gotoxy_m(x,y);
    printf("%s",str);

}
void intro(){
    print_rectangle(28,10,30,10,WELCOME_BORDER_COLOR);
    print_xy(43,15,"Welcome to snake game!!",WELCOME_TEXT_COLOR);
    getch();
}
void menu(){
    system("cls");
    gotoxy_m(40,7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    printf("------- ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    printf("Main Menu");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    printf(" -------");
    int i;
    for(i = 0 ; i < NUMBER_OF_OPTIONS ; i++){
        gotoxy_m(38,8+i);
        printForwardArrow(i);
        print_xy(42,8+i,optionsList[i],10);
    }

}
void input(){
    if(_kbhit()){
        int c1 = getch();
        if(state == 0){
            if(c1 == 224){
                int c2 = getch();
                if(c2 == 72){
                    if(arrowY >  0){
                        arrowY--;
                    }else{
                        arrowY = NUMBER_OF_OPTIONS - 1;
                    }
                }else if(c2 == 80){
                    if(arrowY < NUMBER_OF_OPTIONS - 1){
                        arrowY++;
                    }else{
                        arrowY = 0;
                    }
                }
            }else if(c1 == 13) { /// ENTER key
                enter = 1;
                fflush(stdin);
            }else if(c1 == 27){
                if(state == 1 || state == 2){ /// suppose it's the game state or load game
                    state = 0;
                }
            }
        }else if(state == 1){ /// NEW GAME
            /// somethings that controls the position of the head.
            /// xPos,yPos
            if(c1 == 224){
                int c2 = getch();
                start = 1;
                if(c2 == 72){ /// up
                    direction = 0;
                }else if(c2 == 80){ /// down
                    direction = 2;
                }else if(c2 == 75){ /// left
                    direction = 3;
                }else if(c2 == 77){ /// right
                    direction = 1;
                }
            }else if(c1 == 27){
                if(state == 1 || state == 2){ /// suppose it's the game state or load game
                    state = 0;
                    reset();
                }
            }
        }

    }
}
void logic(){
    if(state == 0){ /// menu state
        set_option_arrow();
    }
    if(enter == 1){
        if(state == 0){
            if(arrowY == 0){ /// NEW GAME
                state = 1;
            }else if(arrowY == 1){ /// LOAD GAME
                state = 2;
            }else if(arrowY == 2){ /// EXIT
                state = 3;
            }
        }
        enter = 0;
    }
    if(state == 1){ /// NOW WE'RE PLAYING
            ///  this portion is for direction setting
            if(start == 1){

                prevXPos = xPos; /// position of the head
                prevYPos = yPos;
                prev2XPos = prevXPos; /// position of tail 0
                prev2YPos = prevYPos;

                int i;
                prevXPos = tailSections[0].x;
                prevYPos = tailSections[0].y;

                tailSections[0].x = xPos;
                tailSections[0].y = yPos;

                for ( i = 1; i < tailNumber; i++)
                {
                    prev2XPos = tailSections[i].x;
                    prev2YPos = tailSections[i].y;
                    tailSections[i].x = prevXPos;
                    tailSections[i].y = prevYPos;
                    prevXPos = prev2XPos;
                    prevYPos = prev2YPos;
                }
                if(direction == 0){ /// up
                    yPos--;
                }else if(direction == 1){ /// right
                    xPos += 2;
                }else if(direction == 2){ /// down
                    yPos++;
                }else if(direction == 3){ /// left
                    xPos -= 2;
                }
                /// boundary setting
                if(yPos > BORDER_Y_ZERO+BORDER_HEIGHT - 1){
                    yPos = BORDER_Y_ZERO + 1;
                }
                if(yPos < BORDER_Y_ZERO + 1){
                    yPos = BORDER_Y_ZERO +BORDER_HEIGHT - 1;
                }

                if(xPos > BORDER_X_ZERO+BORDER_WIDTH * 2){
                    xPos = BORDER_X_ZERO + 1; /// this fuckin' bug... I forgot that I added spaces.
                }
                if(xPos < BORDER_X_ZERO){
                    xPos = BORDER_X_ZERO +BORDER_WIDTH * 2- 1 ;
                }
                if(xPos == fruitXPos && yPos == fruitYPos){
                    generateFruitPos();
                    score++;
                    tailNumber++;
                }

                /// check if tails overlap:
                for(i = 0 ; i < tailNumber ; i++){
                    if(tailSections[i].x == xPos && tailSections[i].y == yPos){
                        Sleep(1000);
                        reset();
                    }
                }

            }

        }

    if(state == 0 || state == 2 || state == 1){
        Sleep(100);
    }
}

void show(){
    if(state == 0){  /// menu state
        menu();
    }else if(state == 1){ /// NEW GAME
        new_game();
    }else if(state == 2){ /// LOAD GAME
        load_game();
    }
    else{ /// EXIT
        exit(0);
    }

}
void new_game(){
    system("cls");
    gotoxy_m(40,10);
    print_rectangle(BORDER_X_ZERO,BORDER_Y_ZERO,BORDER_WIDTH,BORDER_HEIGHT,BORDER_COLOR); /// GAME BORDERS
    print_xy(xPos, yPos,"O",2); /// drawing the head
    /// time to draw the tail
    print_xy(fruitXPos,fruitYPos,"F",5); /// drawing the fruit
    int i;
    for(i = 0 ;  i < tailNumber; i++){
        print_xy(tailSections[i].x,tailSections[i].y,"o",2);
    }
    gotoxy_m(46,1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
    printf("----- Score: %d -----",score);
}

void load_game(){
    system("cls");
    gotoxy_m(40,10);
    printf("Load Game motherfucker!!!!");
}
void set_console_dimensions(int width,int height){
    SMALL_RECT windowSize = {0 , 0 , width , height}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}
void reset(){
    settings();
}
void end_game(){
    /// here I want to register a user...get his score and his name.
}
void generateFruitPos(){
    fruitXPos = (rand() % (BORDER_WIDTH*2)) + BORDER_X_ZERO ;
    fruitYPos = (rand() % (BORDER_HEIGHT)) + BORDER_Y_ZERO ;
    if(fruitXPos % 2 == 0){
        fruitXPos++;
    }
    if(fruitYPos == BORDER_Y_ZERO){
        fruitYPos++;
    }
    if(fruitYPos == BORDER_Y_ZERO + BORDER_HEIGHT){
        fruitYPos--;
    }
}
