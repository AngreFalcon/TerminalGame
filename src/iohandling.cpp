#include "iohandling.h"

//source file containing exclusively input handling, including error checking and input validation

int inputErrorNag(int a){
    if (std::cin.fail()){
        while(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "\n---------------------\nYour input is invalid\n";
            std::cin >> a;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return a;
    }
    else{
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return a;
    }
}
char inputErrorNag(char a){
    if (std::cin.fail()){
        while(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "\n---------------------\nYour input is invalid\n";
            std::cin >> a;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return a;
    }
    else{
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return a;
    }
}
std::string inputErrorNag(std::string a){
    if (std::cin.fail()){
        while(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "\n---------------------\nYour input is invalid\n";
            //std::getline(std::cin, a);
            std::cin >> a;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return a;
    }
    else{
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return a;
    }
}

QString askInput(const std::string &a){
    bool retryInput;
    std::string tempUserValue;
    char verify = 'y';
    do {
        std::cout << a;
        std::getline (std::cin, tempUserValue);
        std::cout << "Is " << tempUserValue << " correct? Y/N" << std::endl;
        std::cin >> verify;
        verify = inputErrorNag(verify);
        if (toupper(verify) == 'Y'){
            retryInput = false;
        }
        else {
            retryInput = true;
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
    //finds the directory the executable is currently running in, appends the /saves/ directory to the end of the string, and creates the folder if it doesn't already exist
    QDir dir(QCoreApplication::applicationDirPath() + fileLocation);
    if (DEBUG) std::cout << "\nVerifying directory at \"" << QCoreApplication::applicationDirPath().toStdString() + fileLocation.toStdString() << "\"\n";
    if (!dir.exists()){
        std::cout << terminalOutput.toStdString();
        dir.mkpath(".");
    }
    return;
}

bool ioSaveFile(const QString &fileLocation, const QString &terminalOutput, const QJsonObject &writeObject){
    QSaveFile saveFile(QCoreApplication::applicationDirPath() + fileLocation);
    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        std::cout <<  terminalOutput.toStdString();
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
        std::cout << fileLocation.toStdString();
        std::cout << terminalOutput.toStdString();
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    return loadDoc.object();
}

void ioRemoveFile(const QString &fileLocation, const QString &terminalOutput){
    QFile removeFile(QCoreApplication::applicationDirPath() + fileLocation);
    if (!removeFile.open(QIODevice::ReadOnly)){
        std::cout << "Could not find the save file for that character.\nPlease make sure you spelled the character's name right.\n";
    }
    else{
        removeFile.remove();
        std::cout << terminalOutput.toStdString();
    }
    return;
}
