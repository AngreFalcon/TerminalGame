#include "statemanager.h"

StateManager::StateManager(){
    currentState = NULL;
    menuInput = -1;
    previousStates = QStringList();
    stateList = {};
}


void StateManager::setState(const QString &stateName, bool ignore){
    if (DEBUG) std::cout << "\nSetting state to \"" << stateName.toStdString() << "\"\n";
    if (DEBUG) printPreviousStates();
    if (!stateList.contains(stateName)){
        std::cout << "State \"" << stateName.toStdString() << "\" does not exist.\n";
        return;
    }
    if (currentState != NULL && !ignore) currentState->exit();
    for (QMap<QString, Gamestate>::iterator i = stateList.begin(); i != stateList.end(); i++){
        if (currentState == &i.value() && (previousStates.isEmpty() || previousStates.last() != i.key())) previousStates.append(i.key());
    }
    currentState = &stateList[stateName];
    if (!ignore) currentState->enter();
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
        std::cout << "\n" << previousStates[i].toStdString() << "\n";
    }
    return;
}
