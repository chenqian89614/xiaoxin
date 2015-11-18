#include "SoundsetLayer.h"
#include "MenuLayer.h"
#include "Constant.h"
#include "AppMacros.h"

USING_NS_CC;

bool SoundsetLayer::init()
{
	//调用父类的初始化
	if(!Layer::init())
	{
		return false;
	}
	//添加背景
	this->addChild(TankSceneManager::getGround(),0);
	MenuLayer::initTitle(this);
	initMenu();
	musicRefresh();
	effectRefresh();
	return true;
}

void SoundsetLayer::initMenu()
{
	//创建菜单项
	musicItem = MenuItemImage::create
	(
			PIC_PATH+std::string("close_music.png"),
			PIC_PATH+std::string("close_music_select.png"),
			CC_CALLBACK_0(SoundsetLayer::musicChange,this)
	);
	musicItem->setPosition(Point(780,380));
	effectItem = MenuItemImage::create
	(
			PIC_PATH+std::string("close_effect.png"),
			PIC_PATH+std::string("close_effect_select.png"),
			CC_CALLBACK_0(SoundsetLayer::effectChange,this)
	);
	effectItem->setPosition(Point(780,300));
	MenuItemImage* backItem = MenuItemImage::create
	(
			PIC_PATH+std::string("back_menu.png"),
			PIC_PATH+std::string("back_menu_select.png"),
			CC_CALLBACK_0(SoundsetLayer::toMenuLayer,this)
	);
	backItem->setPosition(Point(780,140));
	//设置菜单位置

	//创建菜单容器
	Menu* menu = Menu::create(musicItem,effectItem,backItem,NULL);
	//设置惨淡原点位置
	menu->setPosition(Point::ZERO);

	this->addChild(menu);
}

void SoundsetLayer::musicChange()
{
	Constant::musicFlag=!Constant::musicFlag;
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	Constant::playMusic();
	musicRefresh();
	UserDefault::getInstance()->setBoolForKey("music", Constant::musicFlag);
}

void SoundsetLayer::musicRefresh()
{
	if(Constant::musicFlag)
	{
		musicItem->setNormalSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("close_music.png"),
			Rect(0,0,190,50))
		);
		musicItem->setSelectedSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("close_music_select.png"),
			Rect(0,0,200,50))
		);
	}else
	{
		musicItem->setNormalSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("open_music.png"),
			Rect(0,0,200,50))
		);
		musicItem->setSelectedSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("open_music_select.png"),
			Rect(0,0,200,50))
		);
	}
}

void SoundsetLayer::effectChange()
{
	Constant::effectFlag=!Constant::effectFlag;
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	effectRefresh();
	UserDefault::getInstance()->setBoolForKey("effect", Constant::effectFlag);
}

void SoundsetLayer::effectRefresh()
{
	if(Constant::effectFlag)
	{
		effectItem->setNormalSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("close_effect.png"),
			Rect(0,0,174,50))
		);
		effectItem->setSelectedSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("close_effect_select.png"),
			Rect(0,0,174,50))
		);
	}else
	{
		effectItem->setNormalSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("open_effect.png"),
			Rect(0,0,174,50))
		);
		effectItem->setSelectedSpriteFrame
		(
			SpriteFrame::create(PIC_PATH+std::string("open_effect_select.png"),
			Rect(0,0,174,50))
		);
	}
}

void SoundsetLayer::toMenuLayer()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	tsm->toMenuLayer();
}
