#include "PianoLayer.h"
#include "LoadLayer.h"
#include "AppMacros.h"
#include "MusicUtil.h"
#include "MusicLoad.h"

using namespace cocos2d;
using namespace std;
using namespace ui;

PianoLayer::~PianoLayer()
{
    for(int i=0; i<8; i++)
    {
        LoadLayer::instrument3D.at(i)->release();
    }
}

//实现PianoLayer类中的init方法，初始化布景
bool PianoLayer::init()
{
	//调用父类的初始化
    if ( !Layer::init() )
    {
        return false;
    }
    
    degree = 0;
    musicFlag = false;
    pauseFlag = false;
    instrumentName = "piano";
    instrumentNumber = 1;
    changeFlag = true;
    musicNum = 0;

    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    Sprite* volume = Sprite::create(pic_RESOURE_PATH + "volume_cn.png");				//音量
    volumeSize = volume->getContentSize();
    volume->setScale(1.2);
    volume->setPosition(Point(volumeSize.width/2 + 20, visibleSize.height - volumeSize.height/2));
    this->addChild(volume, 2);

    exit = Sprite::create(pic_RESOURE_PATH + "exit.png");			//退出
    Size exitSize = exit->getContentSize();
    exit->setScale(1.2);
    exit->setPosition(Point(visibleSize.width - exitSize.width/2, visibleSize.height - exitSize.height/2));
    this->addChild(exit, 2);

    slider = Slider::create();
	slider->loadBarTexture(pic_RESOURE_PATH + "soundBackGround.png");
	slider->loadSlidBallTextures(pic_RESOURE_PATH + "transparent.png",pic_RESOURE_PATH + "transparent.png", "");
	slider->loadProgressBarTexture(pic_RESOURE_PATH + "sound.png");
	slider->setAnchorPoint(Point(0, 0.5));
	sliderSize = slider->getContentSize();
	slider->setPercent(CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()*100);
	slider->setPosition(Point(volumeSize.width*1.2 + 20,  visibleSize.height - volumeSize.height/2));
	slider->addEventListener(CC_CALLBACK_2(PianoLayer::sliderEvent, this));
	this->addChild(slider, 5);

	instrument = Sprite::create(pic_RESOURE_PATH + "piano_cn.png");	//选择
    Size selectSize = instrument->getContentSize();
    instrument->setPosition(
    		Point(
    				visibleSize.width - exitSize.width - selectSize.width/2 -20,
    				visibleSize.height - selectSize.height/2
    		));
    this->addChild(instrument, 2);

    selection = Sprite::create(pic_RESOURE_PATH + "back.png");			//背景
    selection->setPosition(
    		Point(
    				visibleSize.width - exitSize.width - selectSize.width/2 -20,
    				visibleSize.height - selectSize.height/2
    		));
    this->addChild(selection, 1);

    Sprite* left = Sprite::create(pic_RESOURE_PATH + "left.png");			//左键
    leftSize = left->getContentSize();
    left->setScale(SCALE);
    left->setPosition(
    		Point(
    				leftSize.width/2*SCALE + 10,
    				visibleSize.height - volumeSize.height - leftSize.height*SCALE/2 - 5
    		));
    this->addChild(left, 2);

    Sprite* right = Sprite::create(pic_RESOURE_PATH + "right.png");		//右键
    rightSize = right->getContentSize();
    right->setScale(SCALE);
    right->setPosition(
    		Point(
    				visibleSize.width - rightSize.width*SCALE/2 - 10,
    				visibleSize.height - volumeSize.height - rightSize.height*SCALE/2 - 5
    		));
    this->addChild(right, 2);

    //第二个参数为最大储存数
    SpriteBatchNode* batchNode = SpriteBatchNode::create(pic_RESOURE_PATH + "white_small.jpg", 50); 		//小键盘
	batchNode->setAnchorPoint(Point(0, 0));
	batchNode->setPosition(
			Point(
					leftSize.width*SCALE + LEFT_INTERVAL,
					visibleSize.height - volumeSize.height - ABOVE_INTERVAL
				));
	this->addChild(batchNode);

	for(int i = 0; i<PIANO_KEY; i++)									//小键盘
	{
		Sprite* whiteSmall = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 34, 57));
		whiteSmall->setScale(SCALE);
		whiteSmall->setAnchorPoint(Point(0, 0));
		smallSize = whiteSmall->getContentSize();
		whiteSmall->setPosition(Point(i*smallSize.width*SCALE,0));
		batchNode->addChild(whiteSmall, 2);
	}

	selectBack = Sprite::create(pic_RESOURE_PATH + "selectBack.png");
	backSize = selectBack->getContentSize();
	selectBack->setPosition(
			Point(
					leftSize.width*SCALE + LEFT_INTERVAL + smallSize.width*SCALE*7 + backSize.width/2,
					visibleSize.height - volumeSize.height - 37
			));
	this->addChild(selectBack, 4);

	float width = PIANO_KEY*smallSize.width*SCALE - backSize.width;   						//总长
	percent = (selectBack->getPosition().x - backSize.width/2 - leftSize.width*SCALE - LEFT_INTERVAL) / width;

	float positionX = -percent*WHITE_INTERVAL*13;									//
	for(int i=0; i<PIANO_KEY; i++)
	{
		Sprite* white = Sprite::create(pic_RESOURE_PATH + "white.png");
		white->setScale(1.12);
		white->setAnchorPoint(Point(0, 0));
		white->setPosition(Point(positionX + i*WHITE_INTERVAL, 0));
		string tempNumber = StringUtils::format("%d", i);
		whiteSize = white->getContentSize();
		piano.insert(pair<string,Sprite*>(tempNumber, white));
	}
	for(int i = PIANO_KEY,j=0;i<38; i++)
	{
		Sprite* black = Sprite::create(pic_RESOURE_PATH + "black.png");
		black->setScale(1.12);
		black->setAnchorPoint(Point(0.5, 0));
		blackSize = black->getContentSize();
		black->setPosition(Point(positionX + (i-21+j)*WHITE_INTERVAL, (whiteSize.height - blackSize.height)*1.12));
		string tempNumber = StringUtils::format("%d", i);
		if((i-21)%5==0||(i-21)==2||(i-21)==7||(i-21)==12)
		{
			j++;
		}
		piano_black.insert(pair<string,Sprite*>(tempNumber, black));
	}

	map<string, Sprite*>::iterator iter;
	for(iter=piano.begin(); iter != piano.end();iter++)
	{
		this->addChild(iter->second, 5);
	}
	for(iter=piano_black.begin(); iter != piano_black.end(); iter++)
	{
		this->addChild(iter->second, 6);
	}

	for(int i = PIANO_KEY,j = 0; i<38; i++)
	{
		Sprite* blackSmall;
		float positionX;
		if(i==37)
		{
			blackSmall = Sprite::create(pic_RESOURE_PATH + "black_small_half.jpg");
			Size size = blackSmall->getContentSize();
			positionX = leftSize.width*SCALE + LEFT_INTERVAL + (i-21+j)*smallSize.width*SCALE-size.width/2;
		}else
		{
			blackSmall = Sprite::create(pic_RESOURE_PATH + "black_small.jpg");
			positionX = leftSize.width*SCALE + LEFT_INTERVAL + (i-21+j)*smallSize.width*SCALE;
		}
		blackSmall->setScale(SCALE);
		blackSmall->setAnchorPoint(Point(0.5, 0));
		blackSmall->setPosition(Point(
				positionX,
				visibleSize.height - volumeSize.height - ABOVE_INTERVAL + smallSize.height*SCALE/2));
		if((i-21)%5==0||(i-21)==2||(i-21)==7||(i-21)==12)
		{
			j++;
		}
		this->addChild(blackSmall, 2);
	}

	//设置定时回调指定方法干活
	auto director = Director::getInstance();
	schedRound = director->getScheduler();

	//创建退出单点触摸监听
	EventListenerTouchOneByOne* listenerExit = EventListenerTouchOneByOne::create();
	//开始触摸时回调onTouchBegan方法
	listenerExit->onTouchBegan = CC_CALLBACK_2(PianoLayer::onTouchExitBegan, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerExit, exit);
	//创建乐器单点触摸监听
	EventListenerTouchOneByOne* listenerSelect = EventListenerTouchOneByOne::create();
	listenerSelect->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerSelect->onTouchBegan = CC_CALLBACK_2(PianoLayer::onTouchBegan, this);
	listenerSelect->onTouchEnded = CC_CALLBACK_2(PianoLayer::onTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerSelect, instrument);
	//创建左箭头单点触摸监听
	EventListenerTouchOneByOne* listenerLeft = EventListenerTouchOneByOne::create();
	listenerLeft->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerLeft->onTouchBegan = CC_CALLBACK_2(PianoLayer::onTouchLeftBegan, this);
	listenerLeft->onTouchEnded = CC_CALLBACK_2(PianoLayer::onTouchLeftEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerLeft, left);
	//创建右箭头单点触摸监听
	EventListenerTouchOneByOne* listenerRight= EventListenerTouchOneByOne::create();
	listenerRight->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerRight->onTouchBegan = CC_CALLBACK_2(PianoLayer::onTouchRightBegan, this);
	listenerRight->onTouchEnded = CC_CALLBACK_2(PianoLayer::onTouchRightEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerRight, right);
	//创建单点触摸监听
	EventListenerTouchOneByOne* listenerBack = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerBack->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerBack->onTouchBegan = CC_CALLBACK_2(PianoLayer::onTouchSelectBegan, this);
	listenerBack->onTouchMoved = CC_CALLBACK_2(PianoLayer::onTouchSelectMoved, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerBack, selectBack);
	//---------------------------------单点触控，用于选择钢琴键-----------------------------
	//创建单点触摸监听
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//开始触摸时回调onTouchBegan方法
	listener->onTouchBegan = CC_CALLBACK_2(PianoLayer::onMyTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//---------------------------------多点触控，用于点击钢琴键------------------------------
	//创建一个多点触摸监听
	auto listenerTouch = EventListenerTouchAllAtOnce::create();
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchesBegan = CC_CALLBACK_2(PianoLayer::onMyTouchesBegan, this);
	//触摸移动时回调onTouchMoved方法
	listenerTouch->onTouchesMoved = CC_CALLBACK_2(PianoLayer::onMyTouchesMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchesEnded = CC_CALLBACK_2(PianoLayer::onMyTouchesEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

    return true;
}
void PianoLayer::sliderEvent(Ref *pSender, Slider::EventType type)		//拖拉条回调方法
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		float f = slider->getPercent();
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(f/100);
	}
}
void PianoLayer::percentUpdate()
{
	Point selectPosition = selectBack->getPosition();
	float width = PIANO_KEY*smallSize.width*SCALE - backSize.width;   //总长
	percent = (selectBack->getPosition().x - backSize.width/2 - leftSize.width*SCALE - LEFT_INTERVAL) / width;
	timeL = (selectPosition.x - backSize.width/2 - leftSize.width*SCALE - LEFT_INTERVAL)/SPEED;
	timeR = (leftSize.width*SCALE + LEFT_INTERVAL + PIANO_KEY*smallSize.width*SCALE - selectPosition.x -  backSize.width/2)/SPEED;
}
void PianoLayer::deleteSelf()
{
	pauseFlag = false;
	slider->setEnabled(true);
	schedRound->pauseTarget(this);
	degree = 0;
	musicNum = 0;
	this->removeChild(menuBack);
	changePic(instrumentNumber);
}
void PianoLayer::changePic(int number)
{
	 switch(number)
	{
	case 1:
		instrument->setTexture(pic_RESOURE_PATH + "piano_cn.png");
		break;
	case 2:
		instrument->setTexture(pic_RESOURE_PATH + "sax_cn.png");
		break;
	case 3:
		instrument->setTexture(pic_RESOURE_PATH + "musicbox_cn.png");
		break;
	case 4:
		instrument->setTexture(pic_RESOURE_PATH + "guitar_cn.png");
		break;
	case 5:
		instrument->setTexture(pic_RESOURE_PATH + "violin_cn.png");
		break;
	case 6:
		instrument->setTexture(pic_RESOURE_PATH + "flute_cn.png");
		break;
	case 7:
		instrument->setTexture(pic_RESOURE_PATH + "crystal_cn.png");
		break;
	case 8:
		instrument->setTexture(pic_RESOURE_PATH + "koto_cn.png");
		break;
	}
}
bool PianoLayer::onTouchExitBegan(Touch* touch, Event* event)
{
	if(pauseFlag)
	{
		return false;
	}
	//获取当前触摸对象，并转化为精灵
	Sprite* target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的尺寸大小
	Size size = target->getContentSize();
	//创建一个矩形对象，大小与目标精灵相等
	Rect rect = Rect(0, 0, size.width, size.height);
	if(rect.containsPoint(location))
	{
		exit->setTexture(pic_RESOURE_PATH + "exit_down.png");
		Director::getInstance()->end();
		return true;
	}else
	{
		return false;
	}
}
bool PianoLayer::onTouchSelectBegan(Touch* touch, Event* event)
{
	if(pauseFlag)
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
	if( rect.containsPoint(location) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
void PianoLayer::onTouchSelectMoved(Touch* touch, Event* event)
{
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto location = touch->getLocation();								//获取当前触摸点
	if(location.x<= leftSize.width*SCALE + LEFT_INTERVAL + backSize.width/2)
	{
		selectBack->setPosition(Point(leftSize.width*SCALE + LEFT_INTERVAL + backSize.width/2, visibleSize.height - volumeSize.height - 37));
	}else if(location.x>=890 - backSize.width/2)
	{
		selectBack->setPosition(Point(visibleSize.width - rightSize.width*SCALE - LEFT_INTERVAL - backSize.width/2, visibleSize.height - volumeSize.height - 37));
	}else
	{
		//设置精灵坐标
		selectBack->setPosition(Point(location.x, visibleSize.height - volumeSize.height - 37));
	}
	percentUpdate();
	float positionX = -percent*WHITE_INTERVAL*13;
	map<string, Sprite*>::iterator iter;
	for(int i = 0; i<PIANO_KEY; i++)
	{
		string number = StringUtils::format("%d", i);
		iter = piano.find(number.c_str());
		iter->second->setPosition(Point(positionX + i*WHITE_INTERVAL, 0));
	}
	for(int i = PIANO_KEY, j=0; i<38; i++)
	{
		string number = StringUtils::format("%d", i);
		iter = piano_black.find(number.c_str());
		iter->second->setPosition(Point(positionX + (i-21+j)*WHITE_INTERVAL, (whiteSize.height - blackSize.height)*1.12));
		if((i-21)%5==0||(i-21)==2||(i-21)==7||(i-21)==12)
		{
			j++;
		}
	}
}
bool PianoLayer::onTouchLeftBegan(Touch* touch, Event* event)
{
	if(pauseFlag)
	{
		return false;
	}
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	Point point = selectBack->getPosition();
	Size selectSize = selectBack->getContentSize();
	//判断触摸点是否在目标的范围内
	if( rect.containsPoint(location) )
	{
		if(point.x<70 + selectSize.width/2)
		{
			return false;
		}else
		{
			percentUpdate();
			selectBack->runAction(MoveTo::create(timeL, Point(leftSize.width*SCALE + LEFT_INTERVAL + backSize.width/2, visibleSize.height - volumeSize.height - 37)));
			map<string, Sprite*>::iterator iter;
			for(int i = 0; i<PIANO_KEY; i++)
			{
				string number = StringUtils::format("%d", i);
				iter = piano.find(number.c_str());
				iter->second->runAction(MoveTo::create(timeL, Point(i*WHITE_INTERVAL, 0)));
			}
			for(int i = PIANO_KEY, j=0; i<38; i++)
			{
				string number = StringUtils::format("%d", i);
				iter = piano_black.find(number.c_str());
				iter->second->runAction(MoveTo::create(timeL, Point((i-21+j)*WHITE_INTERVAL, (whiteSize.height - blackSize.height)*1.12)));
				if((i-21)%5==0||(i-21)==2||(i-21)==7||(i-21)==12)
				{
					j++;
				}
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}
void PianoLayer::onTouchLeftEnded(Touch* touch, Event* event)
{
	selectBack->stopAllActions();
	map<string, Sprite*>::iterator iter;
	for(iter=piano.begin(); iter!= piano.end();iter++)
	{
		iter->second->stopAllActions();
	}
	for(iter = piano_black.begin(); iter != piano_black.end(); iter++)
	{
		iter->second->stopAllActions();
	}
}
bool PianoLayer::onTouchRightBegan(Touch* touch, Event* event)
{
	if(pauseFlag)
	{
		return false;
	}
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	Point point = selectBack->getPosition();
	//判断触摸点是否在目标的范围内
	if( rect.containsPoint(location) )
	{
		if(point.x>=890 - size.width/2)
		{
			return false;
		}else
		{
			percentUpdate();
			float width = -WHITE_INTERVAL*13;
			selectBack->runAction(MoveTo::create(timeR, Point(leftSize.width*SCALE + LEFT_INTERVAL + PIANO_KEY*smallSize.width*SCALE - backSize.width/2, visibleSize.height - volumeSize.height - 37)));
			map<string, Sprite*>::iterator iter;
			for(int i = 0; i<PIANO_KEY; i++)
			{
				string number = StringUtils::format("%d", i);
				iter = piano.find(number.c_str());
				iter->second->runAction(MoveTo::create(timeR, Point(width + i*WHITE_INTERVAL, 0)));
			}
			for(int i = PIANO_KEY, j=0; i<38; i++)
			{
				string number = StringUtils::format("%d", i);
				iter = piano_black.find(number.c_str());
				iter->second->runAction(MoveTo::create(timeR, Point(width + (i-21+j)*WHITE_INTERVAL, (whiteSize.height - blackSize.height)*1.12)));
				if((i-21)%5==0||(i-21)==2||(i-21)==7||(i-21)==12)
				{
					j++;
				}
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}
 void PianoLayer::onTouchRightEnded(Touch* touch, Event* event)
 {
	 selectBack->stopAllActions();
	 map<string, Sprite*>::iterator iter;
	for(iter=piano.begin(); iter!= piano.end();iter++)
	{
		iter->second->stopAllActions();
	}
	for(iter = piano_black.begin(); iter != piano_black.end(); iter++)
	{
		iter->second->stopAllActions();
	}
 }

 bool PianoLayer::onTouchBegan(Touch* touch, Event* event)
 {
	 if(pauseFlag)
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
	if( rect.containsPoint(location) )
	{
		selection->setTexture(pic_RESOURE_PATH + "back_down.png");
		return true;
	}
	else
	{
		return false;
	}
 }

 void PianoLayer::onTouchEnded(Touch* touch, Event* event)
 {
	 pauseFlag = true;
	 slider->setEnabled(false);
	 //获取可见区域尺寸
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	 selection->setTexture(pic_RESOURE_PATH + "back.png");
	 underside = Sprite::create(pic_RESOURE_PATH + "blackBackGround.png");
	 underside->setPosition(visibleSize.width/2, visibleSize.height/2);
	 this->addChild(underside, 10);
	 menuBack = Sprite::create(pic_RESOURE_PATH + "kuang.png");
	 menuBack->setPosition(visibleSize.width/2, visibleSize.height/2);
	 menuSize = menuBack->getContentSize();
	 underside->addChild(menuBack, 5);
	 for(int i=1, row=0, col=0; i<9; i++)
	 {
		Sprite* selects = Sprite::create(pic_RESOURE_PATH + "instrument.png");
		sSize = selects->getContentSize();
		//-----------------------------------------------------
		string instrument = getInstrumentChinese(i);
		Label* labels = Label::createWithTTF(instrument, fonts_RESOURE_PATH + "FZKATJW.ttf", 40, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		labels->setColor(Color3B::BLACK);
		selects->addChild(labels, 2);
		selects->setScale(0.9);
		labels->setPosition(Point(sSize.width/2 , sSize.height/2));
		selects->setPosition(Point(220 + 260*col, 300 - 80*row));
		if(i%2 == 0)
		{
			 row++;
			 col--;
		}else
		{
			 col++;
		}
		string number = StringUtils::format("%d", i);
		select.insert(pair<string,Sprite*>(number, selects));
	 }
	 map<string,Sprite*>::iterator iter;
	 for(iter = select.begin(); iter!=select.end(); iter++)
	 {
		 int number = atoi(iter->first.c_str());
		 if(number == instrumentNumber)
		 {
			 iter->second->setTexture(pic_RESOURE_PATH + "yellow.png");
		 }
		 menuBack->addChild(iter->second, 1);
	 }

	 //创建单点触摸监听
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listener->setSwallowTouches(false);
	//开始触摸时回调onTouchBegan方法
	listener->onTouchBegan = CC_CALLBACK_2(PianoLayer::onTouchBeganInstrument, this);
	listener->onTouchEnded = CC_CALLBACK_2(PianoLayer::onTouchEndedInstrument, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, underside);

 }
 //-----------------------------------------------------------------------------------选择乐器
 bool PianoLayer::onTouchBeganInstrument(Touch* touch, Event* event)
 {
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	bool flag = false;
	int number;
	map<string, Sprite*>::iterator iter;
	for(iter = select.begin(); iter != select.end(); iter++)
	{
		float xMax = iter->second->getPosition().x + sSize.width/2 + visibleSize.width/2 - menuSize.width/2;
		float xMin = iter->second->getPosition().x - sSize.width/2 + visibleSize.width/2 - menuSize.width/2;
		float yMax = iter->second->getPosition().y + sSize.height/2 + visibleSize.height/2 - menuSize.height/2;
		float yMin = iter->second->getPosition().y - sSize.height/2 + visibleSize.height/2 - menuSize.height/2;
		if(touch->getLocation().x<xMax && touch->getLocation().x>xMin && touch->getLocation().y>yMin && touch->getLocation().y<yMax)
		{
			flag = true;
			iter->second->setTexture(pic_RESOURE_PATH + "yellow.png");
			number = atoi(iter->first.c_str());
			break;
		}
	}
	if(!flag)
	{
		return false;
	}
	if(number != instrumentNumber)
	{
		RemoveMusic(instrumentName);
		instrumentNumber = number;
		instrumentName = getInstrument(instrumentNumber);
		return true;
	}else
	{
		pauseFlag = false;
		this->removeChild(underside);
		for(int i=1; i<9; i++)
		{
			string no = StringUtils::format("%d", i);
			iter = select.find(no);
			select.erase(iter);
		}
		slider->setEnabled(true);
		return false;
	}
 }
 void PianoLayer::onTouchEndedInstrument(Touch* touch, Event* event)
 {
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	map<string, Sprite*>::iterator iter;
	for(int i=1; i<9; i++)
	{
		string no = StringUtils::format("%d", i);
		iter = select.find(no);
		select.erase(iter);
	}
	this->removeChild(underside);

	menuBack = Sprite::create(pic_RESOURE_PATH + "kuang.png");						//----------------------------------------------
	menuBack->setPosition(Point(visibleSize.width/2, visibleSize.height/2-70));
	Size boxSize = menuBack->getContentSize();
    Label* label = Label::createWithTTF("\u65b0\u7684\u4e50\u5668\u58f0\u97f3\u8d44\u6e90\u6b63\u5728\u52a0\u8f7d\u4e2d\uff0c\u8bf7\u7a0d\u7b49!!!",fonts_RESOURE_PATH + "FZKATJW.ttf", 60);
	label->setWidth(360);
	menuBack->addChild(label, 1);
	label->setPosition(Point(boxSize.width/2+100, boxSize.height/2));

	//------------------------------------- 3D --------------------------------
	menuBack->addChild(LoadLayer::instrument3D.at(instrumentNumber-1), 3);
	LoadLayer::instrument3D.at(instrumentNumber-1)->setPosition(Point(boxSize.width/4-25, boxSize.height/2-50));

	if(changeFlag)
	{
		schedRound->schedule(schedule_selector(PianoLayer::update), this, 0.01, false);
		changeFlag = false;
	}else
	{
		//定时回调update
		schedRound->resumeTarget(this);
	}

	this->addChild(menuBack, 10);
 }

 void PianoLayer::update(float delta)
 {
	if(degree%10 == 0)
	{
		LoadMusic(instrumentName, musicNum);
		musicNum++;
	}
	degree+=1;

	if(degree <= 370)
	{
		LoadLayer::instrument3D.at(instrumentNumber-1)->setRotation3D(Vertex3F(0, degree, 0));
	}else
	{
		deleteSelf();
	}
 }

void PianoLayer::onMyTouchesBegan(const std::vector<Touch*>& pTouches, Event *pEvent)
{
	if(pauseFlag)
	{
		return;
	}
	string number;
	musicFlag = false;
	//获取触控点列表的迭代器
	auto touchIter = pTouches.begin();
	//迭代器
	map<string, Sprite*>::iterator iter;
	map<string, Sprite*>::iterator iter_black;
	//通过迭代器遍历触控点列表
	for (; touchIter != pTouches.end(); touchIter++)
	{
		//获取一个触控点
		auto pTouch = (Touch*)(*touchIter);
		for(iter = piano.begin(); iter != piano.end(); iter++)
		{
			Point positionSprite = iter->second->getPosition();
			float xMax = positionSprite.x + whiteSize.width*1.12;
			float xMin = positionSprite.x;
			float yMax = positionSprite.y + whiteSize.height*1.12;
			float yMin = positionSprite.y;
			//判断触摸点是否在目标的范围内
			if(pTouch->getLocation().x>xMin && pTouch->getLocation().x<xMax && pTouch->getLocation().y>yMin && pTouch->getLocation().y<yMax)
			{
				touchIndex[pTouch->getID()] = atoi(iter->first.c_str());
				for(iter_black = piano_black.begin(); iter_black != piano_black.end(); iter_black++)
				{
					float xMaxB = iter_black->second->getPosition().x + blackSize.width*1.12/2;
					float xMinB = iter_black->second->getPosition().x - blackSize.width*1.12/2;
					float yMaxB = iter_black->second->getPosition().y + blackSize.height*1.12;
					float yMinB = iter_black->second->getPosition().y;
					if(pTouch->getLocation().x>xMinB && pTouch->getLocation().x<xMaxB && pTouch->getLocation().y>yMinB && pTouch->getLocation().y<yMaxB)
					{
						index = touchIndex[pTouch->getID()];
						number = iter_black->first;
						temp[pTouch->getID()] = atoi(iter_black->first.c_str());
						iter_black->second->setTexture(pic_RESOURE_PATH + "black_down.png");
						if(blackIndex[pTouch->getID()] == 0 && !musicFlag)
						{
							int musicIndex = atoi(number.c_str());					//点击的琴键对应的标号
							playMusic(musicIndex, instrumentName);
							musicFlag = true;
						}
						blackIndex[pTouch->getID()] = atoi(iter_black->first.c_str());
						break;
					}
				}
				if(blackIndex[pTouch->getID()] != 0)
				{
					break;
				}
				iter->second->setTexture(pic_RESOURE_PATH + "white_down.png");
				number = iter->first;
				if(!musicFlag)
				{
					int musicIndex = atoi(number.c_str());					//点击的琴键对应的标号
					playMusic(musicIndex, instrumentName);
					musicFlag = true;
				}
			}
		}
	}
}

 void PianoLayer::onMyTouchesMoved(const std::vector<Touch*>& pTouches, Event *pEvent)
 {
	if(pauseFlag)
	{
		return;
	}
    //记录琴键坐标
	float xMax;
	float xMin;
	float yMax;
	float yMin;
	//获取触控点列表的迭代器
	auto touchIter = pTouches.begin();
	//通过迭代器遍历触控点列表
	for (; touchIter != pTouches.end(); touchIter++)
	{
		auto pTouch = (Touch*)(*touchIter);
		string number0 = StringUtils::format("%d", touchIndex[pTouch->getID()]);
		string number1 = StringUtils::format("%d", touchIndex[pTouch->getID()]+1);
		string number2 = StringUtils::format("%d",touchIndex[pTouch->getID()]-1);
		map<string, Sprite*>::iterator iter = piano.find(number0.c_str());
		map<string, Sprite*>::iterator iter_next;
		map<string, Sprite*>::iterator iter_last;
		map<string, Sprite*>::iterator iter_black;

		for(iter_black = piano_black.begin(); iter_black != piano_black.end(); iter_black++)		//移动到黑键
		{
			musicFlag = false;
			xMax = iter_black->second->getPosition().x + blackSize.width*1.12/2;
			xMin = iter_black->second->getPosition().x - blackSize.width*1.12/2;
			yMax = iter_black->second->getPosition().y + blackSize.height*1.12;
			yMin = iter_black->second->getPosition().y;
			if(pTouch->getLocation().x>xMin && pTouch->getLocation().x<xMax && pTouch->getLocation().y>yMin && pTouch->getLocation().y<yMax)
			{
				blackIndex[pTouch->getID()] = atoi(iter_black->first.c_str());
				if(temp[pTouch->getID()] != blackIndex[pTouch->getID()])
				{
					index = atoi(iter->first.c_str());
					temp[pTouch->getID()] = blackIndex[pTouch->getID()];
					iter_black->second->setTexture(pic_RESOURE_PATH + "black_down.png");
					iter->second->setTexture(pic_RESOURE_PATH + "white.png");
					if(!musicFlag)
					{
						int musicIndex = atoi(iter_black->first.c_str());					//点击的琴键对应的标号
						playMusic(musicIndex, instrumentName);
						musicFlag = true;
					}
				}
			}
		}
		if(touchIndex[pTouch->getID()] != 21)										//不为最后一个白键，才有下一个
		{
			iter_next = piano.find(number1.c_str());
			xMax = iter_next->second->getPosition().x + whiteSize.width*1.12;
			xMin = iter_next->second->getPosition().x;
			yMax = iter_next->second->getPosition().y + whiteSize.height*1.12;
			yMin = iter_next->second->getPosition().y;
			if(pTouch->getLocation().x>xMin && pTouch->getLocation().x<xMax && pTouch->getLocation().y>yMin && pTouch->getLocation().y<yMax)	//向右移动
			{
				musicFlag = false;
				if(blackIndex[pTouch->getID()] != 0)
				{
					string number = StringUtils::format("%d", blackIndex[pTouch->getID()]);
					blackIndex[pTouch->getID()] = 0;
					temp[pTouch->getID()] = 0;
					piano_black.find(number.c_str())->second->setTexture(pic_RESOURE_PATH + "black.png");
				}
				iter->second->setTexture(pic_RESOURE_PATH + "white.png");
				iter_next->second->setTexture(pic_RESOURE_PATH + "white_down.png");
				if(!musicFlag)
				{
					int musicIndex = atoi(iter_next->first.c_str());					//点击的琴键对应的标号
					playMusic(musicIndex, instrumentName);
					musicFlag = true;
				}
				touchIndex[pTouch->getID()]++;
				continue;
			}
		}
		if(touchIndex[pTouch->getID()] != 0)										//不为第一个白键，才有上一个
		{
			iter_last = piano.find(number2.c_str());
			xMax = iter_last->second->getPosition().x + whiteSize.width*1.12;
			xMin = iter_last->second->getPosition().x;
			yMax = iter_last->second->getPosition().y + whiteSize.height*1.12;
			yMin = iter_last->second->getPosition().y;
			if(pTouch->getLocation().x>xMin && pTouch->getLocation().x<xMax && pTouch->getLocation().y>yMin && pTouch->getLocation().y<yMax)	//向左移动
			{
				musicFlag = false;
				if(blackIndex[pTouch->getID()] != 0)
				{
					string number = StringUtils::format("%d", blackIndex[pTouch->getID()]);
					blackIndex[pTouch->getID()] = 0;
					temp[pTouch->getID()] = 0;
					piano_black.find(number.c_str())->second->setTexture(pic_RESOURE_PATH + "black.png");
				}
				iter->second->setTexture(pic_RESOURE_PATH + "white.png");
				iter_last->second->setTexture(pic_RESOURE_PATH + "white_down.png");
				if(!musicFlag)
				{
					int musicIndex = atoi(iter_last->first.c_str());					//点击的琴键对应的标号
					playMusic(musicIndex, instrumentName);
					musicFlag = true;
				}
				touchIndex[pTouch->getID()]--;
				continue;
			}
		}
		if(blackIndex[pTouch->getID()] != 0)
		{
			musicFlag = false;
			string number = StringUtils::format("%d", index);
			iter = piano.find(number.c_str());
			number = StringUtils::format("%d", blackIndex[pTouch->getID()]);
			iter_black = piano_black.find(number.c_str());
			xMax = iter->second->getPosition().x + whiteSize.width*1.12;
			xMin = iter->second->getPosition().x;
			yMax = iter->second->getPosition().y + whiteSize.height*1.12;
			yMin = iter->second->getPosition().y;
			if(pTouch->getLocation().x>xMin && pTouch->getLocation().x<xMax && pTouch->getLocation().y>yMin && pTouch->getLocation().y<yMax)
			{
				if(xMin<iter_black->second->getPosition().x)
				{
					if(pTouch->getLocation().x<(iter_black->second->getPosition().x-blackSize.width*1.12/2) || pTouch->getLocation().y<(iter_black->second->getPosition().y-blackSize.height*1.12))
					{
						iter_black->second->setTexture(pic_RESOURE_PATH + "black.png");
						iter->second->setTexture(pic_RESOURE_PATH + "white_down.png");
						touchIndex[pTouch->getID()] = atoi(iter->first.c_str());
						blackIndex[pTouch->getID()] = 0;
						temp[pTouch->getID()] = 0;
						if(!musicFlag)
						{
							int musicIndex = atoi(iter->first.c_str());					//点击的琴键对应的标号
							playMusic(musicIndex, instrumentName);
							musicFlag = true;
						}
					}
				}else if(xMin==iter_black->second->getPosition().x)
				{
					if(pTouch->getLocation().x>(iter_black->second->getPosition().x+blackSize.width*1.12/2) || pTouch->getLocation().y<(iter_black->second->getPosition().y-blackSize.height*1.12))
					{
						iter_black->second->setTexture(pic_RESOURE_PATH + "black.png");
						iter->second->setTexture(pic_RESOURE_PATH + "white_down.png");
						touchIndex[pTouch->getID()] = atoi(iter->first.c_str());
						blackIndex[pTouch->getID()] = 0;
						temp[pTouch->getID()] = 0;
						if(!musicFlag)
						{
							int musicIndex = atoi(iter->first.c_str());					//点击的琴键对应的标号
							playMusic(musicIndex, instrumentName);
							musicFlag = true;
						}
					}
				}
			}
		}
	}
 }

void PianoLayer::onMyTouchesEnded(const std::vector<Touch*>& pTouches, Event *pEvent)
{
	//获取触控点列表的迭代器
	auto touchIter = pTouches.begin();
	//通过迭代器遍历触控点列表
	for(; touchIter != pTouches.end(); touchIter++)
	{
		auto pTouch = (Touch*)(*touchIter);
		string number = StringUtils::format("%d", touchIndex[pTouch->getID()]);
		map<string, Sprite*>::iterator iter = piano.find(number.c_str());
		iter->second->setTexture(pic_RESOURE_PATH + "white.png");
		if(blackIndex[pTouch->getID()] != 0)					//判断是否有黑键被按下
		{
			number = StringUtils::format("%d", blackIndex[pTouch->getID()]);
			iter = piano_black.find(number.c_str());
			iter->second->setTexture(pic_RESOURE_PATH + "black.png");
			blackIndex[pTouch->getID()] = 0;
			temp[pTouch->getID()] = 0;
		}
	}
	musicFlag = false;
}

bool PianoLayer::onMyTouchBegan(Touch* touch, Event* event)	//选择框事件触控事件
{
	if(pauseFlag)
	 {
		 return false;
	 }
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float xMin = leftSize.width*SCALE + LEFT_INTERVAL + backSize.width/2;
	float xMax = xMin + PIANO_KEY*smallSize.width*SCALE -  backSize.width;
	float yMin = visibleSize.height - volumeSize.height - 37 - smallSize.height/2*SCALE;
	float yMax = yMin + smallSize.height*SCALE;
	float soundXMax = volumeSize.width*1.2 + 20 + sliderSize.width;
	float soundXMin = volumeSize.width*1.2 + 20;
	float soundYMax = visibleSize.height - volumeSize.height/2 + sliderSize.height/2;
	float soundYMin = visibleSize.height - volumeSize.height/2 - sliderSize.height/2;
	if(touch->getLocation().x>xMin - backSize.width/2 && touch->getLocation().x<xMin && touch->getLocation().y>yMin && touch->getLocation().y<yMax)
	{
		selectBack->setPosition(Point(xMin , yMin + smallSize.height/2*SCALE));
	}else if(touch->getLocation().x<xMax + backSize.width/2 && touch->getLocation().x>xMax && touch->getLocation().y>yMin && touch->getLocation().y<yMax)
	{
		selectBack->setPosition(Point(xMax , yMin +  smallSize.height/2*SCALE));
	}else if(touch->getLocation().x>xMin && touch->getLocation().x<xMax && touch->getLocation().y>yMin && touch->getLocation().y<yMax)
	{
		selectBack->setPosition(Point(touch->getLocation().x, yMin + smallSize.height/2*SCALE));
	}else if(touch->getLocation().x>soundXMin && touch->getLocation().x<soundXMax && touch->getLocation().y>soundYMin && touch->getLocation().y<soundYMax){
		float p = (touch->getLocation().x - soundXMin)/sliderSize.width;
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(p);
		slider->setPercent(p*100);
	}else
	{
		return false;
	}
	percentUpdate();
	float positionX = -percent*WHITE_INTERVAL*13;
	map<string, Sprite*>::iterator iter;
	for(int i = 0; i<PIANO_KEY; i++)
	{
		string number = StringUtils::format("%d", i);
		iter = piano.find(number.c_str());
		iter->second->setPosition(Point(positionX + i*WHITE_INTERVAL, 0));
	}
	for(int i = PIANO_KEY, j=0; i<38; i++)
	{
		string number = StringUtils::format("%d", i);
		iter = piano_black.find(number.c_str());
		iter->second->setPosition(Point(positionX + (i-21+j)*WHITE_INTERVAL, (whiteSize.height - blackSize.height)*1.12));
		if((i-21)%5==0||(i-21)==2||(i-21)==7||(i-21)==12)
		{
			j++;
		}
	}
	return true;
}
