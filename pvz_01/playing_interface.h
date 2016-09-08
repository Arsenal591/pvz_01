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
	void playAudio(QString);//����ָ����ַ����Ƶ�ļ�����Ч��

	void refresh();//�ػ���Ϸ����
	void gameOver(bool);//��Ϸ����ʱ������Ϸ����
	void restartGame();//��Ϸ��ͷ��ʼ������Ϸ����
	void backToWelcome();//��Ϸ��;����ʱ������Ϸ����

	void startOption();//��ѡ��˵�
	void finishOption(int, int);//�ر�ѡ��˵�

	void setCards(QVector<int>);//�ڽ�������ӿ�Ƭ��Ϣ

	void dealCardClicked(int);//��Ӧ��Ƭ����¼�
	void dealSunshineClicked(MyLabel*);//��Ӧ�������¼�
	void dealPlantClicked(MyLabel*);//��Ӧֲ�����¼�

	void deleteZombie(int);//�ӽ�����ɾ����ʬ
	void deletePlant(int);//�ӽ�����ɾ��ֲ��
	void deleteSunshine(MyLabel*);//�ӽ�����ɾ������
	void deleteBullet(int);//�ӽ�����ɾ���ӵ�

	void addZombie(enum ZOMBIE_TYPE, int, int);//�ڽ�������ӽ�ʬ
	void addPlant(enum PLANT_TYPE, int, int);//�ڽ��������ֲ��
	void addSunshine(int, int, bool);//�ڽ������������
	void addBullet(enum BULLET_TYPE, int, int, bool);//�ڽ������������

	void bulletMove(int);//�����ӵ��ƶ�
	void zombieMove(int, int, int);//����ʬ�ƶ�

protected:
	//����������д�����¼�������
	void mousePressEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);
	void paintEvent(QPaintEvent*);

private:
	void setCardRect();
	void setCellRect();

private slots:
	void leadInAnimation();//��������
	void cardAnimation();//��Ƭ�ж���

signals:
	void shovelClicked();//���ӱ����ʱ֪ͨ�߼���
	void shovelCanceled();//���ӱ�ȡ��ʱ֪ͨ�߼���
	void doneCardClicked(int);//��Ƭ�����ʱ֪ͨ�߼���
	void doneSunshineClicked(MyLabel*);//���ⱻ���ʱ֪ͨ�߼���
	void donePlantClicked(MyLabel*);//ֲ�ﱻ���ʱ֪ͨ�߼���
	void gameReturn();//��Ϸ����ʱ֪ͨ������
	void resetEverything();//��Ϸ���¿�ʼʱ֪ͨ������ʹ�������߼���������

private:
	GameConsole* info;
	QMediaPlayer *musicPlayer, *audioPlayer;
	QPixmap backgroundImage, cardBoxImage;
	QLabel *backgroundLabel, *cardBoxLabel;
	QRect cardRect[6];
	QRect cellRect[5][10];
	SelectCard* selectCard;//��Ƭѡ���

	MyButton* option;//ѡ�ť
	OptionMenu* menu;//ѡ��˵�

	QLabel* sunshineDisplay;
	QVector<MyLabel*>plantsShown;
	QVector<MyLabel*>zombiesShown;
	QVector<MyLabel*>cardsShown;
	QVector<MyLabel*>sunshineShown;
	QVector<MyLabel*>bulletsShown;
};