#include "game_console.h"
#include "qtimer"

GameConsole::GameConsole(QWidget* parent)
{
	this->setParent(parent);
	duration = 0;
	sunshine = 100;

	normalTimer = new QTimer(this);
	specialTimer = new QTimer(this);
	normalTimer->setInterval(1);
	specialTimer->setInterval(1000);
}