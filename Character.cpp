#include "Character.h"
#include <string>
#include <iostream>
#include <memory>


Character* Character::instance = nullptr;

Character* Character::GetInstance(string name)
{
	if (!instance)
	{
		instance = new Character(name);
	}
	return instance;
}

Character::Character(string name) : maxhealth(200), health(maxhealth),
level(1), attackpower(30), experience(0), name(name), gold(0) {}

string& Character::getname()
{
	return name;
}

int& Character::getlevel()
{
	return level;
}

int& Character::gethealth()
{
	return health;
}

int& Character::getattackpower()
{
	return attackpower;
}

int& Character::getgold()
{
	return gold;
}

int& Character::getexperience()
{
	return experience;
}

void Character::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;
}

void Character::attack(Monster& targetMonster) 
{
	targetMonster.takeDamage(attackpower);
	cout << name << " attacks " << targetMonster.getname() << " for " <<
		attackpower << " damage!\n";
}

void Character::displayStatus()
{
	cout << name << "'s status" << endl
		<< "HP: " << health << " / " << maxhealth << endl
		<< "Power: " << attackpower << endl
		<< "Level: " << level << endl
		<< "Gold: " << gold << endl
		<< "Exp: " << experience << " / 100" << endl;
}
/*
void Character::useitem(int index) {
	if (index >= 0 && index < inventory.size()) {
		inventory[index]->use();
		inventory.erase(inventory.begin() + index);  
	}
}
*/
void Character::levelUp()
{
	if (level <= 10)
	{
		level++;
		attackpower = attackpower + (level * 5);
		maxhealth = maxhealth + (level * 20);
		health = maxhealth;
		cout << "Level Up!" << endl;
	}
}

void Character::gainEXP(int exp)
{
	experience += exp;
	if (experience >= 100)
	{
		levelUp();
		experience %= 100;
	}
}


