#include"plant.h"

Plant::Plant(PLANT_TYPE tp, int tx, int ty) :type(tp), lastAttack(-999999), cellx(tx), celly(ty), ifPicked(true)
{
	switch (tp)
	{
	case peashooter:
		hp = 600, atk = 0, range = 0, cd = 7500, recharge = 1400, prepare = 0, cost = 100;
		break;
	case sunflower:
		hp = 600, atk = 0, range = 0, cd = 7500, recharge = 8000, prepare = 0, cost = 50;
		break;
	case wallnut:
		hp = 6000, atk = 0, range = 0, cd = 30000, recharge = 0, prepare = 0, cost = 50;
		break;
	case cherrybomb:
		hp = 600, atk = 1800, range = 1, cd = 30000, recharge = 0, prepare = 3500, cost = 150;
		break;
	case snowpea:
		hp = 600, atk = 0, range = 0, cd = 7500, recharge = 1400, prepare = 0, cost = 175;
		break;
	case repeater:
		hp = 600, atk = 0, range = 0, cd = 7500, recharge = 1400, prepare = 0, cost = 200;
		break;
	case torchwood:
		hp = 600, atk = 0, range = 0, cd = 7500, recharge = 0, prepare = 0, cost = 175;
		break;
	case potatomine:
		hp = 600, atk = 1800, range = 0, cd = 30000, recharge = 0, prepare = 15000, cost = 25;	
		break;
	case chomper:
		hp = 600, atk = 1800, range = 1, cd = 7500, recharge = 42000, prepare = 0, cost = 150;
		break;
	default:
		break;
	}
}