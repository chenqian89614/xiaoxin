#ifndef _PlayerCar_H_
#define _PlayerCar_H_
#include "cocos2d.h"
#include "CarFatherClass.h"
using namespace cocos2d;

class PlayerCar : public CarFatherClass
{
public :
	PlayerCar(int carNum,int x,int y,int angle,int a,int MAX_Speed,int MAX_pointR);
	~PlayerCar();
	Sprite* playerCarSprite = NULL;
	int carNum;
	int a;
	int MAX_Speed;
	int MAX_pointR;
	//车的状态，0为正常态，1为捡到道具后的无敌态
	int state = 0;
	void refresh();
};
#endif
