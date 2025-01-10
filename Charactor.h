#pragma once
#include <vector>
#include <string>
#include "Item.h"

using namespace std;


class Charactor
{
	static Charactor* instance;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int max_experience;
	int gold;
	std::vector<Item*>inventory;

public:
	Charactor(string name);
	~Charactor();

	std::string name;
	static Charactor* getinstance(string name);
	void display_Status();
	void LevelUp();
	void UseItem();
	void visitShop();
};

