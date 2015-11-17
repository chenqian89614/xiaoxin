#include "BirdLayer.h"
#include "MainLayer.h"
#include "Collision.h"
#include "SimpleAudioEngine.h"
#include "RankBirdLayer.h"
#include <time.h>

using namespace cocos2d;
using namespace cocos2d::extension;

//ʵ��BirdLayer���е�init��������ʼ������
bool BirdLayer::init()
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
    stopFlag = false;
    gameFlag = true;
    readyFlag = true;
    overFlag = false;

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

	//����һ������ڵ����
	effectNode = NodeGrid::create();
	//������ڵ���ӵ�����
	this->addChild(effectNode, 1);
	//��ϷԤ������
	ready = Sprite::create("readyBird.png");
	//���þ�������λ��
	ready->setPosition(Point(visibleSize.width/2, visibleSize.height*4/7));
	//��������ӵ�������
	effectNode->addChild(ready, 10);

	//�������澫��1
	floor = Sprite::create("floor.png");
	//����ê��
	floor->setAnchorPoint(Point(0, 0));
	//���þ������λ��
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	//��ȡ���澫��ߴ��С
	Size floorSize = floor->getContentSize();
	//�������
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));
	//����һ��LabelAtlas����
	pLabelAtlas = LabelAtlas::create("0","number.png", 48, 64,'0');
	//����LabelAtlas����λ��
	pLabelAtlas->setPosition(Point(visibleSize.width/2,visibleSize.height/5*4));
	//��LabelAtlas������ӵ�������
	this->addChild(pLabelAtlas,4);

	//������ͣ��ť����
	pause = Sprite::create("pause.png");
	//���þ���λ��
	pause->setPosition(Point(32, 928));
	this->addChild(pause,10);

	//�������㴥������
	EventListenerTouchOneByOne* listenerPause = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerPause->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerPause->onTouchBegan = CC_CALLBACK_2(BirdLayer::onTouchPause, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPause, pause);


	//===========��ʼ��С��===========
	initBird();
	//��ȡ�����ߴ�
	Size backgroundSize = background->getContentSize();
	//����С����
    bird = Sprite::create();
    //���þ���λ��
    bird->setPosition(Point(140 + origin.x, origin.y +floorSize.height + backgroundSize.height/2));
    //��ӵ�������
    this->addChild(bird, 2);
    //���Ŷ���
	bird->runAction(RepeatForever::create(animAc));

    //����һ�����㴥������
	auto listener = EventListenerTouchOneByOne::create();
	//�����´�����
	listener->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listener->onTouchBegan = CC_CALLBACK_2(BirdLayer::onTouchBegan, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
//��ʼ��Ϸ
void BirdLayer::startGame()
{
	//��ȼ������Ϊfalse
	Director::getInstance()->setDepthTest(false);
	effectNode->runAction(SplitRows::create(0.5f, 30));
	initColumn1();
	initColumn2();
	birdRun();
	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//��ʱ�ص�update
	sched->schedule(schedule_selector(BirdLayer::update_column), this, 0.05, false);
	sched->schedule(schedule_selector(BirdLayer::update_bird), this, 0.05, false);
}
void BirdLayer::initBird()
{
	//��ȡ����֡
	SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("bird.plist", "birdP.png");
	//����ͼƬ������
	std::string animBird[3] =
	{
			"bird1.png",
			"bird2.png",
			"bird3.png"
	};
	//������Ŷ���֡������
	Vector<SpriteFrame*> animFrames;
	//��ȡ����֡
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[0]));
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[1]));
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[2]));
	//�����������󣬴�֡�����������������Ϊ0.1��
	Animation *anim = Animation::createWithSpriteFrames(animFrames, 0.1f);
	//����������������
	animAc = Animate::create(anim);
	//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
	animAc->retain();
}
//���������
int BirdLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%5+1;
	return number;
}

void BirdLayer::birdRun()
{
	//С��λ��
	Point birdPosition = bird->getPosition();
	//����ߴ�
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
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�����ߴ��С
	Size backSize = background->getContentSize();
	//��ȡ����ߴ��С
	Size floorSize = floor->getContentSize();
	//��ȡ�����
	int i = random();
	int height1 = 400/i;
	int height2 = backSize.height - height1 - 196;
	//����SpriteBatchNode����
	SpriteBatchNode* columnNode1 = SpriteBatchNode::create("column1.png");
	//����SpriteBatchNode����
	SpriteBatchNode* columnNode2 = SpriteBatchNode::create("column2.png");
	columnFlag1 = true;
	//����Scale9Sprite����
	columnUnder1 = Scale9Sprite::create();
	//����ͼ���������
	columnUnder1->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
	//����ê��
	columnUnder1->setAnchorPoint(Point(0, 0));
	//����ͼ������
	columnUnder1->setContentSize(Size(96, height1));
	if(count>0)
	{
		//����λ��
		columnUnder1->setPosition(Point(visibleSize.width, floorSize.height));
	}else
	{
		//����λ��
		columnUnder1->setPosition(Point(visibleSize.width*2, floorSize.height));
	}
	//����Scale9Sprite����
	columnOn1 = Scale9Sprite::create();
	//����ͼ���������
	columnOn1->updateWithBatchNode(columnNode2, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 370));
	//����ê��
	columnOn1->setAnchorPoint(Point(0, 0));
	//����ͼ������
	columnOn1->setContentSize(Size(96, height2));
	if(count>0)
	{
		//����λ��
		columnOn1->setPosition(Point(visibleSize.width, visibleSize.height - height2));
	}else
	{
		//����λ��
		columnOn1->setPosition(Point(visibleSize.width*2, visibleSize.height - height2));
	}
	//��ӵ�������
	this->addChild(columnUnder1, 0);
	this->addChild(columnOn1, 0);
	columnUnder1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
	columnOn1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
}

void BirdLayer::initColumn2()
{
	columnFlag2 = true;
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�����ߴ��С
	Size backSize = background->getContentSize();
	//��ȡ����ߴ��С
	Size floorSize = floor->getContentSize();
	//��ȡ�����
	int i = random();
	int height1 = 400/i;
	int height2 = backSize.height - height1 - 196;
	//��ȡ����1��λ��
	Point columnPosition = columnUnder1->getPosition();
	//����SpriteBatchNode����
	SpriteBatchNode* columnNode1 = SpriteBatchNode::create("column1.png");
	//����SpriteBatchNode����
	SpriteBatchNode* columnNode2 = SpriteBatchNode::create("column2.png");
	//����Scale9Sprite����
	columnUnder2 = Scale9Sprite::create();
	//����ͼ���������
	columnUnder2->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
	//����ê��
	columnUnder2->setAnchorPoint(Point(0, 0));
	//����ͼ������
	columnUnder2->setContentSize(Size(96, height1));
	//����λ��
	columnUnder2->setPosition(Point(columnPosition.x + 320, floorSize.height));
	//����Scale9Sprite����
	columnOn2 = Scale9Sprite::create();
	//����ͼ���������
	columnOn2->updateWithBatchNode(columnNode2, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 370));
	//����ê��
	columnOn2->setAnchorPoint(Point(0, 0));
	//����ͼ������
	columnOn2->setContentSize(Size(96, height2));
	//����λ��
	columnOn2->setPosition(Point(columnPosition.x + 320, visibleSize.height - height2));
	//��ӵ�������
	this->addChild(columnUnder2, 0);
	this->addChild(columnOn2, 0);
	columnUnder2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
	columnOn2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
}

void BirdLayer::replay()
{
	overFlag = true;
	//����
	string medal;
	//ɾ������
	removeChild(pLabelAtlas);
	Sprite* over = Sprite::create("gameOver.png");
	over->setPosition(Point(270, 1200));
	this->addChild(over, 10);

	overRank = Sprite::create("scoreOver.png");
	overRank->setPosition(Point(270, -100));
	this->addChild(overRank, 10);

	//���¿�ʼ
	replayItem = MenuItemImage::create(
		"replay.png",
		"replay_off.png",
		 CC_CALLBACK_1(BirdLayer::menuCallbackItem0, this) //���ʱִ�еĻص�����
	);
	replayItem->setPosition(Point(150, -250));
	//�������˵�
	menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(BirdLayer::menuCallbackItem1, this) //���ʱִ�еĻص�����
	);
	menuItem->setPosition(Point(380, -250));

	Menu* menu = Menu::create(replayItem, menuItem, NULL);
	//���ò˵�λ��
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
	//ִ�ж���
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
	//��Ϸ����
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

//С��ʱ����
void BirdLayer::update_bird(float delta)
{
	if(gameFlag && !runFlag)
	{
		birdRun();
	}
	//��ȡС��ǰλ��
	Point birdPosition = bird->getPosition();
	//��ȡС��ߴ��С
	Size birdSize = bird->getContentSize();
	//��ȡ����ߴ��С
	Size floorSize = floor->getContentSize();
	//��ȡ����λ��
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnOn1->getPosition();
	Point columnPosition3 = columnUnder2->getPosition();
	Point columnPosition4 = columnOn2->getPosition();
	//��ȡ���ӳߴ��С
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
	//�����ײ
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
		if(gameFlag)//ʧ����ֹͣ����
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
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//��ȡ��ǰ����
	auto location = target->convertToNodeSpace(touch->getLocation());
	//��ȡ����Ĵ�С
	auto size = target->getContentSize();
	//����һ�����ζ������С�뾫����ͬ
	auto rect = Rect(0, 0, size.width, size.height);
	//�жϴ������Ƿ���Ŀ��ķ�Χ��
	if(!stopFlag && rect.containsPoint(location) )
	{
		stopFlag = true;
		pause->setTexture("continue_pause.png");
		Director::getInstance()->pause();
		//--------------------------------------------
		pauseBack = Sprite::create("setBackground.png");
		pauseBack->setPosition(Point(270, 600));
		this->addChild(pauseBack, 10);

		//���ְ�ť
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

		//��Ч��ť
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

		//������Ϸ
		MenuItemImage* conItem = MenuItemImage::create(
				"continue.png",
				"continue_off.png",
				CC_CALLBACK_1(BirdLayer::menuCallbackItem3, this) //���ʱִ�еĻص�����
		);
		conItem->setPosition(Point(80, 80));
		//�������˵�
		MenuItemImage* backItem = MenuItemImage::create(
			"menu.png",
			"menu_off.png",
			 CC_CALLBACK_1(BirdLayer::menuCallbackItem2, this) //���ʱִ�еĻص�����
		);
		backItem->setPosition(Point(225, 80));
		//�������˵�
		MenuItemImage* againItem = MenuItemImage::create(
			"replay.png",
			"replay_off.png",
			 CC_CALLBACK_1(BirdLayer::menuCallbackItem4, this) //���ʱִ�еĻص�����
		);
		againItem->setPosition(Point(370, 80));

		Menu* menu = Menu::create(againItem, conItem, backItem, NULL);
		//���ò˵�λ��
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
//�������˵���ťִ�з���
void BirdLayer::menuCallbackItem2(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToMainScene();
}
//������Ϸ��ťִ�з���
void BirdLayer::menuCallbackItem3(Ref* pSender)
{
	stopFlag = false;
	this->removeChild(pauseBack);
	pause->setTexture("pause.png");
	Director::getInstance()->resume();
}
//���¿�ʼ��Ϸ��ťִ�з���
void BirdLayer::menuCallbackItem4(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToFlappyScene(1);
}
//�������ָ�ѡ��ִ�з���
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
//��Ч��ѡ��ִ�з���
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
