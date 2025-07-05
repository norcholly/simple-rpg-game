#pragma once
#include "Entity.h"
#include <string>


class Mob:public Entity {
        std::string name;
        int valueGold;
        int valueXp;

    public:
        Mob(int x, int y, std::string n, int vg, int vxp);

        void setName(std::string x);
        void setValueGold(int x);
        void setValueXp(int x);

        std::string getName() const;
        int getValueGold() const;
        int getValueXp() const;
};
