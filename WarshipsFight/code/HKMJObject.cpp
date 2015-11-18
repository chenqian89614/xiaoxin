#include "HKMJObject.h"
#include "cocos2d.h"
using namespace cocos2d;
HKMJObject::HKMJObject(int x,int y)
{
	this->x = x;
	this->y = y;
	hkmjSprite = Sprite::create("jdg.png");
	hkmjSprite->setPosition(Point(x,y));
}
