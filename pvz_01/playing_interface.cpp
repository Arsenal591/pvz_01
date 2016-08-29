#include "playing_interface.h"
#include "qpropertyanimation.h"
#include "qlabel.h"
#include "qmessagebox.h"
#include "qpalette.h"

const QString PlayingInterface::backgroundPath = "../pvz-material/images/interface/background1.jpg";
const QString PlayingInterface::cardBoxPath = "../pvz-material/cardbox.png";
PlayingInterface::PlayingInterface(QWidget* parent)
{
	this->setParent(parent);
	this->setFixedWidth(1200);
	this->setFixedHeight(800);
	leadInAnimation();
}

void PlayingInterface::leadInAnimation()
{
	//debug();
	backgroundImage = QPixmap(backgroundPath);
	backgroundImage = backgroundImage.scaled(QSize(1867,800));
	QLabel* label = new QLabel(this);
	label->setFixedSize(QSize(1867, 800));
	label->setPixmap(backgroundImage);
	label->show();
	QPropertyAnimation* animation = new QPropertyAnimation(label, "geometry");
	animation->setDuration(10000);
	animation->setStartValue(QRect(0, 0, 1200, 800));
	animation->setKeyValueAt(0.50, QRect(-667, 0, 1200, 800));
	animation->setKeyValueAt(0.60, QRect(-667, 0, 1200, 800));
	animation->setEndValue(QRect(-200, 0, 1200, 800));
	animation->start();
	QObject::connect(animation, SIGNAL(finished()), this, SLOT(cardAnimation()));
}

void PlayingInterface::cardAnimation()
{
	cardBoxImage = QPixmap(cardBoxPath);
	QLabel* label = new QLabel(this);
	label->setFixedSize(QSize(435, 84));
	label->setPixmap(cardBoxImage);
	label->show();
	QPropertyAnimation* animation = new QPropertyAnimation(label, "geometry");
	animation->setDuration(1000);
	animation->setStartValue(QRect(165, -84, 165, 84));
	animation->setEndValue(QRect(165, 0, 165, 84));
	animation->start();
}

void PlayingInterface::debug()
{
	QString message = "signal got";
	QMessageBox info(QMessageBox::Information, QString(""), message, QMessageBox::Ok);
	info.show();
	info.exec();
}