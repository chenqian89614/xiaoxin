#include "RankFruitLayer.h"

using namespace cocos2d;
using namespace std;

bool RankFruitLayer::init()
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

	//�������а񱳾�
	Sprite* rank = Sprite::create("rankBackground.png");
	//���þ���λ��
	rank->setPosition(Point(270, 530));
	//��ӵ�������
	this->addChild(rank, 1);
	//��������
	Sprite* title = Sprite::create("rankFruit.png");
	//���þ���λ��
	title->setPosition(Point(270, 850));
	//��ӵ�������
	this->addChild(title, 1);

	//
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(RankFruitLayer::menuCallBack0, this) //���ʱִ�еĻص�����
	);
	menuItem->setPosition(Point(80, 50));
	//
	MenuItemImage* nextItem = MenuItemImage::create(
		"back.png",
		"back_off.png",
		 CC_CALLBACK_1(RankFruitLayer::menuCallBack1, this) //���ʱִ�еĻص�����
	);
	nextItem->setPosition(Point(460, 50));

	Menu* menu = Menu::create(menuItem, nextItem, NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	//��ʾ����
	int *tempFruit = new int[5];
	load();
	//��ȡ������
	for(int i = 0; i<5; i++)
	{
		string score;
		string number = StringUtils::format("%d", (i+1));
		tempFruit[i] = atoi(scoreFruit[i].c_str());
		if(tempFruit[i] == 0)
		{
			score = "-";
		}else
		{
			score = scoreFruit[i];
		}
		labels = Label::createWithTTF (number, "FZKATJW.ttf", 60, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		rank->addChild(labels);
		labels->setPosition(Point(100, 280-(50*i)));
		labels->enableOutline(Color4B(187, 187, 187, 255),2);
		labels = Label::createWithTTF (score, "FZKATJW.ttf", 60, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		rank->addChild(labels);
		labels->setPosition(Point(315, 280-(50*i)));
		labels->enableOutline(Color4B(187, 187, 187, 255),2);
	}
    return true;
}
//��¼����
void RankFruitLayer::save(int newScore)
{
	string score;
	string oldScore;
	int *tempFruit = new int[5];
	load();
	//��ȡ������
	for(int i = 0; i<5; i++)
	{
		tempFruit[i] = atoi(scoreFruit[i].c_str());
	}
	//���·��������������Ƚ�
	for(int i = 4; i>=0; i--)
	{
		if(newScore>=tempFruit[i])
		{
			score = StringUtils::format("%d", newScore);
			if(i!=4)
			{
				oldScore = StringUtils::format("%d", tempFruit[i]);
				UserDefault::getInstance()->setStringForKey(StringUtils::format("f%d", (i+1)).c_str() , oldScore);
			}
			UserDefault::getInstance()->setStringForKey(StringUtils::format("f%d", i).c_str(), score);
		}else
		{
			break;
		}
	}
	//ˢ��
	UserDefault::getInstance()->flush();
}
//��ȡ����
void RankFruitLayer::load()
{
	for(int i=0; i<5; i++)
	{
		scoreFruit[i] = UserDefault::getInstance()->getStringForKey(StringUtils::format("f%d", i).c_str(), "0");
	}
}
//�������˵�
void RankFruitLayer::menuCallBack0(Ref* pSender)
{
	sceneManager->goToMainScene();
}
//����һ�����а�
void RankFruitLayer::menuCallBack1(Ref* pSender)
{
	sceneManager->goToRankBirdScene();
}
