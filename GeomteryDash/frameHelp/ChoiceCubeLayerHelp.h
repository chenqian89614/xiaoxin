#ifndef _ChoiceCubeLayerHelp_H_
#define _ChoiceCubeLayerHelp_H_

#include "cocos2d.h"
#include "SpriteManager.h"

using namespace cocos2d;

class ChoiceCubeLayerHelp
{
public :
	ChoiceCubeLayerHelp(Layer* layerIn);
	void initCreateSprite();
	bool JudgeSp(Sprite* sp);
	void saveDate();
	void getDate();
public :
	Layer* layer;
	SpriteManager* sh;
	int p1 = 779;
	int p2 = 110;
	int p3 = 30;
	int p4 = 30;
	int p11;
	int p12;
	int p13;
	int p14;

};

#endif
