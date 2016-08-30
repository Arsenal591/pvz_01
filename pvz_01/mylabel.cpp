#include "mylabel.h"
#include <qevent.h>
//#include "playing_interface.h"
#include "pvz_01.h"
#include "qdebug.h"

MyLabel::MyLabel(QWidget* parent, ELEM_TYPE t, int n) :type(t), cardNum(n)
{ 
	this->setParent(parent); 
	switch (t)
	{
	case card:
		break;
	case sunshine:
		break;
	case plant:
		break;
	case zombie:
		MainWindow* f = static_cast<MainWindow*>(this->parentWidget());
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
		emit sunshineClicked();
		return;
	case zombie:
		emit mayPutPlant(ev->x() + rect.x(), ev->y() + rect.y());//×ø±ê±ä»»
		return;
	default:
		break;
	}
	QLabel::mousePressEvent(ev);
}