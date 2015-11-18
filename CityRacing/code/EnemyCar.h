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
	//敌车状态---------------0：正常行驶---1：被玩家的车撞----2：被玩家的车撞
	int state = 0;
	EnemyCar(int carNum,int x,int y,int speed,int state);
	~EnemyCar();

	void refresh();
};
#endif
