#pragma once
#include <qwidget>

class PlayingInterface :public QWidget
{
	Q_OBJECT
public:
	PlayingInterface();
public slots:
	void leadInAnimation();
	void cardAnimation();
	void debug();
private:
	QPixmap backgroundImage, cardBoxImage;
	static const QString backgroundPath, cardBoxPath;
signals:
};