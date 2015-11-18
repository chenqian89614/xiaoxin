#ifndef _Rocket_H_
#define _Rocket_H_
#include "cocos2d.h"

using namespace cocos2d;
class Rocket
{
public:
	Rocket(int x ,int y);
	~Rocket();
	int x = 0;
	int y = 0;
	Sprite* rocketSprite = NULL;
	void refresh();
};

#endif
