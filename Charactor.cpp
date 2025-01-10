#include "Charactor.h"
#include <iostream>
#include <string>


using namespace std;
Charactor::Charactor(string name)//생성자
{
    this->name = name;
    this->level = 1;
    this->maxHealth = 200;
    this->health = maxHealth;
    this->attack = 30;
    this->experience = 0;
    this->max_experience = 100;
    this->gold = 0;
}

Charactor::~Charactor()
{
    delete instance;
    cout << "메모리 정상 반환" << endl;
}



Charactor* Charactor::getinstance(string name)
{
    if (instance == nullptr) {
        instance = new Charactor(name);
    }
    return instance;
}

void Charactor::display_Status()
{
    cout << "레벨: " << level << endl;
    cout << "최대체력: " << maxHealth << endl;
    cout << "공격력" << attack << endl;
}

void Charactor::LevelUp()
{
    if (level > 10) {
        this->level += 1;
        this->maxHealth += 20;
        this->attack += 5;
    }
}

void Charactor::UseItem()
{
    

}

void Charactor::visitShop()
{
}
