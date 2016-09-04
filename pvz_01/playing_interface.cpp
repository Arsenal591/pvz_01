#include "playing_interface.h"
#include "qpropertyanimation.h"
#include "qlabel.h"
#include "qmessagebox.h"
#include "qpushbutton.h"
#include "qpalette.h"
#include "pvz_01.h"
#include "qdebug"
#include "qevent"
#include "qmovie"
#include "qmovie.h"

PlayingInterface::PlayingInterface(QWidget* parent, GameConsole* t)
{
	this->info = t;

	this->setParent(parent);
	this->setFixedWidth(1200);
	this->setFixedHeight(800);

	setCardRect();
	setCellRect();

	memset(ifPlantExist, 0, sizeof(ifPlantExist));
	
	option = new MyButton(this, OPTION_BUTTON_PATH);
	option->setSize(QRect(1000, -3, 113, 41));
	option->setOffset(2, 2);
	option->show();

	backgroundImage = QPixmap(BACKGROUND_PATH);
	backgroundImage = backgroundImage.scaled(QSize(1867, 800));
	backgroundLabel = new QLabel(this);
	backgroundLabel->setFixedSize(QSize(1867, 800));
	backgroundLabel->setPixmap(backgroundImage);
	backgroundLabel->show();

	cardBoxImage = QPixmap(CARDBOX_PATH);
	cardBoxLabel = new QLabel(this);
	cardBoxLabel->setFixedSize(QSize(435, 84));
	cardBoxLabel->setPixmap(cardBoxImage);
	cardBoxLabel->hide();

	sunshineDisplay = new QLabel(this);
	//sunshineDisplay = new QLabel(parent);
	sunshineDisplay->setGeometry(QRect(185, 60, 30, 15));
	sunshineDisplay->setAlignment(Qt::AlignCenter);
	QPalette pal;
	pal.setColor(QPalette::Background, QColor(0xff, 0xff, 0xff, 0xff));
	sunshineDisplay->setPalette(pal);
	sunshineDisplay->setFont(QFont("consolas", 9));
	sunshineDisplay->show();

	SelectCard* selectCard = new SelectCard(this);
	//SelectCard* selectCard = new SelectCard(this->parentWidget());
	selectCard->show();
	connect(selectCard, SIGNAL(selected(QVector<int>)), this, SLOT(setCards(QVector<int>)));
	connect(selectCard, SIGNAL(selected(QVector<int>)), selectCard, SLOT(hide()));
	connect(selectCard, SIGNAL(selected(QVector<int>)), info, SLOT(setCards(QVector<int>)));
	//leadInAnimation();
}
void PlayingInterface::setCards(QVector<int> res)
{
	qDebug() << "cards set\n";
	qDebug() << res.size() << '\n';
	for (int i = 0; i < res.size(); i++)
	{
		cardsShown.push_back(new MyLabel(cardBoxLabel, card, res[i]));
		cardsShown[i]->setGeometry(cardRect[i]);
		cardsShown[i]->show();
		connect(cardsShown[i], SIGNAL(cardClicked(int)), this, SLOT(dealCardClicked(int)));
	}
	leadInAnimation();
}
void PlayingInterface::mousePressEvent(QMouseEvent* ev)
{
	//pay attention: 此时只需处理点地板（放置植物），其他有效鼠标事件均已被MyLabel捕获
	if (ev->x() >= 135 && ev->x() <= 1105 && ev->y() >= 110 && ev->y() <= 760)
	{
		qDebug() << ev->x() << ' ' << ev->y() << '\n';
		this->info->dealPutPlant(ev->x(), ev->y());
		return;
	}
	QWidget::mousePressEvent(ev);
}

void PlayingInterface::setCardRect()
{
	int yLinePos = 85;
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
			int width = (j % 2) ? 105 : 110;
			cellRect[i][j] = QRect(yLinePos, xLinePos, width, 130);
			yLinePos += width;
		}
		xLinePos += 130;
	}
}
void PlayingInterface::leadInAnimation()
{
	QPropertyAnimation* animation = new QPropertyAnimation(backgroundLabel, "geometry");
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
	cardBoxLabel->show();
	QPropertyAnimation* animation = new QPropertyAnimation(cardBoxLabel, "geometry");
	animation->setDuration(1000);
	animation->setStartValue(QRect(165, -84, 165, 84));
	animation->setEndValue(QRect(165, 0, 165, 84));
	QObject::connect(animation, SIGNAL(finished()), info, SLOT(gameStart()));
	animation->start();
}

void PlayingInterface::gameOver(bool check)
{
	QString str;
	if (check == true)
		str = QStringLiteral("恭喜你通过本关！");
	else str = QStringLiteral("僵尸吃掉了你的脑子");
	QMessageBox box(QMessageBox::Information, QStringLiteral("提示"), str, QMessageBox::Yes);
	if (box.exec() == QMessageBox::Yes)
		emit gameReturn();
}

void PlayingInterface::dealCardClicked(int n)
{
	qDebug() << "card " << n << "is picked\n";
	emit doneCardClicked(n);
}
void PlayingInterface::dealSunshineClicked(MyLabel* label)
{
	emit doneSunshineClicked(label);
}
void PlayingInterface::addPlant(PLANT_TYPE tp, int x, int y)
{
	MyLabel* newLabel = new MyLabel(this, plant);
	newLabel->cellx = x, newLabel->celly = y;
	newLabel->QLabel::setGeometry(cellRect[x][y]);
	plantsShown.push_back(newLabel);
	newLabel->setPath(PLANT_FOLDER[tp]);
	qDebug() << PLANT_FOLDER[tp] << '\n';
	QMovie* movie = new QMovie(newLabel->getPath() + "1.gif");
	newLabel->setMovie(movie);
	movie->start();
	newLabel->show();
}
void PlayingInterface::addSunshine(int x, int y, bool ifDrop)
{
	MyLabel* newLabel = new MyLabel(this, sunshine);
	newLabel->cellx = x, newLabel->celly = y;
	connect(newLabel, SIGNAL(sunshineClicked(MyLabel*)), this, SLOT(dealSunshineClicked(MyLabel*)));

	QRect rect = cellRect[x][y];
	newLabel->setGeometry(QRect(rect.x() + 0.5*rect.width(), rect.y() + 0.5*rect.height(), 60, 60));
	
	newLabel->setPath(SUNSHINE_PATH);
	QMovie* movie = new QMovie(newLabel->getPath());
	movie->setScaledSize(QSize(60, 60));
	newLabel->setMovie(movie);
	movie->start();

	sunshineShown.push_back(newLabel);
	newLabel->show();

	if (ifDrop)
	{
		QPropertyAnimation* animation = new QPropertyAnimation(newLabel, "geometry");
		QRect startPos(rect.x() + 0.5 * rect.width(), 0, 60, 60);
		if (y < 4)startPos.moveTop(84);
		animation->setStartValue(startPos);
		animation->setEndValue(QRect(rect.x() + 0.5*rect.width(), rect.y() + 0.5*rect.height(), 60, 60));
		int dt = (rect.y() + 0.5*rect.height()) * 10;
		animation->setDuration(dt);
		animation->start();
	}
}
void PlayingInterface::addZombie(enum ZOMBIE_TYPE tp, int x, int y)
{
	qDebug() << tp << ' ' << x << ' ' << y << '\n';
	MyLabel* newLabel = new MyLabel(this, zombie);
	connect(newLabel, SIGNAL(mayPutPlant(int, int)), info, SLOT(dealPutPlant(int, int)));
	newLabel->cellx = x, newLabel->celly = y;
	newLabel->rect = cellRect[x][y];

	QString str = ZOMBIE_FOLDER[tp];
	switch (tp)
	{
	case normal:
		//str = ZOMBIE_FOLDER[tp];
		break;
	case bucket:
		//str = 
		break;
	case pole:
		//str += "PoleVaultingZombie/";
		newLabel->rect.setWidth(newLabel->width() + 70);
		newLabel->rect.moveLeft(newLabel->rect.x() - 30);
		break;
	default:
		break;
	}
	newLabel->setGeometry(newLabel->rect);
	newLabel->setPath(str);

	QMovie* newMovie = new QMovie(str + "1.gif");
	newLabel->setMovie(newMovie);
	newMovie->start();

	zombiesShown.push_back(newLabel);
	newLabel->show();
}
void PlayingInterface::addBullet(enum BULLET_TYPE tp, int x, int y)
{
	MyLabel* newLabel = new MyLabel(this, bullet);
	newLabel->rect = QRect(cellRect[x][y].x() + 60, cellRect[x][y].y() + 30, 60, 25);
	newLabel->setGeometry(newLabel->rect);
	QString str = BULLET_FOLDER[tp];
	switch (tp)
	{
	case normal:
		break;
	case fire:
		break;
	case ice:
		break;
	default:
		break;
	}
	qDebug() << str <<'\n';
	newLabel->setPath(str);
	//newLabel->setPixmap(newLabel->getPath());
	QMovie* newMovie = new QMovie(newLabel->getPath());
	newLabel->setMovie(newMovie);
	newMovie->start();
	bulletsShown.push_back(newLabel);
	newLabel->show();
}
void PlayingInterface::deleteSunshine(MyLabel* label)
{
	for(int i = 0; i < sunshineShown.size(); i++)
		if (label == sunshineShown[i])
		{
			delete sunshineShown[i];
			sunshineShown.remove(i);
			break;
		}
}
void PlayingInterface::deleteBullet(int rank)
{
	delete bulletsShown[rank];
	bulletsShown.remove(rank);
}
void PlayingInterface::deleteZombie(int rank)
{
	delete zombiesShown[rank];
	zombiesShown.remove(rank);
}
void PlayingInterface::deletePlant(int rank)
{
	delete plantsShown[rank];
	plantsShown.remove(rank);
}
void PlayingInterface::zombieMove(int rank, int tx, int ty)
{
	zombiesShown[rank]->rect.moveLeft(zombiesShown[rank]->rect.x() - 1);
	zombiesShown[rank]->cellx = tx;
	zombiesShown[rank]->celly = ty;
}
void PlayingInterface::bulletMove(int rank)
{
	bulletsShown[rank]->rect.moveLeft(bulletsShown[rank]->x() + 1);
}
void PlayingInterface::refresh()
{
	const GameConsole& currentConsole = *info;

	//display  sunshine
	QString str;
	str.setNum(currentConsole.sunshineLeft);
	sunshineDisplay->setText(str);

	//display  card
	for (int i = 0; i < currentConsole.cards.size(); i++)
	{
		Card* chosen = currentConsole.cards[i];
		str = CARD_PATH[chosen->getType()];
		if (currentConsole.duration - chosen->getLastUsed() >= chosen->getCd()
			&& currentConsole.sunshineLeft >= chosen->getCost())
			str += "1.jpg";
		else str += "2.jpg";
		cardsShown[i]->setPixmap(str);
	}

	//display   plants
	for (int i = 0; i < currentConsole.plants.size(); i++)
	{
		Plant* chosen = currentConsole.plants[i];
		QMovie* newMovie = new QMovie;
		QMovie* oldMovie = plantsShown[i]->movie();
		switch (chosen->type)
		{
		case peashooter:case sunflower:case repeater:case snowpea:case torchwood:
			newMovie->setFileName(plantsShown[i]->path + "1.gif");
			break;
		case wallnut:
			if (chosen->hp < 1333)newMovie->setFileName(plantsShown[i]->path + "3.gif");
			else if (chosen->hp < 2667)newMovie->setFileName(plantsShown[i]->path + "2.gif");
			else newMovie->setFileName(plantsShown[i]->path + "1.gif");
			break;
		case potatomine:
			if (currentConsole.duration - chosen->putTime >= chosen->prepare)
				newMovie->setFileName(plantsShown[i]->path + "2.gif");
			else newMovie->setFileName(plantsShown[i]->path + "1.gif");
			if (chosen->lastAttack > 0)
				newMovie->setFileName(plantsShown[i]->path + "3.gif");
			break;
		case chomper:
			if (currentConsole.duration - chosen->lastAttack <= 2000)
				newMovie->setFileName(plantsShown[i]->path + "2.gif");
			else if (currentConsole.duration - chosen->lastAttack < chosen->recharge)
				newMovie->setFileName(plantsShown[i]->path + "3.gif");
			else newMovie->setFileName(plantsShown[i]->path + "1.gif");
			break;
		case cherrybomb:
			if (chosen->lastAttack > 0)
				newMovie->setFileName(plantsShown[i]->path + "2.gif");
			else
				newMovie->setFileName(plantsShown[i]->path + "1.gif");
			break;
		}
		if (oldMovie->fileName() != newMovie->fileName())
		{
			delete plantsShown[i]->movie();
			plantsShown[i]->setMovie(newMovie);
			newMovie->start();
		}
		else delete newMovie;
	}

	//display   zombies
	for (int i = 0; i < currentConsole.zombies.size(); i++)
	{
		Zombie* chosen = currentConsole.zombies[i];
		QMovie* newMovie = new QMovie;
		QMovie* oldMovie = zombiesShown[i]->movie();
		if (chosen->type == bucket || chosen->type == pole)
		{
			if (chosen->hp <= 270)
			{
				chosen->type = normal;
				zombiesShown[i]->path = ZOMBIE_FOLDER[normal];
			}
		}

		if (chosen->status == 1)//掉脑袋
		{
			if (chosen->ifAttacking)
				newMovie->setFileName(zombiesShown[i]->path + "4.gif");
			else
				newMovie->setFileName(zombiesShown[i]->path + "3.gif");
		}
		else if (chosen->status == 0)//一切正常
		{
			if (chosen->ifAttacking)
				newMovie->setFileName(zombiesShown[i]->path + "2.gif");
			else
			{
				if(chosen->type == pole && chosen->step == 0)
					newMovie->setFileName(zombiesShown[i]->path + "8.gif");
				else
					newMovie->setFileName(zombiesShown[i]->path + "1.gif");
			}
		}
		else if (chosen->status == 2)
		{
			if (chosen->ifBurned)
				newMovie->setFileName(zombiesShown[i]->path + "10.gif");
			else
				newMovie->setFileName(zombiesShown[i]->path + "5.gif");
		}

		if (chosen->type == pole && chosen->step != 0)
		{
			if (chosen->step == 1)
				newMovie->setFileName(zombiesShown[i]->path + "6.gif");
			else if (chosen->step == 2)
			{
				newMovie->setFileName(zombiesShown[i]->path + "7.gif");
				if(currentConsole.duration == chosen->lastStepTime)
					zombiesShown[i]->rect.moveLeft(zombiesShown[i]->rect.x() - 50);
			}
			else 
			{
				if (currentConsole.duration == chosen->lastStepTime)
					zombiesShown[i]->rect.moveLeft(zombiesShown[i]->rect.x() - 20);
			}
		}
		if (oldMovie->fileName() != newMovie->fileName())
		{
			delete zombiesShown[i]->movie();
			zombiesShown[i]->setMovie(newMovie);
			newMovie->start();
		}
		else delete newMovie;

		if(chosen->status != 2)
			zombiesShown[i]->setGeometry(zombiesShown[i]->rect);
		else
		{
			QRect rect = zombiesShown[i]->rect;
			zombiesShown[i]->setGeometry(rect.x() - 60, rect.y(), rect.width() + 60, rect.height());
		}
	}

	//display bullets
	for (int i = 0; i < currentConsole.bullets.size(); i++)
	{
		if (bulletsShown[i]->movie()->fileName() != BULLET_FOLDER[currentConsole.bullets[i]->type])
		{
			delete bulletsShown[i]->movie();
			QMovie* movie = new QMovie(BULLET_FOLDER[currentConsole.bullets[i]->type]);
			movie->start();
			bulletsShown[i]->setMovie(movie);
		}
		bulletsShown[i]->setGeometry(bulletsShown[i]->rect);
	}
}
