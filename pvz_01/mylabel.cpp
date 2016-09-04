#include "mylabel.h"
#include <qevent.h>
#include "pvz_01.h"
#include "qdebug.h"

MyLabel::MyLabel(QWidget* parent, ELEM_TYPE t, int n) :type(t), cardNum(n)
{ 
	this->setParent(parent); 
}

void MyLabel::mousePressEvent(QMouseEvent* ev)
{
	qDebug() << "s2ignal\n";
	switch (type)
	{
	case card:
		emit cardClicked(cardNum);
		qDebug() << "signal\n";
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