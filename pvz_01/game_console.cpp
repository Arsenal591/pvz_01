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
	this->setParent(parent);
	duration = 0;
	sunshineLeft = 1000;

	normalTimer = new QTimer(this);
	specialTimer = new QTimer(this);
	normalTimer->setInterval(1);
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
			if (j <= 8)
				width = (j % 2) ? 105 : 110;
			else
				width = 95;
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

void GameConsole::dealNormalLoop()
{
	duration++;
	//qDebug() << duration << '\n';
	//sunshineLeft += 50;

	//for()
	emit timeToShow();
}
void GameConsole::dealSpecialLoop()
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
	sunshineLeft += 25;
	//从QVector<Sunshine*>sunshines列表中删除对应项
	//发出信号，使得对应的label被删除
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
