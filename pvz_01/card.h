#pragma once
#include"plant.h"

class Card
{
private:
	PLANT_TYPE cardType;
	int cd, cost;
	int lastUsed;
public:
	Card(PLANT_TYPE);
	PLANT_TYPE getType() { return cardType; }
	void setLastUsed(int t) { lastUsed = t; }
	int getLastUsed() { return lastUsed; }
	int getCd() { return cd; }
	int getCost() { return cost; }
};