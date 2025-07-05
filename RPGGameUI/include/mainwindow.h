#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameManager.h"
#include "Mob.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setMobs();
    void startBattle();
    void opponentInfo();
    void processTurn(int choice);
    void endBattle();
    void endGame();
    void setPlayerInfo(const Player& player);

private slots:
    // Main Widget
    void on_startGameBtn_clicked();
    void on_exitGameBtn_clicked();

    // InputName Widget
    void on_startWithNameBtn_clicked();

    // Tutorial Widget
    void on_continueBtn_clicked();

    // Game Widget
    void on_goToBattleBtn_clicked();
    void on_shopBtn_clicked();
    void on_inventoryBtn_clicked();
    void on_sleepBtn_clicked();
    void on_suicideBtn_clicked();

    // Battle Widget
    void on_attackBtn_clicked();
    void on_healBtn_clicked();
    void on_retreatBtn_clicked();

    // Shop Widget
    void on_backBtn_clicked();
    void on_buyDpBtn_clicked();
    void on_buyHpBtn_clicked();
    void on_buyPotionBtn_clicked();

    // Inventory Widget
    void on_turnBackBtn_clicked();

    // Suicide Widget
    void on_mainMenuBtn_clicked();

private:
    Ui::MainWindow *ui;
    GameManager* game = nullptr;

    QWidget *Battle;
    QWidget *Shop;
    QWidget *Game;
    QWidget *Suicide;
    QWidget *Main;
    QWidget *Inventory;
    QWidget *InputName;
    QWidget *Tutorial;

    // Battle Widget
    std::vector<Mob> mobs;
    int turn;
    int currentMobIndex;
    int day;
};
#endif // MAINWINDOW_H
