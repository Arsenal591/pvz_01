#pragma once
#include <qwidget>

class PlayingInterface :public QWidget
{
	Q_OBJECT
public:
	PlayingInterface();
	void leadInAnimation();
private:
	QPixmap backgroundImage;
	static const QString path;
signals:

};