#include "general_interface.h"

GeneralInterface::GeneralInterface(QWidget* parent, QString backgroundPath)
{
	this->setParent(parent);
	this->setFixedSize(QSize(1200, 800));

	QPixmap* backgroundImage = new QPixmap(backgroundPath);
	this->setAutoFillBackground(true);
	QPalette* palette = new QPalette;
	*backgroundImage = backgroundImage->scaled(this->size(), Qt::IgnoreAspectRatio);
	palette->setBrush(QPalette::Background, QBrush(*backgroundImage));
	this->setPalette(*palette);
	delete(palette);

	goback = new MyButton(this, RETURN_BUTTON_PATH);
	goback->setSize(QRect(1050,745,113,41));
	goback->setOffset(2, 2);

	connect(goback, SIGNAL(clicked()), this, SIGNAL(switchToMain()));
}