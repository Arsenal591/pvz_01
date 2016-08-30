#pragma once
#include <qwidget>

class PlayingInterface :public QWidget
{
	Q_OBJECT
public:
	explicit PlayingInterface(QWidget* parent = nullptr);
	QRect getCellRect(int x, int y) { return cellRect[x][y]; }
public slots:
	void leadInAnimation();
	void cardAnimation();
	//void debug();
private:
	QPixmap backgroundImage, cardBoxImage;
	static const QString backgroundPath, cardBoxPath;
	QRect cardRect[6];
	QRect cellRect[5][10];

	void setCardRect();
	void setCellRect();
signals:
};