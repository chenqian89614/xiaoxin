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
	//����״̬��0Ϊ����̬��1Ϊ�񵽵��ߺ���޵�̬
	int state = 0;
	void refresh();
};
#endif
