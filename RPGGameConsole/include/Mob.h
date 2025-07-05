#pragma once
#include "Entity.h"
#include <string>
using namespace std;

class Mob:public Entity {
        string name;
        int valueGold;
        int valueXp;

    public:
        Mob(int x, int y, string n, int vg, int vxp);

        void setName(string x);
        void setValueGold(int x);
        void setValueXp(int x);

        string getName() const;
        int getValueGold() const;
        int getValueXp() const;
};