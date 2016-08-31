#pragma once
#include<qobject>

enum PLANT_TYPE{peashooter, sunflower, wallnut};
class Plant:public QObject 
{
	Q_OBJECT
public:
	int hp, atk, range, cd, recharge, prepare, cost;
	int lastAttack;
	//int posx, posy;//坐标
	bool ifPicked;//产生的阳光是否已经被拾起；若为false，则不能产生阳光
	//int lastPicked;//上一次被拾起的时间
	PLANT_TYPE type;
	QString path;
	int cellx, celly;//格子
public:
	Plant(PLANT_TYPE tp, int tx, int ty) ;
	//virtual void attack() = 0;
	//virtual void draw() = 0;
};