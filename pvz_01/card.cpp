#include "card.h"

Card::Card(PLANT_TYPE type):cardType(type),lastUsed(-999999)
{
	switch (type)
	{
	case peashooter:
		cd = 7500, cost = 100;
		break;
	case sunflower:
		cd = 7500, cost = 50;
		break;
	case wallnut:
		cd = 30000, cost = 50;
		break;
	case cherrybomb:
		cd = 30000, cost = 150;
		break;
	case snowpea:
		cd = 7500, cost = 175;
		break;
	case repeater:
		cd = 7500, cost = 200;
		break;
	case torchwood:
		cd = 7500, cost = 175;
		break;
	case potatomine:
		cd = 30000, cost = 25;
		break;
	case chomper:
		cd = 7500, cost = 150;
		break;
	default:
		break;
	}
}