#include <iostream>
#include "Dungeon.h"
/*#include "GameCharacter.cpp"
#include "Player.cpp"
#include "Item.cpp"
#include "Room.cpp"*/

int main()
{
	// SET UP PLAYER
	cout << "Welcome to our dungeon crawler! What is your name?" << endl;
	string playerName;
	cin >> playerName;
	Player player = Player(playerName, 100, 20, 10);
	cout << "You have " << player.coinPurse << " coins" << endl;
	cout << "You have " << player.currentHealth << " health, " << player.attack - 5 << " attack, and " << player.defence << " defence." << endl;
	cout << "In your inventory, you have: " << endl;
	for (int i = 0; i < player.inventory.size(); i++)
	{
		cout << player.inventory[i].name << " attack: " << player.inventory[i].attack << " defence: " << player.inventory[i].defence << endl;
	}
	cout << "You now have " << player.currentHealth << " health, " << player.attack << " attack, and " << player.defence << " defence." << endl;

	// SET UP FIRST ROOM
	Room firstRoom = Room(0, false, vector<Item>(), vector<GameCharacter>()); // first room is empty

	// SET UP SECOND ROOM
	Item fork = Item("Fork", 0, 20, 0, true, false); // set up item
	vector<Item> secondRoomItems;
	secondRoomItems.push_back(fork); // apply item to item group
	Room secondRoom = Room(1, false, secondRoomItems, vector<GameCharacter>()); // apply item group to room

	// SET UP THE THIRD ROOM
	GameCharacter firstEnemy = GameCharacter("Goblin", 50, 15, 5); // set up enemy
	Item fishbones = Item("Fishbones", 0, 1, 0, false, false); // set up loot
	Item coin = Item("20 Gold Coins", 0, 0, 0, false, true);
	coin.coinWorth = 20;
	firstEnemy.addLoot(fishbones); // apply loot to enemy
	firstEnemy.addLoot(coin);
	vector<GameCharacter> thirdRoomEnemies; 
	thirdRoomEnemies.push_back(firstEnemy); // apply enemy to enemy group
	Room thirdRoom = Room(2, false, vector<Item>(), thirdRoomEnemies); // apply enemy group to room

	// SET UP THE FOURTH ROOM
	GameCharacter secondEnemy = GameCharacter("Stone Golumn", 100, 20, 10); // set up enemy
	Item diamond = Item("Diamond", 0, 0, 5, false, false); // set up loot
	secondEnemy.addLoot(diamond); // apply loot to enemy
	vector<GameCharacter> fourthRoomEnemies;
	fourthRoomEnemies.push_back(secondEnemy); // apply enemy to enemy group
	Room fourthRoom = Room(3, true, vector <Item>(), fourthRoomEnemies); // apply enemy group to room

	// PUT PLAYER IN DUNGEON
	Dungeon dungeon = Dungeon(player);

	// PUT ROOMS IN DUNGEON
	dungeon.rooms[0] = firstRoom;
	dungeon.rooms[1] = secondRoom;
	dungeon.rooms[2] = thirdRoom;
	dungeon.rooms[3] = fourthRoom;

	while (true)
	{
		int result = dungeon.runDungeon();
		if (result != 1)
			break;
	}
	cout << "Goodbye!" << endl;
	return 0;
}

