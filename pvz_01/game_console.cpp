#include "game_console.h"
#include "qtimer"
//#include "qvector.h"
#include "qdebug.h"

GameConsole::GameConsole(QWidget* parent)
{
	this->setParent(parent);
	duration = 0;
	sunshineLeft = 100;

	normalTimer = new QTimer(this);
	specialTimer = new QTimer(this);
	normalTimer->setInterval(1);
	specialTimer->setInterval(1000);

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
	//qDebug() << duration << '\n';
	//sunshineLeft += 50;
	emit timeToShow();
}
void GameConsole::dealSpecialLoop()
{

}

void GameConsole::dealCardClicked(int n)
{
	if (cards[n]->getCost() >= sunshineLeft)
		cardChosen = cards[n];
	else
		cardChosen = nullptr;
}