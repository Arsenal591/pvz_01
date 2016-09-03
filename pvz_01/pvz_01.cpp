#include "pvz_01.h"
#include <qurl>
#include <qmediaplayer>
#include <qmessagebox>

MainWindow::MainWindow(QWidget* parent)
{
	status = Begin;
	currentWidget = new WelcomeInterface(this);
	currentWidget->show();
	historyWidget = nullptr;
	connect();
	playMusic();
}

void MainWindow::playMusic()
{
	player = new QMediaPlayer(this);
	player->setAudioRole(QAudio::MusicRole);
	player->setMedia(QUrl("../pvz-material/audio/awooga.mp3"));
	player->setVolume(100);
	QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), player, SLOT(play()));
	player->play();
}
void MainWindow::connect()
{
	QObject::connect(currentWidget, SIGNAL(switchToEnd()), this, SLOT(close()));
	QObject::connect(currentWidget, SIGNAL(switchToPlay()), this, SLOT(startPlaying()));
}

void MainWindow::close()
{
	currentWidget->close();
}

void MainWindow::startPlaying()
{
	status = Playing;

	if (historyWidget != nullptr)
	{
		QMessageBox box(QMessageBox::Question, QStringLiteral("提示"), QStringLiteral("是否想要继续从前的回合？\n"), QMessageBox::Ok| QMessageBox::No);
		if (box.exec() == QMessageBox::Ok)
		{
			gameContinue();
			return;
		}
		else
		{
			//reset the console and the interface
		}
	}
	delete currentWidget;
	currentWidget = new PlayingInterface(this, &console);
	currentWidget->show();
	QObject::connect(&console, SIGNAL(gameOver(bool)), currentWidget, SLOT(gameOver(bool)));
	QObject::connect(currentWidget, SIGNAL(gameReturn()), this, SLOT(gameReturn()));
	QObject::connect(&console, SIGNAL(timeToShow()), currentWidget, SLOT(refresh()));

	QObject::connect(currentWidget, SIGNAL(doneCardClicked(int)), &console, SLOT(dealCardClicked(int)));
	QObject::connect(currentWidget, SIGNAL(doneSunshineClicked(MyLabel*)), &console, SLOT(dealSunshineClicked(MyLabel*)));

	QObject::connect(&console, SIGNAL(deleteZombie(int)), currentWidget, SLOT(deleteZombie(int)));
	QObject::connect(&console, SIGNAL(deletePlant(int)), currentWidget, SLOT(deletePlant(int)));
	QObject::connect(&console, SIGNAL(deleteSunshine(MyLabel*)), currentWidget, SLOT(deleteSunshine(MyLabel*)));
	QObject::connect(&console, SIGNAL(deleteBullet(int)), currentWidget, SLOT(deleteBullet(int)));

	QObject::connect(&console, SIGNAL(addZombie(ZOMBIE_TYPE, int, int)), currentWidget, SLOT(addZombie(ZOMBIE_TYPE, int, int)));
	QObject::connect(&console, SIGNAL(addPlant(PLANT_TYPE, int, int)), currentWidget, SLOT(addPlant(PLANT_TYPE, int, int)));
	QObject::connect(&console, SIGNAL(addSunshine(int, int, bool)), currentWidget, SLOT(addSunshine(int, int, bool)));
	QObject::connect(&console, SIGNAL(addBullet(BULLET_TYPE, int, int)), currentWidget,SLOT(addBullet(BULLET_TYPE, int, int)));

	QObject::connect(&console, SIGNAL(zombieMove(int, int, int)), currentWidget, SLOT(zombieMove(int, int, int)));
	QObject::connect(&console, SIGNAL(bulletMove(int)), currentWidget, SLOT(bulletMove(int)));
}

void MainWindow::gameStart()
{
	console.gameStart();
}

void MainWindow::gameReturn()
{
	status = Begin;
	currentWidget->hide();
	historyWidget = currentWidget;
	currentWidget = new WelcomeInterface(this);
	currentWidget->show();
	connect();
}

void MainWindow::gameContinue()
{
	if (historyWidget == nullptr)return;
	delete currentWidget;
	currentWidget = historyWidget;
	currentWidget->show();
	console.gameStart();
}