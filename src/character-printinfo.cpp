#include "character.h"

void Character::printCharacterInfo(bool desc){
    //this is a debugging method used to print the player character's name to terminal
    std::cout << "\n-------";
    std::cout << "\nName: " << characterName_.toStdString();
    std::cout << "\nSpecies: "; assetData->printPlayerSpecies(characterSpecies_);
    std::cout << "\nLevel: " << characterLevel_;
    if (desc) {
        std::cout << "\n-------\nDescription: \n"; assetData->printPlayerDescription(characterSpecies_);
        std::cout << "\n-------";
    }
    return;
}

void Character::printCharacterStats(){
    //this is a debugging method used to print the player character's stats to terminal
    for (QMap<QString, int>::const_iterator i = characterStats_.constBegin(); i != characterStats_.constEnd(); i++){
        QString statKey = i.key();
        if (statKey.contains(QRegularExpression("^max"))) statKey[3] = statKey[3].toUpper();
        statKey[0] = statKey[0].toUpper();
        std::cout << "\n" << statKey.toStdString() << ": " << characterStats_[i.key()];
    }
    std::cout << "\n-------";
    return;
}

void Character::printCharacterEquippedItems(){
    int iteratorCount = 1;
    for (QMap<QString, QString>::const_iterator i = characterEquippedItems_.constBegin(); i != characterEquippedItems_.constEnd(); i++, iteratorCount++){
        const QString attributeKey = i.key();
        QString itemTypeName = attributeKey;
        itemTypeName[0] = itemTypeName[0].toUpper();
        if (itemTypeName[0] == 'L' || itemTypeName[0] == 'R') itemTypeName[1] = itemTypeName[1].toUpper();
        std::cout << "\n" << iteratorCount << ": "; if (iteratorCount < 10) std::cout << " ";
        std::cout << std::left << std::setw(20);
        if (characterEquippedItems_[attributeKey] != "null"){
            std::cout << "Equipped " + itemTypeName.toStdString() + ": ";
            std::cout << makeStdString(assetData->printEquippedItem(characterEquippedItems_[attributeKey])["itemname"]);
        }
        else {
            std::cout << "Equipped " + itemTypeName.toStdString() + ": " << "Nothing";
        }
    }
    std::cout << "\n-------";
    return;
}
