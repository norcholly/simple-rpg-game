#pragma once
#include "Entity.h"
#include <vector>
#include <string>


class Player:public Entity {
        std::string name;
        int gold;
        int armorPoint;
        int lvl;
        int xp;

        // statistics
        int sumKilledMobs;
        int sumEarnedGolds;
        int sumScore;
 
    public:
        Player(int x, int y, std::string n, int lvl, int xp, int g, int a, int km, int eg, int sc);

        std::vector<std::string> inventory;

        void setName(std::string x);
        void setGold(int x);
        void buyItem(std::string item);
        void setAP(int x);
        void setKM(int x);
        void setEG(int x);
        void setScore(int x);
        void setLvl(int x);
        void setXp(int x);

        std::string getName() const;
        int getGold() const;
        int getAP() const;
        int getKM() const;
        int getEG() const;
        int getScore() const;
        int getLvl() const;
        int getXp() const;
};
