#ifndef _EnemyCar_H_
#define _EnemyCar_H_
#include "cocos2d.h"
#include "CarFatherClass.h"
using namespace cocos2d;

class EnemyCar : public CarFatherClass
{
public:
	int carNum = 0;
	int speed = 0;
	Sprite* enemyCarSprite = NULL;
	bool RL = false ;
	//�г�״̬---------------0��������ʻ---1������ҵĳ�ײ----2������ҵĳ�ײ
	int state = 0;
	EnemyCar(int carNum,int x,int y,int speed,int state);
	~EnemyCar();

	void refresh();
};
#endif
