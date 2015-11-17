#ifndef _MusicLayerHelp_H_
#define _MusicLayerHelp_H_

#include "cocos2d.h"
#include "SpriteManager.h"

using namespace cocos2d;

class MusicLayerHelp
{
public :
	MusicLayerHelp(Layer* layerIn);
	void initCreateSprite();
	bool JudgeSp(Sprite* sp);
public :
	Layer* layer;
	SpriteManager* sh;
};

#endif
