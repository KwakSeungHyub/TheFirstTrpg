// GameManager.h
#pragma once
#include "Character.h"
#include "Monster.h"
#include "BossMonster.h"
#include "Shop.h"

class GameManager {
public:
    static Monster* GenerateMonster(int level);
    static BossMonster* GenerateBossMonster(int level);
    static void Battle(Character* player);
    static void VisitShop(Character* player);
    static void DisplayInventory(Character* player);
};