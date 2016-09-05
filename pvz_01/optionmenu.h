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
	void finish();
signals:
	void setVolume(int, int);
};

class OptionMenuAdvanced :public OptionMenu
{
	Q_OBJECT
};