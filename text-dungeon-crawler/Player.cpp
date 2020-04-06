#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string n, int h, int a, int d) : GameCharacter(n, h, a, d) //sets up new player
{
	Item dagger = Item("Dagger", 0, 5, 0);
	addItem(dagger);
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
	cout << "You have found: " << endl << endl;
	vector<Item> items = room->items; // -> = pointer
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].isCoin == true)
		{
			cout << items[i].name << endl;
			addCoin(items[i].coinWorth);
		}
		else if (items[i].isPotion == true)
		{
			cout << items[i].name << endl;
			takeHealthPotion(&items[i]);
			addItem(items[i]);
		}
		else
		{
			cout << currentRoom->items[i].name << " attack: " << currentRoom->items[i].attack << ", defense: " << currentRoom->items[i].defence << endl;
			addItem(items[i]);
		}
	}
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "You now have " << coinPurse << " coins." << endl << endl;
	cout << "In your inventory, you now have: " << endl << endl;
	for (int i = 0; i < inventory.size(); i++)
	{
		cout << inventory[i].name << " attack: " << inventory[i].attack << ", defense: " << inventory[i].defence << endl;
	}
	cout << endl << "You now have " << currentHealth << " health, " << attack << " attack, and " << defence << " defense." << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void Player::takeHealthPotion(Item * potion)
{
	cout << "Would you like to take a health potion?" << endl;
	string actions[] = { "a. Yes", "b. No" };
	cout << "Choose an action:" << endl;
	for (int i = 0; i < 2; i++) {
		cout << actions[i] << endl;
	}
	string input;
	cin >> input;
	while (true)
	{
		if (input == "a")
		{
			cout << "You have taken the health potion." << endl;
			currentHealth += potion->potionHealthAddAmount;
			cout << "You now have " << currentHealth << " health." << endl;
			potion->name += "-empty";
			potion->isPotion = false;
			break;
		}
		else if (input == "b")
			break;
		else
			cout << "Inproper input" << endl;
	}
}

void Player::changeRooms(Room* newRoom) //current room
{
	previousRoom = currentRoom;
	currentRoom = newRoom;
}