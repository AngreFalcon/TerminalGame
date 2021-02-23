#include "terminalmanip.h"


void resizeTerminalWindow(){
    int windowMargins[2] = {0,0};
    #ifdef _WINDOWS_
        if (DEBUG) std::cout << "\nWindows header included\n";
        returnSizeOfWindow(windowMargins);
        if (windowMargins[0] != WINDOWWIDTH || windowMargins[1] != WINDOWHEIGHT){
            if (DEBUG) std::cout << "\nWindow resized\n";
            SMALL_RECT windowSize = {0, 0, 1, 1};
            //buffer has to be bigger than window; resize window to smallest margins possible so that no matter the target window size, resizing will succeed
            if (!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)) std::cout << "\nSetting console window minimum failed: " << GetLastError() << "\n";
            if (!SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), {BUFFERWIDTH, BUFFERHEIGHT})) std::cout << "\nSetting console window buffer failed: " << GetLastError() << "\n";
            windowSize.Right = WINDOWWIDTH;
            if (!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)) std::cout << "\nSetting console window width failed: " << GetLastError() << "\n";
            windowSize.Bottom = WINDOWHEIGHT;
            if (!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)) std::cout << "\nSetting console window height failed: " << GetLastError() << "\n";
        }
        if (DEBUG) returnSizeOfWindow(windowMargins);
    #elif defined(_SYS_IOCTL_H)
        returnSizeOfWindow(windowMargins);
        if (windowMargins[0] != WINDOWWIDTH || windowMargins[1] != WINDOWHEIGHT) {
            if (DEBUG) std::cout << "\nWindow resized\n";
            std::cout << "\e[8;" << WINDOWHEIGHT << ";" << WINDOWWIDTH << "t";
        }
    #endif
    return;
}

void returnSizeOfWindow(int (&windowMargins)[2]){
    #ifdef _WINDOWS_
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        windowMargins[0] = csbi.srWindow.Right - csbi.srWindow.Left, windowMargins[1] = csbi.srWindow.Bottom - csbi.srWindow.Top;
        if (DEBUG) std::cout << "\nColumns: " << windowMargins[0] << "\nRows: " << windowMargins[1];
    #elif defined(_SYS_IOCTL_H)
        struct winsize size;
        ioctl(fileno(stdout), TIOCGWINSZ, &size);
        windowMargins[0] = (int)(size.ws_col);
        windowMargins[1] = (int)(size.ws_row);
        if (DEBUG) std::cout << "\nColumns: " << windowMargins[0] << "\nRows: " << windowMargins[1];
    #endif
    return;
}
