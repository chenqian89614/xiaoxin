#include "Rocket.h"
#include "cocos2d.h"

using namespace cocos2d;

Rocket::Rocket(int x ,int y)
{
	this->x = x;
	this->y = y;
	rocketSprite = Sprite::create();
	rocketSprite->setAnchorPoint(Point(0.5,0.5));
	rocketSprite->setScale(0.5);
}
void Rocket::refresh()
{
	rocketSprite->setPosition(Point(x,y));
}
