#ifndef PVZ_01_H
#define PVZ_01_H

#include <QtWidgets/QMainWindow>
#include "ui_pvz_01.h"

class pvz_01 : public QMainWindow
{
	Q_OBJECT

public:
	pvz_01(QWidget *parent = 0);
	~pvz_01();

private:
	Ui::pvz_01Class ui;
};

#endif // PVZ_01_H
