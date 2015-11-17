#include "RankBirdLayer.h"

using namespace cocos2d;
using namespace std;

bool RankBirdLayer::init()
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
	Sprite* backGround = Sprite::create("night.png");
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
	Sprite* title = Sprite::create("rankBird.png");
	//���þ���λ��
	title->setPosition(Point(270, 850));
	//��ӵ�������
	this->addChild(title, 1);

	//
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(RankBirdLayer::menuCallBack0, this) //���ʱִ�еĻص�����
	);
	menuItem->setPosition(Point(80, 50));
	//
	MenuItemImage* nextItem = MenuItemImage::create(
		"next.png",
		"next_off.png",
		 CC_CALLBACK_1(RankBirdLayer::menuCallBack1, this) //���ʱִ�еĻص�����
	);
	nextItem->setPosition(Point(460, 50));

	Menu* menu = Menu::create(menuItem, nextItem, NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	//��ʾ����
	int *tempBird = new int[5];
	load();
	//��ȡ������
	for(int i = 0; i<5; i++)
	{
		string score;
		string number = StringUtils::format("%d", (i+1));
		tempBird[i] = atoi(scoreBird[i].c_str());
		if(tempBird[i] == 0)
		{
			score = "-";
		}else
		{
			score = scoreBird[i];
		}
		labels = Label::createWithTTF (number, "FZKATJW.ttf", 60, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		rank->addChild(labels,2);
		labels->setPosition(Point(90, 280-(50*i)));
		labels->enableOutline(Color4B(187, 187, 187, 255),2);
		labels = Label::createWithTTF (score, "FZKATJW.ttf", 60, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		rank->addChild(labels,2);
		labels->setPosition(Point(315, 280-(50*i)));
		labels->enableOutline(Color4B(187, 187, 187, 255),2);
	}
    return true;
}
//��¼����
void RankBirdLayer::save(int newScore)
{
	string score;
	string oldScore;
	int *tempBird = new int[5];
	load();
	//��ȡ������
	for(int i = 0; i<5; i++)
	{
		tempBird[i] = atoi(scoreBird[i].c_str());
	}
	//���·��������������Ƚ�
	for(int i = 4; i>=0; i--)
	{
		if(newScore>=tempBird[i])
		{
			score = StringUtils::format("%d", newScore);
			if(i!=4)
			{
				oldScore = StringUtils::format("%d", tempBird[i]);
				UserDefault::getInstance()->setStringForKey(StringUtils::format("b%d", (i+1)).c_str() , oldScore);
			}
			UserDefault::getInstance()->setStringForKey(StringUtils::format("b%d", i).c_str(), score);
		}else
		{
			break;
		}
	}
	//ˢ��
	UserDefault::getInstance()->flush();
}
//��ȡ����
void RankBirdLayer::load()
{
	for(int i=0; i<5; i++)
	{
		scoreBird[i] = UserDefault::getInstance()->getStringForKey(StringUtils::format("b%d", i).c_str(), "0");
	}
}
//�������˵�
void RankBirdLayer::menuCallBack0(Ref* pSender)
{
	sceneManager->goToMainScene();
}
//����һ�����а�
void RankBirdLayer::menuCallBack1(Ref* pSender)
{
	sceneManager->goToRankFruitScene();
}
