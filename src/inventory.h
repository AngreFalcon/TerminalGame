#ifndef INVENTORY_H
#define INVENTORY_H
#include "assets.h"
#include "globals.h"
#include <iomanip>
#include <iostream>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QVector>

class Assets;

class Inventory final {
public:
    Inventory();
    void inventoryWriteSaveData(const QString &characterName_);
    void inventoryReadSaveData(const QString &characterName_);

    void printPlayerInv();
    bool printUsableItems(const QString &itemBoolKey);

    void equippedItem(int invIndex, QString &userSelection, QMap<QString, QString> &playerEquippedItems_);
    void unequippedItem(const QString &invIndex);
    void usedItem(int invIndex, QMap<QString, int> &playerStats_);

private:
    QJsonObject playerInventoryMap_;
    QStringList playerUsableItemsArray_;

    void removeItem(const QString &inventoryKey, int inventoryCount);
    void addItem(const QString &inventoryKey, int inventoryCount);

};

#endif // INVENTORY_H
