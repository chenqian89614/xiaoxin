#ifndef __StartLayer_H__
#define __StartLayer_H__

#include "cocos2d.h"
#include "CityRacingSceneManager.h"

using namespace cocos2d;
class StartLayer : public cocos2d::Layer
{
public:
	CityRacingSceneManager* crsm;
	Sprite* spriteTouch;
	Sprite* (sp) [6];
	bool setFlag=false;
	MenuItemImage* musicOnItem;
	MenuItemImage* musicOffItem;
	MenuItemImage* soundOnItem;
	MenuItemImage* soundOffItem;

	static int gameMode ;
	static int gameModeLevel ;
	static bool soundFlag ;
	static bool yxFlag ;
	//初始化的方法
	virtual bool init();
	void isFirstEnter();
	void initSound();
	void initMusicBT();
	void initSoundYxFlag();
	void settingBT();
	void setMusicVisible();
	void setSoundVisible();
	//开始单点触控事件的处理方法
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void goLevelMode();
	void goSpeedMode();
	void goGarage();
	void goShop();
	void goRate();
	void goPHB();
	void goHelpLayer();
    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(StartLayer);
};
#endif
