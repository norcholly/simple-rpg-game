#include "ConsoleManager.h"
#include <iostream>

void Console::print(const string& message) {
    cout << message << endl;
}

void Console::printInfo(const string& message) {
    cout << "[INFO] " << message << endl;
}

void Console::printWarning(const string& message) {
    cout << "[WARNING] " << message << endl;
}

void Console::printError(const string& message) {
    cout << "[ERROR] " << message << endl;
}

void Console::printBattle(const string& message) {
    cout << "[BATTLE] " << message << endl;
}

void Console::printLine() {
    cout << "---------" << endl;
}

void Console::printNoEndl(const string& message) {
    cout << message;
}