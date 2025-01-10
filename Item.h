#pragma once
#include <string>
#include <vector>

class Character;

class Item {
public:
    // 아이템 이름 지정
    virtual std::string GetName() const = 0;
    // 아이템 사용을 위한 함수
    virtual void Use(Character* character) = 0;
    virtual ~Item() = default;
};