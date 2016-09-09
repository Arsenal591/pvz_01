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
	void setMusicAudioPlayers(QMediaPlayer* mp, QMediaPlayer* ap) { musicPlayer = mp; audioPlayer = ap; }//将musicPlayer audioPlayer指向全局播放器
	void playAudio(QString);//播放指定路径的音频

public slots:
	void startOption();//打开选项卡
	void finishOption(int, int);//关闭选项卡，并获取用户设置的音乐和音效的音量

protected:
	void mousePressEvent(QMouseEvent*);

private:
	void drawBackground();

private:
	QPixmap backgroundImage;//背景图
	MyButton* button;//选项按钮
	QMediaPlayer *musicPlayer, *audioPlayer;
	OptionMenu* menu;//选项卡

signals:
	void switchToOption();//需要加载选项卡时，发出信号
	void switchToPlay();//需要开始一局游戏时，发出信号
	void switchToHelp();//需要加载帮助界面时，发出信号
	void switchToThanks();//需要加载鸣谢界面时，发出信号
	void switchToEnd();//需要退出游戏时，发出信号
};