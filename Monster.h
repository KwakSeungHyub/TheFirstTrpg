#pragma once
#include "Character.h"
#include "Item.h"
#include <string>

class Monster 
{

private:
	std::string name;
	int attackpower;
	int health;
	int level;

	int getRandomSpec(int min, int max);
	

public:
	
	Monster(std::string name, int characterlevel);
	virtual ~Monster();
	std::string getname();
	int gethealth();
	int getattackpower();
	int getlevel();
	virtual void attack(Character& targetCharacter);
	void takeDamage(int damage);

};