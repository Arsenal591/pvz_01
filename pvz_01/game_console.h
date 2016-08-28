#pragma once

#include "zombie.h"
#include "plant.h"
#include "sunshine.h"
#include "bullet.h"
#include "card.h"
//class QTimer;
class GameConsole
{
public:
	GameConsole(QWidget* parent = nullptr);
	void dealNormalLoop();
	void dealSpecialLoop();
private:
	enum GAME_STATUS { Begin, Playing, About, Thanks, Setting }status;
	QTimer *normalTimer, *specialTimer;
	QVector<Zombie>zombies;
	QVector<Zombie>unbornZombies;
	QVector<Plant>plants;
	QVector<Sunshine>sunshines;
	QVector<Bullet>bullets;
	QVector<Card>cards;
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