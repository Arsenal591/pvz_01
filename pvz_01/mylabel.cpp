#include "mylabel.h"
#include <qevent.h>
#include "pvz_01.h"
#include "qdebug.h"

MyLabel::MyLabel(QWidget* parent, ELEM_TYPE t, int n) :type(t), cardNum(n)
{ 
	this->setParent(parent); 
	MainWindow* f = static_cast<MainWindow*>(this->parentWidget());
	switch (t)
	{
	case card:
		break;
	case sunshine:
		break;
	case plant:
		break;
	case zombie:
		QObject::connect(this, SIGNAL(mayPutPlant(int, int)), &(f->getConsole()), SLOT(dealPutPlant(int, int)));
	case bullet:
		QObject::connect(this, SIGNAL(mayPutPlant(int, int)), &(f->getConsole()), SLOT(dealPutPlant(int, int)));
		break;
	default:
		break;
	}
}

void MyLabel::mousePressEvent(QMouseEvent* ev)
{
	switch (type)
	{
	case card:
		emit cardClicked(cardNum);
		return;
	case sunshine:
		emit sunshineClicked(this);
		return;
	case zombie:
		emit mayPutPlant(ev->x() + rect.x(), ev->y() + rect.y());//坐标变换
		return;
	case bullet:
		emit mayPutPlant(ev->x() + rect.x(), ev->y() + rect.y());//坐标变换
		return;
	default:
		break;
	}
	QLabel::mousePressEvent(ev);
}