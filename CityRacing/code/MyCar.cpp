#include "MyCar.h"

MyCar::MyCar(int carNum,int x,int y)
{
	this->carNum=carNum;
	this->x=x;
	this->y=y;
}
MyCar::~MyCar(){}
Sprite* MyCar::refresh()
{
	Sprite* myCar = NULL;
	myCar = Sprite::create(StringUtils::format("%d.png",carNum));
	myCar->setPosition(Point(x,y));
	return myCar;
}
