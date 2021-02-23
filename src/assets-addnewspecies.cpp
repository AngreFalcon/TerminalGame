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
    std::string speciesDescription;

    speciesContainerObject["name"] = userStringInput;
    userStringInput = askInput("Please decide what the plural for your species name is.\n");
    speciesContainerObject["pluralname"] = userStringInput;

    std::cout << "\nAnd enter a description for your species (" << makeStdString(speciesContainerObject["name"]) << "). Press enter to finish writing.\n----------------------------------------------------------------------";
    for (int i = 0; i < userStringInput.size(); i++) std::cout << "-";
    std::cout << "\n";
    std::getline(std::cin, speciesDescription);

    speciesContainerObject["description"] = QString::fromStdString(speciesDescription);

    return;
}

QJsonObject Assets::designSpeciesStats(){
    QJsonObject statsObject;
    int statPoints = 18;

    std::cout << "\nNext, assign your stat points; health, strength, and speed\nYou have 18 points to assign in total.\n\nEnter the number of health points your species has, maximum 15.\n(Each point represents 10 health points.\n";
    statsObject["health"] = designSpeciesStatsNag("health", statPoints, 3) * 10;
    statsObject["maxhealth"] = statsObject["health"];
    statPoints -= statsObject["health"].toInt() / 10;

    std::cout << "\nYou have " << statPoints << " points remaining.\nNext, enter the number of strength points your species has.\nMaximum: " << statPoints - 2 << "\n";
    statsObject["strength"] = designSpeciesStatsNag("strength", statPoints, 2);
    statPoints -= statsObject["strength"].toInt();

    std::cout << "\nYou have " << statPoints << " points remaining.\nNow enter the number of mana points your species starts with.\nMaximum: " << statPoints - 1 << "\n";
    statsObject["mana"] = designSpeciesStatsNag("mana", statPoints, 1);
    statPoints -= statsObject["mana"].toInt();

    std::cout << "\nYou have " << statPoints << " point"; if (statPoints>1) std::cout << "s"; std::cout << " remaining.\nFinally, enter the number of speed points your species will start with.\n";
    statsObject["speed"] = designSpeciesStatsNag("speed", statPoints, 0);

    return statsObject;
}

int Assets::designSpeciesStatsNag(const QString &statKey, int statPoints, int modifier){
    int userInput;
    std::cin >> userInput;
    userInput = inputErrorNag(userInput);
    while (userInput < 1 || userInput > statPoints - modifier){
        std::cout << "\nPlease choose a valid number of " << statKey.toStdString() << " points.\n";
        std::cin >> userInput;
        userInput = inputErrorNag(userInput);
    }
    return userInput;
}

QJsonObject Assets::designSpeciesFeatures(){
    QJsonObject featuresObject;
    QStringList descriptorsList;
    std::cout << "\nWhat is your species primarily covered in?\n";
    int j = 1;
    for (QJsonObject::const_iterator i = descriptorsMap_.constBegin(); i != descriptorsMap_.constEnd(); i++){
        descriptorsList.append(i.key());
        QString tempString = i.key(); tempString[0] = tempString[0].toUpper();
        std::cout << j << ": " << tempString.toStdString() << "\n";
        j++;
    }
    std::cin >> j;
    j = inputErrorNag(j);

    featuresObject["speciessingular"] = descriptorsMap_[descriptorsList[j-1]].toObject()["singular"];
    featuresObject["speciesplural"] = descriptorsMap_[descriptorsList[j-1]].toObject()["plural"];
    featuresObject["speciesadjective"] = descriptorsMap_[descriptorsList[j-1]].toObject()["adjective"];

    std::cout << "\nAnd which of these does your species feature?\n";
    for (j = 0; j != mawDescriptorsMap_.size(); j++){
        QString tempString = mawDescriptorsMap_[j]; tempString[0] = tempString[0].toUpper();
        std::cout << j+1 << ": " << tempString.toStdString() << "\n";
    }
    std::cin >> j;
    j = inputErrorNag(j);
    featuresObject["mouth"] = mawDescriptorsMap_[j-1];

    return featuresObject;
}

char Assets::designSpeciesConfirmation(const QJsonObject &speciesObject){
    char verifySpecies;
    QJsonObject featuresObject = speciesObject["features"].toObject();
    std::cout << "\nMembers of your species are referred to as " << makeStdString(speciesObject["pluralname"]) << ".\nYour " << makeStdString(featuresObject["speciesplural"], 1);
    std::cout << isPlural(featuresObject["speciesplural"].toString(), "distinguish", "distinguishes") << " you from other inhabitants of the realm, and adorning your face is a " << makeStdString(featuresObject["mouth"], 1) << ".";
    std::cout << "\n\nIs that alright? Y/N\n";
    std::cin >> verifySpecies;
    verifySpecies = inputErrorNag(verifySpecies);
    verifySpecies = toupper(verifySpecies);
    return verifySpecies;
}
