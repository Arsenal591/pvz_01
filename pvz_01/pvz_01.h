#ifndef PVZ_01_H
#define PVZ_01_H

#include <QtWidgets/QMainWindow>
#include "ui_pvz_01.h"
#include "game_console.h"
#include "welcome_interface.h"
#include "playing_interface.h"

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
	//GameConsole _Console;
	QWidget* currentWidget;
	void connect();
};

#endif