#pragma once
class Plant
{
	Q_OBJECT
public:
	static const int hp, atk, range, cd, recharge, prepare, cost;
private:
	int lastAttack;
	//int posx, posy;//����
	int cellx, celly;//����
public:
	Plant();
	virtual void attack() = 0;
	virtual void draw() = 0;
};