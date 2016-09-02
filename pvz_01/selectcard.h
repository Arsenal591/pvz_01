#pragma once

#include <qevent>
#include <qlabel>
#include <qpalette>
#include <qsignalmapper>
#include <qvector>
#include "mybutton.h"
#include "pathname.h"

class SelectCard:public QWidget
{
	Q_OBJECT
private:
	bool ifSelected[9];
	int selectedSum;
	QRect choiceRect[10];
	MyButton* buttons[9];
	MyButton* ok;
	QLabel* statement;
public:
	SelectCard(QWidget* parent = nullptr);
	void connect();
public slots:
	void dealCard(int);
	void submit();
	void hide();
signals:
	void selected(QVector<int>);
};