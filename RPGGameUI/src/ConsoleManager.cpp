#include "ConsoleManager.h"

static QTextEdit* consoleOutput = nullptr;

void Console::setOutput(QTextEdit* outputArea) {
    consoleOutput = outputArea;
}

void Console::print(const std::string& message) {
    if (consoleOutput) {
        consoleOutput->append(QString::fromStdString(message));
    }
}

void Console::printInfo(const std::string& message) {
    if (consoleOutput) {
        consoleOutput->append(QString::fromStdString("<span style='color: blue;'>[INFO] </span>" + message));
    }
}

void Console::printWarning(const std::string& message) {
    if (consoleOutput) {
        consoleOutput->append(QString::fromStdString("<span style='color: red;'>[WARNING] </span>" + message));
    }
}

void Console::printError(const std::string& message) {
    if (consoleOutput) {
        consoleOutput->append(QString::fromStdString("[ERROR] " + message));
    }
}

void Console::printBattle(const std::string& message) {
    if (consoleOutput) {
        consoleOutput->append(QString::fromStdString("<span style='color: orange;'>[BATTLE] </span>" + message));
    }
}

void Console::printLine() {
    if (consoleOutput) {
        consoleOutput->append(QString::fromStdString("------------"));
    }
}

