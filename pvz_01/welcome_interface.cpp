#include "welcome_interface.h"
#include "qpalette.h"
#include "qpainter.h"
#include "qevent.h"
#include "qlabel.h"

const QString WelcomeInterface::path = "../pvz-material/images/interface/surface.jpg";
WelcomeInterface::WelcomeInterface(QWidget* parent)
{
	this->setFixedWidth(1200);
	this->setFixedHeight(800);
	drawBackground();
}

void WelcomeInterface::drawBackground()
{
	backgroundImage = QPixmap(path);
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
	else if (mousex >= 800 && mousex <= 875 && mousey >= 490 && mousey <= 545)
		emit switchToEnd();
	else return QWidget::mousePressEvent(mouseEvent);
}