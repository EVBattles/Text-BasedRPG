#pragma once

#include "Room.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameCharacter
{
public:
	Room * currentRoom;
	Room * previousRoom;
	vector<Item> inventory;
	int coinPurse;
	Player(string = "", int = 0, int = 0, int = 0); //name, health, attack, defence
	void addItem(Item);
	void increaseStats(int, int, int); //health, attack, defence
	void lootRoom(Room*);
	void changeRooms(Room*); //current room
	void addCoin(int); // add coins to coinPurse
};

#endif