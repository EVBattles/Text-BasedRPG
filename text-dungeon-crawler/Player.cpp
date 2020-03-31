#include "Player.h"

Player::Player(string n, int h, int a, int d) : GameCharacter(n, h, a, d) //sets up new player
{
	Item dagger = Item("Dagger", 0, 5, 0, false);
	addItem(dagger);
	Item key = Item("Key", 0, 0, 0, false);
	addItem(key);
}

void Player::addItem(Item item)
{
	inventory.push_back(item);
	increaseStats(item.health, item.attack, item.defence);
}

void Player::increaseStats(int h, int a, int d) //health, attack, defence
{
	currentHealth += h;
	maxHealth += h;
	attack += a;
	defence += d;
}

void Player::lootRoom(Room* room)
{
	vector<Item> items = room->items; // -> = pointer
	for (int i = 0; i < items.size(); i++)
	{
		addItem(items[i]);
	}
}

void Player::changeRooms(Room* newRoom) //current room
{
	previousRoom = currentRoom;
	currentRoom = newRoom;
}