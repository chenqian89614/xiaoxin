#include "BirdLayer.h"
#include "MainLayer.h"
#include "Collision.h"
#include "SimpleAudioEngine.h"
#include "RankBirdLayer.h"
#include <time.h>

using namespace cocos2d;
using namespace cocos2d::extension;

//实现BirdLayer类中的init方法，初始化布景
bool BirdLayer::init()
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
    stopFlag = false;
    gameFlag = true;
    readyFlag = true;
    overFlag = false;

	int i = random();

	if(i%2 == 0)
	{
		//创建背景
		background = Sprite::create("morning.png");
	}else
	{
		//创建背景
		background = Sprite::create("night.png");
	}
	//设置锚点
	background->setAnchorPoint(Point(0, 0));
	//设置精灵对象的位置
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//将精灵添加到布景中
	this->addChild(background, 0);

	//创建一个网络节点对象
	effectNode = NodeGrid::create();
	//将网格节点添加到布景
	this->addChild(effectNode, 1);
	//游戏预备界面
	ready = Sprite::create("readyBird.png");
	//设置精灵对象的位置
	ready->setPosition(Point(visibleSize.width/2, visibleSize.height*4/7));
	//将精灵添加到布景中
	effectNode->addChild(ready, 10);

	//创建地面精灵1
	floor = Sprite::create("floor.png");
	//设置锚点
	floor->setAnchorPoint(Point(0, 0));
	//设置精灵对象位置
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	//获取地面精灵尺寸大小
	Size floorSize = floor->getContentSize();
	//地面滚动
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));
	//创建一个LabelAtlas对象
	pLabelAtlas = LabelAtlas::create("0","number.png", 48, 64,'0');
	//设置LabelAtlas对象位置
	pLabelAtlas->setPosition(Point(visibleSize.width/2,visibleSize.height/5*4));
	//将LabelAtlas对象添加到布景中
	this->addChild(pLabelAtlas,4);

	//创建暂停按钮精灵
	pause = Sprite::create("pause.png");
	//设置精灵位置
	pause->setPosition(Point(32, 928));
	this->addChild(pause,10);

	//创建单点触摸监听
	EventListenerTouchOneByOne* listenerPause = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerPause->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerPause->onTouchBegan = CC_CALLBACK_2(BirdLayer::onTouchPause, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPause, pause);


	//===========初始化小鸟===========
	initBird();
	//获取背景尺寸
	Size backgroundSize = background->getContentSize();
	//创建小鸟精灵
    bird = Sprite::create();
    //设置精灵位置
    bird->setPosition(Point(140 + origin.x, origin.y +floorSize.height + backgroundSize.height/2));
    //添加到布景中
    this->addChild(bird, 2);
    //播放动画
	bird->runAction(RepeatForever::create(animAc));

    //创建一个单点触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listener->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listener->onTouchBegan = CC_CALLBACK_2(BirdLayer::onTouchBegan, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
//开始游戏
void BirdLayer::startGame()
{
	//深度检测设置为false
	Director::getInstance()->setDepthTest(false);
	effectNode->runAction(SplitRows::create(0.5f, 30));
	initColumn1();
	initColumn2();
	birdRun();
	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//定时回调update
	sched->schedule(schedule_selector(BirdLayer::update_column), this, 0.05, false);
	sched->schedule(schedule_selector(BirdLayer::update_bird), this, 0.05, false);
}
void BirdLayer::initBird()
{
	//获取缓冲帧
	SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("bird.plist", "birdP.png");
	//动画图片的名称
	std::string animBird[3] =
	{
			"bird1.png",
			"bird2.png",
			"bird3.png"
	};
	//创建存放动画帧的向量
	Vector<SpriteFrame*> animFrames;
	//获取动画帧
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[0]));
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[1]));
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[2]));
	//创建动画对象，从帧向量产生动画，间隔为0.1秒
	Animation *anim = Animation::createWithSpriteFrames(animFrames, 0.1f);
	//创建动画动作对象
	animAc = Animate::create(anim);
	//因为暂时不用，保持引用，防止被自动释放
	animAc->retain();
}
//生成随机数
int BirdLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%5+1;
	return number;
}

void BirdLayer::birdRun()
{
	//小鸟位置
	Point birdPosition = bird->getPosition();
	//地面尺寸
	Size floorSize = floor->getContentSize();
	float time = (birdPosition.y-240)/135;
	bird->runAction(Sequence::create(MoveTo::create(time, Point(birdPosition.x, floorSize.height+40)), NULL));
}

void BirdLayer::setRunFlag1()
{
	runFlag = true;
}
void BirdLayer::setRunFlag2()
{
	runFlag = false;
}

void BirdLayer::initColumn1()
{
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取背景尺寸大小
	Size backSize = background->getContentSize();
	//获取地面尺寸大小
	Size floorSize = floor->getContentSize();
	//获取随机数
	int i = random();
	int height1 = 400/i;
	int height2 = backSize.height - height1 - 196;
	//创建SpriteBatchNode对象
	SpriteBatchNode* columnNode1 = SpriteBatchNode::create("column1.png");
	//创建SpriteBatchNode对象
	SpriteBatchNode* columnNode2 = SpriteBatchNode::create("column2.png");
	columnFlag1 = true;
	//创建Scale9Sprite对象
	columnUnder1 = Scale9Sprite::create();
	//设置图像操作区域
	columnUnder1->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
	//设置锚点
	columnUnder1->setAnchorPoint(Point(0, 0));
	//设置图像伸缩
	columnUnder1->setContentSize(Size(96, height1));
	if(count>0)
	{
		//设置位置
		columnUnder1->setPosition(Point(visibleSize.width, floorSize.height));
	}else
	{
		//设置位置
		columnUnder1->setPosition(Point(visibleSize.width*2, floorSize.height));
	}
	//创建Scale9Sprite对象
	columnOn1 = Scale9Sprite::create();
	//设置图像操作区域
	columnOn1->updateWithBatchNode(columnNode2, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 370));
	//设置锚点
	columnOn1->setAnchorPoint(Point(0, 0));
	//设置图像伸缩
	columnOn1->setContentSize(Size(96, height2));
	if(count>0)
	{
		//设置位置
		columnOn1->setPosition(Point(visibleSize.width, visibleSize.height - height2));
	}else
	{
		//设置位置
		columnOn1->setPosition(Point(visibleSize.width*2, visibleSize.height - height2));
	}
	//添加到布景中
	this->addChild(columnUnder1, 0);
	this->addChild(columnOn1, 0);
	columnUnder1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
	columnOn1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
}

void BirdLayer::initColumn2()
{
	columnFlag2 = true;
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取背景尺寸大小
	Size backSize = background->getContentSize();
	//获取地面尺寸大小
	Size floorSize = floor->getContentSize();
	//获取随机数
	int i = random();
	int height1 = 400/i;
	int height2 = backSize.height - height1 - 196;
	//获取柱子1的位置
	Point columnPosition = columnUnder1->getPosition();
	//创建SpriteBatchNode对象
	SpriteBatchNode* columnNode1 = SpriteBatchNode::create("column1.png");
	//创建SpriteBatchNode对象
	SpriteBatchNode* columnNode2 = SpriteBatchNode::create("column2.png");
	//创建Scale9Sprite对象
	columnUnder2 = Scale9Sprite::create();
	//设置图像操作区域
	columnUnder2->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
	//设置锚点
	columnUnder2->setAnchorPoint(Point(0, 0));
	//设置图像伸缩
	columnUnder2->setContentSize(Size(96, height1));
	//设置位置
	columnUnder2->setPosition(Point(columnPosition.x + 320, floorSize.height));
	//创建Scale9Sprite对象
	columnOn2 = Scale9Sprite::create();
	//设置图像操作区域
	columnOn2->updateWithBatchNode(columnNode2, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 370));
	//设置锚点
	columnOn2->setAnchorPoint(Point(0, 0));
	//设置图像伸缩
	columnOn2->setContentSize(Size(96, height2));
	//设置位置
	columnOn2->setPosition(Point(columnPosition.x + 320, visibleSize.height - height2));
	//添加到布景中
	this->addChild(columnUnder2, 0);
	this->addChild(columnOn2, 0);
	columnUnder2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
	columnOn2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
}

void BirdLayer::replay()
{
	overFlag = true;
	//奖牌
	string medal;
	//删除分数
	removeChild(pLabelAtlas);
	Sprite* over = Sprite::create("gameOver.png");
	over->setPosition(Point(270, 1200));
	this->addChild(over, 10);

	overRank = Sprite::create("scoreOver.png");
	overRank->setPosition(Point(270, -100));
	this->addChild(overRank, 10);

	//重新开始
	replayItem = MenuItemImage::create(
		"replay.png",
		"replay_off.png",
		 CC_CALLBACK_1(BirdLayer::menuCallbackItem0, this) //点击时执行的回调方法
	);
	replayItem->setPosition(Point(150, -250));
	//返回主菜单
	menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(BirdLayer::menuCallbackItem1, this) //点击时执行的回调方法
	);
	menuItem->setPosition(Point(380, -250));

	Menu* menu = Menu::create(replayItem, menuItem, NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);
	//-----------------------------------------------------------------------------
	RankBirdLayer* rank = RankBirdLayer::create();
	rank->load();
	rank->save(count);
	int i = atoi(rank->scoreBird[0].c_str());
	string tempScore = StringUtils::format("%d", count);
	Label* newScore = Label::createWithTTF (tempScore, "FZKATJW.ttf", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	newScore->setColor(Color3B::YELLOW);
	newScore->enableOutline(Color4B(187, 187, 187, 255),2);
	overRank->addChild(newScore);
	newScore->setPosition(Point(320, 130));
	if(i<count)
	{
		Label* ss = Label::createWithTTF (tempScore, "FZKATJW.ttf", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		ss->setColor(Color3B::YELLOW);
		ss->enableOutline(Color4B(187, 187, 187, 255),2);
		overRank->addChild(ss);
		ss->setPosition(Point(320, 50));
	}else
	{
		Label* ss = Label::createWithTTF (rank->scoreBird[0], "FZKATJW.ttf", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		ss->setColor(Color3B::YELLOW);
		ss->enableOutline(Color4B(187, 187, 187, 255),2);
		overRank->addChild(ss);
		ss->setPosition(Point(320, 50));
	}
	if(count>=atoi(rank->scoreBird[2].c_str()))
	{
		medal = "third.png";
		if(count>=atoi(rank->scoreBird[1].c_str()))
		{
			medal = "slider.png";
			if(count>=atoi(rank->scoreBird[0].c_str()))
			{
				medal = "gold.png";
			}
		}
		Sprite* gold = Sprite::create(medal);
		overRank->addChild(gold, 5);
		gold->setPosition(Point(90, 88));
	}
	//执行动作
	over->runAction(
		Sequence::create(
				MoveTo::create(0.2, Point(270, 750)),
				CallFunc::create(CC_CALLBACK_0(BirdLayer::moveObject, this)),
				NULL
	));
}

void BirdLayer::moveObject()
{
	overRank->runAction(MoveTo::create(0.6, Point(270, 550)));
	replayItem->runAction(MoveTo::create(0.6, Point(150, 380)));
	menuItem->runAction(MoveTo::create(0.6, Point(380, 380)));
}

void BirdLayer::gameOver()
{
	//游戏结束
	gameFlag = false;
	Point birdPosition = bird->getPosition();
	Size birdSize = bird->getContentSize();
	Size floorSize = floor->getContentSize();
	floor->stopAllActions();
	columnUnder1->stopAllActions();
	columnOn1->stopAllActions();
	columnUnder2->stopAllActions();
	columnOn2->stopAllActions();
	bird->stopAllActions();
	bird->runAction(Sequence::create(Spawn::createWithTwoActions(MoveTo::create(0.2, Point(birdPosition.x, floorSize.height+birdSize.width/2)), RotateTo::create(0.2, 90)), NULL));
	if(!overFlag)
	{
		replay();
	}
}

void BirdLayer::update_column(float delta)
{
	//
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnUnder2->getPosition();
	//
	Size columnSize = columnUnder1->getContentSize();
	if(columnPosition1.x<=-columnSize.width)
	{
		removeChild(columnUnder1);
		removeChild(columnOn1);
		initColumn1();
	}
	if(columnPosition2.x<=-columnSize.width)
	{
		removeChild(columnUnder2);
		removeChild(columnOn2);
		initColumn2();
	}
}

//小鸟定时下落
void BirdLayer::update_bird(float delta)
{
	if(gameFlag && !runFlag)
	{
		birdRun();
	}
	//获取小鸟当前位置
	Point birdPosition = bird->getPosition();
	//获取小鸟尺寸大小
	Size birdSize = bird->getContentSize();
	//获取地面尺寸大小
	Size floorSize = floor->getContentSize();
	//获取柱子位置
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnOn1->getPosition();
	Point columnPosition3 = columnUnder2->getPosition();
	Point columnPosition4 = columnOn2->getPosition();
	//获取柱子尺寸大小
	Size columnSize1 = columnUnder1->getContentSize();
	Size columnSize2 = columnOn1->getContentSize();
	Size columnSize3 = columnUnder2->getContentSize();
	Size columnSize4 = columnOn2->getContentSize();

	if(birdPosition.x>columnPosition1.x && columnFlag1)
	{
		count++;
		string num =StringUtils::toString(count);
		pLabelAtlas->setString(num);
		if(MainLayer::soundFlag)
		{
			pointSound();
		}
		columnFlag1 = false;
	}

	if(birdPosition.x>columnPosition3.x && columnFlag2)
	{
		count++;
		string num =StringUtils::toString(count);
		pLabelAtlas->setString(num);
		if(MainLayer::soundFlag)
		{
			pointSound();
		}
		columnFlag2 = false;
	}
	//检测碰撞
	bool check = collision((birdPosition.x - birdSize.width), (birdPosition.y - birdSize.height), (birdPosition.x + birdSize.width), (birdPosition.y + birdSize.height),
			0, 0, floorSize.width, floorSize.height);
	bool check1 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition1.x, columnPosition1.y, (columnPosition1.x + columnSize1.width), (columnPosition1.y + columnSize1.height));
	bool check2 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition2.x, columnPosition2.y, (columnPosition2.x + columnSize2.width), (columnPosition2.y + columnSize2.height));
	bool check3 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition3.x, columnPosition3.y, (columnPosition3.x + columnSize3.width), (columnPosition3.y + columnSize3.height));
	bool check4 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition4.x, columnPosition4.y, (columnPosition4.x + columnSize4.width), (columnPosition4.y + columnSize4.height));
	if(check || check1 || check2 || check3 || check4)
	{
		if(gameFlag)//失败是停止声音
		{
			if(MainLayer::soundFlag)
			{
				hitSound();
			}
			if(check1 || check2 || check3 || check4)
			{
				if(MainLayer::soundFlag)
				{
					dieSound();
				}
			}
		}
		gameOver();
	}
}

bool BirdLayer::onTouchPause(Touch* touch, Event* event)
{
	if(!gameFlag)
	{
		return false;
	}
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	//判断触摸点是否在目标的范围内
	if(!stopFlag && rect.containsPoint(location) )
	{
		stopFlag = true;
		pause->setTexture("continue_pause.png");
		Director::getInstance()->pause();
		//--------------------------------------------
		pauseBack = Sprite::create("setBackground.png");
		pauseBack->setPosition(Point(270, 600));
		this->addChild(pauseBack, 10);

		//音乐按钮
		Sprite* music = Sprite::create("music.png");
		pauseBack->addChild(music, 1);
		music->setPosition(Point(120, 300));

		CheckBox* checkMusic = CheckBox::create(
				"sound_on.png",
				"sound_off.png",
				"sound_off.png",
				"sound_stop.png",
				"sound_stop.png"
		);
		pauseBack->addChild(checkMusic, 1);
		checkMusic->setPosition(Point(350, 300));
		checkMusic->setSelectedState(!MainLayer::musicFlag);
		checkMusic->addEventListener(CC_CALLBACK_2(BirdLayer::selectedEvent0, this));

		//音效按钮
		Sprite* sound = Sprite::create("sound.png");
		pauseBack->addChild(sound, 1);
		sound->setPosition(Point(120, 200));

		CheckBox* checkSound = CheckBox::create(
				"sound_on.png",
				"sound_off.png",
				"sound_off.png",
				"sound_stop.png",
				"sound_stop.png"
		);
		pauseBack->addChild(checkSound, 1);
		checkSound->setPosition(Point(350, 200));
		checkSound->setSelectedState(!MainLayer::soundFlag);
		checkSound->addEventListener(CC_CALLBACK_2(BirdLayer::selectedEvent1, this));

		//继续游戏
		MenuItemImage* conItem = MenuItemImage::create(
				"continue.png",
				"continue_off.png",
				CC_CALLBACK_1(BirdLayer::menuCallbackItem3, this) //点击时执行的回调方法
		);
		conItem->setPosition(Point(80, 80));
		//返回主菜单
		MenuItemImage* backItem = MenuItemImage::create(
			"menu.png",
			"menu_off.png",
			 CC_CALLBACK_1(BirdLayer::menuCallbackItem2, this) //点击时执行的回调方法
		);
		backItem->setPosition(Point(225, 80));
		//返回主菜单
		MenuItemImage* againItem = MenuItemImage::create(
			"replay.png",
			"replay_off.png",
			 CC_CALLBACK_1(BirdLayer::menuCallbackItem4, this) //点击时执行的回调方法
		);
		againItem->setPosition(Point(370, 80));

		Menu* menu = Menu::create(againItem, conItem, backItem, NULL);
		//设置菜单位置
		menu->setPosition(Point::ZERO);
		pauseBack->addChild(menu,1);
		return true;
	}
	else
	{
		return false;
	}
}

bool BirdLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point birdPosition = bird->getPosition();
	if(gameFlag)
	{
		if(readyFlag)
		{
			startGame();
			readyFlag = false;
		}
		if(MainLayer::soundFlag)
		{
			wingSound();
		}
		int move = 105;
		auto action = Spawn::createWithTwoActions(MoveTo::create(0.2, Point(birdPosition.x, birdPosition.y + move)), RotateTo::create(0, -30));
		bird->stopAllActions();
		bird->runAction(RepeatForever::create(animAc));
		bird->runAction(
				Sequence::create(
						CallFunc::create(CC_CALLBACK_0(BirdLayer::setRunFlag1, this)),
						action,
						DelayTime::create(0.05 ),
						CallFunc::create(CC_CALLBACK_0(BirdLayer::setRunFlag2, this)),
						RotateTo::create(2.0, 90),
						NULL
		));
	}
	return true;
}
void BirdLayer::menuCallbackItem0(Ref* pSender)
{
	sceneManager->goToFlappyScene(1);
}
void BirdLayer::menuCallbackItem1(Ref* pSender)
{
	sceneManager->goToMainScene();
}
//返回主菜单按钮执行方法
void BirdLayer::menuCallbackItem2(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToMainScene();
}
//继续游戏按钮执行方法
void BirdLayer::menuCallbackItem3(Ref* pSender)
{
	stopFlag = false;
	this->removeChild(pauseBack);
	pause->setTexture("pause.png");
	Director::getInstance()->resume();
}
//重新开始游戏按钮执行方法
void BirdLayer::menuCallbackItem4(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToFlappyScene(1);
}
//背景音乐复选框执行方法
void BirdLayer::selectedEvent0(Ref* pSender,CheckBox::EventType type)
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
//音效复选框执行方法
void BirdLayer::selectedEvent1(Ref* pSender,CheckBox::EventType type)
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

void BirdLayer::wingSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
}

void BirdLayer::pointSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
}

void BirdLayer::hitSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
}

void BirdLayer::dieSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
}
