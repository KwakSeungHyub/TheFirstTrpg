#include "Monster.h"
#include <string>
#include <iostream>
#include <random>

int Monster::getRandomSpec(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

Monster::Monster(std::string name, int characterLevel) :
	name(name), level(characterLevel) 
{
	health = getRandomSpec(level * 20, level * 30);
	attackpower = getRandomSpec(level * 5, level * 10);
}

Monster:: ~Monster(){}

std::string Monster::getname()
{
	return name;
}

int Monster::gethealth()
{
	return health;
}

int Monster::getattackpower()
{
	return attackpower;
}

int Monster::getlevel()
{
	return level;
}

void Monster::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)  health = 0; 
}

void Monster::attack(Character& targetCharacter)
{
	targetCharacter.takeDamage(attackpower);
	std::cout << name << " attacks " << targetCharacter.getname() << " for " <<
		attackpower << " damage!\n";
}