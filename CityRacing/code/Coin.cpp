#include "Coin.h"
#include "cocos2d.h"

using namespace cocos2d;

Coin::Coin(int x ,int y)
{
	this->x = x;
	this->y = y;
	coinSprite = Sprite::create();
	coinSprite->setAnchorPoint(Point(0.5,0.5));
}

void Coin::refresh()
{
	coinSprite->setPosition(Point(x,y));
}
