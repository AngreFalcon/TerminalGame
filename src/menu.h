#ifndef MENU_H
#define MENU_H
#include "assets.h"
#include "globals.h"
#include "iohandling.h"
#include "player.h"
#include "statemanager.h"
#include "terminalmanip.h"
#include <iostream>
#include <QMap>

void entryPoint();
void initializeStates();

bool mainMenu();
void mainMenuEnter();
void mainMenuExit();

bool gameMenu();
void gameMenuEnter();
void gameMenuExit();

bool extraOptionsMenu();
void extraOptionsMenuEnter();
void extraOptionsMenuExit();

bool partyOptionsMenu();
void partyOptionsMenuEnter();
void partyOptionsMenuExit();

#endif // MENU_H
