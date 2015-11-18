#include "PuKe.h"
#include "cocos2d.h"

using namespace cocos2d;

PuKe::PuKe(Texture2D* tt2d,int pkNum,Rect r,int x,int y)
{
	this->pkNum = pkNum;
	this->x = x;
	this->y = y;
	pukeSprite = Sprite::createWithTexture(tt2d);
	pukeSprite->setTextureRect(r);
}
PuKe::~PuKe()
{

}
//返回扑克精灵-更新
Sprite* PuKe::refresh()
{
	pukeSprite->setPosition(Point(x,y));
	return pukeSprite;
}
