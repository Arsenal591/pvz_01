#pragma once
#include <qevent.h>
#include <qlabel.h>

enum ELEM_TYPE{card, sunshine, plant, zombie, bullet};

class MyLabel :public QLabel
{
	Q_OBJECT
public:
	ELEM_TYPE type;
	QString path;
	int cardNum;//avalible if and only (type == card)
	QRect rect;//useful if and only (type == zombie)
	int cellx, celly;//avalible if and only (type != card)
protected:
	void mousePressEvent(QMouseEvent*);
signals:
	void sunshineClicked(MyLabel*);
	void cardClicked(int);
	//void resetCardChosen();
	void mayPutPlant(int, int);
public:
	MyLabel(QWidget* parent, ELEM_TYPE t, int n = -1);
	void setPath(QString str) { path = str; }
	QString getPath() { return path; }
	//void setGeometry(QRect geo) {};
};