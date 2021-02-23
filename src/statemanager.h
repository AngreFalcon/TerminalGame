#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "globals.h"
#include <iostream>
#include <QMap>
#include <QString>

class Gamestate final {
public:
    void (*enter)() = [](){return;};
    void (*exit)() = [](){return;};
    bool (*execute)() = [](){return false;};

};

class StateManager final {
public:
    StateManager();

    int menuInput;
    QMap<QString, Gamestate> stateList;
    QStringList previousStates;

    void setState(const QString &stateName, bool ignore = false);
    void mainLoop();

    void printPreviousStates();

private:
    Gamestate *currentState;

};

#endif // STATEMANAGER_H
