#include "DialogLayer.h"
#include "AppMacros.h"
#include "GameSceneManager.h"
#include "GameLayer.h"

//初始化声音标志位为true
bool DialogLayer::isMusic = true;
//初始化粒子效果的标志位为true
bool DialogLayer::isParticle = true;

using namespace cocos2d;
//初始化方法
bool DialogLayer::init()
{
	//初始化显示暂停界面的标志位为false
    bool bRet = false;
    do {
    	//设置屏幕的透明度
        CC_BREAK_IF(!LayerColor::initWithColor(ccc4(0, 0, 0, 160),800,480));
        //调用initDialog方法
        this->initDialog();
        //将标志位设为true
        bRet = true;
    }
    //判断
    while (0);

    return bRet;
}

void DialogLayer::initDialog()
{
	//加载音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_button_press.mp3"
	);
	//创建一个精灵对象，包含暂停游戏字样，充当背景
    Sprite* plabel = Sprite::create("plabel.png");
    //设置精灵对象的位置
    plabel->setPosition(Point(105, 240));
    //将背景精灵添加到布景中
    this->addChild(plabel, BACKGROUND_LEVEL_CGQ+1);

    //叉号——1
	x_1 = Sprite::create("x.png");
	//设置精灵对象的位置
	x_1->setPosition(Point(400,150));
	if(isParticle)
	{
		x_1->setVisible(false);
	}else{
		x_1->setVisible(true);
	}
	//将X号精灵对象添加到布景中
	this->addChild(x_1, DASHBOARD_LEVEL_CGQ+1);

	//叉号——2
	x_2 = Sprite::create("x.png");
	//设置精灵对象的位置
	x_2->setPosition(Point(400,330));
	if(isMusic)
	{
		x_2->setVisible(false);
	}else{
		x_2->setVisible(true);
	}

	//将X号精灵对象添加到布景中
	this->addChild(x_2, DASHBOARD_LEVEL_CGQ+1);

	//创建继续游戏的菜单按钮
    MenuItemImage *resume = MenuItemImage::create
	(
		 "resume.png", 		//平时的图片
		 "resume3.png",  	//选中时的图片
		 //点击菜单按钮时执行的回调方法
		 CC_CALLBACK_1(DialogLayer::menuCallbackContinueGame,this)
	);
	//设置继续游戏菜单按钮的位置
    resume->setPosition(Point(250,240));

    //创建表示粒子效果的精灵
	MenuItemImage *par = MenuItemImage::create
	(
		 "p.png", 	//平时的图片
		 "p.png",  	//选中时的图片
		 //点击时执行的回调方法
		 CC_CALLBACK_0(DialogLayer::parused,this)
	);
	//设置表示粒子效果的菜单按钮的位置
	par->setPosition(Point(400,150));

	//创建表示声音的精灵
	MenuItemImage *sound = MenuItemImage::create
	(
		 "s.png", 	//平时的图片
		 "s.png" , 	//选中时的图片
		 //点击时执行的回调方法
		 CC_CALLBACK_0(DialogLayer::sounded,this)
	);
	//设置声音菜单按钮的位置
	sound->setPosition(Point(400,330));

    //创建回主菜单的精灵
   	MenuItemImage *saveExit = MenuItemImage::create
   	(
   		"exit.png", 	//平时的图片
   		"exit3.png",  	//选中时的图片
   		//点击时执行的回调方法
   		CC_CALLBACK_1(DialogLayer::homeSence,this)
   	);
   	//设置退出菜单按钮的位置
  	saveExit->setPosition(Point(550,240));

	//创建菜单对象
	m_pMenu = Menu::create(resume,saveExit,sound,par, NULL);
	//设置菜单位置
	m_pMenu->setPosition(Point(0,0));
	//将菜单按钮添加到布景中
	this->addChild(m_pMenu, DASHBOARD_LEVEL_CGQ);
}

//去主菜单场景的回调方法
void DialogLayer::homeSence(Object* pSender)
{
	//播放音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//游戏暂停的标志为设为false
	GameLayer::isPause=false;
	//把sprite从屏幕上删除，并把它执行的动作也删除
	this->removeFromParentAndCleanup(true);
	//获取Director（导演）
	Director* pDirector = Director::getInstance();
	//先切换到继续场景
	pDirector->resume();
	//再切换到主菜单布景
	man->toBeginLayer();
}

//声音的回掉方法
void DialogLayer::sounded()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	isMusic = !isMusic;
	if(isMusic)
	{
		x_2->setVisible(false);
	}else{
		x_2->setVisible(true);
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

//paused的回掉方法
void DialogLayer::parused()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	isParticle=!isParticle;
	x_1->setVisible(!isParticle);
}

//继续游戏的回调方法
void DialogLayer::menuCallbackContinueGame(Object *pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//游戏暂停的标志位设为false
	GameLayer::isPause=false;
	//把sprite从屏幕上删除，并把它执行的动作也删除
    this->removeFromParentAndCleanup(true);
    //获取CCDirector（导演）
	Director* director = Director::getInstance();
	//切换到继续游戏场景
	director->resume();
	//判断声音的标志位
	if(isMusic)
	{
		//继续声音
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

