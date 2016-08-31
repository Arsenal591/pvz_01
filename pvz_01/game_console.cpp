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
	emit timeToShow();
}
void GameConsole::dealSpecialLoop()
{

}

void GameConsole::dealCardClicked(int n)
{
	if (cards[n]->getCost() <= sunshineLeft && duration - cards[n]->getLastUsed() >= cards[n]->getCd())
		cardChosen = cards[n];
	else
		cardChosen = nullptr;
	//if (cardChosen == nullptr)qDebug() << "a null card\n";
}

void GameConsole::dealSunshineClicked(MyLabel* label)
{
	sunshineLeft += 25;
	//��QVector<Sunshine*>sunshines�б���ɾ����Ӧ��
	//�����źţ�ʹ�ö�Ӧ��label��ɾ��
}

void GameConsole::dealPutPlant(int posx, int posy)
{
	//���cardchosen
	if (cardChosen == nullptr)
		return;

	//�����Ӧ�ĸ���
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

	//plants.insert()
	Plant* newPlant = new Plant(cardChosen->getType(), x, y);
	plants.push_back(newPlant);
	//sunshine -=
	sunshineLeft -= cardChosen->getCost();

	//card�����޸�
	cardChosen->setLastUsed(duration);

	//�����źţ����Ӷ�Ӧ��label
	PLANT_TYPE oldType = cardChosen->getType();
	emit addPlant(oldType, x, y);

	cardChosen = nullptr;
	//qDebug() << "success\n";
}
