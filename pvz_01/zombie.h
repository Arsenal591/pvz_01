#pragma once
#include <qobject>
#include <qrect>

enum ZOMBIE_TYPE{normal, bucket, pole};
class Zombie:public QObject
{
	Q_OBJECT
public:
	Zombie(ZOMBIE_TYPE, int, int, QRect, int);
	ZOMBIE_TYPE type;

	//attention: ��ʬΪ���ٹ�����atkΪÿ10����Ĺ�����
	int hp, atk;
	int moveInterval;//�೤ʱ���ƶ�һ������
	int status;//0 ��ʼ��1 ���Դ�, 2 ����, 3 ��ʧ
	bool ifAttacking;

	int step;//�����������е���һ��
	int lastStepTime;//��һ���Ľ���ʱ��

	int deadTime;//����ʱ��

	int cellx, celly;
	int bornTime;
	QRect rect;
};
