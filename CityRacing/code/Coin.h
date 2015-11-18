#ifndef _Coin_H_
#define _Coin_H_
#include "cocos2d.h"

using namespace cocos2d;
class Coin
{
public :
	Coin(int x ,int y);
	~Coin();
	int x = 0;
	int y = 0;
	Sprite* coinSprite = NULL;
	void refresh();
};

#endif
