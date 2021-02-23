#include "menu.h"

StateManager stateManager;

void entryPoint(){
    assetData = new Assets;

    initializeStates();
    stateManager.setState("main");
    stateManager.mainLoop();
    return;
}

void initializeStates(){
    if (DEBUG) std::cout << "\nInitializing \"main\" functions\n";
    stateManager.stateList["main"].execute = &mainMenu;
    stateManager.stateList["main"].enter = &mainMenuEnter;
    stateManager.stateList["main"].exit = &mainMenuExit;

    if (DEBUG) std::cout << "\nInitializing \"game\" functions\n";
    stateManager.stateList["game"].execute = &gameMenu;
    stateManager.stateList["game"].enter = &gameMenuEnter;
    stateManager.stateList["game"].exit = &gameMenuExit;

    if (DEBUG) std::cout << "\nInitializing \"extraoptions\" functions\n";
    stateManager.stateList["extraoptions"].execute = &extraOptionsMenu;
    stateManager.stateList["extraoptions"].enter = &extraOptionsMenuEnter;
    stateManager.stateList["extraoptions"].exit = &extraOptionsMenuExit;

    if (DEBUG) std::cout <<"\nInitializing \"partyoptionsmenu\" functions\n";
    stateManager.stateList["partyoptionsmenu"].execute = &partyOptionsMenu;
    stateManager.stateList["partyoptionsmenu"].enter = &partyOptionsMenuEnter;
    stateManager.stateList["partyoptionsmenu"].exit = &partyOptionsMenuExit;

    return;
}

bool mainMenu(){
    std::cout << "\n\n-------";
    std::cout <<   "\n1: New Game";
    std::cout <<   "\n2: Load Game";
    std::cout <<   "\n3: Reload Assets";
    std::cout <<   "\n4: Remove Species";
    std::cout <<   "\n5: Erase Character";
    std::cout <<   "\n6: Calibrate Terminal Window";
    std::cout <<   "\n0: Quit Game\n";
    std::cin >> stateManager.menuInput;
    switch(inputErrorNag(stateManager.menuInput)){
        case 1:
            //reassign the playersave object so that if a player file is already loaded, we can reset the player attributes
            playerCharacter->newGame();
            stateManager.setState("game");
            break;
        case 2:
            playerCharacter->loadGame();
            if (playerCharacter->verifyPlayerName()) stateManager.setState("game");
            break;
        case 3:
            //reassigns asset object, reloading all assets from their respective files
            delete assetData;
            assetData = new Assets;
            break;
        case 4:
            assetData->removeSpecies();
            break;
        case 5:
            assetData->removeCharacter();
            break;
        case 6:
            resizeTerminalWindow();
            break;
        case 7:
            stateManager.setState("extraoptions", true);
            break;
        case 0:
            std::cout << "Goodbye.\n";
            return false;
        default:
            std::cout << "Try choosing one of the menu options.\n";
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
    std::cout << "\n\n-------";
    std::cout <<   "\n1: Equip Item";
    std::cout <<   "\n2: Unequip Item";
    std::cout <<   "\n3: Use Item";
    std::cout <<   "\n4: Save Game";
    std::cout <<   "\n5: Show Additional Options";
    std::cout <<   "\n0: Exit";
    std::cout <<   "\n";
    std::cin >> stateManager.menuInput;
    switch(inputErrorNag(stateManager.menuInput)){
        case 1:
            playerCharacter->equipPartyMember();
            break;
        case 2:
            playerCharacter->unequipPartyMember();
            break;
        case 3:
            playerCharacter->useItemPartyMember();
            break;
        case 4:
            playerCharacter->saveFile();
            break;
        case 5:
            stateManager.setState("extraoptions", true);
            break;
        case 0:
            stateManager.setState("main");
            break;
        default:
            std::cout << "Try choosing one of the menu options.\n";
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
    std::cout << "\n\n-------";
    std::cout <<   "\n1: Print Character Info";
    std::cout <<   "\n2: Print Player Inventory";
    std::cout <<   "\n3: Print Party Info";
    std::cout <<   "\n4: Print Item List";
    std::cout <<   "\n5: Print Species List";
    std::cout <<   "\n6: Print Species Descriptors";
    std::cout <<   "\n0: Return";
    std::cout <<   "\n";
    std::cin >> stateManager.menuInput;
    switch(inputErrorNag(stateManager.menuInput)){
        case 1:
            //debugging case for testing file saving and loading to ensure values are correctly stored within class member variables
            playerCharacter->printPartyMemberIndividual();
            break;
        case 2:
            playerCharacter->playerInventory_.printPlayerInv();
            break;
        case 3:
            playerCharacter->printPartyMemberInfo();
            break;
        case 4:
            assetData->printItemList();
            break;
        case 5:
            assetData->printSpeciesList();
            break;
        case 6:
            assetData->printDescriptorsList();
            break;
        case 7:
            stateManager.setState("extraoptions", true);
            break;
        case 0:
            stateManager.setState(stateManager.previousStates.last());
            stateManager.previousStates.removeLast();
            break;
        default:
            std::cout << "Try choosing one of the menu options.\n";
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
    std::cout << "\n\n-------";
    std::cout <<   "\n0: Return";
    std::cout <<   "\n";
    std::cin >> stateManager.menuInput;
    switch(inputErrorNag(stateManager.menuInput)){
        case 0:
            stateManager.setState(stateManager.previousStates.last());
            stateManager.previousStates.removeLast();
            break;
        default:
            std::cout << "Try choosing one of the menu options.\n";
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
