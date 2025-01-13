#pragma once
#include "Character.h"
#include "Monster.h"
#include "BossMonster.h"
#include "Shop.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include <memory>
#include <vector>
#include <random>

class GameManager {
public:
    // 랜덤 몬스터 생성 (std::unique_ptr<Monster> 반환)
    static std::unique_ptr<Monster> GenerateRandomMonster(int level);

    // 게임 흐름 제어 함수
    void StartGame(Character* player, Shop* shop);

    // 보스 몬스터 생성 (std::unique_ptr<BossMonster> 반환)
    static std::unique_ptr<BossMonster> GenerateBossMonster(int level);

    // 전투 처리 함수
    static void Battle(Character* player);

    // 상점 방문 처리 함수
    static void VisitShop(Character* player, Shop* shop);

    // 인벤토리 확인 함수
    static void DisplayInventory(Character* player);

    // 보스 몬스터 전투 처리 함수
    void BossBattle(Character* player);
};
