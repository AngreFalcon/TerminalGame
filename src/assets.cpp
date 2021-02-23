#include "assets.h"

Assets::Assets(){
    itemsMap_ = {};
    speciesMap_ = {};
    descriptorsMap_ = {};
    mawDescriptorsMap_ = QStringList();
    loadItemData();
    createSpeciesFile();
    loadSpeciesData();
    loadSpeciesDescriptors();
}

//functions used to load assets data defined here
void Assets::loadItemData(){
    itemsMap_ = ioLoadFile("/assets/items.json", "\nCouldn't load items. Double check your assets before playing.\n");
    return;
}

void Assets::loadSpeciesData(){
    speciesMap_ = ioLoadFile("/assets/species.json", "\nCouldn't load species. Double check your assets before playing.\n");
    return;
}

void Assets::loadSpeciesDescriptors(){
    QJsonObject tempMap = ioLoadFile("/assets/speciesdescriptors.json", "\nCouldn't load species descriptors. Double check your assets before playing.\n");
    descriptorsMap_ = tempMap["skindescriptors"].toObject();
    QJsonArray tempArray = tempMap["mawdescriptors"].toArray();
    for (int i = 0; i != tempArray.size(); i++){
        mawDescriptorsMap_.append(tempArray[i].toString());
    }
    return;
}


//functions used to create new assets defined here
bool Assets::createSpeciesFile(){
    QString fileLocation = QCoreApplication::applicationDirPath() + "/assets/species.json";
    QFile saveFile(fileLocation);
    if (saveFile.open(QIODevice::NewOnly)){
        QJsonObject emptyObject;
        QJsonDocument saveDoc(emptyObject);
        saveFile.write(saveDoc.toJson());
        return true;
    }
    else {
        return false;
    }
}

void Assets::addNewSpecies(const QString &playerSpecies){
    QJsonObject writeObject = designSpecies(playerSpecies);
    ioSaveFile("/assets/species.json", "\nCouldn't load species. Double check your assets before playing.\n", writeObject);
    return;
}


//functions used to delete assets defined here
bool Assets::removeSpecies(){
    std::string deleteSpeciesValidation;
    std::cout << "\nAre you sure you want to remove a species?\nThis cannot be undone. Y/N\n";
    std::cin >> deleteSpeciesValidation;
    deleteSpeciesValidation = inputErrorNag(deleteSpeciesValidation);
    if (tolower(deleteSpeciesValidation[0]) == 'y'){
        speciesMap_.remove(askInput("\nPlease enter the species name you'd like to delete.\n").toLower());
        ioSaveFile("/assets/species.json", "\nCouldn't load species. Double check your assets before playing.\n", speciesMap_);
    }
    else std::cout << "\nCanceled. Returning to menu.\n";
    return false;
}

bool Assets::removeCharacter(){
    std::string deleteCharacterValidation;
    std::cout << "\nAre you sure you want to delete a character?\nThis cannot be undone. Y/N\n";
    std::cin >> deleteCharacterValidation;
    deleteCharacterValidation = inputErrorNag(deleteCharacterValidation);
    if (tolower(deleteCharacterValidation[0]) == 'y'){
        ioRemoveFile("/saves/" + askInput("\nPlease enter the character name you'd like to delete.\n") + ".json", "\nErased save file.\n");
    }
    else std::cout << "\nCanceled. Returning to menu.\n";
    return false;
}


//functions used to validate or assign asset data defined here
QJsonObject Assets::assignPlayerStats(const QString &playerSpecies){
    return speciesMap_[playerSpecies].toObject()["stats"].toObject();
}

QString Assets::validateEquippedItems(const QString &invIndex){
    return itemsMap_[invIndex].toObject()["itemtype"].toString();
}

bool Assets::verifySpecies(const QString &speciesName){
    return speciesMap_.contains(speciesName);
}
