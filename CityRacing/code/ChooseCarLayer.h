#ifndef __ChooseCarLayer_H__
#define __ChooseCarLayer_H__

#include "cocos2d.h"
#include "CityRacingSceneManager.h"
#include "MyCar.h"

using namespace cocos2d;
class ChooseCarLayer : public cocos2d::Layer
{
public:
	CityRacingSceneManager* crsm;
	Sprite* bgSpriteO;
	Sprite* bgSpriteT;
    Sprite* (garageBG) [8];
    MyCar* (myCar) [8];
    Sprite* (carSprite) [8];
    int tempCarNum;
	static int currCarNum;
	Point TBGPoint [8];
	Point currPoint;
	LabelAtlas* (userGoldLabel) [8] ;
	Sprite* (lockeSprite) [8];
	virtual bool init();
	void backMenuCallback();
	void refreshMenuSprite();
	void bgUpdate();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	void gameEnter();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	    //��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(ChooseCarLayer);
};
#endif

