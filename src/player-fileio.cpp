#include "player.h"

void Player::newGame(){
    characterName_ = askInput("Name your character.\n");
    characterSpecies_ = askInput("Name your species.\n").toLower();
    if (!assetData->verifySpecies(characterSpecies_)) assetData->addNewSpecies(characterSpecies_);
    QJsonObject playerStatsObject = assetData->assignPlayerStats(characterSpecies_);
    for (QJsonObject::const_iterator i = playerStatsObject.constBegin(); i != playerStatsObject.constEnd(); i++)
        characterStats_[i.key()] = playerStatsObject[i.key()].toInt();
    dirCheck("/saves/" + characterName_ + "/");
    createNPCFile();
    saveFile();
    return;
}

void Player::loadGame(){
    characterName_ = askInput("What is the name of your character?\n");
    createNPCFile();
    loadFile();
    return;
}

void Player::saveFile(){
    QJsonObject writeObject;
    writeObject["player"] = writeSaveFile();
    ioSaveFile("/saves/" + characterName_ + "/" + characterName_ + ".json", "\nCouldn't open save file.\n", writeObject);
    saveParty();
    return;
}

void Player::loadFile(){
    QJsonObject loadData = ioLoadFile("/saves/" + characterName_ + "/" + characterName_ + ".json", "\nCouldn't open save file.\n");
    loadData = loadData["player"].toObject();
    readSaveFile(loadData);
    loadParty();
    return;
}

void Player::loadParty(){
    for (int i = 0; i < 3; i++){
        if (partyKeys_[i] != "null" && partyKeys_[i] != ""){
            playerParty_.insert(partyKeys_[i], NonPlayerChar());
            playerParty_[partyKeys_[i]].loadNPCFile(partyKeys_[i], characterName_);//npc initialization function; pass partyKeys_[i] to specify NPC ID for NPC construction
        }
    }
    return;
}

void Player::saveParty(){
    for (int i = 0; i < 3; i++){
        if (partyKeys_[i] != "null" && partyKeys_[i] != ""){
            playerParty_[partyKeys_[i]].saveNPCFile(partyKeys_[i], characterName_);
        }
    }
    return;
}


QJsonObject Player::writeSaveFile(){
    //create temporary json container and store player information to to
    QJsonObject playerObject;
    playerObject["name"] = characterName_;
    playerObject["species"] = characterSpecies_;
    playerObject["level"] = characterLevel_;
    playerInventory_.inventoryWriteSaveData(characterName_);

    //iterate through list of party member IDs and save them to json array in player's save file
    QJsonArray playerPartyMembers;
    for (int i = 0; i < partyKeys_.length(); i++){
        if (i == 3) break;
        playerPartyMembers.append(partyKeys_[i]);
    }

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
    playerObject["memberids"] = playerPartyMembers;
    playerObject["stats"] = playerStatsObject;
    playerObject["equippeditems"] = equippedItemsObject;

    //save initial temporary json object to our permanent player json container for writing to file
    return playerObject;
}

void Player::readSaveFile(const QJsonObject &json){
    //read contents of player object from save file
    characterName_ = json["name"].toString();
    characterSpecies_ = json["species"].toString();
    characterLevel_ = json["level"].toInt();
    playerInventory_.inventoryReadSaveData(characterName_);

    QJsonArray playerPartyMembers = json["memberids"].toArray();
    for (int i = 0; i < playerPartyMembers.size(); i++){
        if (i == 3) break;
        partyKeys_[i] = playerPartyMembers[i].toString();
    }

    //after reading in all contents of player object, move on to player stats object contained within player object
    QJsonObject playerStatsObject = json["stats"].toObject();
    QJsonObject::const_iterator i;
    for (i = playerStatsObject.constBegin(); i != playerStatsObject.constEnd(); i++){
        QString statKey = i.key();
        characterStats_[statKey] = playerStatsObject[statKey].toInt();
    }

    //check to ensure that equipped items are valid and of correct type for each equip slot, and if not, equip nothing to slot
    QJsonObject equippedItemsObject = json["equippeditems"].toObject();
    for (i = equippedItemsObject.constBegin(); i != equippedItemsObject.constEnd(); i++){
        QString attributeKey = i.key();
        if (assetData->validateEquippedItems(equippedItemsObject[attributeKey].toString()).toStdString() != attributeKey.toStdString()) characterEquippedItems_[attributeKey] = "null";
        else if (equippedItemsObject[attributeKey] == "") characterEquippedItems_[attributeKey] = "null";
        else characterEquippedItems_[attributeKey] = equippedItemsObject[attributeKey].toString();
    }
    return;
}

bool Player::createNPCFile(){
    QString fileLocation = QCoreApplication::applicationDirPath() + "/saves/" + characterName_ + "/NPCs.json";
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
