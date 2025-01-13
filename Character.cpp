#include "Character.h"
#include <string>
#include <iostream>
#include <memory>

Character* Character::instance = nullptr;

Character* Character::GetInstance(std::string name)
{
	if (!instance)
	{
		instance = new Character(name);
	}
	return instance;
}

Character::Character(std::string name) : maxhealth(200), health(maxhealth),
level(1), attackpower(30), experience(0), name(name), gold(0) {}

std::string Character::getname()
{
	return name;
}

int Character::getlevel()
{
	return level;
}

int Character::gethealth()
{
	return health;
}

int Character::getattackpower()
{
	return attackpower;
}

int Character::getgold()
{
	return gold;
}
void Character::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;
}

void Character::attack(Monster& targetMonster) 
{
	targetMonster.takeDamage(attackpower);
	std::cout << name << " attacks " << targetMonster.getname() << " for " <<
		attackpower << " damage!\n";
}

void Character::displayStatus()
{
	std::cout << name << "'s status" << std::endl
		<< "HP: " << health << " / " << maxhealth << std::endl
		<< "Power: " << attackpower << std::endl
		<< "Level: " << level << std::endl
		<< "Gold: " << gold << std::endl
		<< "Exp: " << experience << " / 100" << std::endl;
}

void Character::useitem(int index) {
	if (index >= 0 && index < inventory.size()) {
		inventory[index]->use();
		inventory.erase(inventory.begin() + index);  
	}
}

void Character::levelUp()
{
	if (level <= 10)
	{
		level++;
		attackpower = attackpower + (level * 5);
		maxhealth = maxhealth + (level * 20);
		health = maxhealth;
		std::cout << "Level Up!" << std::endl;
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


