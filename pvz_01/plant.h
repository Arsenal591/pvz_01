#pragma once
#include<qobject>

enum PLANT_TYPE{peashooter, sunflower, wallnut, cherrybomb, snowpea, repeater, threepeater, torchwood};
class Plant:public QObject 
{
	Q_OBJECT
public:
	int hp, atk, range, cd, recharge, prepare, cost;
	int lastAttack;
	bool ifPicked;//�����������Ƿ��Ѿ���ʰ����Ϊfalse�����ܲ�������
	PLANT_TYPE type;
	QString path;
	int cellx, celly;//����
public:
	Plant(PLANT_TYPE tp, int tx, int ty) ;
};