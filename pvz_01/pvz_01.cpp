#include "pvz_01.h"
#include <qdialog>
#include <qurl>
#include <qmediaplayer>
#include <qmediaplaylist>
#include <qsound>

MainWindow::MainWindow(QWidget* parent)
{
	status = Begin;
	currentWidget = new WelcomeInterface(this);
	currentWidget->show();
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
	delete currentWidget;
	currentWidget = new PlayingInterface(this, &console);
	currentWidget->show();
	status = Playing;
	QObject::connect(&console, SIGNAL(timeToShow()), currentWidget, SLOT(refresh()));

	PlayingInterface* f = static_cast<PlayingInterface*>(currentWidget);
	for (int i = 0; i < f->getCardSum(); i++)
	{
		QObject::connect(f->getCardShown(i), SIGNAL(cardClicked(int)), f, SLOT(dealCardClicked(int)));
	}

	QObject::connect(currentWidget, SIGNAL(doneCardClicked(int)), &console, SLOT(dealCardClicked(int)));
	QObject::connect(currentWidget, SIGNAL(doneSunshineClicked()), &console, SLOT(dealSunshineClicked()));
}

void MainWindow::gameStart()
{
	console.gameStart();
}
