
#pragma once
#include "Monster.h"

class Troll : public Monster {
public:
    // 생성자
    Troll(int level);

    // 전리품 테이블 초기화
    void InitializeLootTable() override;  // 가상 함수 재정의

    // 전리품 드롭
    std::unique_ptr<Item> DropItem() override;  // 가상 함수 재정의
};