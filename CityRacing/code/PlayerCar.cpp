#include "PlayerCar.h"
#include "cocos2d.h"
using namespace  cocos2d;

PlayerCar::PlayerCar(int carNum,int x,int y,int angle,int a,int MAX_Speed,int MAX_pointR)
{
	this->carNum=carNum;
	this->x = x;
	this->y = y;
	this->angle = angle;
	this->a = a;
	this->MAX_Speed = MAX_Speed;
	this->MAX_pointR = MAX_pointR;
	playerCarSprite = Sprite::create(StringUtils::format("%d.png",carNum));
	playerCarSprite->setAnchorPoint(Point(0.5,0.5));
	playerCarSprite->retain();
}
void PlayerCar::refresh()
{
	playerCarSprite->setPosition(Point(x,y));
	playerCarSprite->setRotation(angle);
}
