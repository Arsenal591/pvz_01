#include "pvz_01.h"
#include <qdialog>
#include <qsound.h>
#include <qurl.h>
#include <qmediaplayer>

MainWindow::MainWindow(QWidget* parent)
{
	_currentWidget = new WelcomeInterface;
	_currentWidget->show();
	//QSound music("../pvz-material/audio/2.75.mp3");
	//music.play();
	QMediaPlayer* player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile("../pvz-material/audio/2.75.mp3"));
	player->setVolume(100);
	player->play();
}