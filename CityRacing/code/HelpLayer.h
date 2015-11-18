#ifndef _HelpLayer_H_
#define _HelpLayer_H_

#include "cocos2d.h"
#include "CityRacingSceneManager.h"
using namespace cocos2d;

class HelpLayer: public cocos2d::Layer
{
public:
	CityRacingSceneManager* crsm;
	Sprite* bgSpriteO;
	Sprite* bgSpriteT;
	Sprite* (bSprite) [7];
	Point currPoint;
	Point TBGPoint [7];
	Sprite* (spIntro) [7];
	int currIntroIndex = 0;

	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void setBWPosition();
	void bgUpdate();
	void backMenuCallback();
	CREATE_FUNC(HelpLayer);
};
#endif
