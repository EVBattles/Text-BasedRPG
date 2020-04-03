#include <iostream>
#include "Dungeon.h"



/*
Here are some notes on how to create a dungeon in this game:


---------------------------------------------------------------------------GENERAL NOTES:--------------------------------------------------------------------
The mechanics of the game are handled in other files, but the main.cpp holds the items and game characters that are assigned to each room. 


-------------------------------------------------------------------------------ROOMS:-------------------------------------------------------------------------
To change the number of rooms, go to Dungeon.cpp -> handleMovementActions and change the if statements to update the number of rooms and how they connect. 

To create a room in the main.cpp file, call Room #name of room# = Room(Room #, isExit bool, items vector, game characters vector). Make sure to add it to the 
dungeon after you are done designing each room by dungeon.rooms[#room number#] = #room name#; 

Make sure to also to set the final room isExit to true to allow the end player to win. 

To edit trap effects and percentages, go to Dungeon.cpp->handleRoomsWithTraps().


-------------------------------------------------------------------------------ITEMS:--------------------------------------------------------------------------
To create an item, call Item #name of item# = Item(name, health bonus, attack bonus, defense bonus) 

There are several classes of items : equpment, coins, key, and health potion. All items are automatically equipment unless otherwise defined. 

To set an item to be a coin, make sure to call #item name#.isCoin = true; as well as #item name#.coinWorth = #; This will define the item as a coin and 
will define what it is worth to be added to the player's coin purse. 

When creating a Key, make sure that you use a capital K to allow the mechanics of inventory removal to work correctly. When the player uses these items, the program 
will add "-used" to the name and the player will not be able to use them again. You can add statats to the key if you would like, but I recommend just putting in the 
stats as 0s. Also, make sure to set isKey to true. 

To set an item as a health potion, make sure to call #item name#.isPotion = true; and #item name#.potionHealthAddAmount;. This will define the item as a potion and 
define how much health it will restore. Make sure to name the Health Potion as such with capitals to allow the program to add the health properly. When the player uses 
these items, the names will add "-used" and the player will not be able to use them again. 

An item can either be assigned to a room which will put it in a chest, which can be locked, or assigned as loot to a monster. 

To assign an item to a room, make sure to create a vector of items for the room and push each item into that vector. Once the vector is filled, follow the instructions 
regarding rooms to create the room with this vector. 

To assign an item as loot to a monster, call the enemy #enemy name#.addLoot(#item name#); to add the item to its loot inventory. 

To change starting items, stats, and coins for the Player, go to Player.cpp -> Player and change them there. 


--------------------------------------------------------------------------------ENEMY:----------------------------------------------------------------------------
To create an enemy, call GameCharacter #enemy name# = GameCharacter('#Enemy name#', health, attack, defense); From here you can add items to the enemy as loot. 
Once the enemy is created, push the monster onto the vector and include this vector<GameCharacter> as vector<GameCharacter> in your room definition. 

For now, this program only supports one monster per room, but you can add as much loot as you like. 


------------------------------------------------------------------------------EXAMPELS:---------------------------------------------------------------------
+EMPTY ROOM+

Room firstRoom = Room(0, false, vector<Item>(), vector<GameCharacter>());


+ROOM WITH CHEST+

Item fork = Item("Fork", 0, 20, 0); // set up item
fork.isLocked = true;
vector<Item> secondRoomItems;
secondRoomItems.push_back(fork); // apply item to item group
Room secondRoom = Room(1, false, secondRoomItems, vector<GameCharacter>()); // apply item group to room


+ROOM WITH MONSTER+

GameCharacter firstEnemy = GameCharacter("Goblin", 50, 15, 5); // set up enemy
Item fishbones = Item("Fishbones", 0, 1, 0); // set up loot
Item coin = Item("20 Gold Coins", 0, 0, 0);
coin.isCoin = true;
coin.coinWorth = 20;
firstEnemy.addLoot(fishbones); // apply loot to enemy
firstEnemy.addLoot(coin);
vector<GameCharacter> thirdRoomEnemies;
thirdRoomEnemies.push_back(firstEnemy); // apply enemy to enemy group
Room thirdRoom = Room(2, false, vector<Item>(), thirdRoomEnemies); // apply enemy group to room


+PUT PLAYER IN DUNGEON+

Dungeon dungeon = Dungeon(player);


+PUT ROOMS IN DUNGEON+

dungeon.rooms[0] = firstRoom;
dungeon.rooms[1] = secondRoom;
dungeon.rooms[2] = thirdRoom;
dungeon.rooms[3] = fourthRoom;
dungeon.rooms[3].isExit = true;


+CALL RUN DUNGEON+

while (true)
	{
		int result = dungeon.runDungeon();
		if (result != 1)
			break;
	}


+END PROGRAM+

cout << "Goodbye!" << endl;
return 0;
*/




int main()
{
	// SET UP PLAYER
	cout << "Welcome to our dungeon crawler! What is your name?" << endl;
	string playerName;
	cin >> playerName;
	Player player = Player(playerName, 100, 20, 10);
	cout << "You have " << player.coinPurse << " coins" << endl;
	cout << "You have " << player.currentHealth << " health, " << player.attack - 5 << " attack, and " << player.defence << " defense." << endl;
	cout << "In your inventory, you have: " << endl;
	for (int i = 0; i < player.inventory.size(); i++)
	{
		cout << player.inventory[i].name << " attack: " << player.inventory[i].attack << " defence: " << player.inventory[i].defence << endl;
	}
	cout << "You now have " << player.currentHealth << " health, " << player.attack << " attack, and " << player.defence << " defense." << endl;

	// SET UP FIRST ROOM
	Room firstRoom = Room(0, false, vector<Item>(), vector<GameCharacter>()); // first room is empty

	// SET UP SECOND ROOM
	/*Item fork = Item("Fork", 0, 20, 0); // set up item
	Item healthpotion1 = Item("Health Potion", 0, 0, 0);
	healthpotion1.potionHealthAddAmount = 20;
	fork.isLocked = true;
	healthpotion1.isLocked = true;
	healthpotion1.isPotion = true;
	vector<Item> secondRoomItems;
	secondRoomItems.push_back(fork); // apply item to item group
	secondRoomItems.push_back(healthpotion1);*/
	Room secondRoom = Room(1, false, vector<Item>(), vector<GameCharacter>()); // apply item group to room
	secondRoom.isTrap = true;

	// SET UP THE THIRD ROOM
	GameCharacter firstEnemy = GameCharacter("Goblin", 50, 15, 5); // set up enemy
	Item fishbones = Item("Fishbones", 0, 1, 0); // set up loot
	Item coin = Item("20 Gold Coins", 0, 0, 0);
	coin.isCoin = true;
	coin.coinWorth = 20;
	firstEnemy.addLoot(fishbones); // apply loot to enemy
	firstEnemy.addLoot(coin);
	vector<GameCharacter> thirdRoomEnemies; 
	thirdRoomEnemies.push_back(firstEnemy); // apply enemy to enemy group
	Room thirdRoom = Room(2, false, vector<Item>(), thirdRoomEnemies); // apply enemy group to room

	// SET UP THE FOURTH ROOM
	GameCharacter secondEnemy = GameCharacter("Stone Golumn", 100, 20, 10); // set up enemy
	Item diamond = Item("Diamond", 0, 0, 5); // set up loot
	Item healthpotion2 = Item("Health Potion", 0, 0, 0);
	healthpotion2.potionHealthAddAmount = 20;
	healthpotion2.isPotion = true;
	secondEnemy.addLoot(diamond); // apply loot to enemy
	secondEnemy.addLoot(healthpotion2);
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
	dungeon.rooms[3].isExit = true;

	while (true)
	{
		int result = dungeon.runDungeon();
		if (result != 1)
			break;
	}
	cout << "Goodbye!" << endl;
	return 0;
}

