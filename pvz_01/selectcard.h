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
	QStringLiteral("�㶹����:\nÿ�ι������һ���㶹"),
	QStringLiteral("���տ�:\nÿ��һ��ʱ������һ������"),
	QStringLiteral("���ǽ:\nƾ�賬�ߵ�����ֵ�赲��ʬǰ��"),
	QStringLiteral("ӣ��ը��:\nɱ�˷�Χ�ڴ�ɱ��������"),
	QStringLiteral("��������:\nÿ�ι�������һ�ű��㶹"),
	QStringLiteral("˫ǹ�㶹:\nÿ�ι���������������㶹"),
	QStringLiteral("�����׮:\n��������������ͨ�㶹��Ϊ���㶹"),
	QStringLiteral("��������:\nС��ΧȺ��ɱ��"),
	QStringLiteral("ʳ�˻�:\n�����Լ���ǰ�Ľ�ʬ")
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