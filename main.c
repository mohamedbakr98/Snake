#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "major_functions.h"
#include "settings.h"
int main()
{
    srand(time(NULL));   // should only be called once
    settings();
    intro();
    menu();
    while(gameover){
        input();
        logic();
        show();
    }
    return 0;
}
