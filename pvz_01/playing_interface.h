#pragma once
#include <qwidget>
#include <qlabel>

class GameConsole;
//class MainWindow;

class PlayingInterface :public QWidget
{
	Q_OBJECT
public:
	explicit PlayingInterface(QWidget* parent = nullptr);
	const QRect getCellRect(int x, int y) { return cellRect[x][y]; }
public slots:
	void leadInAnimation();
	void cardAnimation();
	void refresh();
	//void debug();
private:
	QPixmap backgroundImage, cardBoxImage;
	static const QString backgroundPath, cardBoxPath;
	QRect cardRect[6];
	QRect cellRect[5][10];
	QLabel* sunshineDisplay;

	void setCardRect();
	void setCellRect();
signals:
};