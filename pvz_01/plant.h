#pragma once
#include<qobject>

enum PLANT_TYPE{peashooter, sunflower, wallnut, cherrybomb, snowpea, repeater, torchwood ,potatomine, chomper};
class Plant:public QObject 
{
	Q_OBJECT
public:
	int hp, atk, range, cd, recharge, prepare, cost;
	int lastAttack;
	bool ifPicked;//产生的阳光是否已经被拾起；若为false，则不能产生阳光
	PLANT_TYPE type;
	QString path;
	int cellx, celly;//格子
public:
	Plant(PLANT_TYPE tp, int tx, int ty) ;
};