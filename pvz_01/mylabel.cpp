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
	qDebug() << "i am pressed\n";
	switch (type)
	{
	case card:
		emit cardClicked(cardNum);
		return;
	case sunshine:
		emit sunshineClicked(this);
		return;
	case zombie:
		break;
	case bullet:
		break;
	case plant:
		emit plantClicked(this);
		return;
	default:
		break;
	}
	QLabel::mousePressEvent(ev);
}