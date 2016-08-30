#pragma once
#include <qevent.h>
#include<qlabel.h>

enum ELEM_TYPE{card, sunshine, plant, zombie};

class MyLabel :public QLabel
{
	Q_OBJECT
private:
	ELEM_TYPE type;
	int cardNum;//avalible if and only (type == card)
	QRect rect;//useful if and only (type == zombie)
protected:
	void mousePressEvent(QMouseEvent*);
signals:
	void sunshineClicked();
	void cardClicked(int);
	void resetCardChosen();
	void mayPutPlant(int, int);
public:
	MyLabel(QWidget* parent, ELEM_TYPE t, int n = -1);
};