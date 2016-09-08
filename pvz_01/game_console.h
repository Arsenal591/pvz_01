#pragma once

#include <qvector>
#include <qwidget>
#include <qtimer>
#include <ctime>
#include "mylabel.h"
#include "pathname.h"
#include "card.h"
#include "zombie.h"
#include "plant.h"
#include "sunshine.h"
#include "bullet.h"

class GameConsole:public QWidget
{
	Q_OBJECT
	friend class PlayingInterface;
public:
	explicit GameConsole(QWidget* parent = nullptr);
	void reset();
	int getLastGameStatus() { return lastGameStatus; }
public slots:
	void setCards(QVector<int>);//在逻辑端添加卡片信息

	void gameStart();//游戏开始时启动逻辑端的计时器
	void dealNormalLoop();//处理normalTimer
	void dealSpecialLoop();//处理specialTimer

	void stopTimer();
	void startTimer();

	void dealSunshineClicked(MyLabel*);//处理阳光点击事件
	void dealPlantClicked(MyLabel*);//处理植物点击事件
	void dealCardClicked(int);//处理卡片点击事件
	void dealShovelClicked() { ifShovelPicked = !ifShovelPicked;}//处理铲子点击事件
	void dealShovelCanceled() { ifShovelPicked = false; }//处理铲子取消事件

	void dealPutPlant(int, int);//在指定坐标处放置植物
private:
	void connect();
	void setCellRect();

	bool ifGameOver();//判断游戏是否结束
	void zombieStrategy();//设置僵尸生成策略

	//***以下函数对攻击、血量或移动进行结算***
	void dealAttackOfPlants();
	void dealAttackOfBullets();
	void dealAttackOfZombies();

	void dealHpOfPlants();
	void dealHpOfZombies();

	void dealBulletsMove();
	void dealZombiesMove();
	//*************************************

	//*****以下函数处理对阳光或僵尸的生成*****
	void sunshinesProduce();
	void zombiesProduce();
	//*************************************
signals:
	void gameOver(bool);//游戏结束时通知界面

	void playAudio(QString);//通知界面播放指定地址的音频

	//***以下函数均在单位的删除、添加、移动发生时，通知界面***
	void deleteSunshine(MyLabel*);
	void deletePlant(int);
	void deleteBullet(int);
	void deleteZombie(int);

	void addSunshine(int, int, bool);
	void addPlant(PLANT_TYPE, int, int);
	void addBullet(enum BULLET_TYPE, int, int, bool);
	void addZombie(enum ZOMBIE_TYPE, int, int);

	void bulletMove(int);
	void zombieMove(int, int, int);
	//****************************************************
	void timeToShow();//通知界面进行重绘
private:
	bool ifHumanWin;
	int lastGameStatus;

	int level;//关卡
	bool visible, infinite, protect;

	int zombieSum;//该关卡应当生产的僵尸总数
	int roundSum;//该关卡的僵尸生产回合总数
	int zombieProduced;//当前生产回合已经生产的僵尸总数
	int* zombieProduceList;
	int round;//当前处在第几个僵尸生产回合中
	int lastRoundFinish;//上一个生产回合结束的时间

	int duration;
	int sunshineLeft;

	QTimer *normalTimer, *specialTimer;

	QVector<Sunshine*>sunshines;
	QVector<Plant*>plants;
	QVector<Bullet*>bullets;
	QVector<Zombie*>zombies;
	QVector<Card*>cards;

	Card* cardChosen;
	bool ifShovelPicked;
	QRect cellRect[5][10];
};