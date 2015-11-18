#include "PauseLayer.h"
#include "AppMacros.h"
#include "Constant.h"
#include "BNSocketUtil.h"

bool PauseLayer::init()
{
	//调用父类的初始化
	if(!Layer::init())
	{
		return false;
	}
	//添加背景
	Sprite *groundSprite=Sprite::create(PIC_PATH+std::string("pausebackground.png"));
	groundSprite->setPosition(Point(480,270));
	this->addChild(groundSprite);

	//初始化菜单
	initPauseMenu();
	initSoundsetMenu();

	this->addChild(pauseMenu);
	return true;
}

void PauseLayer::initPauseMenu()
{
	MenuItemImage *continueItem = MenuItemImage::create
	(
		PIC_PATH+std::string("continue_game.png"),
		PIC_PATH+std::string("continue_game_select.png"),
		CC_CALLBACK_0(PauseLayer::sendContinue,this)
	);
	continueItem->setPosition(Point(360, 330));

	MenuItemImage *soundsetItem = MenuItemImage::create
	(
		PIC_PATH+std::string("soundset.png"),
		PIC_PATH+std::string("soundset_select.png"),
		CC_CALLBACK_0(PauseLayer::toSoundset,this)
	);
	soundsetItem->setPosition(Point(600, 330));

	MenuItemImage *backItem = MenuItemImage::create
	(
		PIC_PATH+std::string("back_menu.png"),
		PIC_PATH+std::string("back_menu_select.png"),
		CC_CALLBACK_0(PauseLayer::backMenu,this)
	);
	backItem->setPosition(Point(360, 210));

	MenuItemImage *exitItem = MenuItemImage::create
	(
		PIC_PATH+std::string("exit_game.png"),
		PIC_PATH+std::string("exit_game_select.png"),
		CC_CALLBACK_0(PauseLayer::gameExit,this)
	);
	exitItem->setPosition(Point(600, 210));

	pauseMenu=Menu::create(continueItem,soundsetItem,backItem,exitItem,NULL);
	pauseMenu->setPosition(Point::ZERO);
	pauseMenu->retain();
}

void PauseLayer::initSoundsetMenu()
{
	musicItem = MenuItemImage::create
	(
		PIC_PATH+std::string("close_effect.png"),
		PIC_PATH+std::string("close_effect_select.png"),
		CC_CALLBACK_0(PauseLayer::musicChange,this)
	);
	musicItem->setPosition(Point(360, 330));

	effectItem = MenuItemImage::create
	(
		PIC_PATH+std::string("close_music.png"),
		PIC_PATH+std::string("close_music_select.png"),
		CC_CALLBACK_0(PauseLayer::effectChange,this)
	);
	effectItem->setPosition(Point(600, 330));

	MenuItemImage *backItem = MenuItemImage::create
	(
		PIC_PATH+std::string("back_menu.png"),
		PIC_PATH+std::string("back_menu_select.png"),
		CC_CALLBACK_0(PauseLayer::toPause,this)
	);
	backItem->setPosition(Point(600, 210));

	soundsetMenu=Menu::create(musicItem,effectItem,backItem,NULL);
	soundsetMenu->setPosition(Point::ZERO);
	soundsetMenu->retain();
}

void PauseLayer::musicChange()
{
	Constant::musicFlag=!Constant::musicFlag;
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	Constant::playMusic();
	musicRefresh();
	UserDefault::getInstance()->setBoolForKey("music", Constant::musicFlag);
}

void PauseLayer::musicRefresh()
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

void PauseLayer::effectChange()
{
	Constant::effectFlag=!Constant::effectFlag;
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	effectRefresh();
	UserDefault::getInstance()->setBoolForKey("effect", Constant::effectFlag);
}

void PauseLayer::effectRefresh()
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

void PauseLayer::sendContinue()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	BNSocketUtil::sendStr("<#STATE#>",9);
	BNSocketUtil::sendInt(2);
}

void PauseLayer::toPause()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	this->removeChild(soundsetMenu);
	this->addChild(pauseMenu);
}

void PauseLayer::toSoundset()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	this->removeChild(pauseMenu);
	this->addChild(soundsetMenu);
	musicRefresh();
	effectRefresh();
}

void PauseLayer::gameExit()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	BNSocketUtil::sendStr("<#EXIT#>",8);
	BNSocketUtil::closeConnect();
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

void PauseLayer::backMenu()
{
	BNSocketUtil::closeConnect();
}

PauseLayer::~PauseLayer()
{
	pauseMenu->release();
	soundsetMenu->release();
}
