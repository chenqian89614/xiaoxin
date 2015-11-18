#include "SetLayer.h"
#include "SimpleAudioEngine.h"
#include "WelcomeLayer.h"
#include "ChoiceLayer.h"
#include "SetUtil.h"
#include "AppConstant.h"
using namespace std;
using namespace cocos2d;
int SetLayer::bgIdx=0;
int SetLayer::mark1Idx=0;
int SetLayer::mark2Idx=0;
SetLayer::~SetLayer()
{

}

bool SetLayer::init()
{
	//���ø���ĳ�ʼ��
	if ( !Layer::init() )
	{
		return false;
	}
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();
	createBgSp(bgIdx);//���������������
	//���ñ�������λ��
	bgSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bgSprite,0);


	createRound1MarkSp(mark1Idx);//������һ�ر�Ǿ������
	round1Marksprite->setScale(1.6);//���þ���������ű�
	if(bgIdx==0)//��������ѡ��ϵ��
	{
		round1Marksprite->setPosition(Point(origin.x+200,origin.y+610));//���þ���λ��
	}else if(bgIdx==1)
	{
		round1Marksprite->setPosition(Point(origin.x+350,origin.y+560));//���þ���λ��
	}else if(bgIdx==2)
	{
		round1Marksprite->setPosition(Point(origin.x+200,origin.y+570));//���þ���λ��
	}
	bgSprite->addChild(round1Marksprite,0);//����һ�ر�Ǿ�����ӵ�ѡ�ر�ǵװ徫����

	createRound2MarkSp(mark2Idx);//�����ڶ��ر�Ǿ������
	round2Marksprite->setScale(1.6);//���þ���������ű�
	if(bgIdx==0)
	{
		round2Marksprite->setPosition(Point(origin.x+320,origin.y+350));//���þ���λ��
	}else if(bgIdx==1)
	{
		round2Marksprite->setPosition(Point(origin.x+200,origin.y+270));//���þ���λ��
	}else if(bgIdx==2)
	{
		round2Marksprite->setPosition(Point(origin.x+350,origin.y+260));//���þ���λ��
	}
	bgSprite->addChild(round2Marksprite,0);//���ڶ��ر�Ǿ�����ӵ�ѡ�ر�ǵװ徫����

	auto backItem = MenuItemImage::create
	(
			pic_PATH+"back.png",
			pic_PATH+"back.png",
			CC_CALLBACK_0(SetLayer::onBack, this)//���ʱִ�еĻص�����
	);
	backItem->setPosition(
			Point(
				origin.x - backItem->getContentSize().width/2+520,	//X����
				origin.y -backItem->getContentSize().height/2+940		//Y����
			)
			);
	//�����˵�����
	auto backMenu = Menu::create(backItem, NULL);
	//���ò˵�λ��
	backMenu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(backMenu, 1);

	//�������㴥������
	EventListenerTouchOneByOne* guanQia = EventListenerTouchOneByOne::create();
	//�����´�����
	guanQia->setSwallowTouches(true);
	//��ʼ����ʱ�ص�enterGame����
	guanQia->onTouchBegan = CC_CALLBACK_2(SetLayer::enterGame, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(guanQia, round1Marksprite);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(guanQia->clone(), round2Marksprite);

	 if(ChoiceLayer::isMusic==false)
	{
		wl->pauseBgMusic();//��ͣ���ű�������
	}else
	{
		wl->resumeBgMusic();//�������ű���
	}
	return true;
}
bool SetLayer::enterGame(Touch* touch,Event* event)
{
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//��ȡ��ǰ����
	auto location = target->convertToNodeSpace(touch->getLocation());
	//��ȡ����Ĵ�С
	auto size = target->getContentSize();
	//����һ�����ζ������С�뾫����ͬ
	auto rect = Rect(0, 0, size.width, size.height);
	if(rect.containsPoint(location)&&target==round1Marksprite)
	{
		if(ChoiceLayer::isSound)
		{
			wl->playSwitchSound();//�����л���Ч
		}
		switch(bgIdx)
		{
		case 0:
			gsm->gogameScene();
			break;
		case 1:
			gsm->goRound3Scene();
			break;
		case 2:
			gsm->goRound5Scene();
			break;
		}

		return true;
	}else if(rect.containsPoint(location)&&target==round2Marksprite)
	{
		if(ChoiceLayer::isSound)
		{
			wl->playSwitchSound();//�����л���Ч
		}
//		gsm->goRound2Scene();
		switch(bgIdx)
		{
		case 0:
			gsm->goRound2Scene();
			break;
		case 1:
			gsm->goRound4Scene();
			break;
		case 2:
			gsm->goRound6Scene();
			break;

		}
		return true;
	}else
	{
		return false;
	}
	return true;
}

void SetLayer::onBack()
{
	if(ChoiceLayer::isSound)
	{
		wl->playSwitchSound();//�����л���Ч
	}
	gsm->goLevelScene();
}
