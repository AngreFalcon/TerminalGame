#include "menu.h"
#include <curses.h>

/*
int main(int argc, char * argv[]){
    QCoreApplication app(argc, argv);

    //check to make sure game folders exist in same directory as executable
    dirCheck("/saves/");
    dirCheck("/assets/", "\nYour assets are missing. Creating assets folder now.\nPlease be sure to populate your assets folder with game files before trying to play.\n");

    entryPoint();
    return 0;
}
*/

int main(int argc, char * argv[]){
    QCoreApplication app(argc, argv);
    initscr();
    printw("Hello World");
    //check to make sure game folders exist in same directory as executable
    //dirCheck("/saves/");
    //dirCheck("/assets/", "\nYour assets are missing. Creating assets folder now.\nPlease be sure to populate your assets folder with game files before trying to play.\n");
    refresh();
    //entryPoint();
    getch();
    endwin();
    return 0;
}
