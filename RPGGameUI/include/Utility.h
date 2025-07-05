#pragma once
#include "Player.h"

int calcScore(Player &player);
std::string getStatsText(const Player &player);
void sleep(Player &player);
void xpControl(Player &player);
int getRandomDamage(int min, int max);
