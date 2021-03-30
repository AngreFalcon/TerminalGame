#include "iohandling.h"

//source file containing exclusively input handling, including error checking and input validation

int inputErrorNagInt(){
    int a;
    while (!(a = getch()) || !isdigit(a)){
        printw("\n---------------------\nYour input is invalid\n");
        flushinp();
    }
    clearTerm();
    flushinp();
    return a;
}

char inputErrorNagChar(){
    char a;
    while (!(a = getch()) || !isalpha(a)){
        printw("\n---------------------\nYour input is invalid\n");
        flushinp();
    }
    flushinp();
    return a;
}

QString askInput(const std::string &a){
    bool retryInput;
    std::string tempUserValue;
    std::string tempOutputString;
    char verify;
    do {
        printw(a.data());
        nocbreak();
        echo();
        while((verify = getch()) != '\n'){
            tempUserValue.push_back(char(verify));
        }
        tempOutputString = "Is " + tempUserValue + " correct? Y/N\n";
        printw(tempOutputString.data());
        cbreak();
        noecho();
        verify = inputErrorNagChar();
        if (toupper(verify) == 'Y'){
            retryInput = false;
        }
        else {
            retryInput = true;
            tempUserValue = "";
            refresh();
        }
    } while (retryInput == true);
    return QString::fromStdString(tempUserValue);
}

std::string isPlural(const QString &pluralString, const std::string &printStringSingular, const std::string &printStringPlural){
    if (pluralString.endsWith("s")) return " " + printStringSingular;
    else return " " + printStringPlural;
}

std::string makeStdString(const QJsonValue &input, int caseType){
    if (caseType == 0) return input.toString().toStdString();
    else if (caseType == 1) return input.toString().toLower().toStdString();
    else if (caseType == 2) return input.toString().toUpper().toStdString();
    else return "";
}

void dirCheck(const QString &fileLocation, const QString &terminalOutput){
    std::string tempOutputString = "\nVerifying directory at \"" + QCoreApplication::applicationDirPath().toStdString() + fileLocation.toStdString() + "\"\n";
    //finds the directory the executable is currently running in, appends the /saves/ directory to the end of the string, and creates the folder if it doesn't already exist
    QDir dir(QCoreApplication::applicationDirPath() + fileLocation);
    if (DEBUG) printw(tempOutputString.data());
    if (!dir.exists()){
        tempOutputString = terminalOutput.toStdString(); printw(tempOutputString.data());
        dir.mkpath(".");
    }
    return;
}

bool ioSaveFile(const QString &fileLocation, const QString &terminalOutput, const QJsonObject &writeObject){
    QSaveFile saveFile(QCoreApplication::applicationDirPath() + fileLocation);
    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        std::string tempOutputString = terminalOutput.toStdString(); printw(tempOutputString.data());
        return false;
    }
    QJsonDocument saveDoc(writeObject);
    if (-1 == saveFile.write(saveDoc.toJson())){
        return false;
    }
    return saveFile.commit();
}

QJsonObject ioLoadFile(const QString &fileLocation, const QString &terminalOutput){
    QFile loadFile(QCoreApplication::applicationDirPath() + fileLocation);
    if (!loadFile.open(QIODevice::ReadOnly)){
        std::string tempOutputString = fileLocation.toStdString(); printw(tempOutputString.data());
        tempOutputString = terminalOutput.toStdString(); printw(tempOutputString.data());
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    return loadDoc.object();
}

void ioRemoveFile(const QString &fileLocation, const QString &terminalOutput){
    QFile removeFile(QCoreApplication::applicationDirPath() + fileLocation);
    if (!removeFile.open(QIODevice::ReadOnly)){
        printw("Could not find the save file for that character.\nPlease make sure you spelled the character's name right.\n");
    }
    else{
        removeFile.remove();
        std::string tempOutputString = terminalOutput.toStdString(); printw(tempOutputString.data());
    }
    return;
}
