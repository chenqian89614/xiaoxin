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
	//���ø���ĳ�ʼ��
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
	//�����˵�����
	auto backMenu = Menu::create(backItem, NULL);
	//���ò˵�λ��
	backMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(backMenu,5);

	bgSprite = Sprite::create(PIC_PATH+std::string("background.png"));
	//���þ�������λ��
	bgSprite->setPosition(Point(480,270));
	//��������ӵ�������
	this->addChild(bgSprite,2);

	for(int i=0;i<5;i++)
	{
		spIntro[i] = Sprite::create((PIC_PATH+StringUtils::format("help%d.png",i)).c_str());//������ʾ����
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
	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onMyTouchBegan, this);
	//��ʼ����ʱ�ص�onTouchMoved����
	listenerTouch->onTouchMoved = CC_CALLBACK_2(HelpLayer::onMyTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(HelpLayer::onMyTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch,this);

	return true;
}


bool HelpLayer::onMyTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(	event->getCurrentTarget());//��ȡ��ǰ�������󣬲�ת��Ϊ��������
	currPoint = touch->getLocation();
	Point location = target->convertToNodeSpace(touch->getLocation());//��ȡ��ǰ����
	auto size = target->getContentSize();			//��ȡ����Ĵ�С
	auto rect = Rect(0, 0, size.width, size.height);//����һ�����ζ������С�뾫����ͬ
	if( rect.containsPoint(location)){	//�жϴ������Ƿ���Ŀ��ķ�Χ��
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
	auto target = static_cast<Sprite*>(				//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
									event->getCurrentTarget());
	Point location = target->convertToNodeSpace(touch->getLocation());//��ȡ��ǰ����
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

