#include "GameCharacter.h"
#include "Item.h"
#include "Room.h"

GameCharacter::GameCharacter(string n, int h, int a, int d)
{
	name = n;
	maxHealth = h;
	currentHealth = h;
	attack = a;
	defence = d;
}

int GameCharacter::takeDamage(int amount)
{
	int damage = amount - defence;
	if (damage < 0)
		damage = 0;
	currentHealth -= damage;
	return damage;
}

bool GameCharacter::checkIsDead()
{
	return currentHealth <= 0;
}

void GameCharacter::addLoot(Item item)
{
	loot.push_back(item);
}