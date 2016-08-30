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
	//void drawCard();
	void refresh();
	//void debug();
private:
	QPixmap backgroundImage, cardBoxImage;
	static const QString backgroundPath, cardBoxPath;
	static const QString cardPathName[3];
	QRect cardRect[6];
	QRect cellRect[5][10];
	QLabel* sunshineDisplay;

	QVector<QLabel*>plantsShown;
	QVector<QLabel*>zombiesShown;
	QVector<QLabel*>cardsShown;

	void setCardRect();
	void setCellRect();
signals:
};