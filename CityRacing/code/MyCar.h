#ifndef  _MyCar_H_
#define  _MyCar_H_

#include "cocos2d.h"

using namespace cocos2d;
class MyCar
{
public:
	MyCar(int carNum,int x,int y);
	~MyCar();
	int carNum = 0;
	Sprite* refresh();
	int x=0;
	int y=0;
};
#endif
