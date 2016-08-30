#pragma once
#include <qwidget>
#include <qlabel>
#include <mylabel.h>

class QMouseEvent;
class GameConsole;
//class MainWindow;

class PlayingInterface :public QWidget
{
	Q_OBJECT
protected:
	void mousePressEvent(QMouseEvent*);
public:
	explicit PlayingInterface(QWidget* parent = nullptr);
	const QRect getCellRect(int x, int y) { return cellRect[x][y]; }
	int getCardSum() { return cardsShown.size(); }
	const MyLabel* getCardShown(int i) { return cardsShown[i]; }
public slots:
	void leadInAnimation();
	void cardAnimation();
	void refresh();

	void dealCardClicked(int);
	//void dealSunshineClicked();

	//void debug();
private:
	QPixmap backgroundImage, cardBoxImage;
	static const QString backgroundPath, cardBoxPath;
	static const QString cardPathName[3];
	QRect cardRect[6];
	QRect cellRect[5][10];
	bool ifPlantExist[5][9];
	QLabel* sunshineDisplay;

	QVector<QLabel*>plantsShown;
	QVector<QLabel*>zombiesShown;
	QVector<MyLabel*>cardsShown;
	QVector<MyLabel*>sunshineShown;

	void setCardRect();
	void setCellRect();
};