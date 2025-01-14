#pragma once
#include <string>

// Equipment 클래스 전방 선언
class Equipment;  // 전방 선언

class Item {
public:
    std::string Name;
    int Price;
    int Amount;

    Item() : Name(""), Price(0), Amount(0) {}

    Item(const std::string& name, int price, int amount = 1)
        : Name(name), Price(price), Amount(amount) {
    }

    virtual ~Item() = default;

    virtual std::string GetName() const { return Name; }
    virtual int GetPrice() const { return Price; }
    virtual int GetAmount() const { return Amount; }

    void IncreaseAmount(int amount) { Amount += amount; }
    void DecreaseAmount(int amount) { Amount = (Amount - amount >= 0) ? Amount - amount : 0; }

    virtual void Use(class Character* character) = 0;

    virtual int GetBonusStat() const { return 0; }
    virtual bool IsEquipable() const { return false; }

    virtual Equipment* GetType() const = 0;  // Equipment* 반환
};
