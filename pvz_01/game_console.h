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
	int level;//关卡
	int zombieSum;//该关卡应当生产的僵尸总数
	int roundSum;//该关卡的僵尸生产回合总数

	int zombieProduced;//当前生产回合已经生产的僵尸总数
	int zombieProduceList[100];
	int round;//当前处在第几个僵尸生产回合中
	int lastRoundFinish;//上一个生产回合结束的时间

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