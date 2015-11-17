#include "AboutLayer.h"

using namespace cocos2d;

bool AboutLayer::init()
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
	Sprite* floor = Sprite::create("floor.png");
	//����ê��
	floor->setAnchorPoint(Point(0, 0));
	//���þ������λ��
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	//�������ھ���
	Sprite* about = Sprite::create("aboutP.png");
	//���þ������λ��
	about->setPosition(Point(visibleSize.width/2, visibleSize.height/2 + 100));
	this->addChild(about);

	//�������˵�
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(AboutLayer::menuCallback, this) //���ʱִ�еĻص�����
	);
	menuItem->setPosition(Point(80, 50));
	Menu* menu = Menu::create(menuItem, NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	return true;
}

void AboutLayer::menuCallback(Ref* pSender)
{
	sceneManager->goToMainScene();
}
