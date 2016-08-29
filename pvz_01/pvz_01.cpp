#include "pvz_01.h"
#include <qdialog>
#include <qurl>
#include <qmediaplayer>
#include <qmediaplaylist>
#include <qsound>

MainWindow::MainWindow(QWidget* parent)
{
	currentWidget = new WelcomeInterface;
	currentWidget->show();
	connect();
	playMusic();
}

void MainWindow::playMusic()
{
	player = new QMediaPlayer;
	player->setAudioRole(QAudio::MusicRole);
	player->setMedia(QUrl("../pvz-material/audio/awooga.mp3"));
	player->setVolume(100);
	player->play();
}
void MainWindow::connect()
{
	QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(playMusic()));
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
	currentWidget = new PlayingInterface;
	currentWidget->show();
}