#include "GameLayer.h"
#include <time.h>

using namespace cocos2d;

//ʵ��GameLayer���е�init��������ʼ������
bool GameLayer::init()
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
	//������ñ���
	int i = random();
	if(i%2 == 0)
	{
		//��������
		background = Sprite::create("morning.png");
	}else
	{
		//��������
		background = Sprite::create("night.png");
	}
	//����ê��
	background->setAnchorPoint(Point(0, 0));
	//���þ�������λ��
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//��������ӵ�������
	this->addChild(background, 0);

	//�������澫��1
	Sprite* floor1 = Sprite::create("floor.png");
	//����ê��
	floor1->setAnchorPoint(Point(0, 0));
	//���þ������λ��
	floor1->setPosition(Point(origin.x, origin.y));
	this->addChild(floor1);
	//���õ������
	floor1->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	//����һ������ڵ����
	effectNode = NodeGrid::create();
	//������ڵ���ӵ�����
	this->addChild(effectNode, 11);
	//�������⾫��
	Sprite* title = Sprite::create("title.png");
	//���þ���λ��
	title->setPosition(Point(270, 800));
	//��������ӵ�������
	effectNode->addChild(title, 12);
	//�ر���ȼ��
	Director::getInstance()->setDepthTest(false);
	//����
	effectNode->runAction(RepeatForever::create(Ripple3D::create(2.0f, Size(64,48),Point(270, 800), 360, 2, 10)));

	//С����Ϸ�˵�
	MenuItemImage* birdItem = MenuItemImage::create(
		"Bird.png",
		"Bird_off.png",
		 CC_CALLBACK_1(GameLayer::menuCallback0, this) //���ʱִ�еĻص�����
	);
	birdItem->setPosition(Point(visibleSize.width/2 - 50, visibleSize.height/2 + 100));

	//ˮ����Ϸ�˵�
	MenuItemImage* fruitItem = MenuItemImage::create(
		"Fruit.png",
		"Fruit_off.png",
		 CC_CALLBACK_1(GameLayer::menuCallback1, this) //���ʱִ�еĻص�����
	);
	fruitItem->setPosition(Point(visibleSize.width/2 + 50, visibleSize.height/2 - 100));

	//�������˵�
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(GameLayer::menuCallback2, this) //���ʱִ�еĻص�����
	);
	menuItem->setPosition(Point(80, 50));
	Menu* menu = Menu::create(menuItem, birdItem, fruitItem, NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	return true;
}
//���������
int GameLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%6;
	return number;
}
void GameLayer::initTitle()
{
	//�������⾫��
	Sprite* title = Sprite::create("title.png");
	//���þ���λ��
	title->setPosition(Point(270, 800));
	//��������ӵ�������
	this->addChild(title, 12);
	//ɾ������ڵ�
	this->removeChild(effectNode);
}
//
void GameLayer::menuCallback0(Ref* pSender)
{
	initTitle();
	sceneManager->goToFlappyScene(0);
}
//
void GameLayer::menuCallback1(Ref* pSender)
{
	initTitle();
	sceneManager->goToSquishyScene(0);
}
//
void GameLayer::menuCallback2(Ref* pSender)
{
	sceneManager->goToMainScene();
}
