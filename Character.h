#pragma once
#include <string>
#include "Item.h"
#include <vector>
#include "Monster.h"

using namespace std;

class Character 
{

private:

	static Character* instance;

	Character(string name);
	~Character() {}

	Character(const Character&) = delete;
	Character& operator =(const Character&) = delete;

	string name;
	int level;
	int health;
	int maxhealth;
	int attackpower;
	int experience;
	int gold;
	vector<Item*> inventory;

public:

	static Character* GetInstance(string name);
	string& getname();
	int& getlevel();
	int& gethealth();
	int& getattackpower();
	int& getgold();
	int& getexperience();
	void attack(Monster& targetMonster);
	void takeDamage(int damage);
	void displayStatus();
	void useitem(int index);
	void levelUp();
	void gainEXP(int exp);
};
