#include "menu.h"
#include <curses.h>

int main(int argc, char * argv[]){
    QCoreApplication app(argc, argv);
    bool resized = resizeTerminalWindow();

    initscr();
    noecho();
    if (resized) getch();
    scrollok(stdscr, true);

    //check to make sure game folders exist in same directory as executable
    dirCheck("/saves/");
    dirCheck("/assets/", "\nYour assets are missing. Creating assets folder now.\nPlease be sure to populate your assets folder with game files before trying to play.\n");
    entryPoint();
    endwin();
    return 0;
}
