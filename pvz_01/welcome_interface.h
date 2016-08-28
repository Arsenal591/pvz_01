#pragma once
#include <qwidget>

class WelcomeInterface:public QWidget
{
private:
	QPixmap backgroundImage;
private:
	void drawBackground();
public:
	WelcomeInterface(QWidget* parent = nullptr);
};