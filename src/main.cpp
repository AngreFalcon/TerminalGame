#include "menu.h"
#include <curses.h>

void initializeGameEnv();

int main(int argc, char * argv[]){
    QCoreApplication app(argc, argv);

    initializeGameEnv();
    entryPoint();
    return 0;
}

void initializeGameEnv(){
    bool resized = resizeTerminalWindow();
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, true);
    if (resized) getch();

    dirCheck("/saves/");
    dirCheck("/assets/", "\nYour assets are missing. Creating assets folder now.\nPlease be sure to populate your assets folder with game files before trying to play.\n");
    return;
}
