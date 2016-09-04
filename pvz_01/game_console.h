#pragma once

#include "zombie.h"
#include "plant.h"
#include "sunshine.h"
#include "bullet.h"
#include "card.h"
#include <qvector>
#include <qwidget>
#include "mylabel.h"
#include <qdebug>
#include <cstdlib>
#include <ctime>

class QTimer;

class GameConsole:public QWidget
{
	Q_OBJECT
	friend class PlayingInterface;
public:
	explicit GameConsole(QWidget* parent = nullptr);
	void reset();
	int getLastGameStatus() { return lastGameStatus; }
public slots:
	void setCards(QVector<int>);

	void gameStart();
	void dealNormalLoop();
	void dealSpecialLoop();

	void dealSunshineClicked(MyLabel*);
	void dealPlantClicked(MyLabel*);
	void dealCardClicked(int);
	void dealShovelClicked() { ifShovelPicked = true;}
	void dealShovelCanceled() { ifShovelPicked = false; }

	void dealPutPlant(int, int);
private:
	void connect();
	void setCellRect();

	bool ifGameOver();
	void zombieStrategy();

	void dealAttackOfPlants();
	void dealAttackOfBullets();
	void dealAttackOfZombies();

	void dealHpOfPlants();
	void dealHpOfZombies();

	void dealBulletsMove();
	void dealZombiesMove();

	void sunshinesProduce();
	void zombiesProduce();
signals:
	void gameOver(bool);

	void deleteSunshine(MyLabel*);
	void deletePlant(int);
	void deleteBullet(int);
	void deleteZombie(int);

	void addSunshine(int, int, bool);
	void addPlant(PLANT_TYPE, int, int);
	void addBullet(enum BULLET_TYPE, int, int);
	void addZombie(enum ZOMBIE_TYPE, int, int);

	void bulletMove(int);
	void zombieMove(int, int, int);

	void timeToShow();
private:
	bool ifHumanWin;
	int lastGameStatus;

	int level;//关卡
	bool visible, infinite, protect;

	int zombieSum;//该关卡应当生产的僵尸总数
	int roundSum;//该关卡的僵尸生产回合总数
	int zombieProduced;//当前生产回合已经生产的僵尸总数
	int* zombieProduceList;
	int round;//当前处在第几个僵尸生产回合中
	int lastRoundFinish;//上一个生产回合结束的时间

	int duration;
	int sunshineLeft;

	QTimer *normalTimer, *specialTimer;

	QVector<Sunshine*>sunshines;
	QVector<Plant*>plants;
	QVector<Bullet*>bullets;
	QVector<Zombie*>zombies;
	QVector<Card*>cards;

	Card* cardChosen;
	bool ifShovelPicked;
	QRect cellRect[5][10];
};