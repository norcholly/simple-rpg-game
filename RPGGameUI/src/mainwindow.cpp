#include "mainwindow.h"
#include "../ui_mainwindow.h"
#include <QApplication>
#include <QTimer>
#include "ConsoleManager.h"
#include "GameManager.h"
#include "Utility.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , turn(1)
    , currentMobIndex(0)
    , day(1)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->Main);

    Console::setOutput(ui->consoleArea);

}

// Essentials
void MainWindow::setMobs() {
    mobs = {
        Mob(30, 10, "Shadowfang", 15, 200),
        Mob(60, 20, "Grimclaw", 25, 25),
        Mob(80, 30, "Bloodhowl", 35, 35),
        Mob(100, 40, "Darkscale", 45, 45),
        Mob(120, 50, "Ironjaw", 55, 55),
        Mob(150, 70, "Nightstalker", 70, 70),
        Mob(200, 100, "Frostbite", 100, 100),
        Mob(250, 200, "Cpp", 200, 100),
        Mob(400, 300, "Fung-Hoo", 200, 200),
        Mob(600, 400, "Jink-Moo", 300, 300),
        Mob(800, 600, "Min-soo", 300, 300)
    };

    currentMobIndex = 0;
    turn = 0;
}

void MainWindow::setPlayerInfo(const Player& player) {
    int currentScore = calcScore(game->getPlayer());
    ui->nameShow->setText(QString::fromStdString("<span style='color: blue;'>Nickname: </span>" + player.getName()));
    ui->levelShow->setText(QString::fromStdString("<span style='color: blue;'>Level: </span>" + std::to_string(player.getLvl())));
    ui->hpShow->setText(QString::fromStdString("<span style='color: blue;'>HP: </span>" + std::to_string(player.getHP())));
    ui->dpShow->setText(QString::fromStdString("<span style='color: blue;'>DP: </span>" + std::to_string(player.getDP())));
    ui->goldShow->setText(QString::fromStdString("<span style='color: blue;'>Gold: </span>" + std::to_string(player.getGold())));
    ui->scoreShow->setText(QString::fromStdString("<span style='color: blue;'>Score: </span>" + std::to_string(currentScore)));
    ui->dayShow->setText(QString::fromStdString("<span style='color: blue;'>Day: </span>" + std::to_string(day)));
}

// Main Widget
void MainWindow::on_startGameBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->InputName);
}

void MainWindow::on_exitGameBtn_clicked() {
    QApplication::quit();
}

// InputName Widget
void MainWindow::on_startWithNameBtn_clicked() {
    delete game;
    day = 1;
    QString name = ui->nameInput->text();
    game = new GameManager(name.toStdString());
    setPlayerInfo(game->getPlayer());

    ui->stackedWidget->setCurrentWidget(ui->Tutorial);
    ui->tutorialArea->setText(QString::fromStdString(
        "<span style='color: green;'>Tutorial:</span><br><br>"
        "<span style='color: blue;'>- The enemy always attacks first in battle.</span><br>"
        "<span style='color: blue;'>- If you die in battle, the game is over!</span><br>"
        "<span style='color: blue;'>- When you drink a health potion, no one attacks that turn.</span><br>"
        "<span style='color: blue;'>- Sleep and end the day to restore your health.</span><br>"
        "<span style='color: blue;'>- If you buy permanent health or attack damage from the shop, sleep before going into battle.</span><br>"
        ));}

// Tutorial Widget
void MainWindow::on_continueBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Game);
}

// Game Widget
void MainWindow::on_goToBattleBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Battle);
    setMobs();
    ui->goldShowOnBattle->setText(QString::fromStdString("Gold: " + std::to_string(game->getPlayer().getGold())));
    ui->hpShowOnBattle->setText(QString::fromStdString("HP: " + std::to_string(game->getPlayer().getHP())));
}

void MainWindow::on_shopBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Shop);
    ui->yourGoldArea->setText(QString::fromStdString("You have " + std::to_string(game->getPlayer().getGold()) + "G"));
    ui->yourGoldArea->setAlignment(Qt::AlignRight);
}

// Inventory Widget (and Button)
void MainWindow::on_inventoryBtn_clicked() {
    QTextBrowser* inventorySlots[16] = {
        ui->invSlot_0, ui->invSlot_1, ui->invSlot_2, ui->invSlot_3,
        ui->invSlot_4, ui->invSlot_5, ui->invSlot_6, ui->invSlot_7,
        ui->invSlot_8, ui->invSlot_9, ui->invSlot_10, ui->invSlot_11,
        ui->invSlot_12, ui->invSlot_13, ui->invSlot_14, ui->invSlot_15
    };

    ui->stackedWidget->setCurrentWidget(ui->Inventory);

    for (const std::string& item : game->getPlayer().inventory) {
        for (int i = 0; i < game->getPlayer().inventory.size(); i++) {
            inventorySlots[i]->setText(QString::fromStdString(item));
        }
    }

}

void MainWindow::on_sleepBtn_clicked() {
    xpControl(game->getPlayer());
    sleep(game->getPlayer());
    day++;
    setPlayerInfo(game->getPlayer());
}

void MainWindow::on_suicideBtn_clicked() {
    calcScore(game->getPlayer());
    std::string statsText = getStatsText(game->getPlayer());
    ui->stackedWidget->setCurrentWidget(ui->Suicide);
    ui->scoreArea->setText(QString::fromStdString(statsText));
}

// Battle Widget
void MainWindow::opponentInfo() {
    ui->attackBtn->setEnabled(false);
    QTimer::singleShot(1000, this, [this]() {
        ui->consoleArea->append(QString::fromStdString("Opponent HP: " + std::to_string(mobs[currentMobIndex].getHP()) + " | Opponent DP: " + std::to_string(mobs[currentMobIndex].getDP() - 10) + " - " + std::to_string(mobs[currentMobIndex].getDP() + 10)));
    });
    QTimer::singleShot(2000, this, [this]() {
        ui->consoleArea->append(QString::fromStdString("Your HP: " + std::to_string(game->getPlayer().getHP()) + " | Your DP: " + std::to_string(game->getPlayer().getDP())));
    });
    QTimer::singleShot(3000, this, [this]() {
        ui->consoleArea->append(QString::fromStdString(""));
        ui->attackBtn->setEnabled(true);
        ui->healBtn->setEnabled(true);
        ui->retreatBtn->setEnabled(true);
    });
}


void MainWindow::endBattle() {
    ui->stackedWidget->setCurrentWidget(ui->Game);
    setPlayerInfo(game->getPlayer());
    currentMobIndex = 0;
    turn = 0;
}

void MainWindow::endGame() {
    calcScore(game->getPlayer());
    std::string statsText = getStatsText(game->getPlayer());
    ui->stackedWidget->setCurrentWidget(ui->Suicide);
    ui->scoreArea->setText(QString::fromStdString(statsText));
    ui->consoleArea->setText(QString::fromStdString(""));
}

void MainWindow::processTurn(int choice) {
    if (choice == 1) {

        ui->attackBtn->setEnabled(false);
        ui->healBtn->setEnabled(false);
        ui->retreatBtn->setEnabled(false);

        // 2s
        QTimer::singleShot(2000, this, [this]() {
            Console::printBattle(mobs[currentMobIndex].getName() + " attacked!");
        });

        // 3s
        QTimer::singleShot(3000, this, [this]() {
            int oldHp = game->getPlayer().getHP();
            int dmg = getRandomDamage(mobs[currentMobIndex].getDP() - 10, mobs[currentMobIndex].getDP() + 10);
            game->getPlayer().setHP(oldHp - dmg);
            Console::printBattle("You lost " + std::to_string(dmg) + " HP");
            ui->hpShowOnBattle->setText(QString::fromStdString("HP: " + std::to_string(game->getPlayer().getHP())));

            if (game->getPlayer().getHP() <= 0) {
                game->getPlayer().setHP(0);
                ui->hpShowOnBattle->setText(QString::fromStdString("HP: " + std::to_string(game->getPlayer().getHP())));

                // 4s
                QTimer::singleShot(1000, this, [this]() {
                    Console::printLine();
                    Console::printBattle(game->getPlayer().getName() + " died!");
                });

                // 6s
                QTimer::singleShot(3000, this, [this]() {
                    endGame();
                });
            } else {
                // 4s
                QTimer::singleShot(1000, this, [this]() {
                    Console::printBattle(game->getPlayer().getName() + " attacked!");

                    if (game->getPlayer().getDP() >= mobs[currentMobIndex].getHP()) {
                        QTimer::singleShot(1000, this, [this]() {
                            mobs[currentMobIndex].setHP(0);
                            Console::printBattle("Omg!");
                        });

                        QTimer::singleShot(2000, this, [this]() {
                            Console::printLine();
                            Console::printBattle(mobs[currentMobIndex].getName() + " died!");
                            Console::printLine();
                        });

                        QTimer::singleShot(3000, this, [this]() {
                            int gold = mobs[currentMobIndex].getValueGold();
                            int xp = mobs[currentMobIndex].getValueXp();

                            game->getPlayer().setGold(game->getPlayer().getGold() + gold);
                            game->getPlayer().setXp(game->getPlayer().getXp() + xp);
                            game->getPlayer().setEG(game->getPlayer().getEG() + gold);
                            game->getPlayer().setKM(game->getPlayer().getKM() + 1);

                            Console::printInfo("You earned " + std::to_string(gold) + " Gold and " + std::to_string(xp) + " XP!");
                            ui->goldShowOnBattle->setText(QString::fromStdString("Gold: " + std::to_string(game->getPlayer().getGold())));
                            turn = 0;
                            currentMobIndex++;

                            ui->attackBtn->setEnabled(true);
                            ui->healBtn->setEnabled(true);
                            ui->retreatBtn->setEnabled(true);
                        });
                    }

                    else {
                        QTimer::singleShot(1000, this, [this]() {
                            int playerDmg = getRandomDamage(game->getPlayer().getDP() - 10, game->getPlayer().getDP() + 10);
                            int mobHp = mobs[currentMobIndex].getHP();
                            mobs[currentMobIndex].setHP(std::max(0, mobHp - playerDmg));
                            Console::printBattle("Opponent loses " + std::to_string(playerDmg) + " HP");

                            // 6s
                            QTimer::singleShot(1000, this, [this]() {
                                if (mobs[currentMobIndex].getHP() <= 0) {
                                    Console::printLine();
                                    Console::printBattle(mobs[currentMobIndex].getName() + " died!");
                                    Console::printLine();

                                    QTimer::singleShot(1000, this, [this]() {
                                        int gold = mobs[currentMobIndex].getValueGold();
                                        int xp = mobs[currentMobIndex].getValueXp();

                                        game->getPlayer().setGold(game->getPlayer().getGold() + gold);
                                        game->getPlayer().setXp(game->getPlayer().getXp() + xp);
                                        game->getPlayer().setEG(game->getPlayer().getEG() + gold);
                                        game->getPlayer().setKM(game->getPlayer().getKM() + 1);

                                        Console::printInfo("You earned " + std::to_string(gold) + " Gold and " + std::to_string(xp) + " XP!");
                                        ui->goldShowOnBattle->setText(QString::fromStdString("Gold: " + std::to_string(game->getPlayer().getGold())));
                                        turn = 0;
                                        currentMobIndex++;

                                        ui->attackBtn->setEnabled(true);
                                        ui->healBtn->setEnabled(true);
                                        ui->retreatBtn->setEnabled(true);
                                    });
                                } else {
                                    Console::printLine();
                                    Console::printInfo(mobs[currentMobIndex].getName() + " is alive.");
                                    opponentInfo();
                                }
                            });
                        });
                    }
                });
            }
        });



    } else if (choice == 3) {
        Console::printInfo("You are retreating...");

    } else if (choice == 2) {
        if (!game->getPlayer().inventory.empty()) {
            if ((game->getPlayer().getHP() + 60) <= (100 + game->getPlayer().getAP())) {
                game->getPlayer().setHP(game->getPlayer().getHP() + 60);

                Console::printLine();
                Console::printInfo("You drank a health potion! Your new HP is now " + std::to_string(game->getPlayer().getHP()));
                Console::printLine();

                game->getPlayer().inventory.pop_back();
            } else {
                Console::printWarning("You dont need to drink a heal potion!");
                turn--;
            }
        } else {
            Console::printWarning("Your inventory is empty!");
            turn--;
        }

    } else {
        Console::printLine();
        Console::printWarning("Are you drunk? Okay, I'm taking you out of the from battle area.");
        Console::printLine();
    }

    turn++;
    QTimer::singleShot(1000, this, [this]() {
        Console::printLine();
        ui->consoleArea->append(QString::fromStdString("Round " + std::to_string(turn) + " | Your opponent is " + mobs[currentMobIndex].getName()));
    });
}

void MainWindow::on_attackBtn_clicked() {
    processTurn(1);
}

void MainWindow::on_healBtn_clicked() {
    processTurn(2);
}

void MainWindow::on_retreatBtn_clicked() {
    processTurn(3);
    endBattle();
}

// Shop Widget
void MainWindow::on_backBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Game);
    setPlayerInfo(game->getPlayer());
}

void MainWindow::on_buyPotionBtn_clicked() {
    if (game->getPlayer().getGold() >= 20 && game->getPlayer().inventory.size() < 16) {
        game->getPlayer().buyItem("Health Potion");
        game->getPlayer().setGold(game->getPlayer().getGold() - 20);
        ui->yourGoldArea->setText(QString::fromStdString("You have " + std::to_string(game->getPlayer().getGold()) + "G"));
        ui->yourGoldArea->setAlignment(Qt::AlignRight);
    }
}

void MainWindow::on_buyDpBtn_clicked() {
    if (game->getPlayer().getGold() >= 50) {
        game->getPlayer().setDP(game->getPlayer().getDP() + 20);
        game->getPlayer().setGold(game->getPlayer().getGold() - 50);
        ui->yourGoldArea->setText(QString::fromStdString("You have " + std::to_string(game->getPlayer().getGold()) + "G"));
        ui->yourGoldArea->setAlignment(Qt::AlignRight);
    }
}

void MainWindow::on_buyHpBtn_clicked() {
    if (game->getPlayer().getGold() >= 70) {
        game->getPlayer().setAP(game->getPlayer().getAP() + 20);
        game->getPlayer().setHP(game->getPlayer().getHP() + game->getPlayer().getAP());
        game->getPlayer().setGold(game->getPlayer().getGold() - 70);
        ui->yourGoldArea->setText(QString::fromStdString("You have " + std::to_string(game->getPlayer().getGold()) + "G"));
        ui->yourGoldArea->setAlignment(Qt::AlignRight);
    }
}

// Inventory Widget

void MainWindow::on_turnBackBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Game);
    setPlayerInfo(game->getPlayer());
}

// Suicide Widget
void MainWindow::on_mainMenuBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Main);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}
