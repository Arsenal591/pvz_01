#pragma once
#include <qwidget>
#include <mybutton.h>
#include <pathname.h>

class WelcomeInterface:public QWidget
{
	Q_OBJECT
private:
	QPixmap backgroundImage;
	void mousePressEvent(QMouseEvent*);
	MyButton* button;
private:
	void drawBackground();
public:
	WelcomeInterface(QWidget* parent = nullptr);
signals:
	void switchToOptions();
	void switchToPlay();
	void switchToHelp();
	void switchToAbout();
	void switchToThanks();
	void switchToEnd();
};