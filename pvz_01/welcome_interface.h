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
	explicit WelcomeInterface(QWidget* parent = nullptr);
	virtual ~WelcomeInterface();
	const MyButton* getButton() { return button; }
signals:
	void switchToOptions();
	void switchToPlay();
	void switchToHelp();
	void switchToAbout();
	void switchToThanks();
	void switchToEnd();
};