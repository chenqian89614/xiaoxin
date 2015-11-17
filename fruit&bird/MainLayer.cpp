#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include<time.h>

using namespace cocos2d;

//初始化音乐播放
bool MainLayer::musicFlag = true;
//初始化音效播放
bool MainLayer::soundFlag = true;

bool MainLayer::init()
{
	//调用父类的初始化
	if ( !CCLayer::init() )
	{
		return false;
	}
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();

	int i = random();

	if(i%2==0)
	{
		//创建背景
		backGround = Sprite::create("morning.png");
	}else
	{
		//创建背景
		backGround = Sprite::create("night.png");
	}
	//设置锚点
	backGround->setAnchorPoint(Point(0, 0));
	//设置精灵对象的位置
	backGround->setPosition(Point(origin.x,origin.y + visibleSize.height - backGround->getContentSize().height));
	//将精灵添加到布景中
	this->addChild(backGround, 0);

	if(musicFlag)
	{
		//播放背景音乐
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("playscene.mp3", true);
	}

	//创建地面精灵1
	Sprite* floor = Sprite::create("floor.png");
	//设置锚点
	floor->setAnchorPoint(Point(0, 0));
	//设置精灵对象位置
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	//游戏开始
	MenuItemImage* gameItem = MenuItemImage::create(
		"start.png",
		"start_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack0, this) //点击时执行的回调方法
	);
	gameItem->setPosition(Point(150, 600));
	//排行榜
	MenuItemImage* rankItem = MenuItemImage::create(
		"rank.png",
		"rank_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack1, this) //点击时执行的回调方法
	);
	rankItem->setPosition(Point(390, 600));
	//设置
	MenuItemImage* setItem = MenuItemImage::create(
		"set.png",
		"set_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack2, this) //点击时执行的回调方法
	);
	setItem->setPosition(Point(150, 450));
	//帮助
	MenuItemImage* helpItem = MenuItemImage::create(
		"help.png",
		"help_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack3, this) //点击时执行的回调方法
	);
	helpItem->setPosition(Point(390, 450));
	//
	MenuItemImage* aboutItem = MenuItemImage::create(
		"about.png",
		"about_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack4, this) //点击时执行的回调方法
	);
	aboutItem->setPosition(Point(150, 300));
	//
	MenuItemImage* exitItem = MenuItemImage::create(
		"exit.png",
		"exit_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack5, this) //点击时执行的回调方法
	);
	exitItem->setPosition(Point(390, 300));

	Menu* menu = Menu::create(gameItem, rankItem, setItem, helpItem, aboutItem, exitItem, NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	//创建一个网络节点对象
	effectNode = NodeGrid::create();
	//将网格节点添加到布景
	this->addChild(effectNode, 10);
	//创建标题精灵
	Sprite* title = Sprite::create("title.png");
	//设置精灵位置
	title->setPosition(Point(270, 800));
	//将精灵添加到布景中
	effectNode->addChild(title, 12);
	//关闭深度检测
	Director::getInstance()->setDepthTest(false);
	//涟漪
	effectNode->runAction(RepeatForever::create(Ripple3D::create(2.0f, Size(32, 24),Point(270, 800), 360, 2, 5)));

	return true;
}
//生成随机数
int MainLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%4;
	return number;
}
void MainLayer::initTitle()
{
	Sprite* title = Sprite::create("title.png");
	//设置精灵位置
	title->setPosition(Point(270, 800));
	//将精灵添加到布景中
	this->addChild(title, 10);
	this->removeChild(effectNode);
}
void MainLayer::menuCallBack0(Ref* pSender)
{
	initTitle();
	sceneManager->goToGameScene();
}
void MainLayer::menuCallBack1(Ref* pSender)
{
	initTitle();
	sceneManager->goToRankBirdScene();
}
void MainLayer::menuCallBack2(Ref* pSender)
{
	initTitle();
	sceneManager->goToSetScene();
}
void MainLayer::menuCallBack3(Ref* pSender)
{
	initTitle();
	sceneManager->goToHelpScene();
}
void MainLayer::menuCallBack4(Ref* pSender)
{
	initTitle();
	sceneManager->goToAboutScene();
}
void MainLayer::menuCallBack5(Ref* pSender)
{
	//结束游戏
	Director::getInstance()->end();
}
