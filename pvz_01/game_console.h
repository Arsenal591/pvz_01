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
	void dealNormalLoop();
	void dealSpecialLoop();
private:
	int duration;
	int sunshine;
	QTimer *normalTimer, *specialTimer;
	QVector<Zombie*>zombies;
	QVector<Zombie*>unbornZombies;
	QVector<Plant*>plants;
	QVector<Sunshine*>sunshines;
	QVector<Bullet*>bullets;
	QVector<Card*>cards;
	Card* cardChosen;
private:
	void dealAttackOfBullets();
	void dealAttackOfZombies();
	void dealHpOfFlowers();
	void dealHpOfZombies();
	void dealBulletsMove();
	void dealFlowersMove();
	void sunshinesProduce();
	void zombiesProduce();
};