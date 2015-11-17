#include "FruitLayer.h"
#include "Collision.h"
#include "MainLayer.h"
#include "RankFruitLayer.h"
#include "SimpleAudioEngine.h"
#include <time.h>

using namespace cocos2d;
using namespace std;
using namespace ui;

//ʵ��FruitLayer���е�init��������ʼ������
bool FruitLayer::init()
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
	//��Ϸ��ͣ��־λ
	stopFlag = false;
	//��Ϸ��ʼ��־λ
	gameFlag = false;
	//��Ϸ׼����־λ
	readyFlag = true;
	//������ɱ�־λ
	actionFlag = false;
	//
	overFlag = false;
	//����vector
	fruit = new vector<Sprite*>();
	int i = random();
	//������������
	if(i%2==0)
	{
		background = Sprite::create("morning.png");
	}else
	{
		background = Sprite::create("night.png");
	}
	//����ê��
	background->setAnchorPoint(Point(0, 0));
	//���þ�������λ��
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//��������ӵ�������
	this->addChild(background, 0);

	//����һ������ڵ�
	effectNode = NodeGrid::create();
	//������ڵ���ӵ�����
	this->addChild(effectNode, 1);
	//׼������
	ready = Sprite::create("readyFruit.png");
	//���þ�������λ��
	ready->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	//��������ӵ�������
	effectNode->addChild(ready, 0);

	//�������澫��
	floor = Sprite::create("floor.png");
	//����ê��
	floor->setAnchorPoint(Point(0, 0));
	//���þ������λ��
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor, 4);
	//�������
	floor->runAction(RepeatForever::create(
		Sequence::create
		(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
		)
	));

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
	listenerPause->onTouchBegan = CC_CALLBACK_2(FruitLayer::onTouchPause, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPause, pause);

	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(FruitLayer::onTouchBegan, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	return true;
}
//
void FruitLayer::startGame()
{
	//��ȼ������Ϊfalse
	Director::getInstance()->setDepthTest(false);
	//ִ����Ч
	effectNode->runAction(SplitCols::create(1.0f, 20));
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	initColumn1();
	initColumn2();
	gameFlag = true;
	//����һ��LabelAtlas����
	pLabelAtlas = LabelAtlas::create("0", "number.png", 48, 64,'0');
	//����LabelAtlas����λ��
	pLabelAtlas->setPosition(Point(visibleSize.width/5,visibleSize.height/5*4));
	//��LabelAtlas������ӵ�������
	this->addChild(pLabelAtlas,4);
	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//��ʱ�ص�update
	sched->schedule(schedule_selector(FruitLayer::update_fruit), this, 1, false);
	sched->schedule(schedule_selector(FruitLayer::update_boss), this, 20, false);
	sched->schedule(schedule_selector(FruitLayer::update_column), this, 0.1, false);
}
void FruitLayer::initColumn1()
{
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�����
	int i = random();
	int height = -(i*5);
	height1 = 800 - height;
	//����Sprite����
	columnUnder1 = Sprite::create("column1.png");
	//����ê��
	columnUnder1->setAnchorPoint(Point(0, 0));
	//����λ��
	columnUnder1->setPosition(Point(visibleSize.width, height));
	//����Sprite����
	columnOn1 = Sprite::create("column2.png");
	//����ê��
	columnOn1->setAnchorPoint(Point(0, 0));
	//����λ��
	columnOn1->setPosition(Point(visibleSize.width, height1));
	//��ӵ�������
	this->addChild(columnUnder1, 3);
	this->addChild(columnOn1, 3);
	int speed = count*0.05 + 15;
	columnUnder1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
	columnOn1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
}
//
void FruitLayer::initColumn2()
{
	//��ȡ�����
	int i = random();
	int height = -(i*6);
	height2 = 800 - height;
	//��ȡ����1��λ��
	Point columnPosition = columnUnder1->getPosition();
	//����SpriteBatchNode����
	columnUnder2 = Sprite::create("column1.png");
	//����SpriteBatchNode����
	columnOn2 = Sprite::create("column2.png");
	//����ê��
	columnUnder2->setAnchorPoint(Point(0, 0));
	//����λ��
	columnUnder2->setPosition(Point(columnPosition.x + 320, height));
	//����ê��
	columnOn2->setAnchorPoint(Point(0, 0));
	//����λ��
	columnOn2->setPosition(Point(columnPosition.x + 320, height2));
	//��ӵ�������
	this->addChild(columnUnder2, 3);
	this->addChild(columnOn2, 3);
	int speed = count*0.05 + 15;
	columnUnder2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
	columnOn2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-speed, 0))));
}
//���������
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
		//��ȡ�����
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
//��ʱ�ص����ִ�ˮ���ķ���
void FruitLayer::update_boss(float delta)
{
	if(gameFlag)
	{
		//��ȡ�����
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
//��������λ�ã����Ҽ���Ƿ���ˮ�������ұ�
void FruitLayer::update_column(float delta)
{
	//��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ����λ��
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnUnder2->getPosition();
	//��ȡ���ӳߴ��С
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
	//��ȡ�����е�ˮ������
	vector<Sprite*>::iterator iter;
	for(iter = fruit->begin(); iter != fruit->end(); iter++)
	{
		//��ȡ��ǰˮ��λ��
		Point fruitPosition = (*iter)->getPosition();
		//��ȡ��ǰˮ���ĳߴ��С
		Size fruitSize = (*iter)->getContentSize();
		if(fruitPosition.x >= (visibleSize.width-fruitSize.width/2))
		{
			gameOver();
		}
	}
	if(bossFlag)
	{
		//��ȡ��ǰˮ��λ��
		Point bossPosition = bossSprite->getPosition();
		//��ȡ��ǰˮ���ĳߴ��С
		Size bossSize = bossSprite->getContentSize();
		if(bossPosition.x >= (visibleSize.width-bossSize.width/2))
		{
			gameOver();
		}
	}
}
//��ײ���
void FruitLayer::check()
{
	//��ȡ����λ��
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnOn1->getPosition();
	Point columnPosition3 = columnUnder2->getPosition();
	Point columnPosition4 = columnOn2->getPosition();
	//��ȡ���ӳߴ��С
	Size columnSize = columnUnder1->getContentSize();
	//��ȡ�����е�ˮ������
	vector<Sprite*>::iterator iter;
	for(iter = fruit->begin(); iter != fruit->end();)
	{
		//��ȡ��ǰˮ��λ��
		Point fruitPosition = (*iter)->getPosition();
		//��ȡ��ǰˮ���ĳߴ��С
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
			//������ը����ϵͳЧ��
			ParticleSystemQuad*  psq = ParticleExplosion::create();
			//��������
			psq->retain();
			psq->setLife(0.5f);
			//������ϵͳ��ӵ�������
			this->addChild(psq, 1);
			//Ϊ����ϵͳ����ͼƬ
			psq->setTexture( Director::getInstance()->getTextureCache()->addImage("fire.png") );
			//��������ϵͳ��λ��
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
		//��ȡ��ǰˮ��λ��
		Point bossPosition = bossSprite->getPosition();
		//��ȡ��ǰˮ���ĳߴ��С
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
	//��Ϸ����
	gameFlag = false;
	//ֹͣ����
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
	//��ȡ�����е�ˮ������
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
	//����
	string medal;
	removeChild(pLabelAtlas);
	//----------------------------------------------------------------------------
	Sprite* over = Sprite::create("gameOver.png");
	over->setPosition(Point(270, 1200));
	this->addChild(over, 10);

	overRank = Sprite::create("scoreOver.png");
	overRank->setPosition(Point(270, -100));
	this->addChild(overRank, 10);

	//���¿�ʼ
	relayItem = MenuItemImage::create(
		"replay.png",
		"replay_off.png",
		 CC_CALLBACK_1(FruitLayer::menuCallback0, this) //���ʱִ�еĻص�����
	);
	relayItem->setPosition(Point(150, -250));
	//�������˵�
	menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(FruitLayer::menuCallback1, this) //���ʱִ�еĻص�����
	);
	menuItem->setPosition(Point(380, -250));

	Menu* menu = Menu::create(relayItem, menuItem, NULL);
	//���ò˵�λ��
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
	//ִ�ж���
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
		checkMusic->addEventListener(CC_CALLBACK_2(FruitLayer::selectedEvent0, this));

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
		checkSound->addEventListener(CC_CALLBACK_2(FruitLayer::selectedEvent1, this));


		//������Ϸ
		MenuItemImage* conItem = MenuItemImage::create(
				"continue.png",
				"continue_off.png",
				CC_CALLBACK_1(FruitLayer::menuCallback3, this) //���ʱִ�еĻص�����
		);
		conItem->setPosition(Point(80, 80));
		//�������˵�
		MenuItemImage* backItem = MenuItemImage::create(
			"menu.png",
			"menu_off.png",
			 CC_CALLBACK_1(FruitLayer::menuCallback2, this) //���ʱִ�еĻص�����
		);
		backItem->setPosition(Point(225, 80));
		//�������˵�
		MenuItemImage* againItem = MenuItemImage::create(
			"replay.png",
			"replay_off.png",
			 CC_CALLBACK_1(FruitLayer::menuCallback4, this) //���ʱִ�еĻص�����
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
void FruitLayer::setFlag()
{
	actionFlag = false;
}
//��ʼ���㴥���¼��Ĵ�����
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
		//��ȡ�ɼ�����ߴ�
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ��ǰ����λ��
		Point touchPosition = touch->getLocation();
		//��ȡ���ӵ�λ��
		int compression1 = height1 - 600;
		int compression2 = height2 - 600;
		//���ö���
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
			//��ȡ���ӳߴ��С
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
//�������ָ�ѡ��ִ�з���
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
//��Ч��ѡ��ִ�з���
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
//����������ײ��Ч
void FruitLayer::wingSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
}
//���żб�ˮ����Ч
void FruitLayer::eatSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("eat.wav");
}
