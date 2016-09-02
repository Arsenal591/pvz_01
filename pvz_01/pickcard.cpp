#include "pickcard.h"

PickCard::PickCard(QWidget* parent)
{
	this->setParent(parent);
	memset(choice, 0, sizeof(choice));
	this->setFixedSize(465, 554);
	this->setGeometry(0, 100, 465, 554);
	
	this->setAutoFillBackground(true);
	QPalette* newQPalette = new QPalette;
	QPixmap* newImg = new QPixmap(PICKCARD_PATH);
	*newImg = newImg->scaled(this->size());
	newQPalette->setBrush(QPalette::Background, QBrush(*newImg));
	this->setPalette(*newQPalette);

	delete newQPalette;
}