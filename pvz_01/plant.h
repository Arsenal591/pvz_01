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
	//int posx, posy;//����
	int cellx, celly;//����
	bool ifPicked;//�����������Ƿ��Ѿ���ʰ����Ϊfalse�����ܲ�������
	int lastPicked;//��һ�α�ʰ���ʱ��
public:
	Plant();
	QString getPath() { return path; }
	//virtual void attack() = 0;
	//virtual void draw() = 0;
};