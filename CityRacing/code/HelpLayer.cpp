#include "cocos2d.h"
#include "AppMacros.h"
#include "HelpLayer.h"
#include "CityRacingSceneManager.h"
#include "AppMacros.h"

using namespace cocos2d;

bool HelpLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	bgSpriteO = Sprite::create("scene1.jpg");
	bgSpriteO->setPosition(270,480);
	this->addChild(bgSpriteO,BGZORDER-1);

	bgSpriteT = Sprite::create("scene1.jpg");
	bgSpriteT->setPosition(270,-480);
	this->addChild(bgSpriteT,BGZORDER);

	Sprite* bg = Sprite::create("MenuBg.png");
	bg->setPosition(270,480);
	this->addChild(bg,2);

	//创建下一个菜单项
	MenuItemImage* backMenu = MenuItemImage::create(
			   "goback.png",	//平时的图片
			   "gobackp.png",	//选中时的图片
			   CC_CALLBACK_0(HelpLayer::backMenuCallback, this) //点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	backMenu->setPosition(Point(40,920));

	//创建菜单对象
	auto menu = Menu::create(backMenu,NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(menu, 4);

	for(int i=0;i<4;i++)
	{
		spIntro[i] = Sprite::create(StringUtils::format("tu%d.png",i+1));
		spIntro[i]->setAnchorPoint(Point(0,0));
		spIntro[i]->setPosition(0+i*350,0);
		TBGPoint[i] = spIntro[i]->getPosition();
	}

	for(int i=6;i>=4;i--)
	{
		spIntro[i] = Sprite::create(StringUtils::format("tu%d.png",i+1));
		spIntro[i]->setAnchorPoint(Point(0,0));
		spIntro[i]->setPosition(0-(7-i)*350,0);
		TBGPoint[i] = spIntro[i]->getPosition();
	}

	Point pp[4];
	pp[0] = Point(0, 0);
	pp[1] = Point(350, 0);
	pp[2] = Point(350, 622);
	pp[3] = Point(0, 622);
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
	for(int i=0; i<7; i++)
	{
		clipper->addChild(spIntro[i],1);
	}
	clipper->setPosition(Point(90,200));
	//将被剪裁节点放置到层中
	this->addChild(clipper, 4);

	Sprite* kSprite = Sprite::create("kuang.png");
	kSprite->setPosition(Point(265,510));
	this->addChild(kSprite,4);

	for(int i=0;i<7;i++)
	{
		if(i == currIntroIndex)
		{
			bSprite[i] = Sprite::create("white.png");
		}else
		{
			bSprite[i] = Sprite::create("blank.png");
		}
		bSprite[i]->setPosition(Point(180+i*30,100));
		this->addChild(bSprite[i],4);
	}

	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onTouchBegan, this);
	//开始触摸时回调onTouchMoved方法
	listenerTouch->onTouchMoved = CC_CALLBACK_2(HelpLayer::onTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, spIntro[0]);
	for(int i=1;i<7;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch->clone(), spIntro[i]);
	}


	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//背景滚屏定时回调
	sched->scheduleSelector(SEL_SCHEDULE(&HelpLayer::bgUpdate),this,0.005,false);

	return true;
}
void HelpLayer::setBWPosition()
{
	int tempNUm = 1;
	for(int i=0;i<7;i++)
	{
		if(i == currIntroIndex)
		{
			bSprite[0]->setPosition(Point(180+i*30,100));
		}else
		{
			bSprite[tempNUm]->setPosition(Point(180+i*30,100));
			tempNUm ++;
		}

	}
}
void HelpLayer::backMenuCallback()
{
	crsm->goStartLyaer();
}
bool HelpLayer::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(	//获取当前触摸对象，并转化为精灵类型
						event->getCurrentTarget());
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
void HelpLayer::onTouchMoved(Touch* touch, Event* event)
{
	for(int i=0;i<7;i++)
	{
		spIntro[i]->setPosition(
				TBGPoint[i].x+(touch->getLocation().x-currPoint.x),
				TBGPoint[i].y
		);
	}
}
void HelpLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(				//获取的当前触摸的对象，并转化为精灵类型
								event->getCurrentTarget());
	Point location = target->convertToNodeSpace(touch->getLocation());//获取当前坐标
	for(int i=0;i<7;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}
	float jlMin = MAX_INT;
	int currIndex = 0;
	for(int i=0;i<7;i++)
	{
		if(fabs(TBGPoint[i].x)<jlMin)
		{
			jlMin = fabs(TBGPoint[i].x);
			currIndex = i;
			currIntroIndex = i;
		}
	}
	int tempNum = currIndex;
	for(int i=0;i<4;i++)
	{
		if(tempNum == 7)
		{
			tempNum = 0;
		}
		spIntro[tempNum]->setPosition(
						0+i*350,
						spIntro[tempNum]->getPosition().y
				);
		tempNum ++;
	}
	tempNum = currIndex;
	for(int i=0;i<4;i++)
	{
		if(tempNum == -1)
		{
			tempNum = 6;
		}
		spIntro[tempNum]->setPosition(
						0-i*350,
						spIntro[tempNum]->getPosition().y
				);
		tempNum --;
	}

	for(int i=0;i<7;i++)
	{
		TBGPoint[i] = spIntro[i]->getPosition();
	}
	setBWPosition();
}
void HelpLayer::bgUpdate()
{
	if(bgSpriteO->getPosition().y==1440)
	{
		bgSpriteO->setPosition(Point(270,-480));
	}else
	{
		bgSpriteO->setPosition(Point(270,bgSpriteO->getPosition().y+1));
	}

	if(bgSpriteT->getPosition().y==1440)
	{
		bgSpriteT->setPosition(Point(270,-480));
	}else
	{
		bgSpriteT->setPosition(Point(270,bgSpriteT->getPosition().y+1));
	}
}
