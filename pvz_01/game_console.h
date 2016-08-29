#pragma once

#include "zombie.h"
#include "plant.h"
#include "sunshine.h"
#include "bullet.h"
#include "card.h"
#include "qvector"
#include "qwidget"

class QTimer;

class GameConsole:public QWidget
{
	Q_OBJECT
	friend class PlayingInterface;
public:
	GameConsole(QWidget* parent = nullptr);
public slots:
	void gameStart();
	void dealNormalLoop();
	void dealSpecialLoop();
private:
	int duration;//how long does this game lasts
	int sunshine;
	QRect cellRect[5][10];
	QRect cardRect[6];
	QTimer *normalTimer, *specialTimer;
	QVector<Zombie*>zombies;
	QVector<Zombie*>unbornZombies;
	QVector<Plant*>plants;
	QVector<Sunshine*>sunshines;
	QVector<Bullet*>bullets;
	QVector<Card*>cards;
	Card* cardChosen;
private:
	void connect();
	void setCellRect();
	void setCardRect();
	//void dealAttackOfBullets();
	//void dealAttackOfZombies();
	//void dealHpOfFlowers();
	//void dealHpOfZombies();
	//void dealBulletsMove();
	//void dealFlowersMove();
	//void sunshinesProduce();
	//void zombiesProduce();
};