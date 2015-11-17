#include "AboutLayer.h"

using namespace cocos2d;

bool AboutLayer::init()
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

	//创建背景
	Sprite* backGround = Sprite::create("morning.png");
	//设置锚点
	backGround->setAnchorPoint(Point(0, 0));
	//设置精灵对象的位置
	backGround->setPosition(Point(origin.x,origin.y + visibleSize.height - backGround->getContentSize().height));
	//将精灵添加到布景中
	this->addChild(backGround, 0);

	//创建地面精灵
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

	//创建关于精灵
	Sprite* about = Sprite::create("aboutP.png");
	//设置精灵对象位置
	about->setPosition(Point(visibleSize.width/2, visibleSize.height/2 + 100));
	this->addChild(about);

	//返回主菜单
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(AboutLayer::menuCallback, this) //点击时执行的回调方法
	);
	menuItem->setPosition(Point(80, 50));
	Menu* menu = Menu::create(menuItem, NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	return true;
}

void AboutLayer::menuCallback(Ref* pSender)
{
	sceneManager->goToMainScene();
}
