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
    std::cout << "\nInventory:";
    for (QJsonObject::const_iterator invCount = playerInventoryMap_.begin(); invCount != playerInventoryMap_.end(); invCount++){
        QJsonObject invItem = playerInventoryMap_[invCount.key()].toObject();
        std::cout << "\n-------\n" << menuIndex << ": Item Name: " << makeStdString(invItem["itemname"]) << "\nItem Count: " << invItem["itemcount"].toInt(); menuIndex++;
        invItem = invItem["itemattributes"].toObject();
        for (QJsonObject::const_iterator i = invItem.constBegin(); i != invItem.constEnd(); i++){
            QString attributeKey = i.key();
            attributeKey[0] = attributeKey[0].toUpper();
            std::cout << "\n" << attributeKey.toStdString() << ": " << i.value().toInt();
        }
    }
    return;
}

bool Inventory::printUsableItems(const QString &itemBoolKey){
    int menuIndex = 1;
    playerUsableItemsArray_ = QStringList();
    std::cout << "\nInventory:";
    for (QJsonObject::const_iterator invCount = playerInventoryMap_.begin(); invCount != playerInventoryMap_.end(); invCount++){
        QJsonObject invItem = playerInventoryMap_[invCount.key()].toObject();
        if (invItem[itemBoolKey].toBool() && invItem["itemcount"].toInt() > 0){
            playerUsableItemsArray_.append(invCount.key());
            std::cout << "\n-------\n" << menuIndex << ": Item Name: " << makeStdString(invItem["itemname"]) << "\nItem Count: " << invItem["itemcount"].toInt(); menuIndex++;
            invItem = invItem["itemattributes"].toObject();
            for (QJsonObject::const_iterator i = invItem.constBegin(); i != invItem.constEnd(); i++){
                QString attributeKey = i.key();
                attributeKey[0] = attributeKey[0].toUpper();
                std::cout << "\n" << attributeKey.toStdString() << ": " << i.value().toInt();
            }
        }
    }
    if (playerUsableItemsArray_.size() != 0){
        std::cout << "\nEnter 0 to cancel.";
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
        std::cout << "equipped " << makeStdString(inventoryItem["itemname"]);
        if (playerEquippedItems_[inventoryItem["itemtype"].toString()] != "null"){
            std::cout << " and";
            unequippedItem(playerEquippedItems_[inventoryItem["itemtype"].toString()]);
        }
        playerEquippedItems_[inventoryItem["itemtype"].toString()] = userSelection;
        removeItem(playerUsableItemsArray_[invIndex], (1));
        return;
    }
    else {
        std::cout << "\nYour selection was invalid.";
        return;
    }
}

void Inventory::unequippedItem(const QString &invIndex){
    addItem(invIndex, (1));
    QJsonObject inventoryItem = playerInventoryMap_[invIndex].toObject();
    std::cout << " unequipped " << makeStdString(inventoryItem["itemname"]);
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
    std::cout << " used " << makeStdString(inventoryItem["itemname"]);
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
