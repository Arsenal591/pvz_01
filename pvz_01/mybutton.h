#pragma once
#include <qpushbutton.h>

class MyButton:public QPushButton
{
	Q_OBJECT
private:
	QPixmap *buttonImg, *pressImg, *releaseImg;
	int offsetx, offsety;
	QRect rect;
public:
	MyButton(QWidget*parent, QString str1, QString str2, QString str3);
	MyButton(QWidget*parent, QString str);
	void setSize(QRect);
	void setOffset(int, int);
protected:
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void enterEvent(QEvent*);
signals:
	void clicked();
	void entered();
};