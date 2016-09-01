#pragma once

#include "zombie.h"
#include "plant.h"
#include "sunshine.h"
#include "bullet.h"
#include "card.h"
#include "qvector"
#include "qwidget"
#include "mylabel.h"
#include "qdebug.h"
#include <cstdlib>
#include <ctime>

class QTimer;

class GameConsole:public QWidget
{
	Q_OBJECT
	friend class PlayingInterface;
public:
	explicit GameConsole(QWidget* parent = nullptr);
public slots:
	void gameStart();
	void dealNormalLoop();
	void dealSpecialLoop();
	void dealSunshineClicked(MyLabel*);
	void dealCardClicked(int);
	void dealPutPlant(int, int);
private:
	int level;//�ؿ�
	int zombieSum;//�ùؿ�Ӧ�������Ľ�ʬ����
	int roundSum;//�ùؿ��Ľ�ʬ�����غ�����

	int zombieProduced;//��ǰ�����غ��Ѿ������Ľ�ʬ����
	int zombieProduceList[100];
	int round;//��ǰ���ڵڼ�����ʬ�����غ���
	int lastRoundFinish;//��һ�������غϽ�����ʱ��

	int duration;//how long does this game lasts
	int sunshineLeft;
	QTimer *normalTimer, *specialTimer;
	QVector<Zombie*>zombies;
	QVector<Zombie*>unbornZombies;
	QVector<Plant*>plants;
	QVector<Sunshine*>sunshines;
	QVector<Bullet*>bullets;
	QVector<Card*>cards;
	Card* cardChosen;
private:
	QRect cellRect[5][10];
	void connect();
	void setCellRect();
	void dealAttackOfPlants();
	void dealAttackOfBullets();
	//void dealAttackOfZombies();
	//void dealHpOfFlowers();
	void dealHpOfZombies();
	void dealBulletsMove();
	void dealZombiesMove();
	//void sunshinesProduce();
	void zombiesProduce();
signals:
	void deleteSunshine(MyLabel*);
	void deleteZombie(MyLabel*);
	void deletePlant(MyLabel*);
	void deleteBullet(int);

	void addSunshine(int, int);
	void addZombie(enum ZOMBIE_TYPE, int, int);
	void addPlant(PLANT_TYPE,int, int);
	void addBullet(enum BULLET_TYPE, int, int);

	//void bulletMove(QRect, int, int);
	//void zombieMove(QRect, int, int);
	void zombieMove(int, int, int);
	void bulletMove(int);
	void timeToShow();
};