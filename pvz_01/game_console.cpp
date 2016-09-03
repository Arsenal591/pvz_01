#include "game_console.h"
#include "qtimer"
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
	sunshineLeft = 2000;
	ifHumanWin = false;

	//���������ʬ������ʽ
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

	cardChosen = nullptr;

	setCellRect();
	connect();
}
void GameConsole::reset()
{
	duration = 0;
	sunshineLeft = 2000;
	ifHumanWin = false;
}
void GameConsole::setCards(QVector<int> res)
{
	qDebug() << "reached\n";
	for (int i = 0; i < res.size(); i++)
	{
		//qDebug() << res[i] << '\n';
		cards.push_back(new Card(PLANT_TYPE(res[i])));
	}
}
void GameConsole::setCellRect()
{
	int xLinePos = 110, yLinePos = 135;
	for (int i = 0; i < 5; i++)
	{
		yLinePos = 135;
		for (int j = 0; j < 10; j++)
		{
			int width = (j % 2) ? 105 : 110;
			cellRect[i][j] = QRect(yLinePos, xLinePos, width, 130);
			yLinePos += width;
		}
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

bool GameConsole::ifGameOver()
{
	for (int i = 0; i < zombies.size(); i++)
	{
		if (zombies[i]->rect.x() <= 10)
		{
			ifHumanWin = false;
			return true;
		}
	}
	if (zombies.size() == 0 && round == roundSum && zombieProduced == zombieProduceList[round])
	{
		ifHumanWin = true;
		level++;
		return true;
	}
	return false;
}

void GameConsole::sunshinesProduce()
{
	for (int i = 0; i < plants.size(); i++)
	{
		if (plants[i]->type == sunshine && duration - plants[i]->lastAttack >= plants[i]->recharge
			&& plants[i]->ifPicked)
		{
			Sunshine* newSunshine = new Sunshine(plants[i]->cellx, plants[i]->celly);
			sunshines.push_back(newSunshine);
			plants[i]->lastAttack = duration;
			plants[i]->ifPicked = false;
			emit addSunshine(plants[i]->cellx, plants[i]->celly, false);
		}
	}
	int randx = rand() % 5, randy = rand() % 9;
	if (!(rand() % 8))
	{
		Sunshine* newSunshine = new Sunshine(randx, randy);
		sunshines.push_back(newSunshine);
		emit addSunshine(randx, randy, true);
	}
}
void GameConsole::zombiesProduce()
{
	if (duration < 1000)return;//��û����һ�غ�
	if (round > roundSum)return;//���һ�غ��Ѿ�����
	if (duration - lastRoundFinish < 10000)//�غϼ����Ϣʱ�䲻��10s
		return;
	if (zombieProduced == zombieProduceList[round])//�ûغ��Ѿ�����
	{
		lastRoundFinish = duration;
		return;
	}
	if (duration == 1000 || duration - lastRoundFinish == 10000)//������һ�غ�
	{
		zombieProduced = 0;
		round++;
	}
	zombieProduced++;
	//qDebug() << "hey i am going to produce a zombie!\n";
	int producePos = rand() % 5;//����ڵ�10�е�ĳһ������
	
	//�˴������ѡ��ʬ����
	int randNum = rand() % 10;
	qDebug() << "randdom is " << randNum << '\n';
	ZOMBIE_TYPE produceType;
	if (randNum <= 10)
		produceType = pole;
	else if (randNum <= 7)
		produceType = bucket;
	else produceType = pole;
	//qDebug() << "in " << randNum << ' ' << 9 << endl;
	Zombie* newZombie = new Zombie(produceType, producePos, 9, cellRect[producePos][9], duration);
	zombies.push_back(newZombie);
	emit addZombie(produceType, producePos, 9);
}
void GameConsole::dealNormalLoop()
{
	if (ifGameOver())
	{
		normalTimer->stop();
		specialTimer->stop();
		emit gameOver(ifHumanWin);
		return;
	}
	duration += 10;
	dealAttackOfPlants();
	dealAttackOfBullets();
	dealAttackOfZombies();
	dealHpOfPlants();
	dealHpOfZombies();
	dealBulletsMove();
	dealZombiesMove();
	emit timeToShow();
}
void GameConsole::dealSpecialLoop()
{
	zombiesProduce();
	sunshinesProduce();
}

void GameConsole::dealCardClicked(int n)
{
	int x;
	for (int i = 0; i < cards.size(); i++)
		if (cards[i]->getType() == n)x = i;
	if (cards[x]->getCost() <= sunshineLeft && duration - cards[x]->getLastUsed() >= cards[x]->getCd())
		cardChosen = cards[x];
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
	newPlant->putTime = duration;
	plants.push_back(newPlant);

	sunshineLeft -= cardChosen->getCost();

	//card�����޸�
	cardChosen->setLastUsed(duration);

	//�����źţ����Ӷ�Ӧ��label
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

		if (zombies[i]->ifFrozen && duration - zombies[i]->frozenTime >= 10000)
		{
			zombies[i]->ifFrozen = false;
			zombies[i]->moveInterval /= 2;
			qDebug() << "i am not frozen\n";
		}

		if (zombies[i]->type == pole)
		{
			if ((zombies[i]->step == 1 || zombies[i]->step == 2) && duration - zombies[i]->lastStepTime >= 2500)
			{
				zombies[i]->step++;
				zombies[i]->lastStepTime = duration;
			}
			if (zombies[i]->step == 3 && zombies[i]->lastStepTime == duration)
			{
				zombies[i]->moveInterval *= 2;
				zombies[i]->celly--;
			}
		}

		zombies[i]->rect.moveLeft(zombies[i]->rect.x() - 1);

		if (zombies[i]->rect.x() + 40 < cellRect[zombies[i]->cellx][zombies[i]->celly].x())
		{
			zombies[i]->celly--;
			qDebug() << "i move to cell " << zombies[i]->cellx << ' ' << zombies[i]->celly << '\n';
		}
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

		for (int j = 0; j < plants.size(); j++)
		{
			QRect trect = cellRect[plants[j]->cellx][plants[j]->celly];
			if ((plants[j]->type == torchwood)
				&& (bullets[i]->rect.x() > trect.x())
				&& (bullets[i]->rect.x() + bullets[i]->rect.width() < trect.x() + trect.width())
				&& (bullets[i]->cellx == plants[j]->cellx)
				&& (plants[j]->celly != bullets[i]->lastChangePosy))
			{
				if (bullets[i]->type == green)
					bullets[i]->changeType(fire);
				else if (bullets[i]->type == ice)
					bullets[i]->changeType(green);
				bullets[i]->lastChangePosy = plants[j]->celly;
			}
		}
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
		case wallnut:case sunflower:case torchwood:
			break;
		case peashooter:case snowpea:
		{
			if (duration - plants[i]->lastAttack < plants[i]->recharge)
				break;
			BULLET_TYPE tp = (plants[i]->type == peashooter) ? green : ice;
			Bullet* newBullet = new Bullet(tp, QRect(rect.x() + 60, rect.y() + 30, 25, 25));
			newBullet->bornTime = duration;
			newBullet->cellx = plants[i]->cellx;
			plants[i]->lastAttack = duration;
			bullets.push_back(newBullet);
			emit addBullet(tp, plants[i]->cellx, plants[i]->celly);
			break; 
		}
		case chomper:
		{
			if (duration - plants[i]->lastAttack < plants[i]->recharge)
				break;
			for (int j = 0; j < zombies.size(); j++)
			{
				if((plants[i]->cellx == zombies[j]->cellx)
					&& ((plants[i]->celly + 1 == zombies[j]->celly)
						|| (plants[i]->celly == zombies[j]->celly)))
				{
					plants[i]->lastAttack = duration;
					zombies[j]->hp -= plants[i]->atk;
				}
			}
			break;
		}
		case cherrybomb:
		{
			if (duration - plants[i]->lastAttack < plants[i]->recharge)
				break;
			if (duration - plants[i]->putTime < plants[i]->prepare)
				break;
			for (int j = 0; j < zombies.size(); j++)
			{
				if (abs(zombies[j]->cellx - plants[i]->cellx) <= 1
					&& abs(zombies[j]->celly - plants[i]->celly) <= 1)
				{
					plants[i]->lastAttack = duration;
					zombies[j]->hp -= plants[i]->atk;
					zombies[j]->ifBurned = true;
					zombies[j]->burnedTime = duration;
				}
			}
			break;
		}
		case potatomine:
		{
			if (duration - plants[i]->lastAttack < plants[i]->recharge)
				break;
			if (duration - plants[i]->putTime < plants[i]->prepare)
				break;
			for (int j = 0; j < zombies.size(); j++)
			{
				if (plants[i]->cellx == zombies[j]->cellx
					&& plants[i]->celly == zombies[j]->celly)
				{
					plants[i]->lastAttack = duration;
					zombies[j]->hp -= plants[i]->atk;
					zombies[j]->ifBurned = true;
					zombies[j]->burnedTime = duration;
				}
			}
		}
			break;
		case repeater:
			break;
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

		for (int j = 0; j < zombies.size(); j++)
		{
			if ((bullets[i]->rect.x() + bullets[i]->rect.width() - 25 > zombies[j]->rect.x())
				&& (bullets[i]->rect.x() < zombies[j]->rect.x() + zombies[j]->rect.width() - 25) 
				&& (bullets[i]->cellx == zombies[j]->cellx))
			{
				zombies[j]->hp -= bullets[i]->atk;
				if (zombies[j]->ifFrozen == false && bullets[i]->type == ice)
				{
					//qDebug() << "i am frozen\n";
					zombies[j]->ifFrozen = true;
					zombies[j]->moveInterval *= 2;
					zombies[j]->frozenTime = duration;
				}

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
		if (zombies[i]->type == pole && zombies[i]->step != 0 && zombies[i]->step != 3)//��Ծ��ʬ��������Ծ
			continue;
		bool ifFound = false;
		for (int j = 0; j < plants.size(); j++)
		{
			if (zombies[i]->cellx == plants[j]->cellx && zombies[i]->celly == plants[j]->celly)
			{
				//qDebug() << "i am attacking a plant!\n";
				ifFound = true;
				if (zombies[i]->type == pole && zombies[i]->step == 0)
				{
					qDebug() << "i am jumping\n";
					zombies[i]->step = 1;
					zombies[i]->lastStepTime = duration;
				}
				else
				{
					zombies[i]->ifAttacking = true;
					plants[j]->hp -= zombies[i]->atk;
					//qDebug() << "i am attacked and my hp is now " << plants[j]->hp << '\n';
				}
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
		if ((plants[i]->type == cherrybomb || plants[i]->type == potatomine)
			&& (duration - plants[i]->lastAttack > 2000) && plants[i]->lastAttack > 0)
			ifDead = true;
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
		if (zombies[i]->status == 3)//�Ѿ�������ʧ
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