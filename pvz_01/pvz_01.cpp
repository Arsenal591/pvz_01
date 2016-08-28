#include "pvz_01.h"
#include <qdialog>
#include <qsound.h>
#include <qurl.h>
#include <qmediaplayer>

MainWindow::MainWindow(QWidget* parent)
{
	currentWidget = new WelcomeInterface;
	currentWidget->show();
	//currentWidget->setParent(this);
	QMediaPlayer* player = new QMediaPlayer(this);
	player->setMedia(QUrl::fromLocalFile("../pvz-material/audio/2.75.mp3"));
	player->setVolume(100);
	player->play();

	connect();
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
	currentWidget = new PlayingInterface;
	currentWidget->show();
}