#include "../include/Mob.h"

Mob::Mob(int hp, int dp, string n, int vg, int vxp)
    : Entity(hp, dp), name(n), valueGold(vg), valueXp(vxp) {}

void Mob::setName(string x) {
    name = x;
}

void Mob::setValueGold(int x) {
    valueGold = x;
}

void Mob::setValueXp(int x) {
    valueXp = x;
}

string Mob::getName() const {
    return name;
}

int Mob::getValueGold() const {
    return valueGold;
}

int Mob::getValueXp() const {
    return valueXp;
}