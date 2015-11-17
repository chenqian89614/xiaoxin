#include "GameLayer.h"
#include <time.h>

using namespace cocos2d;

//实现GameLayer类中的init方法，初始化布景
bool GameLayer::init()
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
	//随机设置背景
	int i = random();
	if(i%2 == 0)
	{
		//创建背景
		background = Sprite::create("morning.png");
	}else
	{
		//创建背景
		background = Sprite::create("night.png");
	}
	//设置锚点
	background->setAnchorPoint(Point(0, 0));
	//设置精灵对象的位置
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//将精灵添加到布景中
	this->addChild(background, 0);

	//创建地面精灵1
	Sprite* floor1 = Sprite::create("floor.png");
	//设置锚点
	floor1->setAnchorPoint(Point(0, 0));
	//设置精灵对象位置
	floor1->setPosition(Point(origin.x, origin.y));
	this->addChild(floor1);
	//设置地面滚动
	floor1->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	//创建一个网络节点对象
	effectNode = NodeGrid::create();
	//将网格节点添加到布景
	this->addChild(effectNode, 11);
	//创建标题精灵
	Sprite* title = Sprite::create("title.png");
	//设置精灵位置
	title->setPosition(Point(270, 800));
	//将精灵添加到布景中
	effectNode->addChild(title, 12);
	//关闭深度检测
	Director::getInstance()->setDepthTest(false);
	//涟漪
	effectNode->runAction(RepeatForever::create(Ripple3D::create(2.0f, Size(64,48),Point(270, 800), 360, 2, 10)));

	//小鸟游戏菜单
	MenuItemImage* birdItem = MenuItemImage::create(
		"Bird.png",
		"Bird_off.png",
		 CC_CALLBACK_1(GameLayer::menuCallback0, this) //点击时执行的回调方法
	);
	birdItem->setPosition(Point(visibleSize.width/2 - 50, visibleSize.height/2 + 100));

	//水果游戏菜单
	MenuItemImage* fruitItem = MenuItemImage::create(
		"Fruit.png",
		"Fruit_off.png",
		 CC_CALLBACK_1(GameLayer::menuCallback1, this) //点击时执行的回调方法
	);
	fruitItem->setPosition(Point(visibleSize.width/2 + 50, visibleSize.height/2 - 100));

	//返回主菜单
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(GameLayer::menuCallback2, this) //点击时执行的回调方法
	);
	menuItem->setPosition(Point(80, 50));
	Menu* menu = Menu::create(menuItem, birdItem, fruitItem, NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	return true;
}
//生成随机数
int GameLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%6;
	return number;
}
void GameLayer::initTitle()
{
	//创建标题精灵
	Sprite* title = Sprite::create("title.png");
	//设置精灵位置
	title->setPosition(Point(270, 800));
	//将精灵添加到布景中
	this->addChild(title, 12);
	//删除网络节点
	this->removeChild(effectNode);
}
//
void GameLayer::menuCallback0(Ref* pSender)
{
	initTitle();
	sceneManager->goToFlappyScene(0);
}
//
void GameLayer::menuCallback1(Ref* pSender)
{
	initTitle();
	sceneManager->goToSquishyScene(0);
}
//
void GameLayer::menuCallback2(Ref* pSender)
{
	sceneManager->goToMainScene();
}
