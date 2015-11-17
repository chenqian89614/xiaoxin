#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include<time.h>

using namespace cocos2d;

//��ʼ�����ֲ���
bool MainLayer::musicFlag = true;
//��ʼ����Ч����
bool MainLayer::soundFlag = true;

bool MainLayer::init()
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

	int i = random();

	if(i%2==0)
	{
		//��������
		backGround = Sprite::create("morning.png");
	}else
	{
		//��������
		backGround = Sprite::create("night.png");
	}
	//����ê��
	backGround->setAnchorPoint(Point(0, 0));
	//���þ�������λ��
	backGround->setPosition(Point(origin.x,origin.y + visibleSize.height - backGround->getContentSize().height));
	//��������ӵ�������
	this->addChild(backGround, 0);

	if(musicFlag)
	{
		//���ű�������
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("playscene.mp3", true);
	}

	//�������澫��1
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

	//��Ϸ��ʼ
	MenuItemImage* gameItem = MenuItemImage::create(
		"start.png",
		"start_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack0, this) //���ʱִ�еĻص�����
	);
	gameItem->setPosition(Point(150, 600));
	//���а�
	MenuItemImage* rankItem = MenuItemImage::create(
		"rank.png",
		"rank_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack1, this) //���ʱִ�еĻص�����
	);
	rankItem->setPosition(Point(390, 600));
	//����
	MenuItemImage* setItem = MenuItemImage::create(
		"set.png",
		"set_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack2, this) //���ʱִ�еĻص�����
	);
	setItem->setPosition(Point(150, 450));
	//����
	MenuItemImage* helpItem = MenuItemImage::create(
		"help.png",
		"help_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack3, this) //���ʱִ�еĻص�����
	);
	helpItem->setPosition(Point(390, 450));
	//
	MenuItemImage* aboutItem = MenuItemImage::create(
		"about.png",
		"about_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack4, this) //���ʱִ�еĻص�����
	);
	aboutItem->setPosition(Point(150, 300));
	//
	MenuItemImage* exitItem = MenuItemImage::create(
		"exit.png",
		"exit_off.png",
		 CC_CALLBACK_1(MainLayer::menuCallBack5, this) //���ʱִ�еĻص�����
	);
	exitItem->setPosition(Point(390, 300));

	Menu* menu = Menu::create(gameItem, rankItem, setItem, helpItem, aboutItem, exitItem, NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	//����һ������ڵ����
	effectNode = NodeGrid::create();
	//������ڵ���ӵ�����
	this->addChild(effectNode, 10);
	//�������⾫��
	Sprite* title = Sprite::create("title.png");
	//���þ���λ��
	title->setPosition(Point(270, 800));
	//��������ӵ�������
	effectNode->addChild(title, 12);
	//�ر���ȼ��
	Director::getInstance()->setDepthTest(false);
	//����
	effectNode->runAction(RepeatForever::create(Ripple3D::create(2.0f, Size(32, 24),Point(270, 800), 360, 2, 5)));

	return true;
}
//���������
int MainLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%4;
	return number;
}
void MainLayer::initTitle()
{
	Sprite* title = Sprite::create("title.png");
	//���þ���λ��
	title->setPosition(Point(270, 800));
	//��������ӵ�������
	this->addChild(title, 10);
	this->removeChild(effectNode);
}
void MainLayer::menuCallBack0(Ref* pSender)
{
	initTitle();
	sceneManager->goToGameScene();
}
void MainLayer::menuCallBack1(Ref* pSender)
{
	initTitle();
	sceneManager->goToRankBirdScene();
}
void MainLayer::menuCallBack2(Ref* pSender)
{
	initTitle();
	sceneManager->goToSetScene();
}
void MainLayer::menuCallBack3(Ref* pSender)
{
	initTitle();
	sceneManager->goToHelpScene();
}
void MainLayer::menuCallBack4(Ref* pSender)
{
	initTitle();
	sceneManager->goToAboutScene();
}
void MainLayer::menuCallBack5(Ref* pSender)
{
	//������Ϸ
	Director::getInstance()->end();
}
