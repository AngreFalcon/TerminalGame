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
int inputErrorNagInt();
int inputErrorNagMultiInt();
char inputErrorNagChar();
QString askInput(const std::string &a);

std::string isPlural(const QString &pluralString, const std::string &printStringPlural, const std::string &printStringSingular);
std::string makeStdString(const QJsonValue &input, int caseType = 0);

void dirCheck(const QString &fileLocation, const QString &terminalOutput = "");

bool ioSaveFile(const QString &saveFile, const QString &terminalOutput, const QJsonObject &writeObject);
QJsonObject ioLoadFile(const QString &saveFile, const QString &terminalOutput);
void ioRemoveFile(const QString &saveFile, const QString &terminalOutput);

#endif // IOHANDLING_H
