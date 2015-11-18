#ifndef _GameOverLayer_H_
#define _GameOverLayer_H_

#include "cocos2d.h"
#include "CityRacingSceneManager.h"
class GameOverLayer: public cocos2d::Layer
{
public:
	CityRacingSceneManager* crsm;
	Sprite* gameOverBg;
	Sprite* (gameOverSprite) [3];
	Sprite* spriteTouch;
	static int gold ;
	static int distance ;
	bool isGameOver = false ;
	Sprite* bgSpriteO;
	Sprite* bgSpriteT;
	int gameModeTemp = -1;
	virtual bool init();
	void bgUpdate();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void continueMenuCallback();
	void garageMenuCallback();
	void shopMenuCallback();
	int myGetIntegerForKey (std::string key);
	void mySetIntegerForKey(std::string key,int value);
	void phbpx();
	CREATE_FUNC(GameOverLayer);
};
#endif
