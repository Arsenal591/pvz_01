#include "playing_interface.h"
#include "qpropertyanimation.h"
#include "qlabel.h"
#include "qmessagebox.h"
#include "qpalette.h"
#include "pvz_01.h"
#include "qdebug.h"
#include "qevent.h"

const QString PlayingInterface::backgroundPath = "../pvz-material/images/interface/background1.jpg";
const QString PlayingInterface::cardBoxPath = "../pvz-material/cardbox.png";
const QString PlayingInterface::cardPathName[] = { "../pvz-material/card_peashooter", "../pvz-material/card_sunflower", "../pvz-material/card_wallnut" };
PlayingInterface::PlayingInterface(QWidget* parent, GameConsole* t)
{
	this->info = t;

	this->setParent(parent);
	this->setFixedWidth(1200);
	this->setFixedHeight(800);

	setCardRect();
	setCellRect();

	memset(ifPlantExist, 0, sizeof(ifPlantExist));

	sunshineDisplay = new QLabel(parent);
	sunshineDisplay->setGeometry(QRect(185, 60, 30, 15));
	sunshineDisplay->setAlignment(Qt::AlignCenter);
	QPalette pal;
	pal.setColor(QPalette::Background, QColor(0xff, 0xff, 0xff, 0xff));
	sunshineDisplay->setPalette(pal);
	//sunshineDisplay->
	sunshineDisplay->setFont(QFont("consolas", 9));
	sunshineDisplay->show();

	for (int i = 0; i < 3; i++)
	{
		cardsShown.push_back(new MyLabel(parent, card, i));
		cardsShown[i]->setGeometry(cardRect[i]);
		//cardsShown[i]->setPalette(pal);
		cardsShown[i]->show();
	}
	leadInAnimation();
}

void PlayingInterface::mousePressEvent(QMouseEvent* ev)
{
	//pay attention: 此时只需处理点地板（放置植物），其他有效鼠标事件均已被MyLabel捕获
	if (ev->x() >= 135 && ev->x() <= 1105 && ev->y() >= 110 && ev->y() <= 760)
	{
		//do some stuff
		this->info->dealPutPlant(ev->x(), ev->y());
		return;
	}
	QWidget::mousePressEvent(ev);
	//delete cardsShown[0];
}

void PlayingInterface::setCardRect()
{
	int yLinePos = 250;
	for (int i = 0; i < 6; i++)
	{
		cardRect[i] = QRect(yLinePos, 10, 45, 63);
		yLinePos += 57;
	}
}
void PlayingInterface::setCellRect()
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
void PlayingInterface::leadInAnimation()
{
	backgroundImage = QPixmap(backgroundPath);
	backgroundImage = backgroundImage.scaled(QSize(1867,800));
	QLabel* label = new QLabel(this);
	label->setFixedSize(QSize(1867, 800));
	label->setPixmap(backgroundImage);
	label->show();
	QPropertyAnimation* animation = new QPropertyAnimation(label, "geometry");
	animation->setDuration(1000);
	animation->setStartValue(QRect(0, 0, 1200, 800));
	animation->setKeyValueAt(0.50, QRect(-667, 0, 1200, 800));
	animation->setKeyValueAt(0.60, QRect(-667, 0, 1200, 800));
	animation->setEndValue(QRect(-200, 0, 1200, 800));
	animation->start();
	QObject::connect(animation, SIGNAL(finished()), this, SLOT(cardAnimation()));
}
void PlayingInterface::cardAnimation()
{
	cardBoxImage = QPixmap(cardBoxPath);
	QLabel* label = new QLabel(this);
	label->setFixedSize(QSize(435, 84));
	label->setPixmap(cardBoxImage);
	label->show();
	QPropertyAnimation* animation = new QPropertyAnimation(label, "geometry");
	animation->setDuration(1000);
	animation->setStartValue(QRect(165, -84, 165, 84));
	animation->setEndValue(QRect(165, 0, 165, 84));
	QObject::connect(animation, SIGNAL(finished()), this->parentWidget(), SLOT(gameStart()));
	animation->start();
}

void PlayingInterface::dealCardClicked(int n)
{
	qDebug() << "card " << n << "is picked\n";
	emit doneCardClicked(n);
}
void PlayingInterface::dealSunshineClicked()
{
	emit doneSunshineClicked();
}
void PlayingInterface::refresh()
{
	//qDebug() << "signal reached!\n";
	MainWindow* temp = static_cast<MainWindow*>(this->parentWidget());
	const GameConsole& currentConsole = temp->getConsole();

	//display  sunshine
	QString str;
	str.setNum(currentConsole.sunshineLeft);
	sunshineDisplay->setText(str);

	//display  card
	for (int i = 0; i < currentConsole.cards.size(); i++)
	{
		Card* chosen = currentConsole.cards[i];
		str = cardPathName[chosen->getType()];
		if (currentConsole.duration - chosen->getLastUsed() >= chosen->getCd()
			&& currentConsole.sunshineLeft >= chosen->getCost())
			str += "_1.jpg";
		else str += "_2.jpg";
		//qDebug() << str << '\n';
		cardsShown[i]->setPixmap(str);
	}

	//display   plants
	for (int i = 0; i < currentConsole.plants.size(); i++)
	{
		Plant* chosen = currentConsole.plants[i];
		//redraw the plants
	}
	//display   zombies
	for (int i = 0; i < currentConsole.zombies.size(); i++)
	{
		Zombie* chosen = currentConsole.zombies[i];
		//. . .
		//redraw the zombies
	}

	for (int i = 0; i < currentConsole.sunshines.size(); i++)
	{
		Sunshine* chosen = currentConsole.sunshines[i];
		//redraw the sunshines
	}
}
