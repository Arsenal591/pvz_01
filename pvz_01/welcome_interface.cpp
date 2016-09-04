#include "welcome_interface.h"
#include "qpalette.h"
#include "qevent.h"

WelcomeInterface::WelcomeInterface(QWidget* parent)
{
	this->setParent(parent);
	this->setFixedWidth(1200);
	this->setFixedHeight(800);
	drawBackground();

	button = new MyButton(this, ADVENTURE_PATH_RELEASED, ADVENTURE_PATH_PRESSED, ADVENTURE_PATH_RELEASED);
	button->setSize(QRect(620, 100, 460, 196));
	button->setOffset(2, 2);
	button->show();

	//connect(button, SIGNAL(clicked()), parent, SLOT(startPlaying()));
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

void WelcomeInterface::mousePressEvent(QMouseEvent* mouseEvent)
{
	int mousex = mouseEvent->x() * 0.75, mousey = mouseEvent->y() * 0.75;//��ΪԭͼƬ
	if (mousex >= 640 && mousex <= 720 && mousey >= 485 && mousey <= 520)
		emit switchToOptions();
	else if (mousex >= 720 && mousex <= 790 && mousey >= 500 && mousey <= 550)
		emit switchToHelp();
		//emit switchToPlay();
	else if (mousex >= 800 && mousex <= 875 && mousey >= 490 && mousey <= 545)
		emit switchToEnd();
	else return QWidget::mousePressEvent(mouseEvent);
}