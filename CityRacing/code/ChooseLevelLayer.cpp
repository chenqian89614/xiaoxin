#include "ChooseLevelLayer.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include "Constant.h"
using namespace cocos2d;


int ChooseLevelLayer::currLevel = -1 ;

bool ChooseLevelLayer::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
		return false;
	}
	//���⾫��
	Sprite* ttSprite = Sprite::create("title.png");
	ttSprite->setPosition(Point(270,780));
	this->addChild(ttSprite,1);

	bgSpriteO = Sprite::create("scene1.jpg");
	bgSpriteO->setPosition(270,480);
	this->addChild(bgSpriteO,BGZORDER-1);

	bgSpriteT = Sprite::create("scene1.jpg");
	bgSpriteT->setPosition(270,-480);
	this->addChild(bgSpriteT,BGZORDER);

	for(int i=0;i<3;i++)
	{
		gate0Sprite[i] = Sprite::create(StringUtils::format("gate%d.png",i));
		gate0Sprite[i]->setPosition(Point(110+i*160,550));
		this->addChild(gate0Sprite[i],BGZORDER+1);

		int lock = UserDefault::getInstance()->getIntegerForKey(
				Constant::uesrGKLock[i].c_str());
		if(lock == 0)
		{
			Sprite* lockSp = Sprite::create("lock.png");
			lockSp->setPosition(Point(110+i*160,550));
			this->addChild(lockSp,BGZORDER+2);
		}
	}
	Sprite* txtund = Sprite::create("txtund.png");
	txtund->setPosition(Point(270,300));
	this->addChild(txtund,BGZORDER+1);

	taskLabel = Label::createWithTTF("\u70b9\u51fb\u5173\u5361\u67e5\u770b\u4efb\u52a1","FZKATJW.ttf",48);
	taskLabel->setPosition(Point(250,67));
	txtund->addChild(taskLabel,1);

	//������һ���˵���
	MenuItemImage* backMenu = MenuItemImage::create(
			   "goback.png",	//ƽʱ��ͼƬ
			   "gobackp.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(ChooseLevelLayer::backMenuCallback, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	backMenu->setPosition(Point(40,920));
	//�����˵�����
	auto menu = Menu::create(backMenu,NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(menu, 1);

	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//����������ʱ�ص�
	sched->scheduleSelector(SEL_SCHEDULE(&ChooseLevelLayer::bgUpdate),this,0.005,false);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ChooseLevelLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChooseLevelLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,gate0Sprite[0]);
	for(int i=1;i<3;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),gate0Sprite[i]);
	}
	return true;
}
void ChooseLevelLayer::backMenuCallback()
{
	crsm->goStartLyaer();
}
bool ChooseLevelLayer::onTouchBegan(Touch* touch, Event* event)
{
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	spriteTouch = static_cast<Sprite*>(event->getCurrentTarget());
	spriteTouch->retain();
	//��ȡ��ǰ����
	auto location = spriteTouch->convertToNodeSpace(touch->getLocation());
	//��ȡ����Ĵ�С
	auto size = spriteTouch->getContentSize();
	//����һ�����ζ������С�뾫����ͬ
	auto rect = Rect(0, 0, size.width, size.height);
	//�жϴ������Ƿ���Ŀ��ķ�Χ��
	if(rect.containsPoint(location)){
		for(int i=0;i<3;i++)
		{
			if(spriteTouch==gate0Sprite[i])
			{
				selectGK = i;
				break;
			}
		}
		selectLevel(spriteTouch);
		return true;
	}
	return false;
}
void ChooseLevelLayer::selectLevel(Sprite* spriteTouch)
{
	if(spriteTouch==gate0Sprite[0])
	{
		int lock = UserDefault::getInstance()->getIntegerForKey(
								Constant::uesrGKLock[0].c_str());
		if(levelFocus == 0&&lock == 1)
		{
			ChooseLevelLayer::currLevel = 0;
			crsm->goChooseCarLayer();
		}
		taskLabel->setString("\u83b7\u53d620\u91d1\u5e01");
		levelFocus = 0;
	}else if(spriteTouch==gate0Sprite[1])
	{
		int lock = UserDefault::getInstance()->getIntegerForKey(
										Constant::uesrGKLock[1].c_str());
		if(levelFocus == 1&&lock == 1)
		{
			ChooseLevelLayer::currLevel = 1;
			crsm->goChooseCarLayer();
		}

		taskLabel->setString("\u81f3\u5c11\u5f00\u51fa2000\u7c73\u4ee5\u5916");
		levelFocus = 1;
	}else if(spriteTouch==gate0Sprite[2])
	{
		int lock = UserDefault::getInstance()->getIntegerForKey(
										Constant::uesrGKLock[2].c_str());
		if(levelFocus == 2&&lock == 1)
		{
			ChooseLevelLayer::currLevel = 2;
			crsm->goChooseCarLayer();
		}
		taskLabel->setString("\u4e0d\u649e\u51fb\u654c\u8f66");
		levelFocus = 2;
	}

}
void ChooseLevelLayer::onTouchEnded(Touch* touch, Event* event)
{
	spriteTouch->runAction(ScaleTo::create(0.1,1));
}
void ChooseLevelLayer::bgUpdate()
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
