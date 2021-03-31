#ifndef IOHANDLING_H
#define IOHANDLING_H
#include "globals.h"
#include "terminalmanip.h"
#include <curses.h>
#include <iostream>
#include <limits>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QString>

//functions
int inputInt();
int inputMultiInt();
char inputChar();
QString inputString(const std::string &a);

std::string isPlural(const QString &pluralString, const std::string &printStringPlural, const std::string &printStringSingular);
std::string makeStdString(const QJsonValue &input, int caseType = 0);

void dirCheck(const QString &fileLocation, const QString &terminalOutput = "");

bool ioSaveFile(const QString &fileLocation, const QString &terminalOutput, const QJsonObject &writeObject);
QJsonObject ioLoadFile(const QString &fileLocation, const QString &terminalOutput);
bool ioCreateFile(const QString &fileLocation);
void ioRemoveFile(const QString &fileLocation, const QString &terminalOutput);

//debugging functions
void printKeyInput();

#endif // IOHANDLING_H
