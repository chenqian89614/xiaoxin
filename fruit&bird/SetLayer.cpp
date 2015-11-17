#include "SetLayer.h"
#include "SimpleAudioEngine.h"
#include "MainLayer.h"
#include <time.h>

using namespace cocos2d;
using namespace std;
using namespace ui;

bool SetLayer::init()
{
	//���ø���ĳ�ʼ��
	if ( !CCLayer::init() )
	{
		return false;
	}
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();
	//��������
	Sprite* backGround = Sprite::create("morning.png");
	//����ê��
	backGround->setAnchorPoint(Point(0, 0));
	//���þ�������λ��
	backGround->setPosition(Point(origin.x,origin.y + visibleSize.height - backGround->getContentSize().height));
	//��������ӵ�������
	this->addChild(backGround, 0);

	//�������澫��
	Sprite* floor1 = Sprite::create("floor.png");
	//����ê��
	floor1->setAnchorPoint(Point(0, 0));
	//���þ������λ��
	floor1->setPosition(Point(origin.x, origin.y));
	this->addChild(floor1);
	floor1->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	Sprite* pauseBack = Sprite::create("setBack.png");
	pauseBack->setPosition(Point(270, 500));
	this->addChild(pauseBack, 10);

	//���ְ�ť
	Sprite* music = Sprite::create("music.png");
	pauseBack->addChild(music, 1);
	music->setPosition(Point(100, 220));

	CheckBox* checkMusic = CheckBox::create(
			"sound_on.png",
			"sound_off.png",
			"sound_off.png",
			"sound_stop.png",
			"sound_stop.png"
	);
	pauseBack->addChild(checkMusic, 1);
	checkMusic->setPosition(Point(320, 220));
	checkMusic->setSelectedState(!MainLayer::musicFlag);
	checkMusic->addEventListener(CC_CALLBACK_2(SetLayer::selectedEvent0, this));
	//��Ч��ť
	Sprite* sound = Sprite::create("sound.png");
	pauseBack->addChild(sound, 1);
	sound->setPosition(Point(100, 140));

	CheckBox* checkSound = CheckBox::create(
			"sound_on.png",
			"sound_off.png",
			"sound_off.png",
			"sound_stop.png",
			"sound_stop.png"
	);
	pauseBack->addChild(checkSound, 1);
	checkSound->setPosition(Point(320, 140));
	checkSound->setSelectedState(!MainLayer::soundFlag);
	checkSound->addEventListener(CC_CALLBACK_2(SetLayer::selectedEvent1, this));

	//�������˵�
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(SetLayer::menuCallBack, this) //���ʱִ�еĻص�����
	);
	menuItem->setPosition(Point(200, 60));

	Menu* menu = Menu::create(menuItem, NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	pauseBack->addChild(menu,1);


	//����һ������ڵ����
	NodeGrid* effectNode = NodeGrid::create();
	//������ڵ���ӵ�����
	this->addChild(effectNode, 11);
	//�������⾫��
	Sprite* title = Sprite::create("title.png");
	//��ȡ���⾫��ߴ��С
	Size size = title->getContentSize();
	//���þ���λ��
	title->setPosition(Point(270, 800));
	//��������ӵ�������
	effectNode->addChild(title, 1);
	//�ر���ȼ��
	Director::getInstance()->setDepthTest(false);
	//����
	effectNode->runAction(RepeatForever::create(Ripple3D::create(2.0f, Size(64,48),Point(270, 800), 360, 2, 10)));

	return true;

}
void SetLayer::menuCallBack(Ref* pSender)
{
	sceneManager->goToMainScene();
}
void SetLayer::selectedEvent0(Ref* pSender,CheckBox::EventType type)
{
    switch (type)
    {
        case CheckBox::EventType::SELECTED:
        	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			MainLayer::musicFlag = false;
            break;
        case CheckBox::EventType::UNSELECTED:
        	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			MainLayer::musicFlag = true;
            break;
        default:
            break;
    }
}
void SetLayer::selectedEvent1(Ref* pSender,CheckBox::EventType type)
{
    switch (type)
    {
        case CheckBox::EventType::SELECTED:
        	MainLayer::soundFlag = false;
            break;
        case CheckBox::EventType::UNSELECTED:
        	MainLayer::soundFlag = true;
            break;
        default:
            break;
    }
}
