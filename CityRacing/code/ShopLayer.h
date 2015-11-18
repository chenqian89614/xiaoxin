#ifndef _ShopLayer_H_
#define _ShopLayer_H_

#include "cocos2d.h"
#include "CityRacingSceneManager.h"
using namespace cocos2d;

class ShopLayer: public cocos2d::Layer
{
public:
	CityRacingSceneManager* crsm;
	Sprite* bgSpriteO;
	Sprite* bgSpriteT;
	Sprite* (itemSprite) [5] ;
	Sprite* selSprite;
	Sprite* spriteTouch;
	int selectIndex = 0 ;
	Label* itemName ;
	Label* itemFunc ;
	LabelAtlas* itemPrice ;
	LabelAtlas* userGoldCount ;
	LabelAtlas* myResourcesCount ;
	std::string itemNameString [5];
	std::string itemPriceString [5];
	std::string itemFuncString [5];
	//初始化的方法
	virtual bool init();
	void initItemFuncIntro();
	void buyItem();
	void itemFuncIntro();
	void bgUpdate();
	void backMenuCallback();
	bool onTouchBegan(Touch* touch, Event* event);
    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(ShopLayer);
};
#endif
