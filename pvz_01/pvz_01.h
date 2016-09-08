#ifndef PVZ_01_H
#define PVZ_01_H

#include <qWidget>
#include "game_console.h"
#include "welcome_interface.h"
#include "playing_interface.h"
#include "general_interface.h"
#include "qmediaplayer.h"

class MainWindow :public QWidget
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
public slots:
	void close();//关闭窗口并结束应用程序
	void resetEverything();//重置逻辑与界面
	void startPlaying();//切换到游戏界面
	void gameStart();//开始游戏
	void gameReturn();//从游戏中返回
	void gameContinue();//继续游戏
	void loadWelcomeInterface();//加载欢迎界面
	void loadHelpInterface();//加载帮助界面
	void loadThanksInterface();//加载鸣谢界面
	void setVolume(int m, int a) { musicPlayer->setVolume(m); audioPlayer->setVolume(a); }
private:
	void playMusic();
	void connectWithWelcomeInterface();
	void connectWithPlayingInterface();
	void connectWithHelpInterface();
	void connectWithThanksInterface();
	void connectConsoleWithPlayingInterface();
private:
	enum GAME_STATUS { Begin, Playing, About, Thanks, Setting }status;
	GameConsole console;
	QWidget* currentWidget;
	QWidget* historyWidget;
	QMediaPlayer *musicPlayer, *audioPlayer;
signals:
	void endApp();
};
#endif