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

	// SET UP FIRST ROOM
	Room firstRoom = Room(0, false, vector<Item>(), vector<GameCharacter>());

	// SET UP SECOND ROOM
	Item fork = Item("Fork", 0, 20, 0);
	vector<Item> secondRoomItems;
	secondRoomItems.push_back(fork);
	Room secondRoom = Room(1, false, secondRoomItems, vector<GameCharacter>());

	// SET UP THE THIRD ROOM
	GameCharacter firstEnemy = GameCharacter("Goblin", 50, 15, 5);
	vector<GameCharacter> thirdRoomEnemies;
	thirdRoomEnemies.push_back(firstEnemy);
	Room thirdRoom = Room(2, false, vector<Item>(), thirdRoomEnemies);

	// SET UP THE FOURTH ROOM
	GameCharacter secondEnemy = GameCharacter("Zombie", 100, 20, 10);
	vector<GameCharacter> fourthRoomEnemies;
	fourthRoomEnemies.push_back(secondEnemy);
	Room fourthRoom = Room(3, true, vector <Item>(), fourthRoomEnemies);

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

