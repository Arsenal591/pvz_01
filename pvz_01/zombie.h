#pragma once
#include<qobject>

class Zombie:public QObject
{
	Q_OBJECT
public:
	//attention: ��ʬΪ���ٹ���
	int hp, speed, atk;

};