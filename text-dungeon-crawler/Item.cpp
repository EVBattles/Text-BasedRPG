#include "Item.h"

Item::Item(string n, int h, int a, int d, bool isL, bool isC) {
	name = n;
	health = h;
	attack = a;
	defence = d;
	isLocked = isL;
	isCoin = isC;
};