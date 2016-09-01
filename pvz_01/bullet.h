#pragma once
#include"qrect"

enum BULLET_TYPE{green,fire,ice};
class Bullet
{
public:
	Bullet(BULLET_TYPE, QRect);
	QRect rect;
	int bornTime;
	int atk;
	BULLET_TYPE type;
	int moveInterval;
	int cellx;
};