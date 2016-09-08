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
	void setCards(QVector<int>);//���߼�����ӿ�Ƭ��Ϣ

	void gameStart();//��Ϸ��ʼʱ�����߼��˵ļ�ʱ��
	void dealNormalLoop();//����normalTimer
	void dealSpecialLoop();//����specialTimer

	void stopTimer();
	void startTimer();

	void dealSunshineClicked(MyLabel*);//�����������¼�
	void dealPlantClicked(MyLabel*);//����ֲ�����¼�
	void dealCardClicked(int);//����Ƭ����¼�
	void dealShovelClicked() { ifShovelPicked = !ifShovelPicked;}//������ӵ���¼�
	void dealShovelCanceled() { ifShovelPicked = false; }//�������ȡ���¼�

	void dealPutPlant(int, int);//��ָ�����괦����ֲ��
private:
	void connect();
	void setCellRect();

	bool ifGameOver();//�ж���Ϸ�Ƿ����
	void zombieStrategy();//���ý�ʬ���ɲ���

	//***���º����Թ�����Ѫ�����ƶ����н���***
	void dealAttackOfPlants();
	void dealAttackOfBullets();
	void dealAttackOfZombies();

	void dealHpOfPlants();
	void dealHpOfZombies();

	void dealBulletsMove();
	void dealZombiesMove();
	//*************************************

	//*****���º�������������ʬ������*****
	void sunshinesProduce();
	void zombiesProduce();
	//*************************************
signals:
	void gameOver(bool);//��Ϸ����ʱ֪ͨ����

	void playAudio(QString);//֪ͨ���沥��ָ����ַ����Ƶ

	//***���º������ڵ�λ��ɾ������ӡ��ƶ�����ʱ��֪ͨ����***
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
	void timeToShow();//֪ͨ��������ػ�
private:
	bool ifHumanWin;
	int lastGameStatus;

	int level;//�ؿ�
	bool visible, infinite, protect;

	int zombieSum;//�ùؿ�Ӧ�������Ľ�ʬ����
	int roundSum;//�ùؿ��Ľ�ʬ�����غ�����
	int zombieProduced;//��ǰ�����غ��Ѿ������Ľ�ʬ����
	int* zombieProduceList;
	int round;//��ǰ���ڵڼ�����ʬ�����غ���
	int lastRoundFinish;//��һ�������غϽ�����ʱ��

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