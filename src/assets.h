#ifndef ASSETS_H
#define ASSETS_H
#include "globals.h"
#include "iohandling.h"
#include <curses.h>
#include <iostream>
#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class Assets final {
public:
    Assets();

    //load functions
    void loadItemData();
    void loadSpeciesData();
    void loadSpeciesDescriptors();

    //creation functions
    bool createSpeciesFile();
    void addNewSpecies(const QString &playerSpecies);

    //deletion functions
    bool removeSpecies();
    bool removeCharacter();

    //assignment and validation functions
    QJsonObject assignPlayerStats(const QString &playerSpecies);
    QString validateEquippedItems(const QString &invIndex);
    bool verifySpecies(const QString &speciesName);

    //print functions
    void printItemList();
    void printSpeciesList();
    void printDescriptorsList();
    void printPlayerSpecies(const QString &playerSpecies);
    void printPlayerDescription(const QString &playerSpecies);
    QJsonObject printEquippedItem(const QString &invIndex);

private:
    QJsonObject itemsMap_;
    QJsonObject speciesMap_;
    QJsonObject descriptorsMap_;
    QStringList mawDescriptorsMap_;

    //these functions are related to species creation and will only be called from within the scope of addNewSpecies()
    QJsonObject designSpecies(const QString &playerSpecies);
    void designSpeciesName(QJsonObject &speciesContainerObject, QString &userStringInput);
    QJsonObject designSpeciesStats();
    int designSpeciesStatsNag(const QString &statKey, int statPoints, int modifier);
    QJsonObject designSpeciesFeatures();
    char designSpeciesConfirmation(const QJsonObject &speciesObject);

};

#endif // ASSETS_H
