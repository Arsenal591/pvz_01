#pragma once
#include <qwidget>
#include <mybutton.h>
#include <pathname.h>
#include <qmediaplayer.h>
#include "qpalette.h"
#include "qevent.h"

class WelcomeInterface:public QWidget
{
	Q_OBJECT
private:
	QPixmap backgroundImage;
	void mousePressEvent(QMouseEvent*);
	MyButton* button;
	QMediaPlayer *musicPlayer, *audioPlayer;
private:
	void drawBackground();
public:
	explicit WelcomeInterface(QWidget* parent = nullptr);
	virtual ~WelcomeInterface();
	const MyButton* getButton() { return button; }
	void setMusicAudioPlayers(QMediaPlayer* mp, QMediaPlayer* ap) { musicPlayer = mp; audioPlayer = ap; }
signals:
	void switchToOptions();
	void switchToPlay();
	void switchToHelp();
	void switchToThanks();
	void switchToEnd();
};