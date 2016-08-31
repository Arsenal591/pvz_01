#include "card.h"
#include "qstring.h"
//class QString;
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
	default:
		break;
	}
}