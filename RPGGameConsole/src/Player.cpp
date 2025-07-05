#include "../include/Player.h"
#include "../include/ConsoleManager.h"

Player::Player(int hp, int dp, std::string n, int lvl, int xp, int g, int ap, int km, int eg, int sc)
    : Entity(hp, dp), name(n), lvl(lvl), xp(xp), gold(g), armorPoint(ap), sumKilledMobs(km), sumEarnedGolds(eg), sumScore(sc) {}

void Player::setName(string x) {
    name = x;
}

void Player::setGold(int x) {
    gold = x;
}

void Player::buyItem(string item) {
    inventory.push_back(item);
}

void Player::setAP(int x) {
    armorPoint = x;
}

void Player::setKM(int x) {
    sumKilledMobs = x;
}

void Player::setEG(int x) {
    sumEarnedGolds = x;
}

void Player::setScore(int x) {
    sumScore = x;
}

void Player::setLvl(int x) {
    lvl = x;
}

void Player::setXp(int x) {
    xp = x;
}

string Player::getName() const {
    return name;
}

int Player::getGold() const {
    return gold;
}

void Player::showInventory() const {
    Console::print("Your Inventory: ");
    for (const string& item : inventory) {
        Console::print(" - " + item);
    }
}

int Player::getAP() const {
    return armorPoint;
}

int Player::getKM() const {
    return sumKilledMobs;
}

int Player::getEG() const {
    return sumEarnedGolds;
}

int Player::getScore() const {
    return sumScore;
}

int Player::getLvl() const {
    return lvl;
}

int Player::getXp() const {
    return xp;
}