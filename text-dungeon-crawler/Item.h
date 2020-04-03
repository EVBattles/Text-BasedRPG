#pragma once
#include <string>

#ifndef ITEM_H
#define ITEM_H

using namespace std;


class Item
{
public:
	string name;
	int health, attack, defence;
	bool isCoin;
	int coinWorth;
	bool isLocked;
	bool isPotion;
	bool isKey;
	int potionHealthAddAmount;
	Item(string, int, int, int); // name, health, attack, defence, isLocked, isCoin
};

#endif