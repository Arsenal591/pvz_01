#pragma once
#include"qrect"

enum BULLET_TYPE{green,fire,ice};
struct Bullet
{
public:
	Bullet(BULLET_TYPE, QRect);
	void changeType(BULLET_TYPE);//改变子弹种类

	BULLET_TYPE type;
	int lastChangePosy;//记录上一次子弹变性的位置，防止多次变性
	QRect rect;//子弹的几何位置
	int bornTime;//子弹的出生时间
	int atk;//子弹的攻击力
	int moveInterval;//子弹的移动间隔
	int cellx;//子弹所在的行
};