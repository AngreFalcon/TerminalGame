#ifndef TERMINALMANIP_H
#define TERMINALMANIP_H
#include "globals.h"
#include <curses.h>
#include <iostream>

#if __has_include("windows.h")
#include <windows.h>
#elif __has_include("sys/ioctl.h")
#include <sys/ioctl.h>
#endif

void scrollTerm();
void clearTerm();
bool resizeTerminalWindow();
void returnSizeOfWindow(int (&windowMargins)[2]);

#endif // TERMINALMANIP_H
