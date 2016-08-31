#include"plant.h"

Plant::Plant(PLANT_TYPE tp, int tx, int ty) :type(tp), lastAttack(-999999), cellx(tx), celly(ty), ifPicked(true)
{
	switch (tp)
	{
	case peashooter:
		hp = 300, atk = 0, range = 0, cd = 7500, recharge = 1400, prepare = 0, cost = 100;
		break;
	case sunflower:
		hp = 300, atk = 0, range = 0, cd = 7500, recharge = 1000, prepare = 0, cost = 50;
		break;
	case wallnut:
		hp = 4000, atk = 0, range = 0, cd = 30000, recharge = 0, prepare = 0, cost = 50;
		break;
	default:
		break;
	}
}