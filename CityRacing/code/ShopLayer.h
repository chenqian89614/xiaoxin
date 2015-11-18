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
	//��ʼ���ķ���
	virtual bool init();
	void initItemFuncIntro();
	void buyItem();
	void itemFuncIntro();
	void bgUpdate();
	void backMenuCallback();
	bool onTouchBegan(Touch* touch, Event* event);
    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(ShopLayer);
};
#endif
