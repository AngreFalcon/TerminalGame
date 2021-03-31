#include "character.h"

Character::Character(){
    characterName_ = "null";
    characterSpecies_ = "null";
    characterLevel_ = 1;
    characterStats_ = {
        {"exhaustion", 0},
        {"experience", 0},
        {"health", 100},
        {"mana", 10},
        {"maxhealth", 100},
        {"speed", 1},
        {"strength", 1}
    };

    initializeEquippedItems();
}

void Character::equipItem(Inventory &playerInventory_){
    int userInput;
    QString userSelection;
    printw("\nChoose item to equip.\n");
    if (playerInventory_.printUsableItems("equippable")){
        printw("\n");
        userInput = inputInt() - 1;
        if (userInput < 0){
            printw("\nDidn't equip anything.");
            return;
        }
        std::string tempOutputString = "\n" + characterName_.toStdString() + " ";
        printw(tempOutputString.data());
        playerInventory_.equippedItem(userInput, userSelection, characterEquippedItems_);
        printw(".");
    }
    else{
        printw("\nNo items to equip.");
        return;
    }
}

void Character::unequipItem(Inventory &playerInventory_){
    int userInput;
    QString inventoryKey;
    printw("\nChoose item to unequip.");
    printCharacterEquippedItems();
    printw("\nEnter 0 to cancel.\n\n");
    userInput = inputInt() - 1;
    if (userInput == -1){
        printw("\nDidn't unequip anything.");
        return;
    }
    else if (userInput < -1 || userInput > equippedItemKeys_.size() - 1){
        printw("\nThat isn't a valid selection.");
        return;
    }
    else if (characterEquippedItems_[equippedItemKeys_[userInput]] == "null"){
        printw("\nNothing is equipped.");
    }
    else{
        inventoryKey = characterEquippedItems_[equippedItemKeys_[userInput]];
        characterEquippedItems_[equippedItemKeys_[userInput]] = "null";
        std::string tempOutputString = "\n" + characterName_.toStdString();
        printw(tempOutputString.data());
        playerInventory_.unequippedItem(inventoryKey);
        printw(".");
    }
    return;
}

void Character::useItem(Inventory &playerInventory_){
    int userInput;
    printw("\nChoose item to use.");
    if (playerInventory_.printUsableItems("consumable")){
        printw("\n\n");
        userInput = inputInt() - 1;
        if (userInput < 0){
            printw("\nDidn't use anything.");
            return;
        }
        std::string tempOutputString = "\n" + characterName_.toStdString();
        printw(tempOutputString.data());
        playerInventory_.usedItem(userInput, characterStats_);
        printw(".");
    }
    else{
        printw("\nNo items to use.");
        return;
    }
}

void Character::initializeEquippedItems(){
    characterEquippedItems_ = {
        //initialize held items to default values
        {"weapon", "null"},
        {"shield", "null"},
        //initialize body armor to default values
        {"helmet", "null"},
        {"bevor", "null"},
        {"cuirass", "null"},
        //initialize arm armor to default values
        {"lpauldron", "null"},
        {"rpauldron", "null"},
        {"lgauntlet", "null"},
        {"rgauntlet", "null"},
        //initialize leg armor to default values
        {"cuisses", "null"},
        {"lgreave", "null"},
        {"rgreave", "null"}
    };
    for (QMap<QString, QString>::const_iterator i = characterEquippedItems_.constBegin(); i != characterEquippedItems_.constEnd(); i++){
        equippedItemKeys_.append(i.key());
    }
    return;
}
