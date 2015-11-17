#include "RankBirdLayer.h"

using namespace cocos2d;
using namespace std;

bool RankBirdLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
    //获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();
	//创建背景
	Sprite* backGround = Sprite::create("night.png");
	//设置锚点
	backGround->setAnchorPoint(Point(0, 0));
	//设置精灵对象的位置
	backGround->setPosition(Point(origin.x,origin.y + visibleSize.height - backGround->getContentSize().height));
	//将精灵添加到布景中
	this->addChild(backGround, 0);

	//创建地面精灵
	Sprite* floor = Sprite::create("floor.png");
	//设置锚点
	floor->setAnchorPoint(Point(0, 0));
	//设置精灵对象位置
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));

	//创建排行榜背景
	Sprite* rank = Sprite::create("rankBackground.png");
	//设置精灵位置
	rank->setPosition(Point(270, 530));
	//添加到布景中
	this->addChild(rank, 1);
	//创建标题
	Sprite* title = Sprite::create("rankBird.png");
	//设置精灵位置
	title->setPosition(Point(270, 850));
	//添加到布景中
	this->addChild(title, 1);

	//
	MenuItemImage* menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(RankBirdLayer::menuCallBack0, this) //点击时执行的回调方法
	);
	menuItem->setPosition(Point(80, 50));
	//
	MenuItemImage* nextItem = MenuItemImage::create(
		"next.png",
		"next_off.png",
		 CC_CALLBACK_1(RankBirdLayer::menuCallBack1, this) //点击时执行的回调方法
	);
	nextItem->setPosition(Point(460, 50));

	Menu* menu = Menu::create(menuItem, nextItem, NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	//显示分数
	int *tempBird = new int[5];
	load();
	//提取各排名
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
//记录分数
void RankBirdLayer::save(int newScore)
{
	string score;
	string oldScore;
	int *tempBird = new int[5];
	load();
	//提取各排名
	for(int i = 0; i<5; i++)
	{
		tempBird[i] = atoi(scoreBird[i].c_str());
	}
	//最新分数与排名分数比较
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
	//刷新
	UserDefault::getInstance()->flush();
}
//读取分数
void RankBirdLayer::load()
{
	for(int i=0; i<5; i++)
	{
		scoreBird[i] = UserDefault::getInstance()->getStringForKey(StringUtils::format("b%d", i).c_str(), "0");
	}
}
//返回主菜单
void RankBirdLayer::menuCallBack0(Ref* pSender)
{
	sceneManager->goToMainScene();
}
//到下一个排行榜
void RankBirdLayer::menuCallBack1(Ref* pSender)
{
	sceneManager->goToRankFruitScene();
}
