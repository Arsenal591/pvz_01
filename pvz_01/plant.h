#pragma once
#include<qobject>

enum PLANT_TYPE{peashooter, sunflower, wallnut};
class Plant:public QObject 
{
	Q_OBJECT
public:
	static const int hp, atk, range, cd, recharge, prepare, cost;
private:
	PLANT_TYPE type;
	QString path;
	int lastAttack;
	//int posx, posy;//坐标
	int cellx, celly;//格子
	bool ifPicked;//产生的阳光是否已经被拾起；若为false，则不能产生阳光
	int lastPicked;//上一次被拾起的时间
public:
	Plant(PLANT_TYPE tp, int tx, int ty) :type(tp), lastAttack(-9999), cellx(tx), celly(ty), ifPicked(true), lastPicked(-9999) {}
	QString getPath() { return path; }
	//virtual void attack() = 0;
	//virtual void draw() = 0;
};