#include "SelectLayer.h"
#include "BNSocketUtil.h"
#include "Constant.h"
#include "AppMacros.h"

bool SelectLayer::init()
{
	//调用父类的初始化
	if(!Layer::init())
	{
		return false;
	}
	//添加背景
	this->addChild(TankSceneManager::getGround(),0);
	initWaitMenu();
	initTexture();

	//创建新线程执行网络功能
	new std::thread(&BNSocketUtil::threadConnectTask,"192.168.191.1", 59421);

	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//定时检测服务器是否要求执行操作
	sched->schedule(SEL_SCHEDULE(&SelectLayer::update), this, 0.01, false);

	return true;
}

void SelectLayer::initTexture()
{
	levelFrame = new SpriteFrame*[4];
	levelFrame[0] = SpriteFrame::create(PIC_PATH+std::string("oneP.png"),Rect(0,0,320,200));
	levelFrame[1] = SpriteFrame::create(PIC_PATH+std::string("oneP_select.png"),Rect(0,0,320,200));
	levelFrame[2] = SpriteFrame::create(PIC_PATH+std::string("twoP.png"),Rect(0,0,320,200));
	levelFrame[3] = SpriteFrame::create(PIC_PATH+std::string("twoP_select.png"),Rect(0,0,320,200));
	for(int i=0; i<4; i++)
	{
		levelFrame[i]->retain();
	}
}

void SelectLayer::initWaitMenu()
{
	//创建正在连接的图片精灵
	waitSprite = Sprite::create(PIC_PATH+std::string("wait.png"));
	waitSprite->setPosition(Point(480,270));
	this->addChild(waitSprite,2,0);
	waitSprite->runAction(RepeatForever::create(Blink::create(0.8f,1)));

	//创建菜单项
	MenuItemImage* backItem = MenuItemImage::create
	(
			PIC_PATH+std::string("back_menu.png"),
			PIC_PATH+std::string("back_menu_select.png"),
			CC_CALLBACK_0(SelectLayer::toMenuLayer,this)
	);
	backItem->setAnchorPoint(Point(0,1));
	backItem->setPosition(Point(20,520));

	//创建菜单容器
	menu = Menu::create(backItem,NULL);
	//设置惨淡原点位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,1);
}

void SelectLayer::update()
{
	if(BNSocketUtil::okFlag==1)
	{
		BNSocketUtil::okFlag = 2;
		toSelectMenu();
		showLevel();
		BNSocketUtil::okFlag = 0;
	}
	if(BNSocketUtil::selectFlag==1)
	{
		BNSocketUtil::selectFlag = 2;
		showLevel();
		BNSocketUtil::selectFlag = 0;
	}
	if(BNSocketUtil::stateFlag==1&&Constant::state==2&&Constant::redOrGreen==0)
	{
		BNSocketUtil::stateFlag = 2;
		tsm->toGameLayer();
		BNSocketUtil::stateFlag = 0;
	}
}

void SelectLayer::showLevel()
{
	if(Constant::level==0)
	{
		firstItem->setNormalSpriteFrame(levelFrame[1]);
		firstItem->setSelectedSpriteFrame(levelFrame[1]);
		secondItem->setNormalSpriteFrame(levelFrame[2]);
		secondItem->setSelectedSpriteFrame(levelFrame[2]);
	}else if(Constant::level==1)
	{
		firstItem->setNormalSpriteFrame(levelFrame[0]);
		firstItem->setSelectedSpriteFrame(levelFrame[0]);
		secondItem->setNormalSpriteFrame(levelFrame[3]);
		secondItem->setSelectedSpriteFrame(levelFrame[3]);
	}
}

void SelectLayer::toSelectMenu()
{
	//移除等待连接标志位
	this->removeChildByTag(0);

	//创建关卡选择按钮
	MenuItemImage* levelItem1 = MenuItemImage::create
	(
			PIC_PATH+std::string("one.png"),
			PIC_PATH+std::string("one_select.png"),
			PIC_PATH+std::string("one_select.png"),
			CC_CALLBACK_0(SelectLayer::sendLevel,this,0)
	);
	levelItem1->setPosition(Point(280,110));
	MenuItemImage* levelItem2 = MenuItemImage::create
	(
			PIC_PATH+std::string("two.png"),
			PIC_PATH+std::string("two_select.png"),
			PIC_PATH+std::string("two_select.png"),
			CC_CALLBACK_0(SelectLayer::sendLevel,this,1)
	);
	levelItem2->setPosition(Point(680,110));
	firstItem = MenuItemImage::create
	(
			PIC_PATH+std::string("oneP.png"),
			PIC_PATH+std::string("oneP.png"),
			CC_CALLBACK_0(SelectLayer::sendLevel,this,0)
	);
	firstItem->setPosition(Point(280,280));
	secondItem = MenuItemImage::create
	(
			PIC_PATH+std::string("twoP.png"),
			PIC_PATH+std::string("twoP.png"),
			CC_CALLBACK_0(SelectLayer::sendLevel,this,1)
	);
	secondItem->setPosition(Point(680,280));

	//判断是否为房主并分别设置
	if(Constant::redOrGreen!=1)
	{
		//设置非房主玩家的菜单按钮为不可用
		levelItem1->setEnabled(false);
		levelItem2->setEnabled(false);
		firstItem->setEnabled(false);
		secondItem->setEnabled(false);
	}
	else
	{
		//创建开始菜单按钮
		MenuItemImage* startGame = MenuItemImage::create
		(
				PIC_PATH+std::string("start_game.png"),
				PIC_PATH+std::string("start_game_select.png"),
				CC_CALLBACK_0(SelectLayer::toGameLayer,this)
		);
		startGame->setAnchorPoint(Point(1,1));
		startGame->setPosition(Point(940,520));
		menu->addChild(startGame);
	}

	//将新建的菜单项添加进菜单
	menu->addChild(firstItem);
	menu->addChild(secondItem);
	menu->addChild(levelItem1);
	menu->addChild(levelItem2);
}

void SelectLayer::sendLevel(int level)
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	//发送选择关卡的信息
	BNSocketUtil::sendStr("<#SELECT#>",10);
	BNSocketUtil::sendInt(level);
}

void SelectLayer::toGameLayer()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	BNSocketUtil::sendStr("<#LEVEL#>",9);
	BNSocketUtil::sendInt(Constant::level);
	tsm->toGameLayer();
}

void SelectLayer::toMenuLayer()
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	BNSocketUtil::closeConnect();
}

SelectLayer::~SelectLayer()
{
	for(int i=0;i<4;i++)
	{
		levelFrame[i]->release();
	}
}

