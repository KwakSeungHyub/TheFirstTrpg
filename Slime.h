#pragma once
#include "Monster.h"

class Slime : public Monster {
public:
    // 생성자
    Slime(int level);

    // 전리품 테이블 초기화
    void InitializeLootTable() override;

    // 전리품 드롭
    std::unique_ptr<Item> DropItem() override;
};
