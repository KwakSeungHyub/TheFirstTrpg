// Item.h
#pragma once
#include <string>

class Item {
public:
    std::string Name;
    int Price;  // 가격 추가

    Item(const std::string& name, int price) : Name(name), Price(price) {}

    virtual std::string GetName() const = 0;
    virtual void Use(class Character* character) = 0;

    virtual int GetPrice() const { return Price; }  // 기본 가격 반환
    virtual ~Item() = default;
};
