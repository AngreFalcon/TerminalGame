#include "player.h"

Player::Player(){
    initializeParty();
}

bool Player::verifyPlayerName(){
    if (characterName_ != "null") return true;
    else return false;
}

QString Player::selectPartyMember(const QString &printStatement, bool manageEquipment){
    int i, j = 1;
    QStringList tempList;
    std::cout << printStatement.toStdString();
    for (i = -1; i < 3; i++){
        if (i == -1){
            std::cout << "1: Yourself\n";
            tempList.append("playercharacter");
        }
        else if (partyKeys_[i] != "null" && partyKeys_[i] != "" && (!manageEquipment || (manageEquipment && playerParty_[partyKeys_[i]].canEquip))){
            j++;
            tempList.append(partyKeys_[i]);
            tempList.last()[0] = tempList.last()[0].toUpper();
            std::cout << j << ": " << tempList.last().toStdString() << "\n";
        }
    }
    std::cin >> i;
    i = inputErrorNag(i) - 1;
    if (i < 0 || i > tempList.size() - 1) std::cout << "\nYour selection was invalid.\n";
    else return tempList[i].toLower();
    return "null";
}

void Player::equipPartyMember(){
    QString tempString = selectPartyMember("\nWho do you want to equip an item to?\n");
    if (tempString == "playercharacter"){
        equipItem(playerInventory_);
    }
    else if (tempString != "null"){
        playerParty_[tempString].equipItem(playerInventory_);
    }
    return;
}

void Player::unequipPartyMember(){
    QString tempString = selectPartyMember("\nWhose equipment do you want to remove?\n");
    if (tempString == "playercharacter"){
        unequipItem(playerInventory_);
    }
    else if (tempString != "null"){
        playerParty_[tempString].unequipItem(playerInventory_);
    }
    return;
}

void Player::useItemPartyMember(){
    QString tempString = selectPartyMember("\nWho would you like to use an item on?\n", false);
    if (tempString == "playercharacter"){
        useItem(playerInventory_);
    }
    else if (tempString != "null"){
        playerParty_[tempString].useItem(playerInventory_);
    }
    return;
}

void Player::printPartyMemberInfo(){
    std::cout << "\nParty Members:";
    for (int i = 0; i < 3; i++){
        if (partyKeys_[i] != "null" && partyKeys_[i] != "") playerParty_[partyKeys_[i]].printCharacterInfo();
    }
    return;
}

void Player::printPartyMemberIndividual(){
    QString tempString = selectPartyMember("\nWhose information do you want to review?\n", false);
    if (tempString == "playercharacter"){
        printCharacterInfo(true);
        printCharacterStats();
        printPartyMemberInfo();
        printCharacterEquippedItems();
    }
    else if (tempString != "null"){
        playerParty_[tempString].printCharacterInfo(true);
        playerParty_[tempString].printCharacterStats();
        playerParty_[tempString].printCharacterEquippedItems();
    }
    return;
}

void Player::initializeParty(){
    playerParty_ = {};
    partyKeys_ = QStringList();
    for (int i = 0; i < 3; i++){
        partyKeys_.append("null");
    }
    std::cout << "\nsuccess";
    return;
}
