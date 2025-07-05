#pragma once

class Entity {
    protected:
        int healthPoint;
        int damagePoint;

    public:
        Entity(int hp, int dp);

        bool isAlive() const;

        void setHP(int x);
        void setDP(int x);

        int getHP() const;
        int getDP() const;


};