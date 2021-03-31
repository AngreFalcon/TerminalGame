#include "iohandling.h"

//source file containing input handling, including error checking and input validation
int inputInt(){ //function can only handle single digit integer grabbing. for larger integers, use inputErrorNagMultiInt()
    int a;
    while (!(a = getch()) || !isdigit(a)){
        printw("\n---------------------\nYour input is invalid\n");
        flushinp();
    }
    return a - 48; // getch() returns ascii value of key entered. subtract 48 from ascii value to get raw integer value
}

int inputMultiInt(){ //function similar to inputErrorNagInt, but can be used for indefinitely long strings of integers
    QString integerArray;
    char a;
    while ((a = getch()) != '\n'){
        if (isdigit(a)){
            printw(std::to_string(a-48).data());
            integerArray.push_back(a);
        }
        else if (a == '\x7f'){ // \x7f = ASCII 127 = backspace/delete key
            int y, x;
            getyx(stdscr, y, x);
            mvprintw(y, x-1, " ");
            move(y, x-1);
            integerArray.remove((integerArray.length()-1), 1);
        }
    }
    int i;
    if (integerArray.size() > 0) i = integerArray.toInt();
    else i = 0;
    return i;
}

char inputChar(){ //function used to grab single char input from user
    char a;
    while (!(a = getch()) || !isalpha(a)){
        printw("\n---------------------\nYour input is invalid\n");
        flushinp();
    }
    return a;
}

QString inputString(const std::string &a){ //function used to grab string input from user
    bool retryInput = true;
    std::string tempUserValue, tempOutputString;
    char userInput = ' ';
    while (retryInput == true){
        printw(a.data());
        nocbreak();
        echo();
        while((userInput = getch()) != '\n'){
            tempUserValue.push_back(userInput);
        }
        cbreak();
        noecho();
        tempOutputString = "Is " + tempUserValue + " correct? Y/N\n";
        do {
            printw(tempOutputString.data());
            userInput = inputChar();
            if (toupper(userInput) == 'Y') retryInput = false;
            else refresh();
        } while (toupper(userInput) != 'Y' && toupper(userInput) != 'N');
    }
    return QString::fromStdString(tempUserValue);
}

std::string isPlural(const QString &pluralString, const std::string &printStringSingular, const std::string &printStringPlural){ //this function is used to check context of a print statement and return either a singular or plural word
    if (pluralString.endsWith("s")) return " " + printStringSingular;
    else return " " + printStringPlural;
}

std::string makeStdString(const QJsonValue &input, int caseType){ //function used to simply cast a QString to a string
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

bool ioCreateFile(const QString &fileLocation){
    QFile saveFile(QCoreApplication::applicationDirPath() + fileLocation);
    if (saveFile.open(QIODevice::NewOnly)){
        QJsonObject emptyObject;
        QJsonDocument saveDoc(emptyObject);
        saveFile.write(saveDoc.toJson());
        return true;
    }
    else {
        return false;
    }
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

void printKeyInput(){
    char a;
    while ((a = getch()) != 48){
        printw(std::to_string(a).data());
    }
    return;
}
