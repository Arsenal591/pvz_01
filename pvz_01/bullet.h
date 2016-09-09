#pragma once
#include"qrect"

enum BULLET_TYPE{green,fire,ice};
struct Bullet
{
public:
	Bullet(BULLET_TYPE, QRect);
	void changeType(BULLET_TYPE);//�ı��ӵ�����

	BULLET_TYPE type;
	int lastChangePosy;//��¼��һ���ӵ����Ե�λ�ã���ֹ��α���
	QRect rect;//�ӵ��ļ���λ��
	int bornTime;//�ӵ��ĳ���ʱ��
	int atk;//�ӵ��Ĺ�����
	int moveInterval;//�ӵ����ƶ����
	int cellx;//�ӵ����ڵ���
};