#include "HelpLayer.h"
#include "Constant.h"
#include "AppMacros.h"

bool HelpLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//添加背景
	this->addChild(TankSceneManager::getGround(),0);
	initView();
	initSprite();

	//配置触控
	auto listenerTouch = EventListenerTouchOneByOne::create();		//创建一个单点触摸监听
	listenerTouch->setSwallowTouches(true);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onMyTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(HelpLayer::onMyTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onMyTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	return true;
}

void HelpLayer::initSprite()
{
	helpPic = new Sprite*[5];
	for(int i=0; i<5; i++)
	{
		char ch[16];
		sprintf(ch,"help%d.png",i+1);
		helpPic[i] = Sprite::create(PIC_PATH+std::string(ch));
		helpPic[i]->setPosition(Point(480+960*i,255));
		helpPic[i]->setScale(0.9f);
		this->addChild(helpPic[i]);
		Sprite *pointTemp = Sprite::create(PIC_PATH+std::string("levels.png"),Rect(20,0,20,20));
		pointTemp->setPosition(Point(480+(i-2)*50,30));
		this->addChild(pointTemp);
	}
	helpPoint = Sprite::create(PIC_PATH+std::string("levels.png"),Rect(0,0,20,20));
	helpPoint->setPosition(Point(380,30));
	this->addChild(helpPoint);
}

void HelpLayer::initView()
{
	//返回菜单
	MenuItemImage* backItem = MenuItemImage::create
	(
			PIC_PATH+std::string("back_menu.png"),
			PIC_PATH+std::string("back_menu_select.png"),
			CC_CALLBACK_0(HelpLayer::toMenuLayer,this)
	);
	backItem->setAnchorPoint(Point(0,1));
	backItem->setPosition(Point(20,520));
	Menu* menu = Menu::create(backItem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
}

bool HelpLayer::onMyTouchBegan(Touch* touch, Event* event)
{
	offset=helpPic[0]->getPosition().x;
	saveX=touch->getLocation().x;
	this->cleanup();
	return true;
}

void HelpLayer::onMyTouchMoved(Touch* touch, Event* event)
{
	int dX=offset+(touch->getLocation().x-saveX)*5/3;
	for(int i=0; i<5; i++)
	{
		helpPic[i]->setPosition(Point(960*i+dX,255));
	}
}

void HelpLayer::onMyTouchEnded(Touch* touch, Event* event)
{
	offset=offset+(touch->getLocation().x-saveX)*5/3;
	saveX=0;
	if(offset>480)
	{
		offset=480;

	}else if(offset<-3360)
	{
		offset=-3360;
	}else
	{
		offset=-((960-offset)/960)*960+480;
		CCLOG("%d",offset);
	}
	for(int i=0; i<5; i++)
	{
		helpPic[i]->runAction(MoveTo::create(0.2f,Point(960*i+offset,255)));
	}
	helpPoint->runAction(MoveTo::create(0.2f,Point(480+(((480-offset)/960)-2)*50,30)));
}

void HelpLayer::toMenuLayer()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	tsm->toMenuLayer();
}
