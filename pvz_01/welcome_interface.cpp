#include "welcome_interface.h"
#include "qpalette.h"
#include "qpainter.h"

WelcomeInterface::WelcomeInterface(QWidget* parent)
{
	this->setFixedWidth(1200);
	this->setFixedHeight(800);
	drawBackground();
}

void WelcomeInterface::drawBackground()
{
	backgroundImage = QPixmap("../pvz-material/images/interface/surface.jpg");
	this->setAutoFillBackground(true);
	QPalette* palette = new QPalette;
	backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
	palette->setBrush(QPalette::Background, QBrush(backgroundImage));
	this->setPalette(*palette);
	delete(palette);
}