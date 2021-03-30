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
    printw("\n\n-------");
    printw("\n1: New Game");
    printw("\n2: Load Game");
    printw("\n3: Reload Assets");
    printw("\n4: Remove Species");
    printw("\n5: Erase Character");
    printw("\n0: Quit Game\n");
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
    printw("\n\n-------");
    printw("\n1: Equip Item");
    printw("\n2: Unequip Item");
    printw("\n3: Use Item");
    printw("\n4: Save Game");
    printw("\n5: Show Additional Options");
    printw("\n0: Exit");
    printw("\n");
    flushinp();
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
    printw("\n\n-------");
    printw("\n1: Print Character Info");
    printw("\n2: Print Player Inventory");
    printw("\n3: Print Party Info");
    printw("\n4: Print Item List");
    printw("\n5: Print Species List");
    printw("\n6: Print Species Descriptors");
    printw("\n0: Return");
    printw("\n");
    flushinp();
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
    printw("\n\n-------");
    printw("\n0: Return");
    printw("\n");
    flushinp();
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
