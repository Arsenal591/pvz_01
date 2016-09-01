#include "bullet.h"

Bullet::Bullet(BULLET_TYPE tp, QRect trect) :type(tp), rect(trect)
{
	switch (tp)
	{
	case green:
		moveInterval = 10, atk = 200;
		break;
	case fire:
		break;
	case ice:
		break;
	default:
		break;
	}
}
