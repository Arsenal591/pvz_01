#include "card.h"
#include "qstring.h"
//class QString;
Card::Card(CARD_TYPE type):cardType(type)
{
	switch (type)
	{
	case Peashooter:
		cd = 750, cost = 100;
		break;
	case Sunflower:
		cd = 750, cost = 50;
		break;
	case Wallnut:
		cd = 3000, cost = 50;
		break;
	default:
		break;
	}
}