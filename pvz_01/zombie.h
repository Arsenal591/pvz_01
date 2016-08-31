#pragma once
#include<qobject>

class Zombie:public QObject
{
	Q_OBJECT
public:
	//attention: ½©Ê¬ÎªÔÈËÙ¹¥»÷
	int hp, speed, atk;

};