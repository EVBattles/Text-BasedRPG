#include "Dungeon.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Dungeon::Dungeon(Player p)
{
	player = p;
}

void Dungeon::printActions(int numActions, string actions[])
{
	cout << "Choose an action:" << endl;
	for (int i = 0; i < numActions; i++) {
		cout << actions[i] << endl;
	}
}

void Dungeon::printStats()
{
	cout << "You now have " << Dungeon::player.currentHealth << " health, " << Dungeon::player.attack << " attack, and " << player.defence << " defense." << endl << endl;
}

void Dungeon::printHealth()
{
	cout << "You now have " << Dungeon::player.currentHealth << " health." << endl << endl;
}

void Dungeon::handleLootActions(Room* room)
{
	Item item = room->items.front();
	int size = room->items.size();
	player.lootRoom(room);
	room->clearLoot();
}

void Dungeon::handleFightActions(GameCharacter * enemy)
{
	string actions[]{ "a. Attack", "b. Retreat" };
	while (true)
	{
		printActions(2, actions);
		string input;
		cin >> input;
		int i = 0;
		int hold = 0;
		bool potion = false;
		// handle player actions
		if (input == "a")
		{
			while (true)
			{
				if (player.inventory[i].isPotion == true)
				{
					potion = true;
					hold = i;
					break;
				}
				i++;
				if (i >= player.inventory.size())
				{
					break;
				}
			}
			if (potion == true)
			{
				player.takeHealthPotion(&player.inventory[hold]);
				cout << player.inventory[hold].name << " " << player.inventory[hold].isPotion << endl;
			}
			int chance;
			srand(time(NULL));
			chance = rand() % 20 + 1;
			int damage = 0;
			if (chance >= 10)
				damage = enemy->takeDamage(player.attack);
			else if (2 <= chance)
				damage = enemy->takeDamage(player.attack / 2);
			else
				cout << "You missed." << endl;
			cout << "Your attack does " << damage << " damage." << endl;
		}
		else if (input == "b")
		{
			player.changeRooms(player.previousRoom);
			enterRoom(player.currentRoom);
			return;
		}
		else
			cout << "Invalid choise" << endl;
		// check if enemy is dead
		if (enemy->checkIsDead())
		{
			cout << "You win! You have defeated the " << enemy->name << "." << endl << endl;
			player.increaseStats(10, 5, 5); // this is a level up, can go back and change this and print out changes
			cout << "You have leveled up! " << endl;
			printStats();
			cout << endl;
			if (enemy->loot.size() >= 0)
			{
				player.currentRoom->dropLoot(enemy);
				cout << "The " << enemy->name << " has dropped some loot." << endl;
				cout << "Would you like to pick up this loot?" << endl;
				string actions[]{ "a. Yes", "b. No" };
				while (true)
				{
					printActions(2, actions);
					string input;
					cin >> input;
					if (input == "a")
					{
						cout << endl << endl;
						player.lootRoom(player.currentRoom);
						break;
					}
					else if (input == "b")
					{
						break;
					}
					else
						cout << "Invalid choise" << endl;
				}
			}
			player.currentRoom->clearEnemies();
			return;
		}
		// handle enemy actions
		cout << endl << endl;
		int echance;
		srand(time(NULL));
		echance = rand() % 20 + 1;
		int damage = 0;
		if (echance >= 10)
			damage = player.takeDamage(enemy->attack);
		else if (5 <= echance)
			damage = player.takeDamage(enemy->attack / 2);
		else
			cout << enemy->name << " missed." << endl;
		cout << "The " << enemy->name << " does " << damage << " damage." << endl;
		printHealth();
		if (player.checkIsDead())
		{
			return;
		}
	}
}

void Dungeon::handleRoomWithTrap(Room* room)
{
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "This room is a trap!" << endl;
	srand(time(NULL));
	int trapType = rand() % 100 + 1;
	if (trapType < 10) // 9%
	{
		int damage = rand() % 30 + 1;
		player.takeDamage(damage);
		if (damage < player.defence)
			damage = 0;
		else
			damage = damage - player.defence;
		cout << "A giant boulder comes rolling out of the door above you and squishes you beneath." << endl;
		cout << "You take " << damage << " damage." << endl;
		printStats();
	}
	else if (10 <= trapType && trapType < 40) // 30%
	{
		int damage = rand() % 18 + 1;
		player.takeDamage(damage);
		if (damage < player.defence)
			damage = 0;
		else
			damage = damage - player.defence;
		cout << "The floor opens up and you fall onto the spiked floor beneath." << endl;
		cout << "You take " << damage << " damage." << endl;
		printStats();
	}
	else if (40 <= trapType && trapType < 45) // 5%
	{
		int damage = rand() % 36 + 1;
		player.takeDamage(damage);
		if (damage < player.defence)
			damage = 0;
		else
			damage = damage - player.defence;
		cout << "You walk into the room and an explosion of fire and magic engulf you." << endl;
		cout << "You take " << damage << " damage." << endl;
		printStats();
	}
	else if (45 <= trapType && trapType < 70) // 25%
	{
		int damage = rand() % 24 + 1;
		player.takeDamage(damage);
		if (damage < player.defence)
			damage = 0;
		else
			damage = damage - player.defence;
		cout << "A snake crawls out from the darkness and strikes your leg." << endl;
		cout << "You take " << damage << " damage." << endl;
		printStats();
	}
	else // 31%
	{
		int damage = rand() % 12 + 1;
		player.takeDamage(damage);
		if (damage < player.defence)
			damage = 0;
		else
			damage = damage - player.defence;
		cout << "The ground is uneven here and you stub your toe." << endl;
		cout << "You take " << damage << " damage." << endl;
		printStats();
	}
	room->isTrap = false;
	cout << "What would you like to do now?" << endl;
	string actions[]{ "a. Move to another room" };
	while (true)
	{
		printActions(1, actions);
		string input;
		cin >> input;
		if (input == "a")
			return;
		else
			cout << "Invalid choise" << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
}

void Dungeon :: handleRoomWithEnemy(Room* room)
{
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
		GameCharacter enemy = room->enemies.front();
		cout << "You enter the room and see a " << enemy.name << " in the middle." << endl;
		string actions[]{ "a. Fight the " + enemy.name, "b. Retreat" };
		while (true)
		{
			printActions(2, actions);
			string input;
			cin >> input;
			if (input == "a")
			{
				handleFightActions(&enemy);// fight
				return;
			}
			else if (input == "b")
			{
				player.changeRooms(player.previousRoom);
				enterRoom(player.currentRoom);
				return;
			}
			else
				cout << "Invalid choise" << endl;
		}
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
}

void Dungeon :: handleRoomWithChest(Room* room)
{
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "You enter the room and see a large chest in the middle." << endl;
	string actions[]{ "a. Loot the chest", "b. Move to another room"};
	while (true)
	{
		printActions(2, actions);
		string input;
		cin >> input;
		bool key = false;
		int hold = 0;
		// check player's inventory for a key
		int i = 0; // while loop 1 counter
		int r = 0; // while loop 2 counter
		while(true)
		{
			if (player.inventory[i].isKey == true)
			{
				key = true;
				hold = i;
				break;
			}
			i++;
			if (i > player.inventory.size())
			{
				break;
			}
		}
		if (input == "a")
		{
			// insert check condition to see if a key is required - check if item is locked
			for (int i = 0; i < room->items.size(); i++)
			{
				if (room->items[i].isLocked == false) // if the chest is not locked
					handleLootActions(room);
				else if (room->items[i].isLocked == true && key == true/*the player has a key*/) // if the chest is locked and the player has a key
				{
					// check to see if the player wants to use a key
					cout << "This chest is locked. Would you like to use a key?" << endl;
					string actions[]{ "a. Yes", "b. No" };
					while (true)
					{
						printActions(2, actions);
						string input;
						cin >> input;
						if (input == "a")
						{// set all items in the room to unlock
							for (int t = 0; t < room->items.size(); t++)
								room->items[i].isLocked = false;
							// remove key from inventory
							player.inventory[hold].name += "-used";
							player.inventory[hold].isKey = false;
							handleLootActions(room); // loot the chest
							break;
						}
						else if (input == "b")
							break;
						else
							cout << "Invalid choise" << endl;
					}
				}
				else // if the chest is locked and the player does not have a key
				{
					cout << "This chest is locked. You need a key." << endl;
					break;
				}
			}
			break;
		}
		else if (input == "b")
			break;
		else
			cout << "Invalid choise" << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
}

void Dungeon::handleEmptyRoom(Room* room)
{
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "You enter the room but it is empty." << endl;
	string actions[]{ "a. Move to another room"};
	while (true)
	{
		printActions(1, actions);
		string input;
		cin >> input;
		if (input == "a")
			return;
		else
			cout << "Invalid choise" << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl << endl;
}

void Dungeon::enterRoom(Room* room)
{
	if (room->enemies.size() != 0)
		handleRoomWithEnemy(room); // handle room with enemy
	else if (room->isTrap == true)
		handleRoomWithTrap(room);
	else if (room->items.size() != 0 && room->isTrap == false)
		handleRoomWithChest(room); // handle room with chest
	else
		handleEmptyRoom(room); // handle empty room
}

void Dungeon::handleMovementActions(Room * room)
{
	while (true)
	{
		if (room->pos == 0)
		{
			string actions[] = { "a. Move right", "b. Move down" };
			printActions(2, actions);
			string input;
			cin >> input;
			if (input == "a")
			{
				player.changeRooms(&rooms[1]);
				return;
			}
			else if (input == "b")
			{
				player.changeRooms(&rooms[2]);
				return;
			}
			else
			{
				cout << "Invalid choise" << endl;
			}
		}
		else if (room->pos == 1)
		{
			string actions[] = { "a. Move left"};
			printActions(1, actions);
			string input;
			cin >> input;
			if (input == "a")
			{
				player.changeRooms(&rooms[0]);
				return;
			}
			else
			{
				cout << "Invalid choise" << endl;
			}
		}
		else if (room->pos == 2)
		{
			string actions[] = { "a. Move up", "b. Move right" };
			printActions(2, actions);
			string input;
			cin >> input;
			if (input == "a")
			{
				player.changeRooms(&rooms[0]);
				return;
			}
			else if (input == "b")
			{
				player.changeRooms(&rooms[3]);
				return;
			}
			else
			{
				cout << "Invalid choise" << endl;
			}
		}
		else
		{
			string actions[] = { "a. Move left" };
			printActions(1, actions);
			string input;
			cin >> input;
			if (input == "a")
			{
				player.changeRooms(&rooms[2]);
				return;
			}
			else
			{
				cout << "Invalid choise" << endl;
			}
		}
	}
}

int Dungeon::performEndGameLogic()
{
	string actions[] = { "a. Yes", "b. No" };
	while (true)
	{
		printActions(2, actions);
		string input;
		cin >> input;
		if (input == "a")
		{
			return 1;
		}
		if (input == "b")
		{
			return 0;
		}
		else
		{
			cout << "Invalid choise" << endl;
		}
	}
}

int Dungeon::runDungeon() //determines win or lose (return 0 for lose)
{
	cout << "Welcome to the dungeon! Inside you will find treasure but also enemies. Enter at your own risk." << endl << endl; // enter story here when have it
	player.currentRoom = &rooms[0];
	player.previousRoom = &rooms[0];
	
	while (true) 
	{
		/*
		ORDER OF PLAY
		enter room
		present actions
		take action - enter sequence
		check if dead
		movement options
		end game logic
		*/
		enterRoom(player.currentRoom);
		if (player.checkIsDead())
		{
			cout << " _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _" << endl;
			cout << "| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| | " << endl;
			// lose the game and exit
			cout << "Game over! Try again?" << endl;
			return performEndGameLogic();
		}
		else 
		{
			if (player.currentRoom->isExit)
			{
				if (player.currentRoom->enemies.size() == 0)
				{
					cout << " _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _" << endl;
					cout << "| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| | " << endl;
					// win the game
					cout << "You win! Play again?" << endl; // change this to next level if adding extra levels to dungeon
					// if extra levels, need to set up another statement like this to actually end the game
					return performEndGameLogic();
				}
			}
		}
		handleMovementActions(player.currentRoom);
	}
}