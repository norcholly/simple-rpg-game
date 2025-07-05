#include "GameManager.h"
#include "Player.h"

GameManager::GameManager(const std::string& playerName)
    : player(100, 20, playerName, 1, 0, 50, 0, 0, 0, 0), day(1) {
}

Player& GameManager::getPlayer() {
    return player;
}
