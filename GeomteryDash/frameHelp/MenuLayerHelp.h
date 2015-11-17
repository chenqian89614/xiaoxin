#ifndef _MenuLayerHelp_H_
#define _MenuLayerHelp_H_

#include "cocos2d.h"
#include "SpriteManager.h"

using namespace cocos2d;

class MenuLayerHelp
{
public :
	MenuLayerHelp(Layer* layerIn);
	void initCreateSprite();
	bool JudgeSp(Sprite* sp);
public :
	Layer* layer;
	SpriteManager* sh;
};

#endif
