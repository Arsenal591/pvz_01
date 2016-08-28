#pragma once
#include "plant.h"

class Sunflower:public Plant
{
private:
	bool ifPicked;//产生的阳光是否已经被拾起；若为false，则不能产生阳光
	int lastPicked;//上一次被拾起的时间
public:
	static const int hp = 300, atk = 0, range = 0, cd = 2400, recharge = 0, prepare = 0, cost = 50;
public:
	Sunflower();
	void attack();
	void draw();
};