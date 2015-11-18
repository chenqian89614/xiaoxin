#include "AppDelegate.h"
#include "AchieveLayer.h"
#include "AppMacros.h"

#define pic_PRE_PATH_AchieveLayer string("")

using namespace cocos2d;

//实现AchieveLayer类中的init方法，初始化布景
bool AchieveLayer::init()
{
    //调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
	//加载音效
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_button_press.mp3"
	);

    //获取可见区域尺寸
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::sharedDirector()->getVisibleOrigin();

    //创建一个精灵对象，充当欢迎界面的背景
    backSprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("background.png"));
    //设置精灵对象的位置
    backSprite->setPosition(Point(400,240));
    //将背景精灵添加到布景中
    this->addChild(backSprite,BACKGROUND_LEVEL_CGQ);

    //创建一个精灵对象，“排行榜”
    Sprite *playSprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paihang.png"));
	//设置精灵对象的位置
    playSprite->setPosition(Point(260,290));
	//将背景精灵添加到布景中
	this->addChild(playSprite,BACKGROUND_LEVEL_CGQ);

    //创建一个表示颁奖台的精灵对象
    Sprite *paihangSprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paihang1.png"));
	//设置精灵对象的位置
    paihangSprite->setPosition(Point(260,110));
	//将背景精灵添加到布景中
	this->addChild(paihangSprite,BACKGROUND_LEVEL_CGQ);

    //创建一个精灵对象，“最高分数”
    Sprite *paih1Sprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paih1.png"));
	//设置精灵对象的位置
    paih1Sprite->setPosition(Point(360,110));
	//将背景精灵添加到布景中
	this->addChild(paih1Sprite,BACKGROUND_LEVEL_CGQ);

    //创建一个精灵对象，“最高分数”
	Sprite *paih2Sprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paih2.png"));
	//设置精灵对象的位置
	paih2Sprite->setPosition(Point(500,110));
	//将背景精灵添加到布景中
	this->addChild(paih2Sprite,BACKGROUND_LEVEL_CGQ);

    //创建一个精灵对象，“最高分数”
	Sprite *paih3Sprite = Sprite::create(pic_PRE_PATH_AchieveLayer+string("paih3.png"));
	//设置精灵对象的位置
	paih3Sprite->setPosition(Point(640,110));
	//将背景精灵添加到布景中
	this->addChild(paih3Sprite,BACKGROUND_LEVEL_CGQ);

	//用于排行榜--计分板
	//创建临时数组
	int *tempScore = new int[3];

	readScore();
	//提取各排名--并打印出分数
	for(int i = 0; i<3; i++)
	{
		string score;//记录主分数-最后的分数
		tempScore[i] = atoi(glareScore[i].c_str());
		//判断
		if(tempScore[i] == 0)
		{
			score = "0";
		}else
		{
			score = glareScore[i];
		}
		//分数
		labels = Label::createWithTTF (score, "Marker Felt.ttf", 45, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		labels->setRotation(-90);
		labels->setColor(Color3B(255,255,255));
		backSprite->addChild(labels);
		labels->setPosition(Point(355+140*i, 290));
	}

	MenuItemImage *fanhuiItem = MenuItemImage::create(
        pic_PRE_PATH_AchieveLayer+string("fanhui.png"),("fanhui.png"),
		CC_CALLBACK_1(AchieveLayer::menuCallBack, this)
	);
	fanhuiItem->setPosition(Point(740,420));
	pMenu = Menu::create(fanhuiItem,NULL);
	pMenu->setPosition(Point(0,0));
	this->addChild(pMenu,GAME_LEVEL_CGQ+1);

	return true;
}

void AchieveLayer::menuCallBack(Object* pSende)
{
	//播放音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//返回主界面
	man->toBeginLayer();
}
//记录分数
void AchieveLayer::saveScore(int newScore)
{
	//记录newScore分数
	string score;
	//之前的分数
	string oldScore;
	//获取原来的分数--5个
	int *tempScore = new int[3];
	//读取分数
	readScore();
	//提取各排名
	for(int i=0; i<3; i++)
	{
		tempScore[i] = atoi(glareScore[i].c_str());//字符串转化为整形
	}

	for(int i=2; i>=0; i--)
	{
		if(newScore>=tempScore[i])
		{
			score = StringUtils::format("%d", newScore);//转化为字符串
			if(i!=2)
			{
				oldScore = StringUtils::format("%d", tempScore[i]);
				UserDefault::getInstance()->setStringForKey(StringUtils::format("%d", (i+1)).c_str(), oldScore);
			}
			UserDefault::getInstance()->setStringForKey(StringUtils::format("%d", i).c_str(), score);
		}else
		{
			break;
		}
	}
	//刷新
	UserDefault::getInstance()->flush();
}
//读取分数
void AchieveLayer::readScore()
{
	for(int i=0; i<3; i++)
	{
		glareScore[i] = UserDefault::getInstance()->getStringForKey(StringUtils::format("%d", i).c_str(), "0");
	}
}

