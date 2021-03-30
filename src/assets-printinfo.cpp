#include "assets.h"

//print functions defined in here
void Assets::printItemList(){
    for (QJsonObject::const_iterator i = itemsMap_.constBegin(); i != itemsMap_.constEnd(); i++){
        if (itemsMap_[i.key()].toObject()["itemname"].toString() != ""){
            std::string tempOutputString = "\n" + makeStdString(itemsMap_[i.key()].toObject()["itemname"]);
            printw(tempOutputString.data());
        }
    }
}

void Assets::printSpeciesList(){
    for (QJsonObject::const_iterator i = speciesMap_.constBegin(); i != speciesMap_.constEnd(); i++){
        if (speciesMap_[i.key()].toObject()["name"].toString() != ""){
            std::string tempOutputString = "\n" + makeStdString(speciesMap_[i.key()].toObject()["name"]);
            printw(tempOutputString.data());
        }
    }
}

void Assets::printDescriptorsList(){
    std::string tempOutputString;
    for (QJsonObject::const_iterator i = descriptorsMap_.constBegin(); i != descriptorsMap_.constEnd(); i++){
        tempOutputString = "\n" + i.key().toStdString();
        printw(tempOutputString.data());
    }
    for (int i = 0; i != mawDescriptorsMap_.size(); i++){
        tempOutputString = "\n" + mawDescriptorsMap_[i].toStdString();
        printw(tempOutputString.data());
    }
}

void Assets::printPlayerSpecies(const QString &playerSpecies){
    printw(makeStdString(speciesMap_[playerSpecies].toObject()["name"]).data());
    return;
}

void Assets::printPlayerDescription(const QString &playerSpecies){
    printw(makeStdString(speciesMap_[playerSpecies].toObject()["description"]).data());
    return;
}

QJsonObject Assets::printEquippedItem(const QString &invIndex){
    return itemsMap_[invIndex].toObject();
}
