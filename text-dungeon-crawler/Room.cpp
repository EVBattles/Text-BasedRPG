#include "Room.h"

Room::Room(int p, bool ie, vector<Item> is, vector<GameCharacter> gcs)
{
	pos = p;
	isExit = ie;
	items = is;
	enemies = gcs;
}
void Room :: clearLoot()
{
	items.clear();
}

void Room :: clearEnemies()
{
	enemies.clear();
}

void Room::dropLoot(GameCharacter * enemy)
{
	int i = 0;
	while (true)
	{
		items.push_back(enemy->loot[i]);
		i++;
		if (i >= enemy->loot.size())
			break;
	}
}