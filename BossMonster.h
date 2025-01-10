#pragma once
#include "Monster.h"

class BossMonster : public Monster {
public:
    BossMonster(const std::string& name, int health, int attack);
};