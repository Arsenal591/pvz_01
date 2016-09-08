#include "bullet.h"

Bullet::Bullet(BULLET_TYPE tp, QRect trect) :type(tp), rect(trect)
{
	switch (tp)
	{
	case green:
		moveInterval = 10, atk = 50;
		break;
	case fire:
		moveInterval = 10, atk = 100;
		break;
	case ice:
		moveInterval = 10, atk = 50;
		break;
	default:
		break;
	}
}

void Bullet::changeType(BULLET_TYPE tp)
{
	type = tp;
	if (type == fire)
		atk = 40;
}
