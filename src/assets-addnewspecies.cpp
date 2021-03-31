#include "assets.h"

//all functions relating to species creation here
QJsonObject Assets::designSpecies(const QString &playerSpecies){
    char verifySpecies = 'N';
    QJsonObject speciesContainerObject;
    while (verifySpecies != 'Y'){
        speciesContainerObject = QJsonObject();
        QString userStringInput = playerSpecies;
        userStringInput[0] = userStringInput[0].toUpper();

        designSpeciesName(speciesContainerObject, userStringInput);
        speciesContainerObject["stats"] = designSpeciesStats();
        speciesContainerObject["features"] = designSpeciesFeatures();
        verifySpecies = designSpeciesConfirmation(speciesContainerObject);
    }
    speciesMap_[playerSpecies] = speciesContainerObject;
    return speciesMap_;
}

void Assets::designSpeciesName(QJsonObject &speciesContainerObject, QString &userStringInput){
    speciesContainerObject["name"] = userStringInput;
    userStringInput = inputString("Please decide what the plural for your species name (" + makeStdString(userStringInput) + ") is.\n");
    speciesContainerObject["pluralname"] = userStringInput;

    std::string tempOutputString = "\nAnd enter a description for your species (" + makeStdString(speciesContainerObject["name"]) + "). Press enter to finish writing.\n----------------------------------------------------------------------";
    for (int i = 0; i < userStringInput.size(); i++) tempOutputString += "-";
    tempOutputString += "\n";
    QString speciesDescription = inputString(tempOutputString);
    speciesContainerObject["description"] = speciesDescription;

    return;
}

QJsonObject Assets::designSpeciesStats(){
    QJsonObject statsObject;
    int statPoints = 18;

    printw("\nNext, assign your stat points; health, strength, and speed\nYou have 18 points to assign in total.\n\nEnter the number of health points your species has, maximum 15.\n(Each point represents 10 health points.\n");
    statsObject["health"] = designSpeciesStatsNag("health", statPoints, 3) * 10;
    statsObject["maxhealth"] = statsObject["health"];
    statPoints -= statsObject["health"].toInt() / 10;

    std::string tempOutputString = "\nYou have " + std::to_string(statPoints) + " points remaining.\nNext, enter the number of strength points your species has.\nMaximum: " + std::to_string(statPoints-2) + "\n";
    printw(tempOutputString.data());
    statsObject["strength"] = designSpeciesStatsNag("strength", statPoints, 2);
    statPoints -= statsObject["strength"].toInt();

    tempOutputString = "\nYou have " + std::to_string(statPoints) + " points remaining.\nNow enter the number of mana points your species starts with.\nMaximum: " + std::to_string(statPoints-1) + "\n";
    printw(tempOutputString.data());
    statsObject["mana"] = designSpeciesStatsNag("mana", statPoints, 1);
    statPoints -= statsObject["mana"].toInt();

    tempOutputString = "\nYou have " + std::to_string(statPoints) + " point";
    printw(tempOutputString.data());
    if (statPoints>1) printw("s");
    printw(" remaining.\nFinally, enter the number of speed points your species will start with.\n");
    statsObject["speed"] = designSpeciesStatsNag("speed", statPoints, 0);

    return statsObject;
}

int Assets::designSpeciesStatsNag(const QString &statKey, int statPoints, int modifier){
    int userInput = inputMultiInt();
    std::string tempOutputString = "\nPlease choose a valid number of " + statKey.toStdString() + " points.\n";
    while (userInput < 1 || userInput > statPoints - modifier){
        printw(tempOutputString.data());
        userInput = inputMultiInt();
    }
    return userInput;
}

QJsonObject Assets::designSpeciesFeatures(){
    QJsonObject featuresObject;
    QStringList descriptorsList;
    std::string tempOutputString;
    printw("\nWhat is your species primarily covered in?\n");
    int j = 1;
    for (QJsonObject::const_iterator i = descriptorsMap_.constBegin(); i != descriptorsMap_.constEnd(); i++){
        descriptorsList.append(i.key());
        QString tempString = i.key(); tempString[0] = tempString[0].toUpper();
        tempOutputString = std::to_string(j) + ": " + tempString.toStdString() + "\n";
        printw(tempOutputString.data());
        j++;
    }
    j = inputInt() - 1;

    featuresObject["speciessingular"] = descriptorsMap_[descriptorsList[j]].toObject()["singular"];
    featuresObject["speciesplural"] = descriptorsMap_[descriptorsList[j]].toObject()["plural"];
    featuresObject["speciesadjective"] = descriptorsMap_[descriptorsList[j]].toObject()["adjective"];

    printw("\nAnd which of these does your species feature?\n");
    for (j = 0; j != mawDescriptorsMap_.size(); j++){
        QString tempString = mawDescriptorsMap_[j]; tempString[0] = tempString[0].toUpper();
        tempOutputString = std::to_string(j+1) + ": " + tempString.toStdString() + "\n";
        printw(tempOutputString.data());
    }
    j = inputInt() - 1;
    featuresObject["mouth"] = mawDescriptorsMap_[j];

    return featuresObject;
}

char Assets::designSpeciesConfirmation(const QJsonObject &speciesObject){
    QJsonObject featuresObject = speciesObject["features"].toObject();
    std::string tempOutputString = "\nMembers of your species are referred to as " + makeStdString(speciesObject["pluralname"]) + ".\nYour " + makeStdString(featuresObject["speciesplural"], 1);
    printw(tempOutputString.data());
    tempOutputString = isPlural(featuresObject["speciesplural"].toString(), "distinguish", "distinguishes") + " you from other inhabitants of the realm, and adorning your face is a " + makeStdString(featuresObject["mouth"], 1) + ".";
    printw(tempOutputString.data());
    printw("\n\nIs that alright? Y/N\n");
    char verifySpecies = inputChar();
    verifySpecies = toupper(verifySpecies);
    return verifySpecies;
}
