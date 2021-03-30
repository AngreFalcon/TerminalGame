#include "terminalmanip.h"

void scrollTerm(){
    keypad(stdscr, true);
    int input = getch();
    do{
        if (input == KEY_UP) scrl(-1);
        else scrl(1);
        input = getch();
    } while (input == KEY_UP || input == KEY_DOWN);
    return;
}

void clearTerm(){
    move(0,0);
    clrtobot();
    refresh();
    return;
}

bool resizeTerminalWindow(){
    int windowMargins[2] = {0,0};
    std::string tempOutputString;
    #ifdef _WINDOWS_
        if (DEBUG) std::cout << "\nWindows header included\n";
        returnSizeOfWindow(windowMargins);
        if (windowMargins[0] != WINDOWWIDTH || windowMargins[1] != WINDOWHEIGHT){
            if (DEBUG) std::cout << "\nWindow resized\n";
            SMALL_RECT windowSize = {0, 0, 1, 1};
            //buffer has to be bigger than window; resize window to smallest margins possible so that no matter the target window size, resizing will succeed
            if (!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)){
                tempOutputString = "\nSetting console window minimum failed: " + std::to_string(GetLastError()) + "\n";
                std::cout << tempOutputString;
            }
            if (!SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), {BUFFERWIDTH, BUFFERHEIGHT})){
                tempOutputString = "\nSetting console window buffer failed: " + std::to_string(GetLastError()) + "\n";
                std::cout << tempOutputString;
                }
            windowSize.Right = WINDOWWIDTH;
            if (!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)){
                tempOutputString = "\nSetting console window width failed: " + std::to_string(GetLastError()) + "\n";
                std::cout << tempOutputString;
                }
            windowSize.Bottom = WINDOWHEIGHT;
            if (!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)){
                tempOutputString = "\nSetting console window height failed: " + std::to_string(GetLastError()) + "\n";
                std::cout << tempOutputString;
                }
            if (DEBUG) returnSizeOfWindow(windowMargins);
            return false;
        }
    #elif defined(_SYS_IOCTL_H)
        returnSizeOfWindow(windowMargins);
        if (windowMargins[0] != WINDOWWIDTH || windowMargins[1] != WINDOWHEIGHT) {
            if (DEBUG) printw("\nWindow resized\n");
            tempOutputString = "\e[8;" + std::to_string(WINDOWHEIGHT) + ";" + std::to_string(WINDOWWIDTH) + "t";
            std::cout << tempOutputString;
            return true;
        }
    #endif
    return false;
}

void returnSizeOfWindow(int (&windowMargins)[2]){
    std::string tempOutputString;
    #ifdef _WINDOWS_
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        windowMargins[0] = csbi.srWindow.Right - csbi.srWindow.Left, windowMargins[1] = csbi.srWindow.Bottom - csbi.srWindow.Top;
    #elif defined(_SYS_IOCTL_H)
        struct winsize size;
        ioctl(fileno(stdout), TIOCGWINSZ, &size);
        windowMargins[0] = (int)(size.ws_col);
        windowMargins[1] = (int)(size.ws_row);
    #endif
    tempOutputString = "\nColumns: " + std::to_string(windowMargins[0]) + "\nRows: " + std::to_string(windowMargins[1]);
    if (DEBUG) printw(tempOutputString.data());
    return;
}
