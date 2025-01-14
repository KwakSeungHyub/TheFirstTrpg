
// BossMonster.h
#pragma once
#include "Monster.h"
#include "Item.h"
#include <memory>
#include <vector>

class BossMonster: public Monster 
{
public:
    BossMonster(int level);

    // 전리품 테이블 초기화
    void InitializeLootTable() override;

    // 전리품 드롭
    std::unique_ptr<Item> DropItem() override;
};
