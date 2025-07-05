#pragma once
#include "Player.h"

class GameManager {    
    Player player;
    int day;

    void showMainMenu();
    void startGame();
    void gameLoop();
    bool processDay();

    public:
        GameManager();
        void run();
};