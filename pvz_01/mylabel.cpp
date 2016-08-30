#include "mylabel.h"
#include <qevent.h>
//#include "playing_interface.h"
#include "pvz_01.h"
#include "qdebug.h"

MyLabel::MyLabel(QWidget* parent, ELEM_TYPE t, int n) :type(t), cardNum(n)
{ 
	this->setParent(parent); 
	//MainWindow* f = static_cast<MainWindow*>(this->parentWidget());
	//if (f == 0)qDebug() << "null\n";
	//PlayingInterface* f = static_cast<PlayingInterface*>(this->parentWidget());
	//connect(this, SIGNAL(cardClicked(int)), f->getWidget(), SLOT(dealCardClicked(int)));
	//connect(this, SIGNAL(sunshineClicked()), f->getWidget(), SLOT(sunshineCardClicked()));
}

void MyLabel::mousePressEvent(QMouseEvent* ev)
{
	switch (type)
	{
	case card:
		emit cardClicked(cardNum);
		break;
	case sunshine:
		emit sunshineClicked();
		break;
	default:
		break;
	}
}