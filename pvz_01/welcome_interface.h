#pragma once
#include <qwidget>
#include <qmediaplayer>
#include <qpalette>
#include <qevent.h>
#include "optionmenu.h"
#include "mybutton.h"
#include "pathname.h"

class WelcomeInterface:public QWidget
{
	Q_OBJECT
public:
	explicit WelcomeInterface(QWidget* parent = nullptr);
	virtual ~WelcomeInterface();
	const MyButton* getButton() { return button; }
	void setMusicAudioPlayers(QMediaPlayer* mp, QMediaPlayer* ap) { musicPlayer = mp; audioPlayer = ap; }//��musicPlayer audioPlayerָ��ȫ�ֲ�����
	void playAudio(QString);//����ָ��·������Ƶ

public slots:
	void startOption();//��ѡ�
	void finishOption(int, int);//�ر�ѡ�������ȡ�û����õ����ֺ���Ч������

protected:
	void mousePressEvent(QMouseEvent*);

private:
	void drawBackground();

private:
	QPixmap backgroundImage;//����ͼ
	MyButton* button;//ѡ�ť
	QMediaPlayer *musicPlayer, *audioPlayer;
	OptionMenu* menu;//ѡ�

signals:
	void switchToOption();//��Ҫ����ѡ�ʱ�������ź�
	void switchToPlay();//��Ҫ��ʼһ����Ϸʱ�������ź�
	void switchToHelp();//��Ҫ���ذ�������ʱ�������ź�
	void switchToThanks();//��Ҫ������л����ʱ�������ź�
	void switchToEnd();//��Ҫ�˳���Ϸʱ�������ź�
};