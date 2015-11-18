#include "ControlLayer.h"
#include "AppMacros.h"
#include "Constant.h"
#include "BNSocketUtil.h"
#include "PauseLayer.h"

USING_NS_CC;

bool ControlLayer::init()
{
	//���ø���ĳ�ʼ��
	if(!Layer::init())
	{
		return false;
	}
	initJoy();
	initView();
	state=2;
	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//��ʱ�ص�update�ķ���
	sched->schedule(SEL_SCHEDULE(&ControlLayer::sendKey), this, 0.05, false);
	sched->schedule(SEL_SCHEDULE(&ControlLayer::update), this, 0.01, false);
	return true;
}

void ControlLayer::getGameLayer(GameLayer *temp)
{
	gameLayer=temp;
}

void ControlLayer::initView()
{
	//��������ֵͼ��
	Sprite *healthSprite=Sprite::create(PIC_PATH+std::string("redbox.png"));
	healthSprite->setAnchorPoint(Point(0,1));
	healthSprite->setPosition(Point(30,510));
	this->addChild(healthSprite);

	//��������ֵ��ֵ
	healthLabel=LabelAtlas::create("0",PIC_PATH+std::string("nums.png"),30,50,'0');
	healthLabel->setAnchorPoint(Point(0,1));
	healthLabel->setPosition(Point(80,510));
	this->addChild(healthLabel);

	//��������ͼ��
	Sprite *scoreSprite=Sprite::create(PIC_PATH+std::string("score_icon.png"));
	scoreSprite->setAnchorPoint(Point(0,1));
	scoreSprite->setPosition(Point(450,510));
	this->addChild(scoreSprite);

	//��������ͼ��
	scoreLabel=LabelAtlas::create("0",PIC_PATH+std::string("nums.png"),30,50,'0');
	scoreLabel->setAnchorPoint(Point(0,1));
	scoreLabel->setPosition(Point(500,510));
	this->addChild(scoreLabel);

	//������ͣ�˵���
	MenuItemImage* pauseItem = MenuItemImage::create
	(
		PIC_PATH+std::string("pause.png"),
		PIC_PATH+std::string("pause_select.png"),
		CC_CALLBACK_0(ControlLayer::sendPause,this)
	);
	pauseItem->setAnchorPoint(Point(1,1));
	pauseItem->setPosition(Point(960,540));

	//�����˵�
	menu = Menu::create(pauseItem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
}

void ControlLayer::sendPause()
{
	BNSocketUtil::sendStr("<#STATE#>",9);
	BNSocketUtil::sendInt(4);
}

void ControlLayer::toPauseLayer()//��ת����ͣ����
{
	menu->setEnabled(false);
	Scene *scene=(Scene*)(this->getParent());
	PauseLayer *pauseLayer=PauseLayer::create();
	scene->addChild(pauseLayer,2,2);
}

void ControlLayer::initJoy()
{
	//�Զ���ҡ�����
	tankStick=BNJoyStick::create(PIC_PATH+std::string("direction.png"),PIC_PATH+std::string("center.png"));
	//����ҡ��ͼƬ��ê��
	tankStick->setAnchorPoint(Point(0.5f, 0.5f));
	//����ҡ��ͼƬ�Ĵ�С
	tankStick->setScale(0.8f);
	//����λ��
	tankStick->setPosition(Point(130,115));
	//��ҡ����ӵ�������
	this->addChild(tankStick);

	//�Զ���ҡ�����
	gunStick=BNJoyStick::create(PIC_PATH+std::string("direction.png"),PIC_PATH+std::string("center.png"));
	//����ҡ��ͼƬ��ê��
	gunStick->setAnchorPoint(Point(0.5f, 0.5f));
	//����ҡ��ͼƬ�Ĵ�С
	gunStick->setScale(0.8f);
	//����λ��
	gunStick->setPosition(Point(830,115));
	//��ҡ����ӵ�������
	this->addChild(gunStick);
}

void ControlLayer::update()
{
	if(BNSocketUtil::dataFlag==1)//��������ֵ�ͷ�������
	{
		BNSocketUtil::dataFlag = 2;
		if(Constant::redOrGreen==0)
		{
			healthLabel->setString(StringUtils::toString(Constant::redHealth));
		}else
		{
			healthLabel->setString(StringUtils::toString(Constant::greenHealth));
		}
		scoreLabel->setString(StringUtils::toString(Constant::score));
		BNSocketUtil::dataFlag = 0;
	}
	if(BNSocketUtil::stateFlag==1)//������Ϸ״̬
	{
		BNSocketUtil::stateFlag = 2;
		if(state==2 && Constant::state==4)
		{
			toPauseLayer();
		}else if(state==4 && Constant::state==2)
		{
			backGameLayer();
		}else if(Constant::state==3)
		{
			Sprite *lose=Sprite::create(PIC_PATH+std::string("lose.png"));
			lose->setPosition(Point(480,270));
			this->addChild(lose);
            Constant::playEffect((PIC_PATH+std::string("lose.mp3")).c_str());
			ActionInterval *ai=Sequence::create
			(
				Blink::create(3.0f, 3),
				CallFunc::create(this,callfunc_selector(ControlLayer::toMenuLayer)),
				NULL
			);
			lose->runAction(ai);
		}else if(Constant::state==0)
		{
			Sprite *win=Sprite::create(PIC_PATH+std::string("win.png"));
			win->setPosition(Point(480,270));
			this->addChild(win);
			ActionInterval *ai=Sequence::create
			(
				Blink::create(3.0f, 3),
				CallFunc::create(this,callfunc_selector(ControlLayer::toMenuLayer)),
				NULL
			);
			win->runAction(ai);
		}
		state=Constant::state;
		BNSocketUtil::stateFlag = 0;
	}
}

void ControlLayer::toMenuLayer()
{
	tsm->toMenuLayer();
}

void ControlLayer::backGameLayer()
{
	menu->setEnabled(true);
	Scene *scene=(Scene*)(this->getParent());
	scene->removeChildByTag(2);
}

void ControlLayer::sendKey()
{
	if(tankStick->touchFlag||gunStick->touchFlag)
	{
		BNSocketUtil::sendStr("<#KEY#>",7);
		BNSocketUtil::sendFloat(tankStick->vx);
		BNSocketUtil::sendFloat(-tankStick->vy);
		BNSocketUtil::sendFloat(gunStick->vx);
		BNSocketUtil::sendFloat(-gunStick->vy);
	}
}
