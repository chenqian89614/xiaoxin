#ifndef _ChooseLevelLayer_H_
#define _ChooseLevelLayer_H_

#include "cocos2d.h"
#include "CityRacingSceneManager.h"
using namespace cocos2d;

class ChooseLevelLayer : public cocos2d::Layer
{
public :
	CityRacingSceneManager* crsm;
	Sprite* bgSpriteO;
	Sprite* bgSpriteT;
	Sprite* (gate0Sprite) [3];
	Sprite* spriteTouch;
	Label* taskLabel ;
	int levelFocus = -1;
	bool isGKLock = false ;
	int selectGK = 0;

	static int currLevel ;

	virtual bool init();
	void selectLevel(Sprite* spriteTouch);
	void backMenuCallback();
	//开始单点触控事件的处理方法
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void bgUpdate();
	CREATE_FUNC(ChooseLevelLayer);
};
#endif
