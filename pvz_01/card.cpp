#include "card.h"
#include "qstring.h"
//class QString;
Card::Card(CARD_TYPE type):cardType(type)
{
	switch (type)
	{
	case Peashooter:
		cd = 0;
		break;
	case Sunflower:
		break;
	case Wallnut:
		break;
	default:
		break;
	}
}