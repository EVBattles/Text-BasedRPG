#include "Dungeon.h"
#include <iostream>
#include <stdlib.h>

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
	cout << "You now have " << Dungeon::player.currentHealth << " health, " << Dungeon::player.attack << " attack, and " << player.defence << " defence." << endl;
}

void Dungeon::printHealth()
{
	cout << "You now have " << Dungeon::player.currentHealth << " health." << endl;
}

void Dungeon::handleLootActions(Room* room)
{
	Item item = room->items.front();
	int size = room->items.size();
	player.lootRoom(room);
	room->clearLoot();
	cout << "You open the chest and find a ";
	for (int i = 0; i < size; i++)
	{
		cout << item.name;
		if (i != size - 1)
		{
			cout << ", ";
		}
		else
		{
			cout << " ";
		}
	}
	cout << endl;
	cout << "In your inventory, you now have: " << endl;
	for (int i = 0; i < player.inventory.size(); i++)
	{
		cout << player.inventory[i].name << " attack: " << player.inventory[i].attack << " defence: " << player.inventory[i].defence << endl;
	}
	cout << endl;
	printStats();
}

void Dungeon::handleFightActions(GameCharacter * enemy)
{
	string actions[]{ "a. Attack", "b. Retreat" };
	while (true)
	{
		printActions(2, actions);
		string input;
		cin >> input;
		// handle player actions
		if (input == "a")
		{
			int chance;
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
			cout << "You win! You have defeated the " << enemy->name << "." << endl;
			player.increaseStats(10, 5, 5); // this is a level up, can go back and change this and print out changes
			cout << "You have leveled up! " << endl;
			printStats();
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
						cout << "You have found: " << endl;
						for (int j = 0; j < player.currentRoom->items.size(); j++)
						{
							cout << player.currentRoom->items[j].name << " attack: " << player.currentRoom->items[j].attack << " defense: " << player.currentRoom->items[j].defence << endl;
						}
						player.lootRoom(player.currentRoom);
						cout << "In your inventory, you now have: " << endl;
						for (int i = 0; i < player.inventory.size(); i++)
						{
							cout << player.inventory[i].name << " attack: " << player.inventory[i].attack << " defence: " << player.inventory[i].defence << endl;
						}
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
		int echance;
		echance = rand() % 20 + 1;
		int damage = 0;
		if (echance >= 10)
			damage = player.takeDamage(enemy->attack);
		else if (5 <= echance)
			damage = enemy->takeDamage(enemy->attack / 2);
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

void Dungeon :: handleRoomWithEnemy(Room* room)
{
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
}

void Dungeon :: handleRoomWithChest(Room* room)
{
	cout << "You enter the room and see a large chest in the middle." << endl;
	string actions[]{ "a. Loot the chest", "b. Move to another room"};
	while (true)
	{
		printActions(2, actions);
		string input;
		cin >> input;
		bool key = false;
		// check player's inventory for a key
		int i = 0; // while loop 1 counter
		int r = 0; // while loop 2 counter
		while(true)
		{
			if (player.inventory[i].name == "Key")
			{
				key = true;
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
							while (true)
							{
								if (player.inventory[r].name == "Key")
								{
									//append the word "-used" to key name string
									player.inventory[r].name += " - used";
									break;
								}
								r++;
							}
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
}

void Dungeon::handleEmptyRoom(Room* room)
{
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
}

void Dungeon::enterRoom(Room* room)
{
	if (room->enemies.size() != 0)
		handleRoomWithEnemy(room); // handle room with enemy
	else if (room->items.size() != 0)
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
	cout << "Welcome to the dungeon! Inside you will find treasure but also enemies. Enter at your own risk." << endl;
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
					// win the game
					cout << "You win! Play again?" << endl; // change this to next level if adding extra levels to dungeon
					// if extra levels, need to set up another statement like this to actually end the game
					return performEndGameLogic();
				}
				else
				{
					// door is locked, kill all enemies
					cout << "The door is still locked. Kill all enemies to win the game." << endl;
					cout << "You have " << player.currentRoom->enemies.size() << " left." << endl;
				}
			}
		}
		handleMovementActions(player.currentRoom);
	}
}