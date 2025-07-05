#include "../include/Entity.h"

Entity::Entity(int hp, int dp) 
    : healthPoint(hp), damagePoint(dp) {}

bool Entity::isAlive() const {
    return healthPoint > 0;
}

void Entity::setHP(int x) {
    healthPoint = x;
}

void Entity::setDP(int x) {
    damagePoint = x;
}

int Entity::getHP() const {
    return healthPoint;
}

int Entity::getDP() const {
    return damagePoint;
}