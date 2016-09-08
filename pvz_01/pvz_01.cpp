#include "pvz_01.h"
#include <qurl>
#include <qmediaplayer>
#include <qmessagebox>

MainWindow::MainWindow(QWidget* parent)
{
	status = Begin;
	historyWidget = nullptr;
	currentWidget = new WelcomeInterface(this);
	currentWidget->show();
	connectWithWelcomeInterface();
	playMusic();

	WelcomeInterface* f = static_cast<WelcomeInterface*>(currentWidget);
	f->setMusicAudioPlayers(this->musicPlayer, this->audioPlayer);
}
void MainWindow::close()
{
	emit endApp();
}

void MainWindow::resetEverything()
{
	musicPlayer->stop();
	musicPlayer->setMedia(QUrl(CHOOSING_MUSIC_PATH));

	console.reset();

	QWidget* temp = currentWidget;
	if (historyWidget)
	{
		delete historyWidget;
		historyWidget = nullptr;
	}
	currentWidget = new PlayingInterface(this, &console);
	currentWidget->show();
	delete temp;

	connectWithPlayingInterface();
	connectConsoleWithPlayingInterface();

	PlayingInterface* f = static_cast<PlayingInterface*>(currentWidget);
	f->setMusicAudioPlayers(this->musicPlayer, this->audioPlayer);
}

void MainWindow::startPlaying()
{
	status = Playing;

	if (historyWidget != nullptr && console.getLastGameStatus() == 0)
	{
		QMessageBox box(QMessageBox::Question, QStringLiteral("提示"), QStringLiteral("是否想要继续此回合？\n"), QMessageBox::Ok | QMessageBox::No);
		if (box.exec() == QMessageBox::Ok)
		{
			gameContinue();
			return;
		}
	}
	delete historyWidget;
	historyWidget = nullptr;
	resetEverything();
}
void MainWindow::gameStart()
{
	console.gameStart();
}

void MainWindow::gameReturn()
{
	status = Begin;
	historyWidget = currentWidget;
	historyWidget->hide();
	loadWelcomeInterface();
}

void MainWindow::gameContinue()
{
	if (historyWidget == nullptr)return;
	delete currentWidget;
	currentWidget = historyWidget;
	currentWidget->show();
	console.gameStart();
	historyWidget = nullptr;
}

void MainWindow::loadWelcomeInterface()
{
	currentWidget = new WelcomeInterface(this);
	currentWidget->show();
	connectWithWelcomeInterface();

	WelcomeInterface* f = static_cast<WelcomeInterface*>(currentWidget);
	f->setMusicAudioPlayers(this->musicPlayer, this->audioPlayer);

	if (musicPlayer->media().canonicalUrl() != QUrl(WELCOME_MUSIC_PATH))
		musicPlayer->setMedia(QUrl(WELCOME_MUSIC_PATH));
}
void MainWindow::loadHelpInterface()
{
	delete currentWidget;
	currentWidget = new GeneralInterface(this, HELP_PATH);
	currentWidget->show();
	connectWithHelpInterface();
}

void MainWindow::loadThanksInterface()
{
	delete currentWidget;
	currentWidget = new GeneralInterface(this, THANKS_PATH);
	currentWidget->show();
}
void MainWindow::playMusic()
{
	audioPlayer = new QMediaPlayer(this);
	audioPlayer->setVolume(100);

	musicPlayer = new QMediaPlayer(this);
	musicPlayer->setAudioRole(QAudio::MusicRole);
	musicPlayer->setMedia(QUrl(WELCOME_MUSIC_PATH));
	musicPlayer->setVolume(100);

	QObject::connect(musicPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), musicPlayer, SLOT(play()));
	musicPlayer->play();
}
void MainWindow::connectWithWelcomeInterface()
{
	WelcomeInterface* f = static_cast<WelcomeInterface*>(currentWidget);
	QObject::connect(f->getButton(), SIGNAL(clicked()), this, SLOT(startPlaying()));
	QObject::connect(currentWidget, SIGNAL(switchToEnd()), this, SLOT(close()));
	QObject::connect(currentWidget, SIGNAL(switchToHelp()), this, SLOT(loadHelpInterface()));
	QObject::connect(currentWidget, SIGNAL(switchToThanks()), this, SLOT(loadThanksInterface()));
	QObject::connect(currentWidget, SIGNAL(switchToOption()), currentWidget, SLOT(startOption()));
}
void MainWindow::connectWithPlayingInterface()
{
	QObject::connect(currentWidget, SIGNAL(gameReturn()), this, SLOT(gameReturn()));
	QObject::connect(currentWidget, SIGNAL(resetEverything()), this, SLOT(resetEverything()));
}
void MainWindow::connectWithHelpInterface()
{
	QObject::connect(currentWidget, SIGNAL(switchToMain()), this, SLOT(loadWelcomeInterface()));
}
void MainWindow::connectWithThanksInterface()
{
	QObject::connect(currentWidget, SIGNAL(switchToMain()), this, SLOT(loadWelcomeInterface()));
}
void MainWindow::connectConsoleWithPlayingInterface()
{
	QObject::connect(&console, SIGNAL(gameOver(bool)), currentWidget, SLOT(gameOver(bool)));
	QObject::connect(&console, SIGNAL(timeToShow()), currentWidget, SLOT(refresh()));

	QObject::connect(currentWidget, SIGNAL(shovelClicked()), &console, SLOT(dealShovelClicked()));
	QObject::connect(currentWidget, SIGNAL(shovelCanceled()), &console, SLOT(dealShovelCanceled()));
	QObject::connect(currentWidget, SIGNAL(donePlantClicked(MyLabel*)), &console, SLOT(dealPlantClicked(MyLabel*)));
	QObject::connect(currentWidget, SIGNAL(doneCardClicked(int)), &console, SLOT(dealCardClicked(int)));
	QObject::connect(currentWidget, SIGNAL(doneSunshineClicked(MyLabel*)), &console, SLOT(dealSunshineClicked(MyLabel*)));

	QObject::connect(&console, SIGNAL(deleteZombie(int)), currentWidget, SLOT(deleteZombie(int)));
	QObject::connect(&console, SIGNAL(deletePlant(int)), currentWidget, SLOT(deletePlant(int)));
	QObject::connect(&console, SIGNAL(deleteSunshine(MyLabel*)), currentWidget, SLOT(deleteSunshine(MyLabel*)));
	QObject::connect(&console, SIGNAL(deleteBullet(int)), currentWidget, SLOT(deleteBullet(int)));

	QObject::connect(&console, SIGNAL(addZombie(ZOMBIE_TYPE, int, int)), currentWidget, SLOT(addZombie(ZOMBIE_TYPE, int, int)));
	QObject::connect(&console, SIGNAL(addPlant(PLANT_TYPE, int, int)), currentWidget, SLOT(addPlant(PLANT_TYPE, int, int)));
	QObject::connect(&console, SIGNAL(addSunshine(int, int, bool)), currentWidget, SLOT(addSunshine(int, int, bool)));
	QObject::connect(&console, SIGNAL(addBullet(BULLET_TYPE, int, int, bool)), currentWidget, SLOT(addBullet(BULLET_TYPE, int, int, bool)));

	QObject::connect(&console, SIGNAL(zombieMove(int, int, int)), currentWidget, SLOT(zombieMove(int, int, int)));
	QObject::connect(&console, SIGNAL(bulletMove(int)), currentWidget, SLOT(bulletMove(int)));

	QObject::connect(&console, SIGNAL(playAudio(QString)), currentWidget, SLOT(playAudio(QString)));
}