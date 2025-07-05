#pragma once
#include <string>
#include <QTextEdit>

namespace Console {
        void print(const std::string& message);
        void printInfo(const std::string& message);
        void printWarning(const std::string& message);
        void printError(const std::string& message);
        void printBattle(const std::string& message);
        void printLine();

        void setOutput(QTextEdit* outputArea);
}
