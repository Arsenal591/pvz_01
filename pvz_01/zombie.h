#pragma once
#include <qobject>
#include <qrect>

enum ZOMBIE_TYPE{normal, bucket, pole, cone, newspaper};
class Zombie:public QObject
{
	Q_OBJECT
public:
	Zombie(ZOMBIE_TYPE, int, int, QRect, int);
	ZOMBIE_TYPE type;

	//attention: 僵尸为匀速攻击，atk为每10毫秒的攻击力
	int hp, atk;
	int moveInterval;//多长时间移动一个像素
	int status;//0 初始，1 掉脑袋, 2 死亡, 3 消失
	bool ifAttacking;

	int step;//跳跃动画进行到哪一步 0 未开始 1 第一步 2 第二步 3 已经结束（只适用于撑杆僵尸）
	int lastStepTime;//上一步的结束时间

	int deadTime;//死亡时间

	int cellx, celly;//所在格子的坐标为(cellx, celly)
	int bornTime;//出生时间
	QRect rect;//僵尸的几何位置

	bool ifFrozen;//僵尸是否被冰冻
	int frozenTime;//僵尸最后一次被冰冻的时间

	bool ifBurned;//僵尸是否被烧焦
	int burnedTime;//僵尸最后一次被烧焦的时间
};
