#include <qpropertyanimation>
#include <qmessagebox>
#include <qpalette>
#include <qevent>
#include <qmovie>
#include "playing_interface.h"
#include "pvz_01.h"
#include <qdebug>

PlayingInterface::PlayingInterface(QWidget* parent, GameConsole* t)
{
	this->info = t;

	this->setParent(parent);
	this->setFixedSize(QSize(1200, 800));

	menu = nullptr;

	//记录卡片和草坪格子在界面的位置
	setCardRect();
	setCellRect();

	//加载背景图
	backgroundImage = QPixmap(BACKGROUND_PATH).scaled(QSize(1867, 800));
	backgroundLabel = new QLabel(this);
	backgroundLabel->setFixedSize(QSize(1867, 800));
	backgroundLabel->setPixmap(backgroundImage);
	backgroundLabel->show();

	//加载卡片盒子
	cardBoxImage = QPixmap(CARDBOX_PATH);
	cardBoxLabel = new QLabel(this);
	cardBoxLabel->setFixedSize(QSize(435, 84));
	cardBoxLabel->setPixmap(cardBoxImage);
	cardBoxLabel->hide();

	//加载选项按钮并绑定信号与槽
	option = new MyButton(this, OPTION_BUTTON_PATH);
	option->setSize(QRect(1000, -3, 113, 41));
	option->setOffset(2, 2);
	option->show();
	connect(option, SIGNAL(clicked()), this, SLOT(startOption()));

	//显示阳光值
	sunshineDisplay = new QLabel(cardBoxLabel);
	sunshineDisplay->setGeometry(QRect(20, 60, 30, 15));
	sunshineDisplay->setAlignment(Qt::AlignCenter);
	sunshineDisplay->setFont(QFont("consolas", 9));
	sunshineDisplay->show();

	//显示卡片选择盒
	selectCard = new SelectCard(this);
	selectCard->show();
	connect(selectCard, SIGNAL(selected(QVector<int>)), this, SLOT(setCards(QVector<int>)));
	connect(selectCard, SIGNAL(selected(QVector<int>)), selectCard, SLOT(hide()));
	connect(selectCard, SIGNAL(selected(QVector<int>)), info, SLOT(setCards(QVector<int>)));
}
PlayingInterface::~PlayingInterface()
{
	delete backgroundLabel;
	delete cardBoxLabel;
	delete option;
	delete selectCard;

	//不要在此处detete menu
	for (int i = 0; i < sunshineShown.size(); i++)
		delete sunshineShown[i];
	for (int i = 0; i < plantsShown.size(); i++)
		delete plantsShown[i];
	for (int i = 0; i < bulletsShown.size(); i++)
		delete bulletsShown[i];
	for (int i = 0; i < zombiesShown.size(); i++)
		delete zombiesShown[i];
}

void PlayingInterface::playAudio(QString str)
{
	QMediaPlayer* player = new QMediaPlayer(this);
	player->setMedia(QUrl(str));
	player->setVolume(audioPlayer->volume());
	player->play();
}

void PlayingInterface::refresh()
{
	update();
}
void PlayingInterface::gameOver(bool ifHumanWin)
{
	QString message;
	if (ifHumanWin == true)
		message = QStringLiteral("恭喜你通过本关！");
	else message = QStringLiteral("僵尸吃掉了你的脑子");
	QMessageBox box(QMessageBox::Information, QStringLiteral("提示"), message, QMessageBox::Yes);
	if (box.exec() == QMessageBox::Yes)
		emit gameReturn();
}
void PlayingInterface::restartGame()
{
	emit playAudio(BUTTONCLICK_AUDIO_PATH);
	info->stopTimer();
	emit resetEverything();
}
void PlayingInterface::backToWelcome()
{
	emit playAudio(BUTTONCLICK_AUDIO_PATH);
	delete menu;
	info->stopTimer();
	emit gameReturn();
}

void PlayingInterface::startOption()
{
	playAudio(BUTTONCLICK_AUDIO_PATH);

	menu = new OptionMenuAdvanced(this);
	menu->show();
	menu->setInitial(musicPlayer->volume(), audioPlayer->volume());
	QObject::connect(menu, SIGNAL(setVolume(int, int)), this, SLOT(finishOption(int, int)));
	QObject::connect(menu, SIGNAL(gameRestart()), this, SLOT(restartGame()));
	QObject::connect(menu, SIGNAL(gameReturn()), this, SLOT(backToWelcome()));

	option->setEnabled(false);
	selectCard->setEnabled(false);
	info->stopTimer();
}
void PlayingInterface::finishOption(int m, int a)
{
	playAudio(BUTTONCLICK_AUDIO_PATH);

	musicPlayer->setVolume(m);
	audioPlayer->setVolume(a);
	delete menu;

	option->setEnabled(true);
	selectCard->setEnabled(true);

	if (info->duration > 0)
		info->startTimer();
}

void PlayingInterface::setCards(QVector<int> res)
{
	playAudio(BUTTONCLICK_AUDIO_PATH);
	for (int i = 0; i < res.size(); i++)
	{
		cardsShown.push_back(new MyLabel(cardBoxLabel, card, res[i]));
		cardsShown[i]->setGeometry(cardRect[i]);
		cardsShown[i]->show();
		connect(cardsShown[i], SIGNAL(cardClicked(int)), this, SLOT(dealCardClicked(int)));
	}
	leadInAnimation();
}

void PlayingInterface::dealCardClicked(int n)
{
	emit playAudio(CARD_PICKED_AUDIO_PATH);
	int x;
	for (int i = 0; i < cardsShown.size(); i++)
		if (cardsShown[i]->cardNum == n)x = i;
	if (info->cardChosen && info->cardChosen->getType() == cardsShown[x]->cardNum)
		this->unsetCursor();
	else
		this->setCursor(QPixmap(PLANT_FOLDER[n] + "0.png"));
	emit doneCardClicked(n);
}
void PlayingInterface::dealSunshineClicked(MyLabel* label)
{
	emit doneSunshineClicked(label);
}
void PlayingInterface::dealPlantClicked(MyLabel* label)
{
	this->unsetCursor();
	emit donePlantClicked(label);
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
void PlayingInterface::deleteSunshine(MyLabel* label)
{
	for (int i = 0; i < sunshineShown.size(); i++)
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

void PlayingInterface::addZombie(enum ZOMBIE_TYPE tp, int x, int y)
{
	MyLabel* newLabel = new MyLabel(this, zombie);
	newLabel->cellx = x, newLabel->celly = y;
	newLabel->rect = cellRect[x][y];

	QString str = ZOMBIE_FOLDER[tp];
	switch (tp)
	{
	case pole:
		newLabel->rect.setWidth(newLabel->width() + 70);
		newLabel->rect.moveLeft(newLabel->rect.x() - 30);
		break;
	default:
		break;
	}
	newLabel->setGeometry(newLabel->rect);
	newLabel->setPath(str);

	QMovie* newMovie = new QMovie(str + "1.gif");
	newMovie->setParent(newLabel);
	newLabel->setMovie(newMovie);
	newMovie->start();

	zombiesShown.push_back(newLabel);
	newLabel->show();
}
void PlayingInterface::addPlant(PLANT_TYPE tp, int x, int y)
{
	MyLabel* newLabel = new MyLabel(this, plant);
	newLabel->cellx = x, newLabel->celly = y;
	newLabel->setGeometry(cellRect[x][y]);
	newLabel->setPath(PLANT_FOLDER[tp]);
	connect(newLabel, SIGNAL(plantClicked(MyLabel*)), this, SLOT(dealPlantClicked(MyLabel*)));

	QMovie* movie = new QMovie(newLabel->getPath() + "1.gif");
	movie->setParent(newLabel);
	newLabel->setMovie(movie);
	movie->start();

	newLabel->show();
	plantsShown.push_back(newLabel);
}
void PlayingInterface::addSunshine(int x, int y, bool ifDrop)
{
	MyLabel* newLabel = new MyLabel(this, sunshine);
	newLabel->cellx = x, newLabel->celly = y;
	QRect rect = cellRect[x][y];
	newLabel->setGeometry(QRect(rect.x() + 0.5*rect.width(), rect.y() + 0.5*rect.height(), 60, 60));
	newLabel->setPath(SUNSHINE_PATH);
	connect(newLabel, SIGNAL(sunshineClicked(MyLabel*)), this, SLOT(dealSunshineClicked(MyLabel*)));

	QMovie* movie = new QMovie(newLabel->getPath());
	movie->setParent(newLabel);
	movie->setScaledSize(QSize(60, 60));
	newLabel->setMovie(movie);
	movie->start();

	newLabel->show();
	sunshineShown.push_back(newLabel);

	if (ifDrop)//执行太阳由空中掉下的动画
	{
		QPropertyAnimation* animation = new QPropertyAnimation(newLabel, "geometry");
		animation->setParent(newLabel);
		QRect startPos(rect.x() + 0.5 * rect.width(), 0, 60, 60);
		if (y < 4) startPos.moveTop(84);
		animation->setStartValue(startPos);
		animation->setEndValue(QRect(rect.x() + 0.5*rect.width(), rect.y() + 0.5*rect.height(), 60, 60));
		int dt = (rect.y() + 0.5*rect.height()) * 10;
		animation->setDuration(dt);
		animation->start();
	}
}
void PlayingInterface::addBullet(enum BULLET_TYPE tp, int x, int y, bool ifSecond)
{
	MyLabel* newLabel = new MyLabel(this, bullet);
	if (ifSecond)
		newLabel->rect = QRect(cellRect[x][y].x() + 85, cellRect[x][y].y() + 30, 60, 25);
	else
		newLabel->rect = QRect(cellRect[x][y].x() + 60, cellRect[x][y].y() + 30, 60, 25);
	newLabel->setGeometry(newLabel->rect);
	newLabel->setPath(BULLET_FOLDER[tp]);

	QMovie* newMovie = new QMovie(newLabel->getPath());
	newMovie->setParent(newLabel);
	newLabel->setMovie(newMovie);
	newMovie->start();

	bulletsShown.push_back(newLabel);
	newLabel->show();
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

void PlayingInterface::mousePressEvent(QMouseEvent* ev)
{
	emit shovelCanceled();
	this->unsetCursor();
	if (ev->x() >= 135 && ev->x() <= 1105 && ev->y() >= 110 && ev->y() <= 760)
	{
		this->info->dealPutPlant(ev->x(), ev->y());
		return;
	}
	QWidget::mousePressEvent(ev);
}
void PlayingInterface::keyPressEvent(QKeyEvent* ev)
{
	if (ev->key() == Qt::Key_S)
	{
		emit shovelClicked();
		playAudio(SHOVEL_AUDIO_PATH);
		if (this->cursor().shape() == Qt::ArrowCursor)
			this->setCursor(QPixmap(SHOVEL_PATH));
		else this->setCursor(Qt::ArrowCursor);
	}
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
	musicPlayer->setMedia(QUrl(PLAYING_MUSIC_PATH));

	QPropertyAnimation* animation = new QPropertyAnimation(backgroundLabel, "geometry");
	animation->setParent(this);
	animation->setDuration(10000);
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
	animation->setParent(this);
	animation->setDuration(2000);
	animation->setStartValue(QRect(165, -84, 165, 84));
	animation->setEndValue(QRect(165, 0, 165, 84));
	QObject::connect(animation, SIGNAL(finished()), info, SLOT(gameStart()));
	animation->start();
}

void PlayingInterface::paintEvent(QPaintEvent*)
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
		QString newFileName;
		switch (chosen->type)
		{
		case peashooter:case sunflower:case repeater:case snowpea:case torchwood:
			newFileName = (plantsShown[i]->path + "1.gif");
			break;
		case wallnut:
			if (chosen->hp < 1333)newFileName = (plantsShown[i]->path + "3.gif");
			else if (chosen->hp < 2667)newFileName = (plantsShown[i]->path + "2.gif");
			else newFileName = (plantsShown[i]->path + "1.gif");
			break;
		case potatomine:
			if (currentConsole.duration - chosen->putTime >= chosen->prepare)
				newFileName = (plantsShown[i]->path + "2.gif");
			else newFileName = (plantsShown[i]->path + "1.gif");
			if (chosen->lastAttack > 0)
				newFileName = (plantsShown[i]->path + "3.gif");
			break;
		case chomper:
			if (currentConsole.duration - chosen->lastAttack <= 2000)
				newFileName = (plantsShown[i]->path + "2.gif");
			else if (currentConsole.duration - chosen->lastAttack < chosen->recharge)
				newFileName = (plantsShown[i]->path + "3.gif");
			else newFileName = (plantsShown[i]->path + "1.gif");
			break;
		case cherrybomb:
			if (chosen->lastAttack > 0)
				newFileName = (plantsShown[i]->path + "2.gif");
			else
				newFileName = (plantsShown[i]->path + "1.gif");
			break;
		}
		if (plantsShown[i]->movie()->fileName() != newFileName)
		{
			delete plantsShown[i]->movie();
			QMovie* newMovie = new QMovie(newFileName);
			newMovie->setParent(plantsShown[i]);
			plantsShown[i]->setMovie(newMovie);
			newMovie->start();
		}
	}
	//display   zombies
	for (int i = 0; i < currentConsole.zombies.size(); i++)
	{
		Zombie* chosen = currentConsole.zombies[i];
		QString newFileName;
		if (chosen->type == bucket)
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
				newFileName = (zombiesShown[i]->path + "4.gif");
			else
				newFileName = (zombiesShown[i]->path + "3.gif");
		}
		else if (chosen->status == 0)//一切正常
		{
			if (chosen->ifAttacking)
				newFileName = (zombiesShown[i]->path + "2.gif");
			else
			{
				if (chosen->type == pole && chosen->step == 0)
					newFileName = (zombiesShown[i]->path + "8.gif");
				else
					newFileName = (zombiesShown[i]->path + "1.gif");
			}
		}
		else if (chosen->status == 2)
		{
			if (chosen->ifBurned)
				newFileName = (zombiesShown[i]->path + "10.gif");
			else
				newFileName = (zombiesShown[i]->path + "5.gif");
		}

		if (chosen->type == pole && chosen->step != 0)
		{
			if (chosen->ifBurned)
				newFileName = (zombiesShown[i]->path + "10.gif");
			else
			{
				if (chosen->step == 1)
					newFileName = (zombiesShown[i]->path + "6.gif");
				else if (chosen->step == 2)
				{
					newFileName = (zombiesShown[i]->path + "7.gif");
					if (currentConsole.duration == chosen->lastStepTime)
					{
						zombiesShown[i]->rect.moveLeft(zombiesShown[i]->rect.x() - 5);
						if (chosen->ifFrozen)
							zombiesShown[i]->rect.moveLeft(zombiesShown[i]->rect.x() - 5);
					}
				}
				else
				{
					if (currentConsole.duration == chosen->lastStepTime)
						zombiesShown[i]->rect.moveLeft(zombiesShown[i]->rect.x() - 5);
				}
			}
		}
		if (zombiesShown[i]->movie()->fileName() != newFileName)
		{
			delete zombiesShown[i]->movie();
			QMovie* newMovie = new QMovie(newFileName);
			newMovie->setParent(zombiesShown[i]);
			zombiesShown[i]->setMovie(newMovie);
			newMovie->start();
		}

		if (chosen->status != 2)
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
			movie->setParent(bulletsShown[i]);
			movie->start();
			bulletsShown[i]->setMovie(movie);
		}
		bulletsShown[i]->setGeometry(bulletsShown[i]->rect);
	}
}
