#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
#include "ChoiceLayer.h"
#include "GameLayer.h"
#include "AppConstant.h"
using namespace std;

//USING_NS_CC;
using namespace cocos2d;
bool WelcomeLayer::playBgM=false;

WelcomeLayer::~WelcomeLayer()
{

}

//实现WelcomeLayer类中的init方法，初始化布景
bool WelcomeLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    //创建选项菜单项
    auto choiceItem = MenuItemImage::create
    (
    		welcomePic_PATH+"option_button_a.png",	//平时的图片
    		welcomePic_PATH+"option_button_b.png",	//选中时的图片
		    CC_CALLBACK_1(WelcomeLayer::menuChoiceCallback, this) //点击时执行的回调方法
	);
    //设置选项菜单项的位置
    choiceItem->setPosition
	(
		Point
		(
			origin.x + choiceItem->getContentSize().width/2+20 ,//X坐标
            origin.y + visibleSize.height - choiceItem->getContentSize().height*2-35//Y坐标
        )
    );

	//创建菜单对象
    auto menu = Menu::create(choiceItem, NULL);
    //设置菜单位置
    menu->setPosition(Point::ZERO);
    //将菜单添加到布景中
    this->addChild(menu, 1);
	//创建开始菜单项
	auto startItem = MenuItemImage::create
	(
			welcomePic_PATH+"play_button_a.png",	//平时的图片
			welcomePic_PATH+"play_button_b.png",	//选中时的图片
		    CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this) //点击时执行的回调方法
	);

	//设置播放菜单项的位置
	startItem->setPosition
	(
		Point
		(
			origin.x + visibleSize.width /2 ,	//X坐标
			origin.y + visibleSize.height/2		//Y坐标
		)
	);
	//创建菜单对象
	auto startMenu = Menu::create(startItem, NULL);
	//设置菜单位置
	startMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(startMenu, 2);

    //创建帮助菜单项
	auto helpItem = MenuItemImage::create
	(
		welcomePic_PATH+"help_button_a.png",
		welcomePic_PATH+"help_button_b.png",
		CC_CALLBACK_1(WelcomeLayer::menuHelpCallback, this) //点击时执行的回调方法
	);
	helpItem->setPosition(
		Point(
			origin.x + helpItem->getContentSize().width/2+20,	//X坐标
			origin.y +helpItem->getContentSize().height/2+105		//Y坐标
		)
	);
	//创建菜单对象
	auto helpMenu = Menu::create(helpItem, NULL);
	//设置菜单位置
	helpMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(helpMenu, 1);

	auto exitItem = MenuItemImage::create
	(
			welcomePic_PATH+"exit1.png",
			welcomePic_PATH+"exit2.png",
			CC_CALLBACK_1(WelcomeLayer::onExit, this)//点击时执行的回调方法
	);
	exitItem->setPosition(
			Point(
				origin.x + exitItem->getContentSize().width/2+300,	//X坐标
				origin.y + exitItem->getContentSize().height/2+200		//Y坐标
			)
			);
	//创建菜单对象
	auto exitMenu = Menu::create(exitItem, NULL);
	//设置菜单位置
	exitMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(exitMenu, 1);

    //创建一个精灵对象，包含background.png图片
    auto bgSprite = Sprite::create(welcomePic_PATH+"bg_01.png");
    //设置精灵对象的位置
    bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //将精灵添加到布景中
    this->addChild(bgSprite, 0);

    preloadBgMusic();//加载背景音乐
    ChoiceLayer::isMusic=UserDefault::getInstance()->getBoolForKey("bool1",true);
    ChoiceLayer::isSound=UserDefault::getInstance()->getBoolForKey("bool2",true);

    if(ChoiceLayer::isMusic==false)
	{
		pauseBgMusic();//暂停播放背景音乐
	}else if(ChoiceLayer::isMusic==true&&playBgM==false)
	{
		playBgMusic();//播放背景音乐
		playBgM=true;//背景音乐已播放过

	}else if((playBgM==true&&ChoiceLayer::isMusic==true)||(playBgM==true&&ChoiceLayer::isMusic==true))
	{
		resumeBgMusic();//继续播放背景
	}


    if(ChoiceLayer::isSound==false)
    {
    	pauseSound();//停止播放音效
    }
    preloadSwitchSound();//加载切换的音效
    preloadClickSound();//加载点击的音效

    return true;
}

void WelcomeLayer::menuChoiceCallback(Object* pSender)
{
	if(ChoiceLayer::isSound==false)
	{
		pauseSound();//停止播放音效
	}else
	{
		playSwitchSound();//播放切换的音效
		playClickSound();//播放点击的音效
	}
	gsm->goChoiceScene();
}

void WelcomeLayer::menuStartCallback(Object* pSender)
{
	if(ChoiceLayer::isSound==false)
	{
		pauseSound();//停止播放音效
	}else
	{
		playSwitchSound();//播放切换的音效
		playClickSound();//播放点击的音效
	}
	gsm->goLevelScene();

}

void WelcomeLayer::menuHelpCallback(Object* pSender)
{
	if(ChoiceLayer::isSound==false)
	{
		pauseSound();//停止播放音效
	}else
	{
		playSwitchSound();//播放切换的音效
		playClickSound();//播放点击的音效
	}
	gsm->goHelpScene();
}

void WelcomeLayer::preloadBgMusic()//加载背景音乐
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
			(sound_PATH+"background.mp3").c_str()					//加载背景音乐
	);
}
void WelcomeLayer::playBgMusic()//播放背景音乐
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
			(sound_PATH+"background.mp3").c_str(),				//播放背景音乐
						true
	);
}
void WelcomeLayer::pauseBgMusic()//暂停播放背景音乐
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();	//暂停播放
}
void WelcomeLayer::resumeBgMusic()//继续播放背景音乐
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();//继续播放
}

void WelcomeLayer::preloadSwitchSound()//加载切换音效
{
	//加载音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
			(sound_PATH+"switchpane.mp3").c_str()
	);
}
void WelcomeLayer::playSwitchSound()//播放切换音效
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"switchpane.mp3").c_str());
}
void WelcomeLayer::preloadClickSound()//加载点击音效
{
	//加载音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
			(sound_PATH+"click.mp3").c_str()
	);
}
void WelcomeLayer::playClickSound()//播放点击音效
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((sound_PATH+"click.mp3").c_str());
}

void WelcomeLayer::pauseSound()//暂停播放音效
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();	//暂停播放
}
void WelcomeLayer::resumeSound()//继续播放音效
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();//继续播放
}

void WelcomeLayer::onExit(Object* pSender)
{
	Director::getInstance()->end();//游戏结束
}
