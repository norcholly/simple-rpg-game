#include "InputManager.h"

string Input::readString() {
    string x;
    getline(cin, x);
    return x;
}

int Input::readInteger() {
    int x;
    cin >> x;
    return x;
}