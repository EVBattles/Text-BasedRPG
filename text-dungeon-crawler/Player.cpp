#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string n, int h, int a, int d) : GameCharacter(n, h, a, d) //sets up new player
{
	Item dagger = Item("Dagger", 0, 5, 0, false, false);
	addItem(dagger);
	Item key = Item("Key", 0, 0, 0, false, false);
	addItem(key);
	int startingCoin = 20;
	addCoin(startingCoin);
}

void Player::addCoin(int add)
{
	coinPurse += add;
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
	cout << "You have found: " << endl;
	vector<Item> items = room->items; // -> = pointer
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].isCoin == true)
		{
			cout << items[i].name << endl;
			addCoin(items[i].coinWorth);
		}
		else
		{
			cout << currentRoom->items[i].name << " attack: " << currentRoom->items[i].attack << " defense: " << currentRoom->items[i].defence << endl;
			addItem(items[i]);
		}
	}
	cout << "You now have " << coinPurse << " coins." << endl;
	cout << "In your inventory, you now have: " << endl;
	for (int i = 0; i < inventory.size(); i++)
	{
		cout << inventory[i].name << " attack: " << inventory[i].attack << " defence: " << inventory[i].defence << endl;
	}
}

void Player::changeRooms(Room* newRoom) //current room
{
	previousRoom = currentRoom;
	currentRoom = newRoom;
}