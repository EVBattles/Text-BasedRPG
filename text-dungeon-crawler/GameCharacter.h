#pragma once
#include <string>
#include <vector>
#include "Item.h"
using namespace std;

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

class GameCharacter
{
public:
	string name;
	int maxHealth, currentHealth, attack, defence;
	vector<Item> loot;
	GameCharacter(string, int, int, int); //name, health, attack, defence
	int takeDamage(int);
	bool checkIsDead();
	void addLoot(Item);
};

#endif