#pragma once
#include <string>
using namespace std;

class Console {
    public:
        static void print(const string& message);
        static void printInfo(const string& message);
        static void printWarning(const string& message);
        static void printError(const string& message);
        static void printBattle(const string& message);
        static void printLine();
        static void printNoEndl(const string& message);
};