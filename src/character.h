#ifndef CHARACTER_H
#define CHARACTER_H
#include "assets.h"
#include "globals.h"
#include "inventory.h"
#include "iohandling.h"
#include <cmath>
#include <curses.h>
#include <iomanip>
#include <iostream>
#include <QMap>
#include <QString>
#include <QStringList>

class Character {
public:
    Character();

    //functions for printing class data belong here
    virtual void printCharacterInfo(bool desc = false);
    void printCharacterStats();
    void printCharacterEquippedItems();

    void equipItem(Inventory &playerInventory_);
    void unequipItem(Inventory &playerInventory_);
    void useItem(Inventory &playerInventory_);

protected:
    int characterLevel_;
    QString characterName_;
    QString characterSpecies_;
    QMap<QString, int> characterStats_;
    QMap<QString, QString> characterEquippedItems_;

private:
    QStringList equippedItemKeys_;

    void initializeEquippedItems();

};

#endif // CHARACTER_H
