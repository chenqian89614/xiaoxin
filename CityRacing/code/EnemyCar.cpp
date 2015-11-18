#include "EnemyCar.h"
#include "cocos2d.h"
using namespace cocos2d;

EnemyCar::EnemyCar(int carNum,int x,int y,int speed,int state)
{
	this->carNum = carNum;
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->state = state;
	enemyCarSprite = Sprite::create(StringUtils::format("%d.png",carNum));
	enemyCarSprite->setAnchorPoint(Point(0.5,1));
}
void EnemyCar::refresh()
{
	enemyCarSprite->setPosition(Point(x,y));
	//enemyCarSprite->setRotation(angle);
	switch(state)
	{
	case 0:
		break;
	case 1:
		if(RL == false)
		{
			angle = angle + 5;
			if(angle == 20)
			{
				RL = true;
			}
		}
		if(RL == true)
		{
			angle = angle - 5;
			if(angle == -20)
			{
				RL = false;
			}
		}
		enemyCarSprite->setRotation(angle);
		break;
	case 2:
		enemyCarSprite->setRotation(-30);
		break;
	case 3:
		enemyCarSprite->setRotation(30);
		break;
	}
}


