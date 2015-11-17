#include "HelpLayer.h"

using namespace cocos2d;

//实现HelpLayer类中的init方法，初始化布景
bool HelpLayer::init()
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
	//创建背景
	Sprite* background = Sprite::create("morning.png");
	//设置锚点
	background->setAnchorPoint(Point(0, 0));
	//设置精灵对象的位置
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//将精灵添加到布景中
	this->addChild(background, 0);

	//创建地面精灵1
	Sprite* floor = Sprite::create("floor.png");
	//设置锚点
	floor->setAnchorPoint(Point(0, 0));
	//设置精灵对象位置
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	//设置地面滚动
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	Sprite* back = Sprite::create("helpBack.png");
	back->setPosition(Point(visibleSize.width/2, visibleSize.height/2 - 5));
	this->addChild(back, 0);

	for(int i=0;i<4;i++)
	{
		sp[i] = Sprite::create(StringUtils::format("help%d.png",i));
		sp[i]->setPosition(180+i*360, 320);
		if(i!=0)
		{
			sp[i]->runAction(FadeOut::create(0));
		}
	}

	//返回菜单
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(HelpLayer::menuCallBack, this) //点击时执行的回调方法

	);
	menuItem->setPosition(Point(270,50));
	Menu* menu = Menu::create(menuItem, NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	Point pp[4];
	pp[0] = Point(0, 0);
	pp[1] = Point(360, 0);
	pp[2] = Point(360, 640);
	pp[3] = Point(0, 640);
	Color4F green(0, 1, 0, 0);
	Color4F red(1, 0, 0, 0);
	//创建剪裁用DrawNode
	DrawNode* shape = DrawNode::create();
	shape->drawPolygon(pp ,4, green, 1,red);
	//创建剪裁节点
	ClippingNode* clipper=ClippingNode::create();
	//设置剪裁模板
	clipper->setStencil(shape);
	//设置被剪裁节点
	for(int i=0; i<4; i++)
	{
		clipper->addChild(sp[i],0);
	}
	clipper->setPosition(Point(90, 160));
	//将被剪裁节点放置到层中
	this->addChild(clipper, 0);

	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onTouchBegan, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, clipper);

	return true;
}
void HelpLayer::onTouchEnded(Touch* touch, Event* event)
{
	do{
		if(moveFlag)
		{
			break;
		}
		//获取的当前触摸的对象，并转化为精灵类型
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//获取当前坐标
		auto location = target->convertToNodeSpace(touch->getLocation());
		endPoint =  location;
		if(beganPoint.x-endPoint.x>=30)
		{
			index++;
			if(index>3)
			{
				index=0;
				sp[0]->setPosition(Point(540,320));
				sp[0]->runAction(FadeOut::create(0));
			}
			sp[index]->setPosition(Point(540,320));
			moveFlag=true;
			for(int i=0;i<3;i++)
			{
				if(i == index)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(-360,0)),
						FadeIn::create(1),
						NULL
					));
				}
				if(i == index-1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(-360,0)),
						FadeOut::create(1),
						NULL
					));
				}
				if(i == index + 1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(-360,0)),
						FadeOut::create(1),
						NULL
					));
				}
			}
			sp[3]->runAction(
					Sequence::create(
					Spawn::create(MoveBy::create(1,Point(-360,0)), FadeIn::create(1),NULL),
					CallFunc::create(CC_CALLBACK_0(HelpLayer::setmoveFlag, this)),
					NULL
			));

		}else if(endPoint.x-beganPoint.x>=30)
		{
			index--;
			if(index<0)
			{
				index = 3;
				sp[3]->setPosition(Point(-180,320));
			}
			sp[index]->setPosition(Point(-180,320));
			moveFlag=true;
			for(int i=3;i>0;i--)
			{
				if(i == index)
				{
					sp[i]->runAction(
						Spawn::create(
							MoveBy::create(1,Point(360,0)),
							FadeIn::create(1),
							NULL
						));
				}
				if(i == index + 1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(360,0)),
						FadeOut::create(1),
						NULL
					));
				}
				if(i == index - 1)
				{
					sp[i]->runAction(
						Spawn::create(
						MoveBy::create(1,Point(360,0)),
						FadeOut::create(1),
						NULL
					));
				}
			}
			sp[0]->runAction(
					Sequence::create(
					Spawn::create(MoveBy::create(1,Point(360,0)), FadeIn::create(1),NULL),
					CallFunc::create(CC_CALLBACK_0(HelpLayer::setmoveFlag, this)),
					NULL
			));
		}
	}while(0);
}
bool HelpLayer::onTouchBegan(Touch* touch, Event* event)
{
	if(moveFlag)
	{
		return false;
	}
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	beganPoint = location;
	return true;
}
void HelpLayer::setmoveFlag()
{
	moveFlag=false;
	if(beganPoint.x-endPoint.x>=30)
	{
		if(index+1>3)
		{
			sp[0]->setPosition(Point(540,320));
		}else
		{
			sp[index+1]->setPosition(Point(540,320));
		}
	}

	if(endPoint.x-beganPoint.x>=30)
	{
		if(index-1<0)
		{
			sp[3]->setPosition(Point(-180,320));
		}else
		{
			sp[index-1]->setPosition(Point(-180,320));
		}
	}
}
void HelpLayer::menuCallBack(Ref* pSender)
{
	sceneManager->goToMainScene();

}
