#pragma once
#include <qevent.h>
#include<qlabel.h>

enum ELEM_TYPE{card, sunshine};


class MyLabel :public QLabel
{
	Q_OBJECT
private:
	ELEM_TYPE type;
	int cardNum;//avalible if and only (type == card)
protected:
	void mousePressEvent(QMouseEvent*);
signals:
	void sunshineClicked();
	void cardClicked(int);
public:
	MyLabel(QWidget* parent, ELEM_TYPE t, int n = -1);
};