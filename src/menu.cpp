#include "menu.h"

StateManager stateManager;

void entryPoint(){
    assetData = new Assets;

    //resizeTerminalWindow();
    initializeStates();
    stateManager.setState("main");
    stateManager.mainLoop();
    return;
}

void initializeStates(){
    if (DEBUG) printw("\nInitializing \"main\" functions\n");
    stateManager.stateList["main"].execute = &mainMenu;
    stateManager.stateList["main"].enter = &mainMenuEnter;
    stateManager.stateList["main"].exit = &mainMenuExit;

    if (DEBUG) printw("\nInitializing \"game\" functions\n");
    stateManager.stateList["game"].execute = &gameMenu;
    stateManager.stateList["game"].enter = &gameMenuEnter;
    stateManager.stateList["game"].exit = &gameMenuExit;

    if (DEBUG) printw("\nInitializing \"extraoptions\" functions\n");
    stateManager.stateList["extraoptions"].execute = &extraOptionsMenu;
    stateManager.stateList["extraoptions"].enter = &extraOptionsMenuEnter;
    stateManager.stateList["extraoptions"].exit = &extraOptionsMenuExit;

    if (DEBUG) printw("\nInitializing \"partyoptionsmenu\" functions\n");
    stateManager.stateList["partyoptionsmenu"].execute = &partyOptionsMenu;
    stateManager.stateList["partyoptionsmenu"].enter = &partyOptionsMenuEnter;
    stateManager.stateList["partyoptionsmenu"].exit = &partyOptionsMenuExit;

    return;
}

bool mainMenu(){
    printw("\n\n--------\n"
               "1: New Game\n"
               "2: Load Game\n"
               "3: Reload Assets\n"
               "4: Remove Species\n"
               "5: Erase Character\n"
               "0: Quit Game\n");
    stateManager.menuInput = inputErrorNagInt();
    switch(stateManager.menuInput){
        case '1':
            //reassign the playersave object so that if a player file is already loaded, we can reset the player attributes
            playerCharacter->newGame();
            stateManager.setState("game");
            break;
        case '2':
            playerCharacter->loadGame();
            if (playerCharacter->verifyPlayerName()) stateManager.setState("game");
            break;
        case '3':
            //reassigns asset object, reloading all assets from their respective files
            delete assetData;
            assetData = new Assets;
            break;
        case '4':
            assetData->removeSpecies();
            break;
        case '5':
            assetData->removeCharacter();
            break;
        case '6':
            stateManager.setState("extraoptions", true);
            break;
        case '0':
            printw("Goodbye.\n");
            return false;
        default:
            printw("Try choosing one of the menu options.\n");
            break;
    }
    return true;
}

void mainMenuEnter(){
    playerCharacter = new Player;
    return;
}

void mainMenuExit(){
    return;
}

bool gameMenu(){
    printw("\n\n--------\n"
               "1: Equip Item\n"
               "2: Unequip Item\n"
               "3: Use Item\n"
               "4: Save Game\n"
               "5: Show Additional Options\n"
               "0: Exit\n");
    stateManager.menuInput = inputErrorNagInt();
    switch(stateManager.menuInput){
        case '1':
            playerCharacter->equipPartyMember();
            break;
        case '2':
            playerCharacter->unequipPartyMember();
            break;
        case '3':
            playerCharacter->useItemPartyMember();
            break;
        case '4':
            playerCharacter->saveFile();
            break;
        case '5':
            stateManager.setState("extraoptions", true);
            break;
        case '0':
            stateManager.setState("main");
            break;
        default:
            printw("Try choosing one of the menu options.\n");
            break;
    }
    return true;
}

void gameMenuEnter(){
    return;
}

void gameMenuExit(){
    delete playerCharacter;
    return;
}

bool extraOptionsMenu(){
    printw("\n\n--------\n"
               "1: Print Character Info\n"
               "2: Print Player Inventory\n"
               "3: Print Party Inf\n"
               "4: Print Item List\n"
               "5: Print Species List\n"
               "6: Print Species Descriptors\n"
               "0: Return\n");
    stateManager.menuInput = inputErrorNagInt();
    switch(stateManager.menuInput){
        case '1':
            //debugging case for testing file saving and loading to ensure values are correctly stored within class member variables
            playerCharacter->printPartyMemberIndividual();
            break;
        case '2':
            playerCharacter->playerInventory_.printPlayerInv();
            break;
        case '3':
            playerCharacter->printPartyMemberInfo();
            break;
        case '4':
            assetData->printItemList();
            break;
        case '5':
            assetData->printSpeciesList();
            break;
        case '6':
            assetData->printDescriptorsList();
            break;
        case '7':
            stateManager.setState("extraoptions", true);
            break;
        case '0':
            stateManager.setState(stateManager.previousStates.last());
            stateManager.previousStates.removeLast();
            break;
        default:
            printw("Try choosing one of the menu options.\n");
            break;
    }
    return true;
}

void extraOptionsMenuEnter(){
    return;
}

void extraOptionsMenuExit(){
    return;
}

bool partyOptionsMenu(){
    printw("\n\n--------\n"
               "0: Return\n");
    stateManager.menuInput = inputErrorNagInt();
    switch(stateManager.menuInput){
        case '0':
            stateManager.setState(stateManager.previousStates.last());
            stateManager.previousStates.removeLast();
            break;
        default:
            printw("Try choosing one of the menu options.\n");
            break;
    }
    return true;
}

void partyOptionsMenuEnter(){
    return;
}

void partyOptionsMenuExit(){
    return;
}
