#include "AppDelegate.h"
#include "HelpLayer.h"
#include "AppMacros.h"
#include "cocos2d.h"

//#define pic_PRE_PATH_HelpLayer string("")

using namespace cocos2d;

//ÊµÏÖHelpLayerÀàÖÐµÄinit·½·¨£¬³õÊ¼»¯²¼¾°
bool HelpLayer::init()
{
    //µ÷ÓÃ¸¸ÀàµÄ³õÊ¼»¯
    if ( !Layer::init() )
    {
        return false;
    }

    //»ñÈ¡¿É¼ûÇøÓò³ß´ç
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    //»ñÈ¡¿É¼ûÇøÓòÔ­µã×ø±ê
    Point origin = Director::sharedDirector()->getVisibleOrigin();

	//¼ÓÔØÒôÐ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_button_press.mp3"
	);

    //´´½¨Ò»¸ö¾«Áé¶ÔÏó£¬°üº¬±³¾°Í¼Æ
    Sprite* backSprite = Sprite::create("backgroundh.png");
    //ÉèÖÃ¾«Áé¶ÔÏóµÄÎ»ÖÃ
    backSprite->setPosition(Point(400,240));
	//½«¾«ÁéÌí¼Óµ½²¼¾°ÖÐ
	this->addChild(backSprite,BACKGROUND_LEVEL_CGQ);

	//´´½¨¡°ÉÏÒ»·ù°ïÖúÍ¼Æ¬¡±¾«Áé
	MenuItemImage *leftItem = MenuItemImage::create
	(
		"left_up.png",
		"left_down.png",
		CC_CALLBACK_1(HelpLayer::menuCallBack0, this)
	);
	leftItem->setScale(1.5);
	//ÉèÖÃ¾«Áé²Ëµ¥°´Å¥µÄÎ»ÖÃ
	leftItem->setPosition(Point(330,450));

	//´´½¨¡°ÏÂÒ»·ù°ïÖúÍ¼Æ¬¡±¾«Áé
	MenuItemImage *rightItem = MenuItemImage::create
	(
		"right_up.png",
		"right_down.png",
		CC_CALLBACK_1(HelpLayer::menuCallBack1, this)
	);
	rightItem->setScale(1.5);
	//ÉèÖÃ¾«Áé²Ëµ¥°´Å¥µÄÎ»ÖÃ.
	rightItem->setPosition(Point(330,30));

	//´´½¨¡°·µ»Ø¡±¾«Áé
	MenuItemImage *fanhuiItem = MenuItemImage::create
	(
		"fanhui.png",
		"fanhui.png",
		CC_CALLBACK_1(HelpLayer::menuCallBack2, this)
	);
	//ÉèÖÃ¾«Áé²Ëµ¥°´Å¥µÄÎ»ÖÃ.
	fanhuiItem->setPosition(Point(40,420));

	pMenu = Menu::create(leftItem,rightItem,fanhuiItem,NULL);
	//ÉèÖÃ²Ëµ¥µÄÎ»ÖÃ
	pMenu->setPosition(Point(0,0));
	//½«²Ëµ¥Ìí¼Óµ½²¼¾°ÖÐ
	this->addChild(pMenu,GAME_LEVEL_CGQ);
	initIntroPic();
    return true;
}
void HelpLayer::initIntroPic()
{
	for(int i = 0;i<9;i++)
	{
		//Í¨¹ýcreateHelp»ñÈ¡¶ÔÓ¦Í¼Æ¬µÄÂ·¾¶
		help[i] = Sprite::create(StringUtils::format("help%d.png",i));
		help[i]->setPosition(Point(440,245+i*480));
		this->addChild(help[i],GAME_LEVEL_CGQ);
	}
}

//ÏòÓÒ¼ýÍ·
void HelpLayer::menuCallBack0(Object* pSende)
{
	//²¥·Å±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"sf_button_press.mp3"
	);
	for(int i= 0 ;i<9;i++)
	{
		help[i] ->setPosition(Point(400,-480));
	}
	currPicIndex ++;
	if(currPicIndex == 9)
	{
		currPicIndex = 0;
	}
	help[currPicIndex%9] ->setPosition(Point(440,245));
}

//Ïò×ó¼ýÍ·
void HelpLayer::menuCallBack1(Object* pSende)
{
	//²¥·Å±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"sf_button_press.mp3"
	);
	for(int i= 0 ;i<9;i++)
	{
		help[i] ->setPosition(Point(400,-480));
	}
	currPicIndex --;
	if(currPicIndex == -1)
	{
		currPicIndex = 8;
	}
	help[currPicIndex%9] ->setPosition(Point(440,245));
}

//Ïò×ó¼ýÍ·
void HelpLayer::menuCallBack2(Object* pSende)
{
	//²¥·ÅÒôÐ§
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//·µ»ØÖ÷½çÃæ
	man->toBeginLayer();
}

