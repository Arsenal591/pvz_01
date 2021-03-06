#include "welcome_interface.h"

WelcomeInterface::WelcomeInterface(QWidget* parent)
{
	this->setParent(parent);
	this->setFixedSize(QSize(1200, 800));
	drawBackground();

	menu = nullptr;

	button = new MyButton(this, ADVENTURE_PATH_RELEASED, ADVENTURE_PATH_PRESSED, ADVENTURE_PATH_RELEASED);
	button->setSize(QRect(620, 100, 460, 196));
	button->setOffset(2, 2);
	button->show();
}

WelcomeInterface::~WelcomeInterface()
{
	delete button;
}

void WelcomeInterface::drawBackground()
{
	backgroundImage = QPixmap(WELCOME_PATH);
	this->setAutoFillBackground(true);
	QPalette* palette = new QPalette;
	backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
	palette->setBrush(QPalette::Background, QBrush(backgroundImage));
	this->setPalette(*palette);
	delete(palette);
}

void WelcomeInterface::playAudio(QString str)
{
	QMediaPlayer* player = new QMediaPlayer(this);
	player->setMedia(QUrl(str));
	player->setVolume(audioPlayer->volume());
	player->play();
}

void WelcomeInterface::startOption()
{
	playAudio(BUTTONCLICK_AUDIO_PATH);
	menu = new OptionMenu(this);
	menu->show();

	menu->setInitial(musicPlayer->volume(), audioPlayer->volume());//设置选项卡上的初始值为当前播放器的音量值时
	QObject::connect(menu, SIGNAL(setVolume(int, int)), this, SLOT(finishOption(int, int)));
}
void WelcomeInterface::finishOption(int m, int a)
{
	playAudio(BUTTONCLICK_AUDIO_PATH);
	musicPlayer->setVolume(m);
	audioPlayer->setVolume(a);
	delete menu;
}

void WelcomeInterface::mousePressEvent(QMouseEvent* mouseEvent)
{
	int mousex = mouseEvent->x() * 0.75, mousey = mouseEvent->y() * 0.75;//化为原图片尺寸
	if (mousex >= 640 && mousex <= 720 && mousey >= 485 && mousey <= 520)
		emit switchToOption();
	else if (mousex >= 720 && mousex <= 790 && mousey >= 500 && mousey <= 550)
		emit switchToHelp();
	else if (mousex >= 800 && mousex <= 875 && mousey >= 490 && mousey <= 545)
		emit switchToEnd();
	else if (mousex >= 555 && mousex <= 625 && mousey >= 510 && mousey <= 550)
		emit switchToThanks();
	else return QWidget::mousePressEvent(mouseEvent);
}