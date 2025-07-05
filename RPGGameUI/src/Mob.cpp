#include "Mob.h"

Mob::Mob(int hp, int dp, std::string n, int vg, int vxp)
    : Entity(hp, dp), name(n), valueGold(vg), valueXp(vxp) {}

void Mob::setName(std::string x) {
    name = x;
}

void Mob::setValueGold(int x) {
    valueGold = x;
}

void Mob::setValueXp(int x) {
    valueXp = x;
}

std::string Mob::getName() const {
    return name;
}

int Mob::getValueGold() const {
    return valueGold;
}

int Mob::getValueXp() const {
    return valueXp;
}
