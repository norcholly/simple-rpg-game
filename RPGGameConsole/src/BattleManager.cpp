#include "../include/BattleManager.h"
#include "../include/Utility.h"
#include "../include/ConsoleManager.h"
#include "../include/InputManager.h"

void battle(Player& player) {
    while (player.getHP() > 0) {
        Console::printLine();
        Console::print("Do you want to start a battle?\n1. Yes\n2. No");
        Console::print("Your HP: " + to_string(player.getHP()) +  " | Your DP: " + to_string(player.getDP() - 10) + " - " + to_string(player.getDP() + 10));
        Console::printLine();
        
        int choice;
        choice = Input::readInteger();

        if (choice != 1) break;

        vector<Mob> mobs = {
            Mob(40, 10, "Shadowfang", 15, 15),
            Mob(60, 20, "Grimclaw", 25, 25),
            Mob(80, 30, "Bloodhowl", 35, 35),
            Mob(100, 40, "Darkscale", 45, 45),
            Mob(120, 50, "Ironjaw", 55, 55),
            Mob(150, 70, "Nightstalker", 70, 70),
            Mob(200, 100, "Frostbite", 100, 100),
            Mob(250, 200, "Cpp", 200, 100)
        };

        bool escape = false;

        for (Mob& mob : mobs) {
            if (escape) break;

            Console::printLine();
            Console::printWarning("A " + mob.getName() + " appeared before you!");

            for (Mob& mob : mobs) {
                if (escape) break;

                int turn = 1;

                while (mob.isAlive()) {
                    Console::printLine();
                    Console::printInfo("Round " + to_string(turn) + " Opponent: " + mob.getName());
                    Console::printInfo("Opponent HP: " + to_string(mob.getHP()) + " | Opponent DP: " + to_string(mob.getDP() - 10) + " - " + to_string(mob.getDP() + 10));
                    Console::printInfo("Your HP: " + to_string(player.getHP()) +  " | Your DP: " + to_string(player.getDP() - 10) + " - " + to_string(player.getDP() + 10));
                    Console::print("1. Attack\n2. Retreat\n3. Drink Health Potion");
                    Console::printLine();

                    int choice;
                    choice = Input::readInteger();
                    Console::printLine();

                    wait(1);

                    if (choice == 1) {
                        Console::printBattle(mob.getName() + " attacked!");
                        int oldPlayerHp = player.getHP();
                        player.setHP(player.getHP() - getRandomDamage(mob.getDP() - 10, mob.getDP() + 10));
                        int newPlayerHp = player.getHP();
                        Console::printBattle("You lost " + to_string(oldPlayerHp - newPlayerHp) + " HP");
                        wait(1);


                        if (player.getHP() <= 0) {
                            Console::printLine();
                            Console::printBattle(player.getName() + " died!");
                            wait(1);
                            escape = true;
                            break;
                        }

                        Console::printBattle(player.getName() + " attacked!");
                        int oldMobHp = mob.getHP();

                        if (player.getDP() >= mob.getHP()) {
                            mob.setHP(0);
                            Console::printBattle("Omg!");
                            wait(1);
                            
                            Console::printLine();
                            Console::printBattle(mob.getName() + " died!");
                            Console::printLine();
                            wait(1);

                            // Altın ve skor
                            int earnedGold = mob.getValueGold();
                            int earnedXp = mob.getValueXp();

                            Console::printLine();
                            Console::printInfo("You earned " + to_string(earnedGold) + " Gold and " + to_string(earnedXp) + " XP!");
                            Console::printLine();
                            wait(1);

                            player.setXp(player.getXp() + earnedXp);
                            player.setGold(player.getGold() + earnedGold);
                            player.setEG(player.getEG() + earnedGold);
                            player.setKM(player.getKM() + 1);
                            
                        } else {
                            mob.setHP(mob.getHP() - getRandomDamage(player.getDP() - 10, player.getDP() + 10));
                            int newMobHp = mob.getHP();
                            Console::printBattle("Opponent loses " + to_string(oldMobHp - newMobHp) + " HP");
                            wait(1);
                            
                            Console::printLine();
                            Console::printInfo(mob.getName() + " is alive, it has " + to_string(mob.getHP()) + " HP.");
                            wait(1);
                        }

                    } else if (choice == 2) {
                        Console::printInfo("You are retreating...");

                        escape = true;
                        break;

                    } else if (choice == 3) {
                        if (!player.inventory.empty()) {
                            if ((player.getHP() + 60) <= (100 + player.getAP())) {
                                player.setHP(player.getHP() + 60);
                                
                                Console::printLine();
                                Console::printInfo("You drank a health potion! Your new HP is now " + to_string(player.getHP()));
                                Console::printLine();

                                player.inventory.pop_back();
                            } else {
                                Console::printWarning("Your HP is already full!");
                            }
                        } else {
                            Console::printWarning("Your inventory is empty!");
                        }

                    } else {
                        Console::printLine();
                        Console::printWarning("Are you drunk? Okay, I'm taking you out of the from battle area.");
                        Console::printLine();

                        escape = true;
                        break;
                    }

                    turn++;
                }

                if (player.getHP() <= 0 || escape) break;
            }

        }
    }
}
