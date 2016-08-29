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
};