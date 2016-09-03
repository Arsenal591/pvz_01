#pragma once

#include <qevent>
#include <qlabel>
#include <qpalette>
#include <qsignalmapper>
#include <qvector>
#include "mybutton.h"
#include "pathname.h"

const QString STATEMENTS[] =
{
	QStringLiteral("豌豆射手:\n每次攻击射出一发豌豆"),
	QStringLiteral("向日葵:\n每隔一段时间生产一个阳光"),
	QStringLiteral("坚果墙:\n凭借超高的生命值阻挡僵尸前行"),
	QStringLiteral("樱桃炸弹:\n杀伤范围内大杀伤力爆破"),
	QStringLiteral("寒冰射手:\n每次攻击发射一颗冰豌豆"),
	QStringLiteral("双枪豌豆:\n每次攻击连续射出两发豌豆"),
	QStringLiteral("火炬树桩:\n将经过自身的普通豌豆变为火豌豆"),
	QStringLiteral("土豆地雷:\n小范围群体杀伤"),
	QStringLiteral("食人花:\n吞下自己面前的僵尸")
};

class SelectCard:public QWidget
{
	Q_OBJECT
private:
	bool ifSelected[9];
	int selectedSum;
	QRect choiceRect[10];
	MyButton* buttons[9];
	MyButton* ok;
	QLabel *statement, *title;
public:
	SelectCard(QWidget* parent = nullptr);
	void connect();
public slots:
	void dealCard(int);
	void changeStatement(int);
	void submit();
	void hide();
signals:
	void selected(QVector<int>);
};