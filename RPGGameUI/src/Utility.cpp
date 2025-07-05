#include <random>
#include "Utility.h"
#include "ConsoleManager.h"

int calcScore(Player &player) {
    player.setScore((player.getKM() * 100) + (player.getEG() * 10));
    return player.getScore();
}

std::string getStatsText(const Player& player) {
    std::string text;
    text += player.getName() + ", the old warrior\n";
    text += "Level: " + std::to_string(player.getLvl()) + "\n";
    text += "Monsters killed: " + std::to_string(player.getKM()) + "\n";
    text += "Total earned gold: " + std::to_string(player.getEG()) + "\n";
    text += "Score: " + std::to_string(player.getScore()) + "\n";
    return text;
}

void sleep(Player &player) {
    player.setHP(100 + player.getAP());
}

void xpControl(Player &player) {
    if (player.getXp() >= 100) {
            player.setLvl(player.getLvl() + 1);
            player.setXp(0);
            player.setAP(player.getAP() + 20);
            player.setDP(player.getDP() + 20);
    };
}

int getRandomDamage(int min, int max) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}
