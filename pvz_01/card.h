#pragma once

enum CARD_TYPE{Peashooter, Sunflower, Wallnut};

class Card
{
private:
	CARD_TYPE cardType;
	int cd, cost;
	int lastUsed;
public:
	Card(CARD_TYPE);
	int getType() { return cardType; }
	void setLastUsed(int t) { lastUsed = t; }
	int getLastUsed() { return lastUsed; }
	int getCd() { return cd; }
	int getCost() { return cost; }
};