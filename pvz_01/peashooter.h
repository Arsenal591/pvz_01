#pragma once
#include"plant.h"

class PeaShooter :public Plant
{
public:
	static const int hp = 300, atk = 20, range = 0, cd = 750, recharge = 1400, prepare = 0, cost = 100;
public:
	PeaShooter();
	void attack();
	void draw();
};

