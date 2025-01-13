#pragma once
#include <string>

class Item {
public:
    std::string Name;
    int Price;  // 가격 정보 저장
    int Amount;  // 수량을 저장할 변수
    // 기본 생성자
    Item()
        : Name(""), Price(0), Amount(0) {
    }
    Item(const std::string& name, int price, int amount = 1)
        : Name(name), Price(price), Amount(amount) {
    }
    

    virtual std::string GetName() const { return Name; }
    virtual int GetPrice() const { return Price; }
    int GetAmount() const { return Amount; }

   
    // 수량 증가 함수
    void IncreaseAmount(int amount) {
        Amount += amount;  // 수량을 증가
    }
    // 수량 감소 함수 추가
    void DecreaseAmount(int amount) {
        Amount -= amount;
        if (Amount < 0) {
            Amount = 0;  // 수량이 0 이하로 떨어지지 않게 처리
        }
    }
    virtual void Use(class Character* character) = 0;
    virtual ~Item() = default;
};
