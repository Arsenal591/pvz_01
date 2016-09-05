#pragma once
#include <qwidget>
#include <qlabel>
#include <mylabel.h>
#include "mybutton.h"
#include "pathname.h"
#include "selectcard.h"
#include "optionmenu.h"

class QMouseEvent;
class GameConsole;

class PlayingInterface :public QWidget
{
	Q_OBJECT
protected:
	void mousePressEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);
	void paintEvent(QPaintEvent*);
public:
	explicit PlayingInterface(QWidget* parent = nullptr, GameConsole* = nullptr);
	virtual ~PlayingInterface();
	const QRect getCellRect(int x, int y) { return cellRect[x][y]; }
	int getCardSum() { return cardsShown.size(); }
	const MyLabel* getCardShown(int i) { return cardsShown[i]; }
public slots:
	void leadInAnimation();
	void cardAnimation();
	void refresh();
	void gameOver(bool);
	void startOption();

	void setCards(QVector<int>);

	void dealCardClicked(int);
	void dealSunshineClicked(MyLabel*);
	void dealPlantClicked(MyLabel*);

	void deleteZombie(int);
	void deletePlant(int);
	void deleteSunshine(MyLabel*);
	void deleteBullet(int);

	void addZombie(enum ZOMBIE_TYPE, int, int);
	void addPlant(enum PLANT_TYPE,int, int);
	void addSunshine(int, int, bool);
	void addBullet(enum BULLET_TYPE, int, int);

	void bulletMove(int);
	void zombieMove(int, int, int);

signals:
	void shovelClicked();
	void shovelCanceled();
	void doneCardClicked(int);
	void doneSunshineClicked(MyLabel*);
	void donePlantClicked(MyLabel*);
	void gameReturn();
private:
	GameConsole* info;
	QPixmap backgroundImage, cardBoxImage;
	QLabel *backgroundLabel, *cardBoxLabel;
	QRect cardRect[6];
	QRect cellRect[5][10];
	SelectCard* selectCard;

	MyButton* option;

	OptionMenu* menu;
	QLabel* sunshineDisplay;
	QVector<MyLabel*>plantsShown;
	QVector<MyLabel*>zombiesShown;
	QVector<MyLabel*>cardsShown;
	QVector<MyLabel*>sunshineShown;
	QVector<MyLabel*>bulletsShown;

	void setCardRect();
	void setCellRect();
};