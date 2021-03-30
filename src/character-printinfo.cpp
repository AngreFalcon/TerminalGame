#include "character.h"

void Character::printCharacterInfo(bool desc){
    std::string tempOutputString;
    //this is a debugging method used to print the player character's name to terminal
    printw("\n-------");
    tempOutputString = "\nName: " + characterName_.toStdString();
    printw(tempOutputString.data());
    printw("\nSpecies: ");
    assetData->printPlayerSpecies(characterSpecies_);
    tempOutputString = "\nLevel: " + std::to_string(characterLevel_);
    printw(tempOutputString.data());
    if (desc) {
        printw("\n-------\nDescription: \n");
        assetData->printPlayerDescription(characterSpecies_);
    }
    printw("\n-------");
    return;
}

void Character::printCharacterStats(){
    //this is a debugging method used to print the player character's stats to terminal
    for (QMap<QString, int>::const_iterator i = characterStats_.constBegin(); i != characterStats_.constEnd(); i++){
        QString statKey = i.key();
        if (statKey.contains(QRegularExpression("^max"))) statKey[3] = statKey[3].toUpper();
        statKey[0] = statKey[0].toUpper();
        std::string tempOutputString = "\n" + statKey.toStdString() + ": " + std::to_string(characterStats_[i.key()]);
        printw(tempOutputString.data());
    }
    printw("\n-------");
    return;
}

void Character::printCharacterEquippedItems(){
    int iteratorCount = 1;
    std::string tempOutputString;
    for (QMap<QString, QString>::const_iterator i = characterEquippedItems_.constBegin(); i != characterEquippedItems_.constEnd(); i++, iteratorCount++){
        const QString attributeKey = i.key();
        QString itemTypeName = attributeKey;
        itemTypeName[0] = itemTypeName[0].toUpper();
        if (itemTypeName[0] == 'L' || itemTypeName[0] == 'R') itemTypeName[1] = itemTypeName[1].toUpper();
        tempOutputString = "\n" + std::to_string(iteratorCount) + ": ";
        printw(tempOutputString.data());
        if (iteratorCount < 10) printw(" ");
        std::cout << std::left << std::setw(20);
        if (characterEquippedItems_[attributeKey] != "null"){
            tempOutputString = "Equipped " + itemTypeName.toStdString() + ": ";
            printw(tempOutputString.data());
            tempOutputString = makeStdString(assetData->printEquippedItem(characterEquippedItems_[attributeKey])["itemname"]);
            printw(tempOutputString.data());
        }
        else {
            tempOutputString = "Equipped " + itemTypeName.toStdString() + ": " + "Nothing";
            printw(tempOutputString.data());
        }
    }
    printw("\n-------");
    return;
}
