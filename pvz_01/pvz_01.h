#ifndef PVZ_01_H
#define PVZ_01_H

#include <QtWidgets/QMainWindow>
#include "ui_pvz_01.h"
#include "game_console.h"
#include "welcome_interface.h"
#include "playing_interface.h"
#include "qmediaplayer.h"

class QMediaPlayer;
class MainWindow :public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
public slots:
	void close();
	void startPlaying();
signals:

private:
	enum GAME_STATUS { Begin, Playing, About, Thanks, Setting }status;
	//GameConsole console;
	QWidget* currentWidget;
	QMediaPlayer* player;

	void playMusic();
	void connect();
};

#endif