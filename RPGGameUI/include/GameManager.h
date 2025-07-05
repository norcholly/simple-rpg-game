#pragma once
#include "Player.h"

class GameManager {    
    Player player;
    int day;

    public:
        Player& getPlayer();
        GameManager(const std::string& playerName);
};
