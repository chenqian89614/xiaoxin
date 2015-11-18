#include "WelcomeLayer.h"
#include "GameLayer.h"
#include "AppMacros.h"
#include "BNSocketUtil.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <string>


//USING_NS_CC;
using namespace cocos2d;
using namespace std;

bool WelcomeLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }

    addMenu();
    //创建一个精灵对象，包含background.png图片
    Sprite  *background = Sprite::create(PIC_PATH+std::string("background.png"));
    background->setPosition(Point(480,270));
    //将精灵添加到布景中
    this->addChild(background, BACKGROUD_LEVEL);
    
    startImage=Sprite::create(PIC_PATH+std::string("start_disable_btn.png"));
    startImage->setPosition(Point(750,400));
    this->addChild(startImage,PROP_LEVEL);
    startImage->setVisible(false);

    Sprite  *logo = Sprite::create(PIC_PATH+std::string("logo.png"));
    logo->setPosition(Point(260,270));
    this->addChild(logo, PROP_LEVEL);

    //显示接收信息的标签
    msgLabel=LabelTTF::create("Msg:", "Arial", 40);
    //设置标签字体的颜色
    msgLabel->setFontFillColor(Color3B::YELLOW);
    msgLabel->setPosition(Vec2(750,400));
    this->addChild(msgLabel, PROP_LEVEL+1);
    BNSocketUtil::msgLabel=msgLabel;
    msgLabel->setVisible(false);

    if(Constant::musicFlag)
    {
        backMusic();
    }
   
    
     return true;
}

//添加菜单项
void WelcomeLayer::addMenu()
{
	//startGame
	MenuItemImage *startItem = MenuItemImage::create
	(
		PIC_PATH+std::string("start_blue_btn.png"),
		PIC_PATH+std::string("start_blue_btn_down.png"),
		PIC_PATH+std::string("start_disable_btn.png"),
	   CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this)
	);
	//setDisabledSpriteFrame(startItem);
	//设置关闭菜单项的位置
	startItem->setPosition(Point(750,400));
	//创建菜单对象
	startMenu = Menu::create(startItem, NULL);
	//设置菜单位置
	startMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(startMenu,BTN_LEVEL);

	//help
	MenuItemImage *helpItem = MenuItemImage::create
	(
			PIC_PATH+std::string("start_green_btn.png"),
			PIC_PATH+std::string("start_green_btn_down.png"),
		   CC_CALLBACK_1(WelcomeLayer::menuHelpCallback, this)
	);
	//设置关闭菜单项的位置
	helpItem->setPosition(Point(750,280));
	//创建菜单对象
	Menu *helpMenu = Menu::create(helpItem, NULL);
	//设置菜单位置
	helpMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(helpMenu,BTN_LEVEL);

	//about
	MenuItemImage *aboutItem = MenuItemImage::create
	(
			PIC_PATH+std::string("start_red_btn.png"),
			PIC_PATH+std::string("start_red_btn_down.png"),
		   CC_CALLBACK_1(WelcomeLayer::menuAboutCallback, this)
	);
	//设置关闭菜单项的位置
	aboutItem->setPosition(Point(750,160));
	//创建菜单对象
	Menu *aboutMenu = Menu::create(aboutItem, NULL);
	//设置菜单位置
	aboutMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(aboutMenu,BTN_LEVEL);

	//exitGame
	MenuItemImage *exitItem = MenuItemImage::create
	(
			PIC_PATH+std::string("choose_game_exit_btn.png"),
			PIC_PATH+std::string("choose_game_exit_btn.png"),
		   CC_CALLBACK_1(WelcomeLayer::menuExitCallback, this)
	);
	//设置关闭菜单项的位置
	exitItem->setPosition(Point(60,485));
	//创建菜单对象
	Menu *exitMenu = Menu::create(exitItem, NULL);
	//设置菜单位置
	exitMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(exitMenu,BTN_LEVEL);
}
//背景音乐
void WelcomeLayer::backMusic()
{
	//加载背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic
	(
		(SOUND_PATH+string("MusicEx_Welcome.mp3")).c_str()
	);
	//播放背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		(SOUND_PATH+string("MusicEx_Welcome.mp3")).c_str(),
		true
	);
}
void WelcomeLayer::menuStartCallback(Ref* sender)
{
	/*
	 * 玩家点击开始游戏后，游戏连接服务器，告诉服务器进入玩家已进入游戏界面
	 */
	if(!BNSocketUtil::connectFlag)
	{
		//连接服务器IP fs
		BNSocketUtil::connect("192.168.253.1",9999);
	}
	removeChild(startMenu);
	startImage->setVisible(true);
	msgLabel->setVisible(true);
	//设置定时回调
	schedule(schedule_selector(WelcomeLayer::jinruGame), 0.5);
}
void WelcomeLayer::gotoGame()
{

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	psm->goGame();
}
void WelcomeLayer::jinruGame(float ft)
{
	//若连接到服务器，则切换界面并停止音乐
	if(BNSocketUtil::connectFlag)
	{
		this->unschedule(SEL_SCHEDULE(&WelcomeLayer::jinruGame));
		MenuItemImage *gotoGame=MenuItemImage::create(
				PIC_PATH+std::string("go_game_btn.png"),
				PIC_PATH+std::string("go_game_btn_down.png"),
			CC_CALLBACK_0(WelcomeLayer::gotoGame,this)
			);
			gotoGame->setPosition(Point(750,400));

			Menu *gotoGameMenu=Menu::create(gotoGame,NULL);

			gotoGameMenu->setPosition(Point::ZERO);
			this->addChild(gotoGameMenu,BTN_LEVEL);

			startImage->setVisible(false);
			msgLabel->setVisible(false);
	}
}
//游戏帮助
void WelcomeLayer::menuHelpCallback(Ref* sender)
{
	psm->goHelp();
}
//游戏关于
void WelcomeLayer::menuAboutCallback(Ref* sender)
{
	psm->goAbout();
}
//退出游戏
void WelcomeLayer::menuExitCallback(Ref* sender)
{
	Director::getInstance()->end();
}
