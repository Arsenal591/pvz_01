#pragma once
#include "plant.h"

class Sunflower:public Plant
{
public:
	static const int hp = 300, atk = 0, range = 0, cd = 2400, recharge = 0, prepare = 0, cost = 50;
public:
	Sunflower();
	void attack();
	void draw();
};