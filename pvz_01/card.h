#pragma once
#include"plant.h"

class Card
{
private:
	PLANT_TYPE cardType;//卡片所代表的植物类型
	int cd, cost;//冷却时间、花费
	int lastUsed;//上一次使用的时间
public:
	Card(PLANT_TYPE);
	PLANT_TYPE getType() { return cardType; }
	void setLastUsed(int t) { lastUsed = t; }
	int getLastUsed() { return lastUsed; }
	int getCd() { return cd; }
	int getCost() { return cost; }
};