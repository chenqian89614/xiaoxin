#ifndef _LevelLayerHelp_H_
#define _LevelLayerHelp_H_

#include "cocos2d.h"
#include "SpriteManager.h"

using namespace cocos2d;

class LevelLayerHelp
{
public :
	LevelLayerHelp(Layer* layerIn);
	void initCreateSprite();
	bool JudgeSp(Sprite* sp);
	void changeLevel(int levelNum, int direction);
	void moveEffet(int direction);
public :
	Layer* layer;
	SpriteManager* sh;
};

#endif
