#include "nonplayerchar.h"

NonPlayerChar::NonPlayerChar(){
    canEquip = true;
}

void NonPlayerChar::printCharacterInfo(bool desc){
    //this is a debugging method used to print the player character's name to terminal
    std::cout << "\n-------";
    std::cout << "\nName: " << characterName_.toStdString();
    std::cout << "\nSpecies: ";
    if (characterSpecies_ != "null") assetData->printPlayerSpecies(characterSpecies_);
    else std::cout << makeStdString(characterSpeciesObject_["name"]);
    std::cout << "\nLevel: " << characterLevel_;
    if (desc) {
        std::cout << "\n-------\nDescription: \n";
        if (characterSpecies_ != "null") assetData->printPlayerDescription(characterSpecies_);
        else std::cout << makeStdString(characterSpeciesObject_["description"]);
        std::cout << "\n-------";
    }
    return;
}

void NonPlayerChar::loadNPCFile(const QString &npcName, const QString &characterName){
    QJsonObject loadData = ioLoadFile("/assets/nonplayercharacters.json", "\nCouldn't open NPC assets file.\n");
    loadData = loadData[npcName.toLower()].toObject();
    QJsonObject loadData2 = ioLoadFile("/saves/" + characterName + "/NPCs.json", "\nCouldn't open NPC save file.\n");
    if (loadData2.contains(npcName.toLower())) {
        loadData = loadData2[npcName.toLower()].toObject();
    }
    readNPCFile(loadData);
    return;
}

void NonPlayerChar::saveNPCFile(const QString &npcName, const QString &characterName){
    if (npcName != "" && npcName != "null"){
        QJsonObject writeObject = ioLoadFile("/saves/" + characterName + "/NPCs.json", "\nCouldn't open NPC save file.\n");
        writeObject[npcName.toLower()] = writeNPCFile();
        ioSaveFile("/saves/" + characterName + "/NPCs.json", "\nCouldn't open NPC save file.\n", writeObject);
    }
    return;
}

void NonPlayerChar::readNPCFile(const QJsonObject &json){
    //read contents of player object from save file
    characterName_ = json["name"].toString();
    if (json["species"].isString()) characterSpecies_ = json["species"].toString();
    else characterSpeciesObject_ = json["species"].toObject();
    characterLevel_ = json["level"].toInt();

    //after reading in all contents of player object, move on to player stats object contained within player object
    QJsonObject playerStatsObject = json["stats"].toObject();
    QJsonObject::const_iterator i;
    for (i = playerStatsObject.constBegin(); i != playerStatsObject.constEnd(); i++){
        QString statKey = i.key();
        characterStats_[statKey] = playerStatsObject[statKey].toInt();
    }

    if (json["equippeditems"].isObject()){
        //check to ensure that equipped items are valid and of correct type for each equip slot, and if not, equip nothing to slot
        QJsonObject equippedItemsObject = json["equippeditems"].toObject();
        for (i = equippedItemsObject.constBegin(); i != equippedItemsObject.constEnd(); i++){
            QString attributeKey = i.key();
            if (assetData->validateEquippedItems(equippedItemsObject[attributeKey].toString()).toStdString() != attributeKey.toStdString()) characterEquippedItems_[attributeKey] = "null";
            else if (equippedItemsObject[attributeKey] == "") characterEquippedItems_[attributeKey] = "null";
            else characterEquippedItems_[attributeKey] = equippedItemsObject[attributeKey].toString();
        }
    }
    else if (json["equippeditems"].isBool()) canEquip = json["equippeditems"].toBool();
    return;
}

QJsonObject NonPlayerChar::writeNPCFile(){
    //create temporary json container and store player information to to
    QJsonObject playerObject;
    playerObject["name"] = characterName_;
    if (characterSpecies_ != "null") playerObject["species"] = characterSpecies_;
    else playerObject["species"] = characterSpeciesObject_;
    playerObject["level"] = characterLevel_;

    //iterate through player's stats and store their values to the correct key in temporary player stats object
    QJsonObject playerStatsObject;
    for (QMap<QString, int>::const_iterator i = characterStats_.constBegin(); i != characterStats_.constEnd(); i++){
        playerStatsObject[i.key()] = characterStats_[i.key()];
    }

    //iterate through equipped items and store their values to their corresponding key in our temporary equipped items object
    QJsonObject equippedItemsObject;
    for (QMap<QString, QString>::const_iterator i = characterEquippedItems_.constBegin(); i != characterEquippedItems_.constEnd(); i++){
        QString attributeKey = i.key();
        if (attributeKey == "") attributeKey = "null";
        equippedItemsObject[attributeKey] = characterEquippedItems_[attributeKey];
    }

    //save second temporary json container to our parent json object
    playerObject["stats"] = playerStatsObject;
    if (canEquip) playerObject["equippeditems"] = equippedItemsObject;
    else playerObject["equippeditems"] = false;

    //save initial temporary json object to our permanent player json container for writing to file
    return playerObject;
}
