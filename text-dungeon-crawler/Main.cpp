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
	cout << "Welcome to my dungeon crawler! What is your name?" << endl;
	string playerName;
	cin >> playerName;
	Player player = Player(playerName, 100, 20, 10);
	cout << endl << "Hello " << playerName << "!" << endl << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
	cout << "Here is a little information about your starting character." << endl << endl << endl;
	cout << "You currently have " << player.coinPurse << " coins in your coin purse." << endl << endl;
	cout << "You currently have " << player.currentHealth << " health, " << player.attack - 5 << " attack, and " << player.defence << " defense." << endl << endl;
	cout << "In your inventory, you currently have: " << endl;
	for (int i = 0; i < player.inventory.size(); i++)
	{
		cout << player.inventory[i].name << " attack: " << player.inventory[i].attack << " defense: " << player.inventory[i].defence << endl;
	}
	cout << endl;
	cout << "With your starting items you now have " << player.currentHealth << " health, " << player.attack << " attack, and " << player.defence << " defense." << endl << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	cout << "Now it is time to start the game!!!" << endl;
	cout << " _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _" << endl;
	cout << "| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| | " << endl;
	cout << endl << endl << endl << endl;
	
	// SET UP ROOM 0
	Room entrance = Room(0, false, vector<Item>(), vector<GameCharacter>()); // first room is empty

	// ------------------------------------------------------------ SET UP ROOM 1
	// set up items
	Item armor = Item("Armor", 0, 0, 20);
	Item healthpotion1 = Item("Health Potion", 0, 0, 0);
	healthpotion1.isPotion = true;
	healthpotion1.potionHealthAddAmount = 50;
	armor.isLocked = true;
	healthpotion1.isLocked = true;
	// apply items to group
	vector<Item> roomOneItems;
	roomOneItems.push_back(armor);
	roomOneItems.push_back(healthpotion1);
	// apply all to room
	Room roomOne = Room(1, false, roomOneItems, vector<GameCharacter>());

	// ------------------------------------------------------------ SET UP ROOM 2
	// set up enemy
	GameCharacter snake = GameCharacter("Snake", 50, 15, 5);
	// set up loot
	Item shield = Item("Shield", 0, 0, 5);
	// add loot to enemy
	snake.addLoot(shield);
	vector<GameCharacter> room2Enemies;
	room2Enemies.push_back(snake);
	// apply all to room
	Room roomTwo = Room(2, false, vector<Item>(), room2Enemies);

	// ------------------------------------------------------------ SET UP ROOM 3
	// set up items
	Item bow = Item("Bow", 0, 15, 0);
	Item coins = Item("200 Coins", 0, 0, 0);
	coins.isCoin = true;
	coins.coinWorth = 200;
	bow.isLocked = false;
	coins.isLocked = false;
	Item diamonds = Item("Diamonds", 0, 5, 0);
	diamonds.isLocked = false;
	// add items to group
	vector<Item> roomThreeItems;
	roomThreeItems.push_back(bow);
	roomThreeItems.push_back(coins);
	roomThreeItems.push_back(diamonds);
	// apply all to room
	Room roomThree = Room(3, false, roomThreeItems, vector<GameCharacter>());

	// ------------------------------------------------------------ SET UP ROOM 4
	// set up items
	Item healthPotion2 = Item("Health Potion", 0, 0, 0);
	healthPotion2.isPotion = true;
	healthPotion2.isLocked = false;
	healthPotion2.potionHealthAddAmount = 50;
	// add items to group
	vector<Item> roomFourItems;
	roomFourItems.push_back(healthPotion2);
	// apply all to room
	Room roomFour = Room(4, false, roomFourItems, vector<GameCharacter>());

	// ------------------------------------------------------------ SET UP ROOM 5
	// set up enemy
	GameCharacter spider = GameCharacter("spider", 100, 30, 10);
	// set up items
	Item knife = Item("Knife", 0, 6, 0);
	Item key1 = Item("Key", 0, 0, 0);
	key1.isKey = true;
	// add items to enemy loot
	spider.addLoot(knife);
	spider.addLoot(key1);
	vector<GameCharacter> room5Enemies;
	room5Enemies.push_back(spider);
	// apply all to room
	Room roomFive = Room(5, false, vector<Item>(), room5Enemies);

	// ------------------------------------------------------------ SET UP ROOM 6
	// set up items
	Item easterEgg = Item("Easter Egg", 0, 0, 0);
	easterEgg.isLocked = true;
	// add items to group
	vector<Item> roomSixItems;
	roomSixItems.push_back(easterEgg);
	// apply all to room
	Room roomSix = Room(6, false, roomSixItems, vector<GameCharacter>());

	// ------------------------------------------------------------ SET UP ROOM 7
	Room roomSeven = Room(7, false, vector<Item>(), vector<GameCharacter>());
	roomSeven.isTrap = true;

	// ------------------------------------------------------------ SET UP ROOM 8 
	Room roomEight = Room(8, false, vector<Item>(), vector<GameCharacter>());
	roomEight.isTrap = true;

	// ------------------------------------------------------------ SET UP ROOM 9
	// set up enemy
	GameCharacter dragon = GameCharacter("Big Red Dragon", 400, 60, 50);
	// set up loot
	Item stolenRiches = Item("Stolen Riches", 0, 0, 0);
	Item key2 = Item("Key", 0, 0, 0);
	key2.isKey = true;
	// apply loot to enemy
	dragon.addLoot(stolenRiches);
	dragon.addLoot(key2);
	vector<GameCharacter> room9Enemies;
	// apply all to room
	room9Enemies.push_back(dragon);
	Room roomNine = Room(9, false, vector<Item>(), room9Enemies);

	// ------------------------------------------------------------ SET UP ROOM 10
	Room roomTen = Room(10, false, vector<Item>(), vector<GameCharacter>());
	roomTen.isTrap = true;

	// ------------------------------------------------------------ SET UP ROOM 11
	// set up items
	Item coins2 = Item("200 coins", 0, 0, 0);
	coins2.isCoin = true;
	coins2.coinWorth = 200;
	coins2.isLocked = false;
	Item sword = Item("Dull Sword", 0, 10, 0);
	sword.isLocked = false;
	vector<Item> roomElevenItems;
	roomElevenItems.push_back(coins2);
	roomElevenItems.push_back(sword);
	Room roomEleven = Room(11, false, roomElevenItems, vector<GameCharacter>());

	// ------------------------------------------------------------ SET UP WIN ROOM
	Room roomTwelve = Room(11, true, vector<Item>(), vector<GameCharacter>());

	// PUT PLAYER IN DUNGEON
	Dungeon dungeon = Dungeon(player);

	// PUT ROOMS IN DUNGEON
	dungeon.rooms[0] = entrance;
	dungeon.rooms[1] = roomOne;
	dungeon.rooms[2] = roomTwo;
	dungeon.rooms[3] = roomThree;
	dungeon.rooms[4] = roomFour;
	dungeon.rooms[5] = roomFive;
	dungeon.rooms[6] = roomSix;
	dungeon.rooms[7] = roomSeven;
	dungeon.rooms[8] = roomEight;
	dungeon.rooms[9] = roomNine;
	dungeon.rooms[10] = roomTen;
	dungeon.rooms[11] = roomEleven;
	dungeon.rooms[12] = roomTwelve;

	while (true)
	{
		int result = dungeon.runDungeon();
		if (result != 1)
			break;
	}
	cout << "Goodbye!" << endl;
	return 0;
}

