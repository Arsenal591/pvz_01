#pragma once

#include <qevent>
#include <qlabel>
#include <qpalette>
#include "mybutton.h"
#include "pathname.h"

class PickCard:public QWidget
{
	Q_OBJECT
private:
	int choice[6];
	QRect choiceRect[10];
public:
	PickCard(QWidget* parent = nullptr);
};