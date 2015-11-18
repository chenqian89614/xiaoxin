#include "SelectLayer.h"
#include "BNSocketUtil.h"
#include "Constant.h"
#include "AppMacros.h"

bool SelectLayer::init()
{
	//���ø���ĳ�ʼ��
	if(!Layer::init())
	{
		return false;
	}
	//��ӱ���
	this->addChild(TankSceneManager::getGround(),0);
	initWaitMenu();
	initTexture();

	//�������߳�ִ�����繦��
	new std::thread(&BNSocketUtil::threadConnectTask,"192.168.191.1", 59421);

	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//��ʱ���������Ƿ�Ҫ��ִ�в���
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
	//�����������ӵ�ͼƬ����
	waitSprite = Sprite::create(PIC_PATH+std::string("wait.png"));
	waitSprite->setPosition(Point(480,270));
	this->addChild(waitSprite,2,0);
	waitSprite->runAction(RepeatForever::create(Blink::create(0.8f,1)));

	//�����˵���
	MenuItemImage* backItem = MenuItemImage::create
	(
			PIC_PATH+std::string("back_menu.png"),
			PIC_PATH+std::string("back_menu_select.png"),
			CC_CALLBACK_0(SelectLayer::toMenuLayer,this)
	);
	backItem->setAnchorPoint(Point(0,1));
	backItem->setPosition(Point(20,520));

	//�����˵�����
	menu = Menu::create(backItem,NULL);
	//���òҵ�ԭ��λ��
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
	//�Ƴ��ȴ����ӱ�־λ
	this->removeChildByTag(0);

	//�����ؿ�ѡ��ť
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

	//�ж��Ƿ�Ϊ�������ֱ�����
	if(Constant::redOrGreen!=1)
	{
		//���÷Ƿ�����ҵĲ˵���ťΪ������
		levelItem1->setEnabled(false);
		levelItem2->setEnabled(false);
		firstItem->setEnabled(false);
		secondItem->setEnabled(false);
	}
	else
	{
		//������ʼ�˵���ť
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

	//���½��Ĳ˵�����ӽ��˵�
	menu->addChild(firstItem);
	menu->addChild(secondItem);
	menu->addChild(levelItem1);
	menu->addChild(levelItem2);
}

void SelectLayer::sendLevel(int level)
{
	Constant::playEffect((SOUND_PATH+std::string("select.wav")).c_str());
	//����ѡ��ؿ�����Ϣ
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

