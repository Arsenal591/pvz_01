#include "mybutton.h"

MyButton::MyButton(QWidget*parent, QString str1, QString str2, QString str3)
{
	this->setParent(parent);
	buttonImg = new QPixmap(str1);
	pressImg = new QPixmap(str2);
	releaseImg = new QPixmap(str3);
	this->setIcon(QIcon(*buttonImg));
	this->setFlat(true);
}

MyButton::MyButton(QWidget*parent, QString str)
{
	this->setParent(parent);
	buttonImg = new QPixmap(str);
	pressImg = new QPixmap(str);
	releaseImg = new QPixmap(str);
	this->setIcon(QIcon(*buttonImg));
	this->setFlat(true);
}

void MyButton::setSize(QRect rect)
{
	*buttonImg = buttonImg->scaled(QSize(rect.width(), rect.height()));
	*pressImg = pressImg->scaled(QSize(rect.width(), rect.height()));
	*releaseImg = releaseImg->scaled(QSize(rect.width(), rect.height()));
	this->setIcon(QIcon(*buttonImg));
	this->setIconSize(QSize(rect.width(), rect.height()));
	this->setGeometry(rect);
	this->rect = rect;
}
void MyButton::setOffset(int x, int y)
{
	offsetx = x;
	offsety = y;
}
void MyButton::mousePressEvent(QMouseEvent*)
{
	this->setIcon(QIcon(*pressImg));
	this->setGeometry(QRect(rect.x() + offsetx, rect.y() + offsety, rect.width(), rect.height()));
}
void MyButton::mouseReleaseEvent(QMouseEvent*)
{
	this->setIcon(QIcon(*releaseImg));
	this->setGeometry(rect);
	emit clicked();
}
void MyButton::enterEvent(QEvent*)
{
	this->setCursor(Qt::PointingHandCursor);
	emit entered();
}