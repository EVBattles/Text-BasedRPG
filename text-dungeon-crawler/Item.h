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
	Item(string, int, int, int); //name, health, attack, defence
};

#endif