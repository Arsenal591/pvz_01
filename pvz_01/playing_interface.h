#pragma once
#include <qwidget>
#include <qlabel>
#include "mylabel.h"
#include "mybutton.h"
#include "pathname.h"
#include "selectcard.h"
#include "optionmenu.h"

class GameConsole;
class QMediaPlayer;

class PlayingInterface :public QWidget
{
	Q_OBJECT
public:
	explicit PlayingInterface(QWidget* parent = nullptr, GameConsole* = nullptr);
	virtual ~PlayingInterface();
	void setMusicAudioPlayers(QMediaPlayer* mp, QMediaPlayer* ap) { musicPlayer = mp, audioPlayer = ap; }

public slots:
	void playAudio(QString);//播放指定地址的音频文件（音效）

	void refresh();//重绘游戏界面
	void gameOver(bool);//游戏结束时处理游戏界面
	void restartGame();//游戏从头开始处理游戏界面
	void backToWelcome();//游戏中途结束时处理游戏界面

	void startOption();//打开选项菜单
	void finishOption(int, int);//关闭选项菜单

	void setCards(QVector<int>);//在界面上添加卡片信息

	void dealCardClicked(int);//响应卡片点击事件
	void dealSunshineClicked(MyLabel*);//响应阳光点击事件
	void dealPlantClicked(MyLabel*);//响应植物点击事件

	void deleteZombie(int);//从界面中删除僵尸
	void deletePlant(int);//从界面中删除植物
	void deleteSunshine(MyLabel*);//从界面中删除阳光
	void deleteBullet(int);//从界面中删除子弹

	void addZombie(enum ZOMBIE_TYPE, int, int);//在界面上添加僵尸
	void addPlant(enum PLANT_TYPE, int, int);//在界面上添加植物
	void addSunshine(int, int, bool);//在界面上添加阳光
	void addBullet(enum BULLET_TYPE, int, int, bool);//在界面上添加阳光

	void bulletMove(int);//处理子弹移动
	void zombieMove(int, int, int);//处理僵尸移动

protected:
	//保护区将重写部分事件处理函数
	void mousePressEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);
	void paintEvent(QPaintEvent*);

private:
	void setCardRect();
	void setCellRect();

private slots:
	void leadInAnimation();//开场动画
	void cardAnimation();//卡片盒动画

signals:
	void shovelClicked();//铲子被点击时通知逻辑端
	void shovelCanceled();//铲子被取消时通知逻辑端
	void doneCardClicked(int);//卡片被点击时通知逻辑端
	void doneSunshineClicked(MyLabel*);//阳光被点击时通知逻辑端
	void donePlantClicked(MyLabel*);//植物被点击时通知逻辑端
	void gameReturn();//游戏结束时通知主程序
	void resetEverything();//游戏重新开始时通知主程序，使其重置逻辑端与界面端

private:
	GameConsole* info;
	QMediaPlayer *musicPlayer, *audioPlayer;
	QPixmap backgroundImage, cardBoxImage;
	QLabel *backgroundLabel, *cardBoxLabel;
	QRect cardRect[6];
	QRect cellRect[5][10];
	SelectCard* selectCard;//卡片选择盒

	MyButton* option;//选项按钮
	OptionMenu* menu;//选项菜单

	QLabel* sunshineDisplay;
	QVector<MyLabel*>plantsShown;
	QVector<MyLabel*>zombiesShown;
	QVector<MyLabel*>cardsShown;
	QVector<MyLabel*>sunshineShown;
	QVector<MyLabel*>bulletsShown;
};