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
	void close();//�رմ��ڲ�����Ӧ�ó���
	void resetEverything();//�����߼������
	void startPlaying();//�л�����Ϸ����
	void gameStart();//��ʼ��Ϸ
	void gameReturn();//����Ϸ�з���
	void gameContinue();//������Ϸ
	void loadWelcomeInterface();//���ػ�ӭ����
	void loadHelpInterface();//���ذ�������
	void loadThanksInterface();//������л����
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