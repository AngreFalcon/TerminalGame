#ifndef NONPLAYERCHAR_H
#define NONPLAYERCHAR_H
#include "character.h"
#include <curses.h>

class NonPlayerChar : public Character {
public:
    NonPlayerChar();

    bool canEquip;

    void printCharacterInfo(bool desc = false);

    void loadNPCFile(const QString &npcName, const QString &characterName);
    void saveNPCFile(const QString &npcName, const QString &characterName);
    void readNPCFile(const QJsonObject &json);
    QJsonObject writeNPCFile();

private:
    QJsonObject characterSpeciesObject_;

};

#endif // NONPLAYERCHAR_H
