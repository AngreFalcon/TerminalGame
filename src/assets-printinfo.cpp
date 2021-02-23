#include "assets.h"

//print functions defined in here
void Assets::printItemList(){
    for (QJsonObject::const_iterator i = itemsMap_.constBegin(); i != itemsMap_.constEnd(); i++){
        if (itemsMap_[i.key()].toObject()["itemname"].toString() != ""){
            std::cout << "\n" << makeStdString(itemsMap_[i.key()].toObject()["itemname"]);
        }
    }
}

void Assets::printSpeciesList(){
    for (QJsonObject::const_iterator i = speciesMap_.constBegin(); i != speciesMap_.constEnd(); i++){
        if (speciesMap_[i.key()].toObject()["name"].toString() != ""){
            std::cout << "\n" << makeStdString(speciesMap_[i.key()].toObject()["name"]);
        }
    }
}

void Assets::printDescriptorsList(){
    for (QJsonObject::const_iterator i = descriptorsMap_.constBegin(); i != descriptorsMap_.constEnd(); i++){
        std::cout << "\n" << i.key().toStdString();
    }
    for (int i = 0; i != mawDescriptorsMap_.size(); i++){
        std::cout << "\n" << mawDescriptorsMap_[i].toStdString();
    }
}

void Assets::printPlayerSpecies(const QString &playerSpecies){
    std::cout << makeStdString(speciesMap_[playerSpecies].toObject()["name"]);
    return;
}

void Assets::printPlayerDescription(const QString &playerSpecies){
    std::cout << makeStdString(speciesMap_[playerSpecies].toObject()["description"]);
    return;
}

QJsonObject Assets::printEquippedItem(const QString &invIndex){
    return itemsMap_[invIndex].toObject();
}
