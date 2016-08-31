#include"zombie.h"

Zombie::Zombie(ZOMBIE_TYPE tp, int tx, int ty, QRect trect, int t)
	:type(tp), cellx(tx), celly(ty), rect(trect), bornTime(t), step(0), lastStepTime(t), ifAttacking(false), status(0)
{
	switch (tp)
	{
	case normal:
		hp = 270, atk = 1, moveInterval = 50;
		break;
	case bucket:
		hp = 1370, atk = 1, moveInterval = 50;
		break;
	case pole:
		hp = 1370, atk = 1, moveInterval = 30;
		break;
	default:
		break;
	}
}