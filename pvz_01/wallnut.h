#pragma once
#include "plant.h"

class Wallnut :public Plant
{
public:
	static const int hp = 4000, atk = 0, range = 0, cd = 30000, recharge = 0, prepare = 0, cost = 50;
public:
	Wallnut();
	void attack();
	void draw();
};