#pragma once
#include<qobject>

enum PLANT_TYPE{peashooter, sunflower, wallnut};
class Plant:public QObject 
{
	Q_OBJECT
public:
	int hp, atk, range, cd, recharge, prepare, cost;
	int lastAttack;
	//int posx, posy;//����
	bool ifPicked;//�����������Ƿ��Ѿ���ʰ����Ϊfalse�����ܲ�������
	//int lastPicked;//��һ�α�ʰ���ʱ��
	PLANT_TYPE type;
	QString path;
	int cellx, celly;//����
public:
	Plant(PLANT_TYPE tp, int tx, int ty) ;
	//virtual void attack() = 0;
	//virtual void draw() = 0;
};