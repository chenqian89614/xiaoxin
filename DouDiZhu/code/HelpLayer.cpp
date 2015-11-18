#include "HelpLayer.h"
#include "AppMacros.h"
#include "WelcomeLayer.h"
#include <string>

using namespace cocos2d;


HelpLayer::~HelpLayer()
{
}

bool HelpLayer::init()
{
	//调用父类的初始化
	if ( !Layer::init())
	{
		return false;
	}

	MenuItemImage* backItem = MenuItemImage::create
	(
		PIC_PATH+std::string("choose_game_exit_btn.png"),
		PIC_PATH+std::string("choose_game_exit_btn.png"),
		CC_CALLBACK_0(HelpLayer::goBack, this)
	);
	backItem->setPosition(Point(40,510));
	//创建菜单对象
	auto backMenu = Menu::create(backItem, NULL);
	//设置菜单位置
	backMenu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(backMenu,5);

	bgSprite = Sprite::create(PIC_PATH+std::string("background.png"));
	//设置精灵对象的位置
	bgSprite->setPosition(Point(480,270));
	//将精灵添加到布景中
	this->addChild(bgSprite,2);

	for(int i=0;i<5;i++)
	{
		spIntro[i] = Sprite::create((PIC_PATH+StringUtils::format("help%d.png",i)).c_str());//创建显示精灵
		spIntro[i]->setAnchorPoint(Point(0,0));
		spIntro[i]->setPosition(160+i*960,90);
		TBGPoint[i] = spIntro[i]->getPosition();
		this->addChild(spIntro[i],3);
	}

	for(int i=0;i<5;i++)
	{
		if(currIntroIndex==i)
		{
			bSprite[i]=Sprite::create(PIC_PATH+std::string("white.png"));
		}else
		{
			bSprite[i]=Sprite::create(PIC_PATH+std::string("black.png"));
		}
		bSprite[i]->setPosition(Point(300+i*90,60));
		this->addChild(bSprite[i],3);
	}
	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onMyTouchBegan, this);
	//开始触摸时回调onTouchMoved方法
	listenerTouch->onTouchMoved = CC_CALLBACK_2(HelpLayer::onMyTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onMyTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch,this);

	return true;
}


bool HelpLayer::onMyTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(	event->getCurrentTarget());//获取当前触摸对象，并转化为精灵类型
	currPoint = touch->getLocation();
	Point location = target->convertToNodeSpace(touch->getLocation());//获取当前坐标
	auto size = target->getContentSize();			//获取精灵的大小
	auto rect = Rect(0, 0, size.width, size.height);//创建一个矩形对象，其大小与精灵相同
	if( rect.containsPoint(location)){	//判断触摸点是否在目标的范围内
		return true;
	}else{
		return false;
	}
}

void HelpLayer::onMyTouchMoved(Touch *touch, Event *event)
{
	for(int i=0;i<5;i++)
	{
		spIntro[i]->setPosition(
				TBGPoint[i].x+(touch->getLocation().x-currPoint.x),
				TBGPoint[i].y
		);
	}
}

void HelpLayer::onMyTouchEnded(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(				//获取的当前触摸的对象，并转化为精灵类型
									event->getCurrentTarget());
	Point location = target->convertToNodeSpace(touch->getLocation());//获取当前坐标
	for(int i=0;i<5;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}

	float jlMin = 10000;
	int currIndex = 0;
	for(int i=0;i<5;i++)
	{
		if(fabs(TBGPoint[i].x)<jlMin)
		{
			jlMin = fabs(TBGPoint[i].x);
			currIndex = i;
			currIntroIndex = i;
		}
	}

	int tempNum = currIndex;
	for(int i=0;i<3;i++)
	{
		if(tempNum == 5)
		{
			tempNum = 0;
		}
		spIntro[tempNum]->setPosition(
						160+i*960,
						spIntro[tempNum]->getPosition().y
				);
		tempNum ++;
	}
	tempNum = currIndex;
	for(int i=0;i<3;i++)
	{
		if(tempNum == -1)
		{
			tempNum = 4;
		}
		spIntro[tempNum]->setPosition(
						160-i*960,
						spIntro[tempNum]->getPosition().y
				);
		tempNum --;
	}

	for(int i=0;i<5;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}
	setBWPosition();
}

void HelpLayer::setBWPosition()
{
	int tempNUm = 1;
	for(int i=0;i<5;i++)
	{
		if(i == currIntroIndex)
		{
			bSprite[0]->setPosition(Point(300+i*90,60));
		}else
		{
			bSprite[tempNUm]->setPosition(Point(300+i*90,60));
			tempNUm ++;
		}
	}
}

void HelpLayer::goBack()
{
	psm->goWelcome();
}

