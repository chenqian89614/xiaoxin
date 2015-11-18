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
	//��ʼ���ķ���
	virtual bool init();
	void isFirstEnter();
	void initSound();
	void initMusicBT();
	void initSoundYxFlag();
	void settingBT();
	void setMusicVisible();
	void setSoundVisible();
	//��ʼ���㴥���¼��Ĵ�����
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void goLevelMode();
	void goSpeedMode();
	void goGarage();
	void goShop();
	void goRate();
	void goPHB();
	void goHelpLayer();
    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(StartLayer);
};
#endif
