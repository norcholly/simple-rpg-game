#pragma once
#include "Player.h"

void battle(Player &player);
void wait(int second);
void shop(Player &player);
void calcScore(Player &player);
void showStats(Player &player);
void sleep(Player &player);
void showInv(Player &player);
void xpControl(Player &player);
void levelControl(Player &player);
int getRandomDamage(int min, int max);
