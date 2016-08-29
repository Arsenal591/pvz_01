#include "game_console.h"
#include "qtimer"
//#include "qvector.h"
#include "qdebug.h"

GameConsole::GameConsole(QWidget* parent)
{
	this->setParent(parent);
	duration = 0;
	sunshine = 100;

	normalTimer = new QTimer(this);
	specialTimer = new QTimer(this);
	normalTimer->setInterval(1);
	specialTimer->setInterval(1000);

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

	cards.push_back(new Card(Peashooter));
	cards.push_back(new Card(Sunflower));
	cards.push_back(new Card(Wallnut));

	cardChosen = nullptr;

	connect();
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
	qDebug() << duration << '\n';
}
void GameConsole::dealSpecialLoop()
{

}