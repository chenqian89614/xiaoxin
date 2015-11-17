#include "FruitLayer.h"
#include "Collision.h"
#include "MainLayer.h"
#include "RankFruitLayer.h"
#include "SimpleAudioEngine.h"
#include <time.h>

using namespace cocos2d;
using namespace std;
using namespace ui;

//实现FruitLayer类中的init方法，初始化布景
bool FruitLayer::init()
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
	//游戏暂停标志位
	stopFlag = false;
	//游戏开始标志位
	gameFlag = false;
	//游戏准备标志位
	readyFlag = true;
	//动作完成标志位
	actionFlag = false;
	//
	overFlag = false;
	//创建vector
	fruit = new vector<Sprite*>();
	int i = random();
	//创建背景精灵
	if(i%2==0)
	{
		background = Sprite::create("morning.png");
	}else
	{
		background = Sprite::create("night.png");
	}
	//设置锚点
	background->setAnchorPoint(Point(0, 0));
	//设置精灵对象的位置
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//将精灵添加到布景中
	this->addChild(background, 0);

	//创建一个网络节点
	effectNode = NodeGrid::create();
	//将网格节点添加到布景
	this->addChild(effectNode, 1);
	//准备界面
	ready = Sprite::create("readyFruit.png");
	//设置精灵对象的位置
	ready->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	//将精灵添加到布景中
	effectNode->addChild(ready, 0);

	//创建地面精灵
	floor = Sprite::create("floor.png");
	//设置锚点
	floor->setAnchorPoint(Point(0, 0));
	//设置精灵对象位置
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor, 4);
	//地面滚动
	floor->runAction(RepeatForever::create(
		Sequence::create
		(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
		)
	));

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
	listenerPause->onTouchBegan = CC_CALLBACK_2(FruitLayer::onTouchPause, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPause, pause);

	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(FruitLayer::onTouchBegan, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	return true;
}
//
void FruitLayer::startGame()
{
	//深度检测设置为false
	Director::getInstance()->setDepthTest(false);
	//执行特效
	effectNode->runAction(SplitCols::create(1.0f, 20));
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	initColumn1();
	initColumn2();
	gameFlag = true;
	//创建一个LabelAtlas对象
	pLabelAtlas = LabelAtlas::create("0", "number.png", 48, 64,'0');
	//设置LabelAtlas对象位置
	pLabelAtlas->setPosition(Point(visibleSize.width/5,visibleSize.height/5*4));
	//将LabelAtlas对象添加到布景中
	this->addChild(pLabelAtlas,4);
	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//定时回调update
	sched->schedule(schedule_selector(FruitLayer::update_fruit), this, 1, false);
	sched->schedule(schedule_selector(FruitLayer::update_boss), this, 20, false);
	sched->schedule(schedule_selector(FruitLayer::update_column), this, 0.1, false);
}
void FruitLayer::initColumn1()
{
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取随机数
	int i = random();
	int height = -(i*5);
	height1 = 800 - height;
	//创建Sprite对象
	columnUnder1 = Sprite::create("column1.png");
	//设置锚点
	columnUnder1->setAnchorPoint(Point(0, 0));
	//设置位置
	columnUnder1->setPosition(Point(visibleSize.width, height));
	//创建Sprite对象
	columnOn1 = Sprite::create("column2.png");
	//设置锚点
	columnOn1->setAnchorPoint(Point(0, 0));
	//设置位置
	columnOn1->setPosition(Point(visibleSize.width, height1));
	//添加到布景中
	this->addChild(columnUnder1, 3);
	this->addChild(columnOn1, 3);
	int speed = count*0.05 + 15;
	columnUnder1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
	columnOn1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
}
//
void FruitLayer::initColumn2()
{
	//获取随机数
	int i = random();
	int height = -(i*6);
	height2 = 800 - height;
	//获取柱子1的位置
	Point columnPosition = columnUnder1->getPosition();
	//创建SpriteBatchNode对象
	columnUnder2 = Sprite::create("column1.png");
	//创建SpriteBatchNode对象
	columnOn2 = Sprite::create("column2.png");
	//设置锚点
	columnUnder2->setAnchorPoint(Point(0, 0));
	//设置位置
	columnUnder2->setPosition(Point(columnPosition.x + 320, height));
	//设置锚点
	columnOn2->setAnchorPoint(Point(0, 0));
	//设置位置
	columnOn2->setPosition(Point(columnPosition.x + 320, height2));
	//添加到布景中
	this->addChild(columnUnder2, 3);
	this->addChild(columnOn2, 3);
	int speed = count*0.05 + 15;
	columnUnder2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
	columnOn2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
}
//生成随机数
int FruitLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%5;
	return number;
}
//
void FruitLayer::update_fruit(float delta)
{
	if(gameFlag)
	{
		//获取随机数
		int i = random();
		float time = 54/(i*2+10);
		string number = StringUtils::format("%d", i);
		string part = "fruit" + number + ".png";
		Sprite* ff = Sprite::create(part);
		ff->setPosition(Point(0, (700 - i*40)));
		this->addChild(ff, 2);
		ff->runAction(MoveTo::create(time, Point(540, (700 - i*40))));
		int down = (700-i*40) - 450;
		if((700 - i*40)<600)
		{
			down = -down;
		}
		ff->runAction(RepeatForever::create(
				Sequence::create(MoveBy::create((time/3), Point(0, -down)), MoveBy::create((time/3), Point(0, down)), NULL)
		));
		fruit->push_back(ff);
	}
}
//定时回调出现大水果的方法
void FruitLayer::update_boss(float delta)
{
	if(gameFlag)
	{
		//获取随机数
		int i = random();
		boss++;
		bossFlag = true;
		string number = StringUtils::format("%d", i);
		string partBoss = "fruit" + number + ".png";
		bossSprite = Sprite::create(partBoss);
		bossSprite->setScale(2);
		bossSprite->setPosition(Point(0, 600));
		this->addChild(bossSprite, 2);
		bossSprite->runAction(MoveTo::create(10, Point(540, 600)));

		slider = Slider::create();
		slider->loadBarTexture("sliderTrack.png");
		slider->loadProgressBarTexture("blood.png");
		slider->setPercent(100);
		slider->setPosition(Point(0, 700));
		this->addChild(slider, 2);
		slider->runAction(MoveTo::create(10, Point(540, 700)));
	}
}
//更新柱子位置，并且检测是否有水果到最右边
void FruitLayer::update_column(float delta)
{
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取柱子位置
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnUnder2->getPosition();
	//获取柱子尺寸大小
	Size columnSize = columnUnder1->getContentSize();
	if(columnPosition1.x<=-columnSize.width)
	{
		actionFlag = false;
		removeChild(columnUnder1);
		removeChild(columnOn1);
		initColumn1();
	}
	if(columnPosition2.x<=-columnSize.width)
	{
		actionFlag = false;
		removeChild(columnUnder2);
		removeChild(columnOn2);
		initColumn2();

	}
	//获取向量中的水果精灵
	vector<Sprite*>::iterator iter;
	for(iter = fruit->begin(); iter != fruit->end(); iter++)
	{
		//获取当前水果位置
		Point fruitPosition = (*iter)->getPosition();
		//获取当前水果的尺寸大小
		Size fruitSize = (*iter)->getContentSize();
		if(fruitPosition.x >= (visibleSize.width-fruitSize.width/2))
		{
			gameOver();
		}
	}
	if(bossFlag)
	{
		//获取当前水果位置
		Point bossPosition = bossSprite->getPosition();
		//获取当前水果的尺寸大小
		Size bossSize = bossSprite->getContentSize();
		if(bossPosition.x >= (visibleSize.width-bossSize.width/2))
		{
			gameOver();
		}
	}
}
//碰撞检测
void FruitLayer::check()
{
	//获取柱子位置
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnOn1->getPosition();
	Point columnPosition3 = columnUnder2->getPosition();
	Point columnPosition4 = columnOn2->getPosition();
	//获取柱子尺寸大小
	Size columnSize = columnUnder1->getContentSize();
	//获取向量中的水果精灵
	vector<Sprite*>::iterator iter;
	for(iter = fruit->begin(); iter != fruit->end();)
	{
		//获取当前水果位置
		Point fruitPosition = (*iter)->getPosition();
		//获取当前水果的尺寸大小
		Size fruitSize = (*iter)->getContentSize();
		bool check1 = collision((fruitPosition.x - fruitSize.width/2), (fruitPosition.y - fruitSize.height/2), (fruitPosition.x + fruitSize.width/2), (fruitPosition.y + fruitSize.height/2),
					columnPosition1.x, columnPosition1.y, (columnPosition1.x + columnSize.width), (columnPosition1.y + columnSize.height));
		bool check2 = collision((fruitPosition.x - fruitSize.width/2), (fruitPosition.y - fruitSize.height/2), (fruitPosition.x + fruitSize.width/2), (fruitPosition.y + fruitSize.height/2),
					columnPosition2.x, columnPosition2.y, (columnPosition2.x + columnSize.width), (columnPosition2.y + columnSize.height));
		bool check3 = collision((fruitPosition.x - fruitSize.width/2), (fruitPosition.y - fruitSize.height/2), (fruitPosition.x + fruitSize.width/2), (fruitPosition.y + fruitSize.height/2),
					columnPosition3.x, columnPosition3.y, (columnPosition3.x + columnSize.width), (columnPosition3.y + columnSize.height));
		bool check4 = collision((fruitPosition.x - fruitSize.width/2), (fruitPosition.y - fruitSize.height/2), (fruitPosition.x + fruitSize.width/2), (fruitPosition.y + fruitSize.height/2),
					columnPosition4.x, columnPosition4.y, (columnPosition4.x + columnSize.width), (columnPosition4.y + columnSize.height));
		if(check1 || check2 || check3 || check4)
		{
			count++;
			this->removeChild(*iter);
			iter = fruit->erase(iter);
			string num =StringUtils::toString(count);
			pLabelAtlas->setString(num);
			//创建爆炸粒子系统效果
			ParticleSystemQuad*  psq = ParticleExplosion::create();
			//保持引用
			psq->retain();
			psq->setLife(0.5f);
			//将粒子系统添加到精灵中
			this->addChild(psq, 1);
			//为粒子系统设置图片
			psq->setTexture( Director::getInstance()->getTextureCache()->addImage("fire.png") );
			//设置粒子系统的位置
			psq->setPosition( Point(fruitPosition.x, fruitPosition.y) );
			if(MainLayer::soundFlag)
			{
				eatSound();
			}
		}else
		{
			if(MainLayer::soundFlag)
			{
				wingSound();
			}
			iter++;
		}
	}
	if(bossFlag)
	{
		//获取当前水果位置
		Point bossPosition = bossSprite->getPosition();
		//获取当前水果的尺寸大小
		Size bossSize = bossSprite->getContentSize();
		bool check1 = collision((bossPosition.x - bossSize.width/2), (bossPosition.y - bossSize.height/2), (bossPosition.x + bossSize.width/2), (bossPosition.y + bossSize.height/2),
					columnPosition1.x, columnPosition1.y, (columnPosition1.x + columnSize.width), (columnPosition1.y + columnSize.height));
		bool check2 = collision((bossPosition.x - bossSize.width/2), (bossPosition.y - bossSize.height/2), (bossPosition.x + bossSize.width/2), (bossPosition.y + bossSize.height/2),
					columnPosition2.x, columnPosition2.y, (columnPosition2.x + columnSize.width), (columnPosition2.y + columnSize.height));
		bool check3 = collision((bossPosition.x - bossSize.width/2), (bossPosition.y - bossSize.height/2), (bossPosition.x + bossSize.width/2), (bossPosition.y + bossSize.height/2),
					columnPosition3.x, columnPosition3.y, (columnPosition3.x + columnSize.width), (columnPosition3.y + columnSize.height));
		bool check4 = collision((bossPosition.x - bossSize.width/2), (bossPosition.y - bossSize.height/2), (bossPosition.x + bossSize.width/2), (bossPosition.y + bossSize.height/2),
					columnPosition4.x, columnPosition4.y, (columnPosition4.x + columnSize.width), (columnPosition4.y + columnSize.height));
		if(check1 || check2 || check3 || check4)
		{
			int percent = slider->getPercent();
			percent = percent - 10/boss;
			slider->setPercent(percent);
			if(percent <= 0)
			{
				count = count + boss*50;
				this->removeChild(bossSprite);
				this->removeChild(slider);
				string num =StringUtils::toString(count);
				pLabelAtlas->setString(num);
				bossFlag = false;
				if(MainLayer::soundFlag)
				{
					eatSound();
				}

			}
		}
	}
}

void FruitLayer::gameOver()
{
	//游戏结束
	gameFlag = false;
	//停止动作
	columnUnder1->stopAllActions();
	columnOn1->stopAllActions();
	columnUnder2->stopAllActions();
	columnOn2->stopAllActions();
	floor->stopAllActions();
	if(bossFlag)
	{
		bossSprite->stopAllActions();
		slider->stopAllActions();
	}
	//获取向量中的水果精灵
	vector<Sprite*>::iterator iter;
	for(iter = fruit->begin(); iter != fruit->end(); iter++)
	{
		(*iter)->stopAllActions();
	}
	if(!overFlag)
	{
		replay();
	}
}

void FruitLayer::replay()
{
	overFlag = true;
	//奖牌
	string medal;
	removeChild(pLabelAtlas);
	//----------------------------------------------------------------------------
	Sprite* over = Sprite::create("gameOver.png");
	over->setPosition(Point(270, 1200));
	this->addChild(over, 10);

	overRank = Sprite::create("scoreOver.png");
	overRank->setPosition(Point(270, -100));
	this->addChild(overRank, 10);

	//重新开始
	relayItem = MenuItemImage::create(
		"replay.png",
		"replay_off.png",
		 CC_CALLBACK_1(FruitLayer::menuCallback0, this) //点击时执行的回调方法
	);
	relayItem->setPosition(Point(150, -250));
	//返回主菜单
	menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(FruitLayer::menuCallback1, this) //点击时执行的回调方法
	);
	menuItem->setPosition(Point(380, -250));

	Menu* menu = Menu::create(relayItem, menuItem, NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);

	//-----------------------------------------------------------------------------
	RankFruitLayer* rank = RankFruitLayer::create();
	rank->load();
	rank->save(count);
	int i = atoi(rank->scoreFruit[0].c_str());
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
		Label* ss = Label::createWithTTF (rank->scoreFruit[0], "FZKATJW.ttf", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		ss->setColor(Color3B::YELLOW);
		ss->enableOutline(Color4B(187, 187, 187, 255),2);
		overRank->addChild(ss);
		ss->setPosition(Point(320, 50));
	}
	if(count>=atoi(rank->scoreFruit[2].c_str()))
	{
		medal = "third.png";
		if(count>=atoi(rank->scoreFruit[1].c_str()))
		{
			medal = "slider.png";
			if(count>=atoi(rank->scoreFruit[0].c_str()))
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
				CallFunc::create(CC_CALLBACK_0(FruitLayer::moveObject, this)),
				NULL
	));
}

void FruitLayer::moveObject()
{
	overRank->runAction(MoveTo::create(0.6, Point(270, 550)));
	relayItem->runAction(MoveTo::create(0.6, Point(150, 380)));
	menuItem->runAction(MoveTo::create(0.6, Point(380, 380)));
}

bool FruitLayer::onTouchPause(Touch* touch, Event* event)
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
		checkMusic->addEventListener(CC_CALLBACK_2(FruitLayer::selectedEvent0, this));

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
		checkSound->addEventListener(CC_CALLBACK_2(FruitLayer::selectedEvent1, this));


		//继续游戏
		MenuItemImage* conItem = MenuItemImage::create(
				"continue.png",
				"continue_off.png",
				CC_CALLBACK_1(FruitLayer::menuCallback3, this) //点击时执行的回调方法
		);
		conItem->setPosition(Point(80, 80));
		//返回主菜单
		MenuItemImage* backItem = MenuItemImage::create(
			"menu.png",
			"menu_off.png",
			 CC_CALLBACK_1(FruitLayer::menuCallback2, this) //点击时执行的回调方法
		);
		backItem->setPosition(Point(225, 80));
		//返回主菜单
		MenuItemImage* againItem = MenuItemImage::create(
			"replay.png",
			"replay_off.png",
			 CC_CALLBACK_1(FruitLayer::menuCallback4, this) //点击时执行的回调方法
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
void FruitLayer::setFlag()
{
	actionFlag = false;
}
//开始单点触控事件的处理方法
bool FruitLayer::onTouchBegan(Touch* touch, Event* event)
{
	do{
		if(actionFlag)
		{
			return false;
		}
		if(readyFlag)
		{
			startGame();
			readyFlag = false;
		}
		Point columnPosition1 = columnUnder1->getPosition();
		Point columnPosition2 = columnUnder2->getPosition();
		//获取可见区域尺寸
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取当前触控位置
		Point touchPosition = touch->getLocation();
		//获取柱子的位移
		int compression1 = height1 - 600;
		int compression2 = height2 - 600;
		//设置动作
		Action* action1 = Sequence::create
		(
				MoveBy::create(0.1, Point(0, compression1)),
				CallFunc::create(CC_CALLBACK_0(FruitLayer::check, this)),
				MoveBy::create(0.1, Point(0, -compression1)),
				CallFunc::create(CC_CALLBACK_0(FruitLayer::setFlag, this)),
				NULL
		);
		Action* action2 = Sequence::create
		(
				MoveBy::create(0.1, Point(0, -compression1)),
				CallFunc::create(CC_CALLBACK_0(FruitLayer::check, this)),
				MoveBy::create(0.1, Point(0, compression1)),
				NULL
		);
		Action* action3 = Sequence::create
		(
				MoveBy::create(0.1, Point(0, compression2)),
				CallFunc::create(CC_CALLBACK_0(FruitLayer::check, this)),
				MoveBy::create(0.1, Point(0, -compression2)),
				CallFunc::create(CC_CALLBACK_0(FruitLayer::setFlag, this)),
				NULL
		);
		Action* action4 = Sequence::create
		(
				MoveBy::create(0.1, Point(0, -compression2)),
				CallFunc::create(CC_CALLBACK_0(FruitLayer::check, this)),
				MoveBy::create(0.1, Point(0, compression2)),
				NULL
		);
		if(gameFlag)
		{
			//获取柱子尺寸大小
			Size columnSize = columnUnder1->getContentSize();
			bool columnCheck1 = collision(columnPosition1.x, columnPosition1.y, columnPosition1.x + columnSize.width, columnPosition1.y + columnSize.height,
							0, 0, visibleSize.width/2, visibleSize.height);
			bool columnCheck2 = collision(columnPosition2.x, columnPosition2.y, columnPosition2.x + columnSize.width, columnPosition2.y + columnSize.height,
							0, 0, visibleSize.width/2, visibleSize.height);
			if(touchPosition.x<visibleSize.width/2)
			{
				if(columnCheck1)
				{
					actionFlag = true;
					columnUnder1->runAction(action1);
					columnOn1->runAction(action2);
				}else if(columnCheck2)
				{
					actionFlag = true;
					columnUnder2->runAction(action3);
					columnOn2->runAction(action4);
				}
			}else if(touchPosition.x>=visibleSize.width/2)
			{
				if(!columnCheck1)
				{
					actionFlag = true;
					columnUnder1->runAction(action1);
					columnOn1->runAction(action2);
				}else if(!columnCheck2)
				{
					actionFlag = true;
					columnUnder2->runAction(action3);
					columnOn2->runAction(action4);
				}
			}
		}//game-------end
	}while(0);

	return true;
}
void FruitLayer::menuCallback0(Ref* pSender)
{
	sceneManager->goToSquishyScene(1);
}

void FruitLayer::menuCallback1(Ref* pSender)
{
	sceneManager->goToMainScene();
}
void FruitLayer::menuCallback2(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToMainScene();
}
void FruitLayer::menuCallback3(Ref* pSender)
{
	stopFlag = false;
	this->removeChild(pauseBack);
	pause->setTexture("pause.png");
	Director::getInstance()->resume();
}
void FruitLayer::menuCallback4(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToSquishyScene(1);
}
//背景音乐复选框执行方法
void FruitLayer::selectedEvent0(Ref* pSender,CheckBox::EventType type)
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
void FruitLayer::selectedEvent1(Ref* pSender,CheckBox::EventType type)
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
//播放柱子相撞音效
void FruitLayer::wingSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
}
//播放夹爆水果音效
void FruitLayer::eatSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("eat.wav");
}
