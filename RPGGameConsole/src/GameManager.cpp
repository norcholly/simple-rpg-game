#include "GameManager.h"
#include "Utility.h"
#include "Player.h"
#include "ConsoleManager.h"
#include "InputManager.h"
#include <limits>

GameManager::GameManager()
    : player(100, 30, "Nameless", 1, 0, 90, 0, 0, 0, 0), day(1) {
}

void GameManager::showMainMenu() {
    Console::print("\n=== Welcome to the Game! ===");
    Console::print("\n1. Start Game\n2. Quit");
}

void GameManager::startGame() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Console::printNoEndl("Your Warrior's Name: ");
    string name = Input::readString();

    player = Player(100, 30, name, 1, 0, 90, 0, 0, 0, 0);
    Console::print("\nCongrats, " + player.getName() + "! Your warrior is created!");
    Console::print("Level: " + to_string(player.getLvl())
         + " | HealthPoint (HP): " + to_string(player.getHP())
         + " | DamagePoint (DP): " + to_string(player.getDP() - 10) + " - " + to_string(player.getDP() + 10)
         + " | Gold: " + to_string(player.getGold())); 

    wait(2);
}

void GameManager::gameLoop() {
    while (player.isAlive()) {
        xpControl(player);
        levelControl(player);

        bool quit = processDay();
        if (quit) {break;}

        if (!player.isAlive()) {
            calcScore(player);
            showStats(player);
            break;
        }
    }
}

bool GameManager::processDay() {
    Console::print("\n--- Day " + to_string(day) + " ---");
    Console::print("1. Go to Battle\n2. Shop\n3. Inventory\n4. Sleep\n5. Suicide");

    int choice;
    choice = Input::readInteger();

    switch (choice) {
        case 1:
            battle(player);
            break;
        case 2:
            shop(player);
            break;
        case 3:
            showInv(player);
            break;
        case 4:
            sleep(player);
            ++day;
            break;
        case 5:
            Console::printInfo("A new psychological trauma...");
            calcScore(player);
            showStats(player);
            return true;
        default:
            Console::printWarning("Wrong choice!");
    }
    return false;
}

void GameManager::run() {
    while (true) {
        showMainMenu();

        int choice;
        choice = Input::readInteger();

        if (choice == 1) {
            startGame();
            gameLoop();
        } else { Console::print("See you!"); break; }
    }
}