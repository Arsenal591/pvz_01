#include "playing_interface.h"
#include "qpropertyanimation.h"
#include "qlabel.h"
//#include "qpalette.h"

const QString PlayingInterface::path = "../pvz-material/images/interface/background1.jpg";
PlayingInterface::PlayingInterface()
{
	this->setFixedWidth(1200);
	this->setFixedHeight(800);
	leadInAnimation();
}

void PlayingInterface::leadInAnimation()
{
	backgroundImage = QPixmap(path);
	backgroundImage = backgroundImage.scaled(QSize(1867,800));
	QLabel* label = new QLabel(this);
	label->setFixedSize(QSize(1867, 800));
	label->setPixmap(backgroundImage);
	label->show();
	QPropertyAnimation* animation = new QPropertyAnimation(label, "geometry");
	animation->setDuration(12000);
	animation->setStartValue(QRect(0, 0, 1200, 800));
	animation->setKeyValueAt(0.45, QRect(-667, 0, 1200, 800));
	animation->setKeyValueAt(0.55, QRect(-667, 0, 1200, 800));
	animation->setEndValue(QRect(-200, 0, 1200, 800));
	animation->start();
}