#pragma once
#include "mybutton.h"
#include "pathname.h"
#include <qpalette>

class GeneralInterface: public QWidget
{
	Q_OBJECT;
private:
	MyButton* goback;
public:
	GeneralInterface(QWidget* parent = nullptr, QString backgroundPath = "");
signals:
	void switchToMain();
};