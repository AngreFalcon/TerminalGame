#include "statemanager.h"

StateManager::StateManager(){
    currentState = NULL;
    menuInput = -1;
    previousStates = QStringList();
    stateList = {};
}


void StateManager::setState(const QString &stateName, bool ignore){
    std::string tempOutputString = "\nSetting state to \"" + stateName.toStdString() + "\"\n";
    if (DEBUG) printw(tempOutputString.data());
    if (DEBUG) printPreviousStates();
    if (!stateList.contains(stateName)){
        std::string tempOutputString = "State \"" + stateName.toStdString() + "\" does not exist.\n";
        printw(tempOutputString.data());
        return;
    }
    if (currentState != NULL && !ignore) currentState->exit();
    for (QMap<QString, Gamestate>::iterator i = stateList.begin(); i != stateList.end(); i++){
        if (currentState == &i.value() && (previousStates.isEmpty() || previousStates.last() != i.key())) previousStates.append(i.key());
    }
    currentState = &stateList[stateName];
    if (!ignore) currentState->enter();
    clearTerm();
    return;
}

void StateManager::mainLoop(){
    bool menuLoopBool = true;
    while (menuLoopBool){
        menuLoopBool = currentState->execute();
    }
}

void StateManager::printPreviousStates(){
    for (int i = 0; i != previousStates.length(); i++){
        std::string tempOutputString = "\n" + previousStates[i].toStdString() + "\n";
        printw(tempOutputString.data());
    }
    return;
}
