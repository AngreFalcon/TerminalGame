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
    std::cout << "\nChoose item to equip.\n";
    if (playerInventory_.printUsableItems("equippable")){
        std::cout << "\n"; std::cin >> userInput;
        userInput = inputErrorNag(userInput) - 1;
        if (userInput < 0){
            std::cout << "\nDidn't equip anything.";
            return;
        }
        std::cout << "\n" << characterName_.toStdString() << " ";
        playerInventory_.equippedItem(userInput, userSelection, characterEquippedItems_);
        std::cout << ".";
    }
    else{
        std::cout << "\nNo items to equip.";
        return;
    }
}

void Character::unequipItem(Inventory &playerInventory_){
    int userInput;
    QString inventoryKey;
    std::cout << "\nChoose item to unequip.";
    printCharacterEquippedItems();
    std::cout << "\nEnter 0 to cancel.\n\n";
    std::cin >> userInput;
    userInput = inputErrorNag(userInput) - 1;
    if (userInput == -1){
        std::cout << "\nDidn't unequip anything.";
        return;
    }
    else if (userInput < -1 || userInput > equippedItemKeys_.size() - 1){
        std::cout << "\nThat isn't a valid selection.";
        return;
    }
    else if (characterEquippedItems_[equippedItemKeys_[userInput]] == "null"){
        std::cout << "\nNothing is equipped.";
    }
    else{
        inventoryKey = characterEquippedItems_[equippedItemKeys_[userInput]];
        characterEquippedItems_[equippedItemKeys_[userInput]] = "null";
        std::cout << "\n" << characterName_.toStdString();
        playerInventory_.unequippedItem(inventoryKey);
        std::cout << ".";
    }
    return;
}

void Character::useItem(Inventory &playerInventory_){
    int userInput;
    std::cout << "\nChoose item to use.";
    if (playerInventory_.printUsableItems("consumable")){
        std::cout << "\n\n";
        std::cin >> userInput;
        userInput = inputErrorNag(userInput);
        userInput--;
        if (userInput < 0){
            std::cout << "\nDidn't use anything.";
            return;
        }
        std::cout << "\n" << characterName_.toStdString();
        playerInventory_.usedItem(userInput, characterStats_);
        std::cout << ".";
    }
    else{
        std::cout << "\nNo items to use.";
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
