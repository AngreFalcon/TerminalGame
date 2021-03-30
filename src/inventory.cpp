#include "inventory.h"

Inventory::Inventory(){
    playerInventoryMap_ = {};
    playerUsableItemsArray_ = QStringList();

}

void Inventory::inventoryWriteSaveData(const QString &characterName_){
    QJsonObject writeObject;
    writeObject["playerinventory"] = playerInventoryMap_;
    ioSaveFile("/saves/" + characterName_ + "/Inventory.json", "\nCouldn't open save file.\n", writeObject);
    return;
}

void Inventory::inventoryReadSaveData(const QString &characterName_){
    QJsonObject loadData = ioLoadFile("/saves/" + characterName_ + "/Inventory.json", "\nCouldn't open save file.\n");
    playerInventoryMap_ = loadData["playerinventory"].toObject();
    return;
}

void Inventory::printPlayerInv(){
    //this is a method used to print the player character's inventory to terminal
    int menuIndex = 1;
    printw("\nInventory:");
    for (QJsonObject::const_iterator invCount = playerInventoryMap_.begin(); invCount != playerInventoryMap_.end(); invCount++){
        QJsonObject invItem = playerInventoryMap_[invCount.key()].toObject();
        std::string tempOutputString = "\n-------\n" + std::to_string(menuIndex) + ": Item Name: " + makeStdString(invItem["itemname"]) + "\nItem Count: " + std::to_string(invItem["itemcount"].toInt());
        printw(tempOutputString.data());
        menuIndex++;
        invItem = invItem["itemattributes"].toObject();
        for (QJsonObject::const_iterator i = invItem.constBegin(); i != invItem.constEnd(); i++){
            QString attributeKey = i.key();
            attributeKey[0] = attributeKey[0].toUpper();
            std::string tempOutputString = "\n" + attributeKey.toStdString() + ": " + std::to_string(i.value().toInt());
            printw(tempOutputString.data());
        }
    }
    return;
}

bool Inventory::printUsableItems(const QString &itemBoolKey){
    int menuIndex = 1;
    playerUsableItemsArray_ = QStringList();
    printw("\nInventory:");
    for (QJsonObject::const_iterator invCount = playerInventoryMap_.begin(); invCount != playerInventoryMap_.end(); invCount++){
        QJsonObject invItem = playerInventoryMap_[invCount.key()].toObject();
        if (invItem[itemBoolKey].toBool() && invItem["itemcount"].toInt() > 0){
            playerUsableItemsArray_.append(invCount.key());
            std::string tempOutputString = "\n-------\n" + std::to_string(menuIndex) + ": Item Name: " + makeStdString(invItem["itemname"]) + "\nItem Count: " + std::to_string(invItem["itemcount"].toInt()); menuIndex++;
            printw(tempOutputString.data());
            invItem = invItem["itemattributes"].toObject();
            for (QJsonObject::const_iterator i = invItem.constBegin(); i != invItem.constEnd(); i++){
                QString attributeKey = i.key();
                attributeKey[0] = attributeKey[0].toUpper();
                tempOutputString = "\n" + attributeKey.toStdString() + ": " + std::to_string(i.value().toInt());
            }
        }
    }
    if (playerUsableItemsArray_.size() != 0){
        printw("\nEnter 0 to cancel.");
        return true;
    }
    else{
        return false;
    }
}

void Inventory::equippedItem(int invIndex, QString &userSelection, QMap<QString, QString> &playerEquippedItems_){
    if (invIndex < playerUsableItemsArray_.size()){
        QJsonObject inventoryItem = playerInventoryMap_[playerUsableItemsArray_[invIndex]].toObject();
        userSelection = playerUsableItemsArray_[invIndex];
        std::string tempOutputString = "equipped " + makeStdString(inventoryItem["itemname"]);
        printw(tempOutputString.data());
        if (playerEquippedItems_[inventoryItem["itemtype"].toString()] != "null"){
            printw(" and");
            unequippedItem(playerEquippedItems_[inventoryItem["itemtype"].toString()]);
        }
        playerEquippedItems_[inventoryItem["itemtype"].toString()] = userSelection;
        removeItem(playerUsableItemsArray_[invIndex], (1));
        return;
    }
    else {
        printw("\nYour selection was invalid.");
        return;
    }
}

void Inventory::unequippedItem(const QString &invIndex){
    addItem(invIndex, (1));
    QJsonObject inventoryItem = playerInventoryMap_[invIndex].toObject();
    std::string tempOutputString = " unequipped " + makeStdString(inventoryItem["itemname"]);
    printw(tempOutputString.data());
    return;
}

void Inventory::usedItem(int invIndex, QMap<QString, int> &playerStats_){
    QJsonObject inventoryItem = playerInventoryMap_[playerUsableItemsArray_[invIndex]].toObject()["itemattributes"].toObject();
    for (QJsonObject::const_iterator i = inventoryItem.constBegin(); i != inventoryItem.constEnd(); i++){
        if (playerStats_.contains(i.key())){
            playerStats_[i.key()] = inventoryItem[i.key()].toInt() + playerStats_[i.key()];
            if (playerStats_.contains("max" + i.key()) && playerStats_[i.key()] > playerStats_["max" + i.key()]) playerStats_[i.key()] = playerStats_["max" + i.key()];
        }
    }
    inventoryItem = playerInventoryMap_[playerUsableItemsArray_[invIndex]].toObject();
    std::string tempOutputString = " used " + makeStdString(inventoryItem["itemname"]);
    printw(tempOutputString.data());
    removeItem(playerUsableItemsArray_[invIndex], (1));
    return;
}

void Inventory::removeItem(const QString &inventoryKey, int inventoryCount){
    QJsonObject inventoryItem = playerInventoryMap_[inventoryKey].toObject();
    inventoryCount = inventoryItem["itemcount"].toInt() - inventoryCount;
    if (inventoryCount > 0){
        inventoryItem["itemcount"] = inventoryCount;
        playerInventoryMap_[inventoryKey] = inventoryItem;
    }
    else playerInventoryMap_.remove(inventoryKey);
    return;
}

void Inventory::addItem(const QString &inventoryKey, int inventoryCount){
    if (playerInventoryMap_.contains(inventoryKey)){
        QJsonObject inventoryItem = playerInventoryMap_[inventoryKey].toObject();
        inventoryCount += inventoryItem["itemcount"].toInt();
        inventoryItem["itemcount"] = inventoryCount;
        playerInventoryMap_[inventoryKey] = inventoryItem;
    }
    else{
        QJsonObject inventoryItem = assetData->printEquippedItem(inventoryKey);
        inventoryItem["itemcount"] = inventoryCount;
        playerInventoryMap_[inventoryKey] = inventoryItem;
    }
    return;
}
