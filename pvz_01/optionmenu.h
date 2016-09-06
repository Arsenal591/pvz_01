#pragma once
#include <qwidget>
#include <qlabel>
#include <qslider>
#include <qlayout>
#include <qgroupbox>
#include "mybutton.h"
#include "pathname.h"

class OptionMenu :public QWidget
{
	Q_OBJECT
private:
	QLabel *musicLabel, *audioLabel;
	QSlider *musicSetting, *audioSetting;
	MyButton* ok;
public:
	OptionMenu(QWidget* parent = nullptr);
	void connect();
	void setInitial(int m, int a) { musicSetting->setValue(m), audioSetting->setValue(a); }
public slots:
	void finish();
signals:
	void setVolume(int, int);
};

class OptionMenuAdvanced :public OptionMenu
{
	Q_OBJECT
private:
	MyButton *restart, *goback;
public:
	OptionMenuAdvanced(QWidget* parent = nullptr);
	void connect();
public slots:
	void sendGameRestart();
	void sendGameReturn();
signals:
	void gameRestart();
	void gameReturn();
};