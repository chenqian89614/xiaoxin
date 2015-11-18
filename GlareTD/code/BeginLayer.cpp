#include "BeginLayer.h"
#include "AppDelegate.h"
#include "ChooseLayer.h"

#include "cocos2d.h"

#define pic_PRE_PATH_BeginLayer string("")
using namespace cocos2d;

//实现BeginLayer类中的init方法，初始化布景
bool BeginLayer::init()
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

    //创建一个精灵对象，包含background.png图片
    auto sprite = Sprite::create(pic_PRE_PATH_BeginLayer+string("background.png"));
    //设置精灵对象的位置
    sprite->setPosition(Point(400,240));
    //将精灵添加到布景中
    this->addChild(sprite,BACKGROUND_LEVEL_CGQ);
	//加载音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sound/sf_button_press.mp3"
	);
    
	//创建“开始游戏”精灵
	MenuItemImage *onePlayer = MenuItemImage::create(
        pic_PRE_PATH_BeginLayer+string("onePlayer.png"),("onePlayer3.png"),
		CC_CALLBACK_1(BeginLayer::oneMode, this)
     );
	//设置精灵菜单按钮的位置
	onePlayer->setPosition(Point(270,240));

	//创建“退出”精灵
	MenuItemImage *twoPlayer = MenuItemImage::create(
        pic_PRE_PATH_BeginLayer+string("exit.png"),("exit.png"),
		CC_CALLBACK_1(BeginLayer::twoMode, this)
	);
	//设置菜单按钮的位置
	twoPlayer->setPosition(Point(660,240));

	//创建“最高分”的精灵
	MenuItemImage *set = MenuItemImage::create(
        pic_PRE_PATH_BeginLayer+string("seclect.png"),("seclect3.png"),
		CC_CALLBACK_1(BeginLayer::setSence, this)
	 );
	//设置最高分菜单按钮的位置
	set->setPosition(Point(530,240));

	//创建”帮助“精灵
	MenuItemImage *help = MenuItemImage::create(
		pic_PRE_PATH_BeginLayer+string("help.png"),("help33.png"),
		CC_CALLBACK_1(BeginLayer::helpSence, this)
	);
	//设置帮助菜单按钮的位置
	help->setPosition(Point(400,240));

	//创建主菜单中的4个菜单对象
	pMenu = Menu::create(onePlayer,twoPlayer,set,help,NULL);
	//设置菜单的位置
	pMenu->setPosition(Point(0,0));
	//将菜单添加到布景中
	this->addChild(pMenu,GAME_LEVEL_CGQ);

	return true;
}

void BeginLayer::oneMode(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//切换到关卡选择界面
	man->toChooseLayer();
}
void BeginLayer::twoMode(Object* pSender)
{
	//播放音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//退出游戏
	Director::getInstance()->end();
}
void BeginLayer::setSence(Object* pSender)
{
	//播放音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//最高分界面
	man->toAchieveLayer();
}
void BeginLayer::helpSence(Object* pSender)
{
	//播放音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sf_button_press.mp3");
	//帮助界面
	man->toHelpLayer();
}
