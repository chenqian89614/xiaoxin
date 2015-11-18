#ifndef _HKMJObject_H_
#define _HKMJObject_H_
#include "cocos2d.h"

using namespace cocos2d;
class HKMJObject
{
public :
	HKMJObject(int x,int y);
	Sprite* hkmjSprite ;
	int lifeValue = 20;
	//起火标志
	bool qhFlag = false;
	//横纵坐标
	int x;
	int y;
	//军舰的冷却时间
	int coolTime0 = 0;
	int coolTime1 = 0;
	int coolTime2 = 0;
	int coolTime3 = 0;
	int coolTime4 = 0;
	//打开必杀技菜单标志
	bool openMenu = false;
	//必杀技的冷却
	int coolTimeBSJ = 100;
	int coolTimePlane = 100;
};
#endif
