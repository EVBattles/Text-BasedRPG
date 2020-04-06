#pragma once

#include "Player.h"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
public:
	Player player;
	Room rooms[13];
	Dungeon(Player);
	int runDungeon(); //determines win or lose (return 0 for lose)
	void enterRoom(Room*);
	void handleEmptyRoom(Room*);
	void handleRoomWithChest(Room*);
	void handleRoomWithEnemy(Room*);
	void handleRoomWithTrap(Room*);
	void handleLootActions(Room*);
	void handleFightActions(GameCharacter*);
	void handleMovementActions(Room*);
	void printActions(int, string[]); //number of actions, string
	int performEndGameLogic();
	void printStats();
	void printHealth();
};

#endif