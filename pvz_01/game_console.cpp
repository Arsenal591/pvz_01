#include "game_console.h"
#include "qtimer"
//#include "qvector.h"
#include "qdebug.h"

bool inRect(int x, int y, QRect rect)
{
	return (x >= rect.x() && x <= rect.x() + rect.width() && y >= rect.y() && y <= rect.y() + rect.height());
}

GameConsole::GameConsole(QWidget* parent)
{
	srand(time(NULL));
	this->setParent(parent);
	duration = 0;
	sunshineLeft = 1000;
	level = 0;
	zombieSum = 1;
	memset(zombieProduceList, 0, sizeof(zombieProduceList));
	zombieProduceList[1] = 1;
	round = 1;
	roundSum = 1;
	zombieProduced = 0;
	lastRoundFinish = -999999;

	normalTimer = new QTimer(this);
	specialTimer = new QTimer(this);
	normalTimer->setInterval(10);
	specialTimer->setInterval(1000);

	cards.push_back(new Card(peashooter));
	cards.push_back(new Card(sunflower));
	cards.push_back(new Card(wallnut));

	cardChosen = nullptr;

	setCellRect();

	connect();
}
void GameConsole::setCellRect()
{
	int xLinePos = 110, yLinePos = 135;
	for (int i = 0; i < 5; i++)
	{
		yLinePos = 135;
		for (int j = 0; j < 10; j++)
		{
			int width;
			//if (j <= 8)
				width = (j % 2) ? 105 : 110;
			//else
				//width = 95;
			cellRect[i][j] = QRect(yLinePos, xLinePos, width, 130);
			//qDebug() << yLinePos << ' ' << xLinePos << ' ' << width << ' ' << 130<<'\n';
			yLinePos += width;
		}
		//qDebug() << "\n";
		xLinePos += 130;
	}
}
void GameConsole::connect()
{
	QObject::connect(normalTimer, SIGNAL(timeout()), this, SLOT(dealNormalLoop()));
	QObject::connect(specialTimer, SIGNAL(timeout()), this, SLOT(dealSpecialLoop()));
}
void GameConsole::gameStart()
{
	normalTimer->start();
	specialTimer->start();
}


void GameConsole::zombiesProduce()
{
	if (duration < 1000)return;//还没到第一回合
	if (round > roundSum)return;//最后一回合已经结束
	if (duration - lastRoundFinish < 10000)//回合间的休息时间不足10s
		return;
	if (zombieProduced == zombieProduceList[round])//该回合已经结束
	{
		lastRoundFinish = duration;
		return;
	}
	if (duration == 1000 || duration - lastRoundFinish == 10000)//进入下一回合
	{
		zombieProduced = 0;
		round++;
	}
	zombieProduced++;
	//qDebug() << "hey i am going to produce a zombie!\n";
	int producePos = rand() % 5;//随机在第10列的某一行生产
	
	//此处随机挑选僵尸种类
	int randNum = rand() % 10;
	ZOMBIE_TYPE produceType;
	if (randNum <= 10)
		produceType = bucket;
	else
	{

	}
	//qDebug() << "in " << randNum << ' ' << 9 << endl;
	Zombie* newZombie = new Zombie(produceType, producePos, 9, cellRect[producePos][9], duration);
	zombies.push_back(newZombie);
	emit addZombie(produceType, producePos, 9);
}
void GameConsole::dealNormalLoop()
{
	duration += 10;
	dealAttackOfPlants();
	dealAttackOfBullets();
	dealAttackOfZombies();
	dealHpOfPlants();
	dealHpOfZombies();
	dealBulletsMove();
	dealZombiesMove();
	//qDebug() << duration << '\n';
	//sunshineLeft += 50;

	//for()
	emit timeToShow();
}
void GameConsole::dealSpecialLoop()
{
	zombiesProduce();
	for (int i = 0; i < plants.size(); i++)
	{
		if (plants[i]->type == sunshine && duration - plants[i]->lastAttack >= plants[i]->recharge 
				&& plants[i]->ifPicked)
		{
			Sunshine* newSunshine = new Sunshine(plants[i]->cellx, plants[i]->celly);
			sunshines.push_back(newSunshine);
			plants[i]->lastAttack = duration;
			plants[i]->ifPicked = false;
			emit addSunshine(plants[i]->cellx, plants[i]->celly);
		}
	}
}

void GameConsole::dealCardClicked(int n)
{
	if (cards[n]->getCost() <= sunshineLeft && duration - cards[n]->getLastUsed() >= cards[n]->getCd())
		cardChosen = cards[n];
	else
		cardChosen = nullptr;
}

void GameConsole::dealSunshineClicked(MyLabel* label)
{
	//qDebug() << "GameConsole::dealSunshineClicked\n";
	sunshineLeft += 25;
	for (int i = 0; i < sunshines.size(); i++)
		if (sunshines[i]->cellx == label->cellx && sunshines[i]->celly == label->celly)
		{
			delete sunshines[i];
			sunshines.remove(i);
			break;
		}
	qDebug() << label->cellx << ' ' << label->celly << '\n';
	for (int i = 0; i < plants.size(); i++)
	{
		qDebug()<<plants[i]->type<<' '<< plants[i]->cellx << ' ' << plants[i]->celly << '\n';
		if (plants[i]->type == sunflower && plants[i]->cellx == label->cellx && plants[i]->celly == label->celly)
		{
			plants[i]->ifPicked = true;
			qDebug() << "sunflower " << plants[i]->cellx << ' ' << plants[i]->celly << "is reset\n";
			break;
		}
	}
	emit deleteSunshine(label);
}

void GameConsole::dealPutPlant(int posx, int posy)
{
	if (cardChosen == nullptr)
		return;
	int x, y;
	bool isFound = false;
	for (int i = 0; i < 5; i++)
	{
		if (isFound)break;
		for (int j = 0; j < 9; j++)
			if (inRect(posx, posy, cellRect[i][j]))
			{
				x = i, y = j;
				isFound = true;
				break;
			}
	}

	Plant* newPlant = new Plant(cardChosen->getType(), x, y);
	plants.push_back(newPlant);

	sunshineLeft -= cardChosen->getCost();

	//card属性修改
	cardChosen->setLastUsed(duration);

	//发出信号，增加对应的label
	PLANT_TYPE oldType = cardChosen->getType();
	emit addPlant(oldType, x, y);

	cardChosen = nullptr;
}

void GameConsole::dealZombiesMove()
{
	for (int i = 0; i < zombies.size(); i++)
	{
		if ((duration - zombies[i]->bornTime) % zombies[i]->moveInterval)
			continue;
		if (zombies[i]->ifAttacking)continue;
		if (zombies[i]->status > 1)continue;

		zombies[i]->rect.moveLeft(zombies[i]->rect.x() - 1);

		//qDebug() << "now is " << duration << '\n';
		//qDebug() << "my pos x is " << zombies[i]->rect.x() << '\n';

		if (zombies[i]->rect.x() + 40 < cellRect[zombies[i]->cellx][zombies[i]->celly].x())
		{
			zombies[i]->celly--;
			qDebug() << "i move to cell " << zombies[i]->cellx << ' ' << zombies[i]->celly << '\n';
		}
		//emit zombieMove(rect, zombies[i]->cellx, zombies[i]->celly);
		emit zombieMove(i, zombies[i]->cellx, zombies[i]->celly);
	}
}
void GameConsole::dealBulletsMove()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if ((duration - bullets[i]->bornTime) % bullets[i]->moveInterval)
			continue;
		bullets[i]->rect.moveLeft(bullets[i]->rect.x() + 1);
		emit bulletMove(i);
	}
}
void GameConsole::dealAttackOfPlants()
{
	for (int i = 0; i < plants.size(); i++)
	{
		QRect rect = cellRect[plants[i]->cellx][plants[i]->celly];
		switch (plants[i]->type)
		{
		case wallnut:
			break;
		case sunflower:
			break;
		case peashooter:
		{
			if (duration - plants[i]->lastAttack < plants[i]->recharge)break;
			Bullet* newBullet = new Bullet(green, QRect(rect.x() + 60, rect.y() + 30, 25, 25));
			newBullet->bornTime = duration;
			newBullet->cellx = plants[i]->cellx;
			plants[i]->lastAttack = duration;
			bullets.push_back(newBullet);
			emit addBullet(green, plants[i]->cellx, plants[i]->celly);
			break; 
		}
		default:
			break;
		}
	}
}
void GameConsole::dealAttackOfBullets()
{
	int i = 0;
	while (i < bullets.size())
	{
		bool ifAttack = false;
		//qDebug() << "this bullet posx is" << bullets[i]->rect.x() << '\n';
		for (int j = 0; j < zombies.size(); j++)
		{
			if ((bullets[i]->rect.x() + bullets[i]->rect.width() - 25 > zombies[j]->rect.x())
				&& (bullets[i]->rect.x() < zombies[j]->rect.x() + zombies[j]->rect.width() - 25) 
				&& (bullets[i]->cellx == zombies[j]->cellx))
			{
				zombies[j]->hp -= bullets[i]->atk;
				//qDebug() << "i am attacked and my hp is now " << zombies[j]->hp << '\n';
				delete bullets[i];
				bullets.remove(i);
				emit deleteBullet(i);
				ifAttack = true;
				break;
			}
		}
		if (!ifAttack)i++;
	}
}
void GameConsole::dealAttackOfZombies()
{
	for (int i = 0; i < zombies.size(); i++)
	{
		if (zombies[i]->status > 1)continue;
		if (zombies[i]->type == pole && zombies[i]->status != 0 && zombies[i]->status != 3)//跳跃僵尸且正在跳跃
			continue;
		bool ifFound = false;
		for (int j = 0; j < plants.size(); j++)
		{
			if (zombies[i]->cellx == plants[j]->cellx && zombies[i]->celly == plants[j]->celly)
			{
				//qDebug() << "i am attacking a plant!\n";
				ifFound = true;
				zombies[i]->ifAttacking = true;
				plants[j]->hp -= zombies[i]->atk;
				qDebug() << "i am attacked and my hp is now " << plants[j]->hp << '\n';
				break;
			}
		}
		if (!ifFound)zombies[i]->ifAttacking = false;
	}
}

void GameConsole::dealHpOfPlants()
{
	int i = 0;
	while (i < plants.size())
	{
		bool ifDead = (plants[i]->hp <= 0);
		if (ifDead)
		{
			delete plants[i];
			plants.remove(i);
			emit deletePlant(i);
		}
		else i++;
	}
}

void GameConsole::dealHpOfZombies()
{
	int i = 0;
	while (i < zombies.size())
	{
		if (zombies[i]->status == 3)
		{
			delete zombies[i];
			zombies.remove(i);
			emit deleteZombie(i);
			continue;
		}
		bool ifDead = (zombies[i]->hp <= 0);
		if (ifDead)
		{
			if (zombies[i]->status != 2)
			{
				zombies[i]->status = 2;
				zombies[i]->deadTime = duration;
			}
			else
			{
				if (duration - zombies[i]->deadTime >= 2000)
					zombies[i]->status = 3;
			}

		}
		else 
		{
			if (zombies[i]->type == ZOMBIE_TYPE::normal)
			{
				if (zombies[i]->hp <= 70)
					zombies[i]->status = 1;
			}
			if (zombies[i]->type == ZOMBIE_TYPE::bucket)
			{

			}
		}
		i++;
	}
}