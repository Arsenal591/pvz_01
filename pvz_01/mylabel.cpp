#include "mylabel.h"
#include <qevent.h>
#include "pvz_01.h"

MyLabel::MyLabel(QWidget* parent, ELEM_TYPE t, int n) :type(t), cardNum(n)
{ 
	this->setParent(parent); 
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
	case plant:
		emit plantClicked(this);
	default:
		break;
	}
	QLabel::mousePressEvent(ev);
}