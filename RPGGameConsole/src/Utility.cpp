#include <thread>
#include <random>
#include "../include/Utility.h"
#include "../include/ConsoleManager.h"
#include "../include/InputManager.h"

void wait(int second) {
    this_thread::sleep_for(chrono::seconds(second));
}

void shop(Player &player) {
    Console::print("\nWelcome to Shop! You can buy any item to help you in battle.");
    while(true) {
        Console::print("You have " + to_string(player.getGold()) + " Gold");
        Console::print("1. Take a Look at the Shop\n2. Go Back");
        int choice;
        choice = Input::readInteger();
        if(choice == 1) {
            Console::print("1. Health Potion - 20G - (Single-use +60HP)\n2. Enhance your Sword - 50G - (Permament +20 DP)\n3. Equip Armor - 70G - (Permanent +20 HP)\n4. Go Back");
            int choice2;
            choice2 = Input::readInteger();
            if (choice2 == 1) {
                if (player.getGold() >= 20) {
                    player.buyItem("Health Potion");
                    Console::print("\nAdded 1 health potion to inventory.");
                    player.setGold(player.getGold() - 20);
                    wait(1);
                } else {
                    Console::print("Not enough gold!");
                }
            } else if (choice2 == 2) {
                if (player.getGold() >= 50) {
                    player.setDP(player.getDP() + 20);
                    Console::print("\nYour attack has been enhanced! New DP: " + to_string(player.getDP()));
                    player.setGold(player.getGold() - 50);
                    wait(1);
                } else {
                    Console::print("\nNot enough gold!");
                }
            } else if (choice2 == 3) {
                if (player.getGold() >= 70) {
                    player.setAP(player.getAP() + 20);
                    player.setHP(player.getHP() + player.getAP());
                    Console::print("\nYour health has increased! New HP: " + to_string(player.getHP()));
                    player.setGold(player.getGold() - 70);
                    wait(1);
                } else {
                    Console::print("\nNot enough gold!");
                    wait(1);
                }
            }
        } else {
            break;
        }
    }
}


void calcScore(Player &player) {
    player.setScore((player.getKM() * 100) + (player.getEG() * 10));
}

void showStats(Player &player) {
    Console::print(player.getName() + ", the old warrior");
    Console::print("Level: " + to_string(player.getLvl()));
    Console::print("Monsters killed: " + to_string(player.getKM()));
    Console::print("Total earned gold: " + to_string(player.getEG()));
    Console::print("Score: " + to_string(player.getScore()));
}

void sleep(Player &player) {
    wait(1);
    Console::printInfo("\nBzzz...");
    wait(2);
    player.setHP(100 + player.getAP());
    Console::printInfo("Good Morning! Your HP is now " + to_string(player.getHP()));
}

void showInv(Player &player) {
    wait(1);
    Console::printLine();
    player.showInventory();
    wait(1);
}

void xpControl(Player &player) {
    if (player.getXp() >= 100) {
            player.setLvl(player.getLvl() + 1);
            wait(1);
            Console::printInfo("Congrats, Your level is now " + to_string(player.getLvl()));
            player.setXp(0);
    };
}

void levelControl(Player &player) {
    for (int i = 1; i < player.getLvl(); i++) {
        player.setAP(player.getAP() + 20);
        player.setDP(player.getDP() + 20);
    }
}

int getRandomDamage(int min, int max) {
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}
