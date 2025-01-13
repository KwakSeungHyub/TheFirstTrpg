#pragma once
#include <string>
#include "Item.h"
#include <vector>
#include "Monster.h"

class Character {

private:

	static Character* instance;

	Character(std::string name);
	~Character() {}

	Character(const Character&) = delete;
	Character& operator =(const Character&) = delete;

	std::string name;
	int level;
	int health;
	int maxhealth;
	int attackpower;
	int experience;
	int gold;
	std::vector<Item*> inventory;

public:

	static Character* GetInstance(std::string name);
	std::string getname();
	int getlevel();
	int gethealth();
	int getattackpower();
	int getgold();
	void attack(Monster& targetMonster);
	void takeDamage(int damage);
	void displayStatus();
	void useitem(int index);
	void levelUp();
	void gainEXP(int exp);
};
