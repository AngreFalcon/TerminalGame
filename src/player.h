#ifndef PLAYER_H
#define PLAYER_H
#include "assets.h"
#include "globals.h"
#include "iohandling.h"
#include "character.h"
#include "nonplayerchar.h"
#include <curses.h>
#include <QJsonObject>
#include <QMap>

class Player final : public Character {
public:
    Player();

    Inventory playerInventory_;

    void printPartyMemberInfo();
    void printPartyMemberIndividual();

    QString selectPartyMember(const QString &printStatement, bool manageEquipment = true);

    void equipPartyMember();
    void unequipPartyMember();
    void useItemPartyMember();

    bool verifyPlayerName();
    void newGame();
    void loadGame();
    void saveFile();
    void loadFile();

private:
    QJsonObject writeSaveFile();
    void readSaveFile(const QJsonObject &json);
    QMap<QString, NonPlayerChar> playerParty_;
    QStringList partyKeys_;

    bool createNPCFile();
    void initializeParty();
    void loadParty();
    void saveParty();
};

#endif // PLAYER_H
