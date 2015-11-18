#include "GameLayer.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include "ChooseCarLayer.h"
#include "PlayerCar.h"
#include "EnemyCar.h"
#include "vector"
#include "CollisionTest.h"
#include "Coin.h"
#include "Rocket.h"
#include "StartLayer.h"
#include "ChooseLevelLayer.h"
#include "Constant.h"
#include "GameOverLayer.h"


using namespace cocos2d;
bool GameLayer::isGameOver = false ;

bool GameLayer::init()
{
	//调用父类的初始化
	if (!Layer::init())
	{
	    return false;
	}
    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    initYBP();

    int level = ChooseLevelLayer::currLevel + 1;
    if(level == 0)
    {
    	level = 1;
    }
   	//创建滚屏背景精灵
   	bgSpriteO = Sprite::create(StringUtils::format("scene%d.jpg",level));
 		bgSpriteO->setPosition(270,480);
   	this->addChild(bgSpriteO,BGZORDER);

   	bgSpriteT = Sprite::create(StringUtils::format("scene%d.jpg",level));
   	bgSpriteT->setPosition(270,1440);
   	this->addChild(bgSpriteT,BGZORDER+1);

   	distanceLabel = LabelAtlas::create(						//创建一个LabelAtlas对象
							 "0","upNum.png",20,23,'0');
	distanceLabel->setAnchorPoint(Point(1,0.5));				//设置LabelAtlas对象锚点
	distanceLabel->setPosition(								//设置LabelAtlas对象位置
						Point(360,910));
	this->addChild(distanceLabel,DJZORDER);						//将LabelAtlas对象添加到布景中

	rocketLabel = LabelAtlas::create(						//创建一个LabelAtlas对象
			StringUtils::format("%d",rocketCount)
			,"upNum.png",20,23,'0');
	rocketLabel->setAnchorPoint(Point(0.5,0.5));				//设置LabelAtlas对象锚点
	rocketLabel->setPosition(								//设置LabelAtlas对象位置
					Point(90,100));
	this->addChild(rocketLabel,DJZORDER);						//将LabelAtlas对象添加到布景中

	no2Label = LabelAtlas::create(							//创建一个LabelAtlas对象
				 "0","upNum.png",20,23,'0');
	no2Label->setAnchorPoint(Point(0.5,0.5));				//设置LabelAtlas对象锚点
	no2Label->setPosition(Point(450,100));					//设置LabelAtlas对象位置
	this->addChild(no2Label,DJZORDER);						//将LabelAtlas对象添加到布景中
	no2Label->setString(StringUtils::format("%d",no2Count));

	goldLabel = LabelAtlas::create(				//创建一个LabelAtlas对象
			 "0","upNum.png",20,23,'0');
	goldLabel->setAnchorPoint(Point(0,0.5));		//设置LabelAtlas对象锚点
	goldLabel->setPosition(							//设置LabelAtlas对象位置
						Point(440,910));
	this->addChild(goldLabel,DJZORDER);						//将LabelAtlas对象添加到布景中

	if(StartLayer::gameModeLevel == 0)
	{
		StartLayer::gameMode = 0;
		restTimeLabel = LabelAtlas::create(						//创建一个LabelAtlas对象
				StringUtils::format("%d",restTime)
				,"upNum.png",20,23,'0');
		restTimeLabel->setPosition(								//设置LabelAtlas对象位置
						Point(170,900));
		this->addChild(restTimeLabel,DJZORDER);						//将LabelAtlas对象添加到布景中

		Sprite* txtundSP = Sprite::create("txtund.png");
		txtundSP->setPosition(Point(270,800));
		this->addChild(txtundSP,MYCARZORDER,101);

		std::string ss ;
		switch(ChooseLevelLayer::currLevel)
		{
		case 0: ss = "\u83b7\u53d620\u91d1\u5e01";break;
		case 1:	ss = "\u81f3\u5c11\u5f00\u51fa2000\u7c73\u4ee5\u5916";break;
		case 2:	ss = "\u4fdd\u6301\u5b8c\u6574\u7684\u8840\u91cf";break;
		}
		Label* taskLabel = Label::createWithTTF(ss,"FZKATJW.ttf",48);
		taskLabel->setPosition(Point(600,50));
		txtundSP->addChild(taskLabel,1);

		taskLabel->runAction(
				Sequence::create(
						MoveTo::create(5,Point(-50,50)),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeTaskSP,this)),
						NULL));
	}

   	//创建下一个菜单项
	pauseItem = MenuItemImage::create(
			   "pauseN.png",						//平时的图片
			   "pauseP.png",						//选中时的图片
			   CC_CALLBACK_0(GameLayer::pauseMenuCallback, this)//点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	pauseItem->setPosition(Point(0,960));
	pauseItem->setAnchorPoint(Point(0,1));

	//创建菜单对象
	auto menu = Menu::create(pauseItem,NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(menu,DJZORDER);

   	allEnemyCarVCT = new std::vector<EnemyCar*>();
   	delEnemyCarVCT = new std::vector<EnemyCar*>();
   	coinSpriteVCT = new std::vector<Coin*>();
   	delCoinSpriteVCT = new std::vector<Coin*>();
   	rocketSpriteVCT = new std::vector<Rocket*>();
   	delRocketSpriteVCT = new std::vector<Rocket*>();
   	allItemSpriteVCT = new std::vector<Sprite*>();
   	delItemSpriteVCT = new std::vector<Sprite*>();

	initFrameCache();
	gameDataReset();
	initUserData();
   	//初始化玩家的车的方法
   	initPlyerCar();
   	initMusic();
   	//倒计时开车的方法
  	DJHCarFire();

	return true;
}
void GameLayer::initUserData()
{
	rocketCount = myGetIntegerForKey(Constant::userRocketCount);
	rocketLabel->setString(StringUtils::format("%d",rocketCount));

	no2Count = myGetIntegerForKey(Constant::userNo2tCount);
	no2Label->setString(StringUtils::format("%d",no2Count));
}
void GameLayer::removeTaskSP()
{
	this->removeChildByTag(101);
}
void GameLayer::initFrameCache()
{
	initSilver();
	initBigFire();
	initHJFire();
	initBoomHZJL();
	initNo2();
	initNo2Che();
	initSpeedLine();
	initPower();
//	initSparks();
}
void GameLayer::initSilver()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile("silver.plist",
			"silver.png");			//将精灵帧文件以及对应的图片添加到内存中
	std::string silver[10]=
	{								//上下左右四段动画8幅图片的名称
		"silver1.png","silver10.png","silver2.png",
		"silver3.png","silver4.png","silver5.png",
		"silver6.png","silver7.png","silver8.png",
		"silver9.png"
	};
	Vector<SpriteFrame*> animFrames;									//创建存放动画帧的向量
	for(int i=0;i<10;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(silver[i]));	  		//将精灵帧添加到向量中
	}
	Animation* anmi=Animation::createWithSpriteFrames(
		animFrames, 0.15f);  			//创建动画对象，从帧向量产生动画，间隔为0.5秒
	anmiAc[1]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[1]->retain();				//因为暂时不用，保持引用，防止被自动释放
}
void GameLayer::initBigFire()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile("big_fire.plist",
		"big_fire.png");			//将精灵帧文件以及对应的图片添加到内存中
	std::string sa[4]=
	{								//上下左右四段动画8幅图片的名称
		"big_fire1.png","big_fire2.png",
		"big_fire3.png","big_fire4.png"
	};
	Vector<SpriteFrame*> animFrames;									//创建存放动画帧的向量
	for(int i=0;i<4;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//将精灵帧添加到向量中
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames, 0.5f);  			//创建动画对象，从帧向量产生动画，间隔为0.3秒
	anmiAc[0]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[0]->retain();				//因为暂时不用，保持引用，防止被自动释放
}
void GameLayer::initNo2()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile("no2h.plist",
		"no2h.png");			//将精灵帧文件以及对应的图片添加到内存中
	std::string sa[4]=
	{								//上下左右四段动画8幅图片的名称
		"no21.png","no22.png",
		"no23.png","no24.png"
	};
	Vector<SpriteFrame*> animFrames;									//创建存放动画帧的向量
	for(int i=0;i<4;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//将精灵帧添加到向量中
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames,0.1f);  			//创建动画对象，从帧向量产生动画，间隔为0.3秒
	anmiAc[5]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[5]->retain();				//因为暂时不用，保持引用，防止被自动释放
}
void GameLayer::initBoomHZJL()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile("newboom.plist",
			"newboom.png");			//将精灵帧文件以及对应的图片添加到内存中
	std::string newboom[7]=
	{								//上下左右四段动画8幅图片的名称
		"newboom1.png","newboom2.png","newboom3.png",
		"newboom4.png","newboom5.png","newboom6.png",
		"newboom7.png"
	};
	std::string boom[7]=
	{								//上下左右四段动画8幅图片的名称
		"boom1.png","boom2.png","boom3.png",
		"boom4.png","boom5.png","boom6.png",
		"boom7.png"
	};

	Vector<SpriteFrame*> animFrames;
	for(int i=0;i<7;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(newboom[i]));	  		//将精灵帧添加到向量中
	}
	Animation* anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//创建动画对象，从帧向量产生动画，间隔为0.5秒
	anmiAc[3]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[3]->retain();				//因为暂时不用，保持引用，防止被自动释放

	animFrames.clear();
	sfc->addSpriteFramesWithFile("boom.plist",
				"boom.png");			//将精灵帧文件以及对应的图片添加到内存中
	for(int i=0;i<7;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(boom[i]));	  		//将精灵帧添加到向量中
	}
	anmi=Animation::createWithSpriteFrames(
		animFrames, 0.15f);  			//创建动画对象，从帧向量产生动画，间隔为0.5秒
	anmiAc[7]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[7]->retain();				//因为暂时不用，保持引用，防止被自动释放
}
void GameLayer::initNo2Che()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile("no2f.plist",
			"no2f.png");			//将精灵帧文件以及对应的图片添加到内存中
	std::string boom[3]=
	{								//上下左右四段动画8幅图片的名称
		"1.png","2.png","3.png"
	};
	Vector<SpriteFrame*> animFrames;
	for(int i=0;i<3;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(boom[i]));	  		//将精灵帧添加到向量中
	}
	Animation* anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//创建动画对象，从帧向量产生动画，间隔为0.5秒
	anmiAc[6]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[6]->retain();				//因为暂时不用，保持引用，防止被自动释放
}
void GameLayer::initSpeedLine()
{
	std::string sa[6]={						//将所有动画图片的路径储存在数组中
		"speed1.png","speed2.png",
		"speed3.png","speed4.png",
		"speed5.png","speed6.png"
	};
	Vector<SpriteFrame*> animFrames;		//创建存放动画帧的列表对象
	for(int i=0;i<6;i++)
	{

		SpriteFrame *f0=SpriteFrame::create(sa[i],
							Rect(0,0,540,960));	//获取此动画中的指定两个帧
		animFrames.pushBack(f0);				//将这一段动画中的两个帧存放到向量中
	}
	Animation *anmi=Animation::createWithSpriteFrames
			(animFrames, 0.05f);					//创建指向动画对象的指针
	anmiAc[8]=Animate::create(anmi);			//创建动画动作对象
	anmiAc[8]->retain();						//因为暂时不用，所以保持引用，防止被自动释放
}
void GameLayer::initPower()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile("power.plist",
		"power.png");			//将精灵帧文件以及对应的图片添加到内存中
	std::string sa[3]=
	{								//上下左右四段动画8幅图片的名称
		"power1.png","power2.png","power3.png"
	};
	Vector<SpriteFrame*> animFrames;									//创建存放动画帧的向量
	for(int i=0;i<3;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//将精灵帧添加到向量中
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//创建动画对象，从帧向量产生动画，间隔为0.3秒
	anmiAc[9]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[9]->retain();				//因为暂时不用，保持引用，防止被自动释放
}

void GameLayer::initHJFire()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//获取缓冲精灵帧的实例
	sfc->addSpriteFramesWithFile("firef.plist",
		"firef.png");			//将精灵帧文件以及对应的图片添加到内存中
	std::string sa[7]=
	{								//上下左右四段动画8幅图片的名称
		"fire1.png","fire2.png","fire3.png",
		"fire4.png","fire5.png","fire6.png",
		"fire7.png"
	};
	Vector<SpriteFrame*> animFrames;									//创建存放动画帧的向量
	for(int i=0;i<7;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//将精灵帧添加到向量中
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//创建动画对象，从帧向量产生动画，间隔为0.3秒
	anmiAc[2]=Animate::create(anmi);	//创建动画动作对象
	anmiAc[2]->retain();				//因为暂时不用，保持引用，防止被自动释放
}

void GameLayer::gameDataReset()
{
	pointR=0;
	//速度
	v = 0;
	count = 0;
	t = 0;
	lifeValue = 135 ;
	distance = 0;
	restTime = 30;
	gold = 0;
	deltaDistance = 1;
	itemSpeed = 10;
	baseSpeed = 10;
	currItemIndex = -1;
	djsTime=0;
	isGameOver = false ;
	onKeyFlag = false ;
	moveSpan=0;
	allEnemyCarVCT->clear();
	delEnemyCarVCT->clear();
   	coinSpriteVCT->clear();
   	delCoinSpriteVCT->clear();
   	rocketSpriteVCT ->clear();
   	delRocketSpriteVCT->clear();
   	allItemSpriteVCT->clear();
   	delItemSpriteVCT->clear();
}
void GameLayer::initMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()
					->preloadBackgroundMusic("drive.mp3");
}
void GameLayer::distanceUpdate()
{
	distance =distance + deltaDistance;
	distanceLabel->setString(StringUtils::format("%d",distance));
}
void GameLayer::pauseMenuCallback()
{
	Director::getInstance()->pause();
	Device::setAccelerometerEnabled(false);
	pauseItem->setEnabled(false);

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	if(StartLayer::soundFlag==true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//播放音乐
							"background.mp3",
							true
							);
	}

	puaseMenuBg = Sprite::create("MenuBg.png");
	puaseMenuBg->setPosition(Point(270,480));
	this->addChild(puaseMenuBg,MENUZRODER);

	puaseSprite[0] = Sprite::create("Resume.png");
	puaseSprite[0]->setPosition(Point(270,600));
	puaseMenuBg->addChild(puaseSprite[0],MENUZRODER);

	puaseSprite[1] = Sprite::create("Restart.png");
	puaseSprite[1]->setPosition(Point(270,520));
	puaseMenuBg->addChild(puaseSprite[1],MENUZRODER);

	puaseSprite[2] = Sprite::create("MainMenu.png");
	puaseSprite[2]->setPosition(Point(270,440));
	puaseMenuBg->addChild(puaseSprite[2],MENUZRODER);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,puaseSprite[0]);
	for(int i=1;i<3;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),puaseSprite[i]);
	}
}
bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	//获取的当前触摸的对象，并转化为精灵类型
	spriteTouch = static_cast<Sprite*>(event->getCurrentTarget());
	spriteTouch->retain();
	//获取当前坐标
	auto location = spriteTouch->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = spriteTouch->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	//判断触摸点是否在目标的范围内
	if(rect.containsPoint(location)){
		Director::getInstance()->resume();
		pauseItem->setEnabled(true);
	if(StartLayer::soundFlag==true){
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//播放音乐
								"drive.mp3",
								true
								);
	}

	if(spriteTouch==puaseSprite[0])
	{
		Device::setAccelerometerEnabled(true);
		spriteTouch->runAction(
				Sequence::create(
						ScaleTo::create(0.1,3),
						CallFunc::create(CC_CALLBACK_0(GameLayer::resumeMenuCallback,this)),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeMenuBg,this)),
						NULL));
	}else if(spriteTouch==puaseSprite[1]){
		Device::setAccelerometerEnabled(true);
		spriteTouch->runAction(
				Sequence::create(
						ScaleTo::create(0.1,3),
						CallFunc::create(CC_CALLBACK_0(GameLayer::restartMenuCallback,this)),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeMenuBg,this)),
						NULL));
	}else if(spriteTouch==puaseSprite[2]){
		Device::setAccelerometerEnabled(true);
		spriteTouch->runAction(
				Sequence::create(
						ScaleTo::create(0.1,3),
						CallFunc::create(CC_CALLBACK_0(GameLayer::mainMenuCallback,this)),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeMenuBg,this)),
						NULL));
	}
	return true;
	}else
	{
		return false;
	}
}
void GameLayer::gameRestart()
{
	this->removeAllChildren();
	this->unscheduleAllSelectors();
	Device::setAccelerometerEnabled(false);
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	init();
}
void GameLayer::resumeMenuCallback()
{
	Director::getInstance()->resume();
}
void GameLayer::restartMenuCallback()
{
	gameRestart();
}
void GameLayer::mainMenuCallback()
{
	crsm->goMainLayer();
}
void GameLayer::removeMenuBg()
{
	this->removeChild(puaseMenuBg,true);
}
void GameLayer::onTouchEnded(Touch* touch, Event* event)
{
	spriteTouch->runAction(ScaleTo::create(0.1,1));
}
void GameLayer::initYBP()
{
	//下仪表精灵对象
	Sprite* underSprite = Sprite::create("under.png");
	underSprite->setPosition(Point(270,107.5));
	this->addChild(underSprite,YBPZORDER);

	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("life.png");
	lifeSprite = Sprite::createWithTexture(texture1);
	lifeSprite->setTextureRect(Rect(0, 0, 135, 56));
	lifeSprite->setAnchorPoint(Point(0,0));
	lifeSprite->setPosition(Point(130,140));
	this->addChild(lifeSprite,DJZORDER);

	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("no2.png");
	no2Sprite = Sprite::createWithTexture(texture2);
	no2Sprite->setTextureRect(Rect(0, 0, 135, 57));
	no2Sprite->setAnchorPoint(Point(1,0));
	no2Sprite->setPosition(Point(410,140));
	this->addChild(no2Sprite,DJZORDER);

	//创建指针精灵对象
	pointSprite = Sprite::create("point.png");
	pointSprite->setAnchorPoint(Point(0.9,0.5));
	pointSprite->setPosition(Point(270,97));
	this->addChild(pointSprite,DJZORDER);

	//上仪表精灵
	Sprite* upSprite = Sprite::create("up.png");
	upSprite->setPosition(Point(300,910));
	this->addChild(upSprite,YBPZORDER);

	//创建下一个菜单项
	no2Item = MenuItemImage::create(
			   "no2N.png",						//平时的图片
			   "no2P.png",						//选中时的图片
			   CC_CALLBACK_0(GameLayer::JSMenuCallback, this)//点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	no2Item->setPosition(Point(480,150));
	no2Item->setEnabled(false);
	//创建下一个菜单项
	rocketItem = MenuItemImage::create(
			   "rocketN.png",						//平时的图片
			   "rocketP.png",						//选中时的图片
			   CC_CALLBACK_0(GameLayer::rocketMenuCallback, this)//点击时执行的回调方法
		);
	//设置下一个菜单项的位置
	rocketItem->setPosition(Point(80,150));
	rocketItem->setEnabled(false);
	//创建菜单对象
	auto menu = Menu::create(rocketItem,no2Item,NULL);
	//设置菜单位置
	menu->setPosition(Point::ZERO);
	//将菜单添加到布景中
	this->addChild(menu,DJZORDER);
}
void GameLayer::onAcceleration(Acceleration* acc, Event* unused_event)
{
	moveSpan = -acc->y*20;
	angle=moveSpan/20*40;
}
void GameLayer::playerCarUpdate()
{
	//玩家的车左右移动
	if(fabs(moveSpan)<3)
	{
		moveSpan=0;
	}
	playerCar->x =playerCar->playerCarSprite->getPosition().x+moveSpan;
	if(playerCar->x<=130)
	{
		playerCar->x=130;
	}else if(playerCar->x>=400)
	{
		playerCar->x=400;
	}

	//玩家的车方向旋转
	if(fabs(angle)<8)
	{
		angle = 0;
	}else if(angle>40)
	{
		angle = 40;
	}else if(angle<-40)
	{
		angle = -40;
	}
	playerCar->angle = angle;
	//更新车的状态
	playerCar->refresh();
}
void GameLayer::initPlyerCar()
{
	playerCar =new PlayerCar(
			(ChooseCarLayer::currCarNum+1)*10+ChooseCarLayer::currCarNum+1,
			270.0,350.0,0,
			ChooseCarLayer::currCarNum+5,
			//动态计算车的最大速度与最大指针角度
			15+ChooseCarLayer::currCarNum*2,
			90+ChooseCarLayer::currCarNum*10
	);
	playerCar->refresh();
	playerCar->playerCarSprite->retain();
	this->addChild(playerCar->playerCarSprite,5);

	if(StartLayer::yxFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
											   "start.mp3");
	}
}
void GameLayer::DJHCarFire()
{
	//交通
	Sprite* trafficSprite = Sprite::create("traffic.png");
	trafficSprite->setPosition(Point(270,650));
	this->addChild(trafficSprite,5,TRAFFICSPRITETAG);
	for(int i=0;i<3;i++)
	{
		//红灯
		redSprite[i] = Sprite::create("red.png");
		redSprite[i]->setPosition(Point(44,175-i*60));
		trafficSprite->addChild(redSprite[i],3);
		//绿灯
		Sprite* greenSprite = Sprite::create("green.png");
		greenSprite->setPosition(Point(44,175-i*60));
		trafficSprite->addChild(greenSprite,2);
	}
	//开启定时回调，倒计时车启动时间
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::trafficUpdate),this,1,false);
}
void GameLayer::trafficUpdate()
{
	do
	{
		if(djsTime==3)
		{
			djsTime=0;
			this->removeChildByTag(TRAFFICSPRITETAG,true);
			this->unschedule(SEL_SCHEDULE(&GameLayer::trafficUpdate));
			//设置定时回调指定方法干活
			auto director = Director::getInstance();
			auto sched = director->getScheduler();
			//背景滚屏定时回调
			sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::bgUpdate),this,0.001,false);
			if(StartLayer::yxFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("start1.mp3");
			}
			if(StartLayer::soundFlag==true){
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//播放音乐
							"drive.mp3",
							true
							);
			}
			break;
		}
		if(StartLayer::yxFlag == true)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("daojishi.mp3");
		}
		redSprite[djsTime]->setVisible(false);
		djsTime++;
	}while(0);
}
void GameLayer::JSMenuCallback()
{
	do{
		if(no2Count == 0)
		{
			break;
		}else if(no2Count == 1)
		{
			no2Sprite->setTextureRect(Rect(0, 0, 0, 57));
		}
		no2Count --;
		mySetIntegerForKey(Constant::userNo2tCount,no2Count);
		no2Label->setString(StringUtils::format("%d",no2Count));
		playerCar->MAX_Speed = playerCar->MAX_Speed + 5;
		playerCar->MAX_pointR = playerCar->MAX_pointR + 15;
		deltaDistance = 2;
		no2Item->setEnabled(false);
		//车尾氮气==============begin
		Sprite* no2SpriteL = Sprite::create();
		no2SpriteL->setAnchorPoint(Point(0.5,1));
		no2SpriteL->setPosition(Point(15,10));
		playerCar->playerCarSprite->addChild(no2SpriteL,MYCARZORDER,NO2SPRITELTAG);
		no2SpriteL->runAction(
				Sequence::create(
						Repeat::create(anmiAc[5]->clone(),7),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeNo2SpriteL,this)),
						NULL));

		Sprite* no2SpriteR = Sprite::create();
		no2SpriteR->setAnchorPoint(Point(0.5,1));
		no2SpriteR->setPosition(Point(40,10));
		playerCar->playerCarSprite->addChild(no2SpriteR,MYCARZORDER,NO2SPRITERTAG);
		no2SpriteR->runAction(
				Sequence::create(
						Repeat::create(anmiAc[5]->clone(),7),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeNo2SpriteR,this)),
						NULL));
		//车尾氮气==============end

		Sprite* no2Sprite = Sprite::create();
		no2Sprite->setAnchorPoint(Point(0.5,1));
		no2Sprite->setPosition(Point(27,110));
		playerCar->playerCarSprite->addChild(no2Sprite,MYCARZORDER,NO2SPRITETAG);
		no2Sprite->runAction(
				Sequence::create(
						Repeat::create(anmiAc[6]->clone(),10),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeNo2Sprite,this)),
						NULL));

		Sprite* speedLineSprite = Sprite::create();
		speedLineSprite->setPosition(Point(270,480));
		this->addChild(speedLineSprite,1,SPEEDLINESPRITETAG);
		speedLineSprite->runAction(
				Sequence::create(
						Repeat::create(anmiAc[8]->clone(),10),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeSpeedLineSprite,this)),
						NULL));
	}while(0);
}
void GameLayer::removeSpeedLineSprite()
{
	this->removeChildByTag(SPEEDLINESPRITETAG);
}
void GameLayer::removeNo2SpriteL()
{
	playerCar->playerCarSprite->removeChildByTag(NO2SPRITELTAG);
	playerCar->MAX_Speed = playerCar->MAX_Speed - 5;
	playerCar->MAX_pointR = playerCar->MAX_pointR - 15;
	deltaDistance = 1;
	no2Item->setEnabled(true);
}
void GameLayer::removeNo2SpriteR()
{
	playerCar->playerCarSprite->removeChildByTag(NO2SPRITERTAG);
}
void GameLayer::removeNo2Sprite()
{
	playerCar->playerCarSprite->removeChildByTag(NO2SPRITETAG);
}
void GameLayer::rocketMenuCallback()
{
	if(rocketCount>0)
	{
		rocketItem->setEnabled(false);
		Rocket* rocket= new Rocket(playerCar->x,playerCar->y);
		this->addChild(rocket->rocketSprite,ENEMYCARZORDER);
		rocket->refresh();
		rocket->rocketSprite->runAction(RepeatForever::create(anmiAc[2]->clone()));
		rocketSpriteVCT ->push_back(rocket);
		rocketCount = rocketCount - 1;
		mySetIntegerForKey(Constant::userRocketCount,rocketCount);
		rocketLabel->setString(StringUtils::format("%d",rocketCount));
	}
}
void GameLayer::enemyCarUpdate()
{
	int newX = rand()%5;
	int flag = 0;
	int enemyArray[5];
	for(int i =0;i<5;i++)
	{
		enemyArray[i] = -1;
	}
	while(true)
	{
		if(flag == newX)
		{
			break;
		}
		int j = rand()%5;
		bool isRepeat = false;
		for(int i=0;i<5;i++)
		{
			if(j==enemyArray[i])
			{
				isRepeat = true;
				break;
			}
		}
		if(isRepeat == false )
		{
			enemyArray[flag] = j;
			flag++;
		}
	}
	for(int i=0;i<newX;i++)
	{
		if(enemyArray[i]==-1)
		{
			continue;
		}
		EnemyCar* enemyCar= new EnemyCar(99,130+enemyArray[i]*70,1000,baseSpeed+ChooseCarLayer::currCarNum*2,0);
		enemyCar->refresh();
		this->addChild(enemyCar->enemyCarSprite,ENEMYCARZORDER);
		allEnemyCarVCT->push_back(enemyCar);
	}
}
//=====================================================
void GameLayer::addStageUpdate()
{
	int stageIndex = rand()%4;
	int newX = rand()%270;
	Sprite* itemSprite = NULL;
	switch(stageIndex)
	{
	case 0://金币道具
		for(int i=0;i<10;i++)
		{
			Coin* coin = new Coin(130+newX,970+i*30);
			this->addChild(coin->coinSprite,COINZORDER);
			coin->refresh();
			coin->coinSprite->runAction(RepeatForever::create(anmiAc[1]->clone()));
			coinSpriteVCT->push_back(coin);
		}
		break;
	case 1://火箭道具
		itemSprite = Sprite::create("item_rocket.png");
		itemSprite->setPosition(Point(130+newX,970));
		this->addChild(itemSprite,COINZORDER);
		//加入向量中
		allItemSpriteVCT->push_back(itemSprite);
		currItemIndex = 1;
		break;
	case 2://护甲道具
		itemSprite = Sprite::create("item_power.png");
		itemSprite->setPosition(Point(130+newX,970));
		this->addChild(itemSprite,COINZORDER);
		//加入向量中
		allItemSpriteVCT->push_back(itemSprite);
		currItemIndex = 2;
		break;
	case 3://加速道具
		itemSprite = Sprite::create("item_no2.png");
		itemSprite->setPosition(Point(130+newX,970));
		this->addChild(itemSprite,COINZORDER);
		//加入向量中
		allItemSpriteVCT->push_back(itemSprite);
		currItemIndex = 3;
		break;
	}
}
void GameLayer::removeBoomHZJL()
{
	this->removeChildByTag(1);
	rocketItem->setEnabled(true);
}
void GameLayer::enemyCarPositionUpdate()
{
	//===============================================遍历敌车======begin
	//遍历车，看是否车屏幕，若未出屏幕则重新设置其位置
	std::vector<EnemyCar*>::iterator tempCar=allEnemyCarVCT->begin();
	while(tempCar!= allEnemyCarVCT->end())
	{
		if((*tempCar)->enemyCarSprite->getPosition().y<=-100)
		{
			delEnemyCarVCT->push_back((*tempCar));
			tempCar = allEnemyCarVCT->erase(tempCar);
			continue;
		}else
		{
			(*tempCar)->y = (*tempCar)->enemyCarSprite->getPosition().y-(*tempCar)->speed;
			(*tempCar)->refresh();
		}
		tempCar++;
	}

	//遍历删除出屏幕的车
	std::vector<EnemyCar*>::iterator tempDelCar=delEnemyCarVCT->begin();
	while(tempDelCar!= delEnemyCarVCT->end())
	{
		this->removeChild((*tempDelCar)->enemyCarSprite,true);
		tempDelCar = delEnemyCarVCT->erase(tempDelCar);
	}
	//===============================================遍历敌车======end


	//=================================================遍历金币========begin
	//遍历删除出屏幕的金币
	std::vector<Coin*>::iterator coinIterator = coinSpriteVCT->begin();
	while(coinIterator!= coinSpriteVCT->end())
	{
		if((*coinIterator)->coinSprite->getPosition().y<=-50)
		{
			delCoinSpriteVCT->push_back((*coinIterator));
			coinIterator = coinSpriteVCT->erase(coinIterator);
			continue ;
		}else
		{
			(*coinIterator)->x = (*coinIterator)->x;
			(*coinIterator)->y = (*coinIterator)->y -itemSpeed;
			(*coinIterator)->refresh();
		}
		coinIterator++;
	}
	//遍历删除出屏幕的金币
	std::vector<Coin*>::iterator delCoinIterator=delCoinSpriteVCT->begin();
	while(delCoinIterator!= delCoinSpriteVCT->end())
	{
		this->removeChild((*delCoinIterator)->coinSprite,true);
		delCoinIterator = delCoinSpriteVCT->erase(delCoinIterator);
	}
//	=================================================遍历金币========end

//===============遍历道具=====================begin
	std::vector<Sprite*>::iterator itemIterator = allItemSpriteVCT->begin();
	while(itemIterator!= allItemSpriteVCT->end())
	{
		if((*itemIterator)->getPosition().y<=-50)
		{
			delItemSpriteVCT->push_back((*itemIterator));
			itemIterator = allItemSpriteVCT->erase(itemIterator);
			continue ;
		}else
		{
			(*itemIterator)->setPosition(
					Point(
						(*itemIterator)->getPosition().x,
						(*itemIterator)->getPosition().y-itemSpeed
					));
		}
	itemIterator++;
	}
	//遍历删除出屏幕的道具
	std::vector<Sprite*>::iterator delItemIterator=delItemSpriteVCT->begin();
	while(delItemIterator!= delItemSpriteVCT->end())
	{
		this->removeChild((*delItemIterator),true);
		delItemIterator = delItemSpriteVCT->erase(delItemIterator);
	}

//===============遍历道具=====================end

//	=================================================遍历火箭====begin
	std::vector<Rocket*>::iterator rocketIterator=rocketSpriteVCT->begin();
	while(rocketIterator!= rocketSpriteVCT->end())
	{
		if((*rocketIterator)->rocketSprite->getPosition().y>=1100)
		{
			delRocketSpriteVCT->push_back((*rocketIterator));
			rocketIterator = rocketSpriteVCT->erase(rocketIterator);
			continue;
		}else
		{
			(*rocketIterator)->y = (*rocketIterator)->rocketSprite->getPosition().y+10;
			(*rocketIterator)->refresh();
		}
		rocketIterator++;
	}
	//遍历删除超出屏幕或击中敌车的火箭
	std::vector<Rocket*>::iterator delRocketIterator=delRocketSpriteVCT->begin();
	while(delRocketIterator!= delRocketSpriteVCT->end())
	{
		this->removeChild((*delRocketIterator)->rocketSprite,true);
		delRocketIterator = delRocketSpriteVCT->erase(delRocketIterator);
		rocketItem->setEnabled(true);
	}
	//===========================================遍历火箭========end
}
//void GameLayer::removeSparksFrame()
//{
//	this->removeChildByTag(SQARKFRAMETAG);
//}
void GameLayer::collisionTestUpdate()
{
	collisionTestPlayerCarAndEnemyCar();
	collisionTestPlayerCarAndCoin();
	collisionTestRocketAndEnemyCar();
	collisionTestPlayerCarAndItem();
}
void GameLayer::collisionTestPlayerCarAndItem()
{
	Point playerCarPoint = playerCar->playerCarSprite->getPosition();
	Size playerCarSize = playerCar->playerCarSprite->getContentSize();
	std::vector<Sprite*>::iterator itemIterator = allItemSpriteVCT->begin();
	while(itemIterator!= allItemSpriteVCT->end())
	{
		Point itemPoint = (*itemIterator)->getPosition();
		Size itemSize = (*itemIterator)->getContentSize();
		bool b = CollisionTest::isCollision(
					playerCarPoint.x,playerCarPoint.y,
					playerCarSize.width,playerCarSize.height,
					itemPoint.x,itemPoint.y,
					itemSize.width,itemSize.height
			);
		if(b == true)
		{
			Sprite* spower = NULL;
			if(StartLayer::yxFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("getCoin.mp3");
			}
			switch(currItemIndex)
			{
			case 1:
//火箭
				rocketCount++;
				rocketLabel->setString(StringUtils::format("%d",rocketCount));
				mySetIntegerForKey(Constant::userRocketCount,rocketCount);
				break;
			case 2:
//护甲
				playerCar->state = 1 ;
				spower = Sprite::create();
				spower->setPosition(Point(
						playerCarSize.width/2,
						playerCarSize.height/2
				));
				playerCar->playerCarSprite->addChild(spower,2,29);
				spower->runAction(
								Sequence::create(
										Repeat::create(anmiAc[9]->clone(),10),
										CallFunc::create(CC_CALLBACK_0(GameLayer::removePowerSprite,this)),
										NULL));
				break;
			case 3:
//加速
				no2Count++;
				no2Label->setString(StringUtils::format("%d",no2Count));
				mySetIntegerForKey(Constant::userNo2tCount,no2Count);
				break;
			}
			delItemSpriteVCT->push_back((*itemIterator));
			itemIterator = allItemSpriteVCT->erase(itemIterator);
			continue ;
		}
		itemIterator++;
	}
}
void GameLayer::removePowerSprite()
{
	playerCar->playerCarSprite->removeChildByTag(29);
	playerCar->state = 0;
}
void GameLayer::collisionTestPlayerCarAndEnemyCar()
{
	Point playerCarPoint = playerCar->playerCarSprite->getPosition();
	Size playerCarSize = playerCar->playerCarSprite->getContentSize();

	//玩家的车与敌车的碰撞检测=========================begin
	std::vector<EnemyCar*>::iterator tempCar=allEnemyCarVCT->begin();
	while(tempCar!= allEnemyCarVCT->end())
	{
		Point enemyCarPoint = (*tempCar)->enemyCarSprite->getPosition();
		Size enemyCarSize = (*tempCar)->enemyCarSprite->getContentSize();
		bool b = CollisionTest::isCollision(
				playerCarPoint.x,playerCarPoint.y,
				playerCarSize.width,playerCarSize.height,
				enemyCarPoint.x,
				enemyCarPoint.y-enemyCarSize.height/2,
				enemyCarSize.width,enemyCarSize.height
		);
		if(b==true)
		{
			if(StartLayer::yxFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom.mp3");
			}
			Sprite* spriteFrame=Sprite::create();							//创建英雄精灵对象
			spriteFrame->setAnchorPoint(Point(0,0));						//设置英雄精灵对象的锚点
			spriteFrame->setPosition(
					Point(enemyCarSize.width/2,0));							//设置英雄精灵对象的初始位置
			(*tempCar)->enemyCarSprite->addChild(spriteFrame,2);			//将英雄精灵对象添加进布景
			//给被撞车添加粒子系统
			addFireLZXT((*tempCar));

			//执行换帧动画
			spriteFrame->runAction(
							Sequence::create(
									anmiAc[0]->clone(),
									anmiAc[0]->clone(),
									NULL));

			if(playerCar->state != 1)
			{
				//撞击后，生命值减5
				lifeValue = lifeValue-5;
			}
			//设置敌车状态为被玩家的车撞
			(*tempCar)->state = 1;
			//如果忘记的车在敌车左侧，则敌车被撞都应朝右偏转
			if(playerCarPoint.x<enemyCarPoint.x)
			{
				(*tempCar)->x = (*tempCar)->x+20;
				playerCar->x = playerCar->x-10;
				playerCar->refresh();
				//设置生命血条
				lifeSprite->setTextureRect(Rect(0, 0, lifeValue, 56));
			}else
			{//如果忘记的车在敌车右侧，则敌车被撞都应朝右偏转
				(*tempCar)->x = (*tempCar)->x-20;
				playerCar->x = playerCar->x+10;
				playerCar->refresh();
				//no2Sprite->setTextureRect(Rect(0, 0, 135, 57));
				//设置生命血条
				lifeSprite->setTextureRect(Rect(0, 0,lifeValue, 56));
			}
			//被撞后朝后移动
			(*tempCar)->y = (*tempCar)->y-50;
			//重置敌车的速度
			(*tempCar)->speed = playerCar->MAX_Speed;
			(*tempCar)->refresh();
			//当生命值为0时，则游戏结束
			if(lifeValue<=0)
			{
				isGameOver = true;
				Device::setAccelerometerEnabled(false);
				pauseItem->setEnabled(false);
				//====================游戏结束
				gameOver();
			}
		}
		tempCar++;
	}
	//玩家的车与敌车的碰撞检测=========================end
}
void GameLayer::collisionTestPlayerCarAndCoin()
{
	Point playerCarPoint = playerCar->playerCarSprite->getPosition();
	Size playerCarSize = playerCar->playerCarSprite->getContentSize();

	//玩家的车与金币的碰撞检测=========================begin
	std::vector<Coin*>::iterator coinIterator = coinSpriteVCT->begin();
	while(coinIterator!= coinSpriteVCT->end())
	{
		Point coinPoint = (*coinIterator)->coinSprite->getPosition();
		Size coinSize = (*coinIterator)->coinSprite->getContentSize();
		bool b = CollisionTest::isCollision(
					playerCarPoint.x,playerCarPoint.y,
					playerCarSize.width,playerCarSize.height,
					coinPoint.x,coinPoint.y,
					40,40
		);
		if(b==true)
		{
			if(StartLayer::yxFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("getCoin.mp3");
			}
			delCoinSpriteVCT->push_back((*coinIterator));
			coinIterator = coinSpriteVCT->erase(coinIterator);
			gold++;
			goldLabel->setString(StringUtils::format("%d",gold));
			continue;
		}
		coinIterator++;
	}
	//玩家的车与金币的碰撞检测=========================end
}
void GameLayer::collisionTestRocketAndEnemyCar()
{
	//火箭和敌车的平碰撞检查 ========================begin
	std::vector<Rocket*>::iterator rocketIterator = rocketSpriteVCT->begin();
	while(rocketIterator!= rocketSpriteVCT->end())
	{
		Point rocketPoint =(*rocketIterator)->rocketSprite->getPosition();
		Size rocketSize = (*rocketIterator)->rocketSprite->getContentSize();

		bool b = false ;
		std::vector<EnemyCar*>::iterator tempCar=allEnemyCarVCT->begin();
		while(tempCar!= allEnemyCarVCT->end())
		{
			Point enemyCarPoint = (*tempCar)->enemyCarSprite->getPosition();
			Size enemyCarSize = (*tempCar)->enemyCarSprite->getContentSize();
			b = CollisionTest::isCollision(
					rocketPoint.x,rocketPoint.y,
					rocketSize.width,rocketSize.height,
					enemyCarPoint.x,
					enemyCarPoint.y-enemyCarSize.height/2,
					enemyCarSize.width,enemyCarSize.height
			);
			if(b==true)
			{
				if(StartLayer::yxFlag == true)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom.mp3");
				}
				//爆炸效果，换帧精灵
				Sprite* boomSprite = Sprite::create();
				boomSprite->setPosition(Point((*tempCar)->x,(*tempCar)->y-enemyCarSize.height/2));
				this->addChild(boomSprite,ENEMYCARZORDER,1);
				boomSprite->runAction(Sequence::create(anmiAc[7]->clone(),
						CallFunc::create(CC_CALLBACK_0(GameLayer::removeBoomHZJL,this)),
						NULL));
				delEnemyCarVCT->push_back((*tempCar));
				tempCar = allEnemyCarVCT->erase(tempCar);
				break;
			}
			tempCar++;
		}
		if(b == true)
		{
			delRocketSpriteVCT->push_back((*rocketIterator));
//			this->removeChild((*rocketIterator)->rocketSprite,true);
			rocketIterator = rocketSpriteVCT->erase(rocketIterator);
			continue ;
		}
		rocketIterator++;
	}
	//火箭和敌车的平碰撞检查 ========================end
}
void GameLayer::addFireLZXT(EnemyCar* enemyCar)
{
	ParticleSystemQuad* psq = ParticleSystemQuad::create("fire.plist");
	psq->setBlendAdditive(true);
	psq->setScale(0.5);
	enemyCar->enemyCarSprite->addChild(psq,MYCARZORDER+1);
	psq->setPosition(Point(
			enemyCar->enemyCarSprite->getContentSize().width/2,0
			));
}
void GameLayer::timeUpdate()
{
	restTime--;
	restTimeLabel->setString(StringUtils::format("%d",restTime));
	if(restTime == 0)
	{
		if(ChooseLevelLayer::currLevel == 0)
		{
			if(gold >=20)
			{
				isGameOver=false;
				UserDefault::getInstance()->setIntegerForKey(
									Constant::uesrGKLock[ChooseLevelLayer::currLevel+1].c_str(),1);
			}else
			{
				isGameOver=true;
			}
		}else if(ChooseLevelLayer::currLevel == 1)
		{
			if(distance >=2000)
			{
				isGameOver=false;
				UserDefault::getInstance()->setIntegerForKey(
													Constant::uesrGKLock[ChooseLevelLayer::currLevel+1].c_str(),1);
			}else
			{
				isGameOver=true;
			}
		}else if(ChooseLevelLayer::currLevel == 2)
		{
			if(lifeValue ==135)
			{
				isGameOver=false;
			}else
			{
				isGameOver=true;
			}
		}
		gameOver();
	}
}
//背景滚屏定时回调方法
void GameLayer::bgUpdate()
{
	if((distance+1)%1200 == 0)
	{
		baseSpeed = baseSpeed +2;
	}
	if(distance == 4000)
	{
		Sprite* speedLineSprite = Sprite::create();
		speedLineSprite->setPosition(Point(270,480));
		this->addChild(speedLineSprite,1,SPEEDLINESPRITETAG);
		speedLineSprite->runAction(
						RepeatForever::create(anmiAc[8]->clone()));
	}
	if(bgSpriteO->getPosition().y-v<-480)
	{
		bgSpriteO->setPosition(Point(270,-480));
	}
	if(bgSpriteO->getPosition().y==-480)
	{
		bgSpriteO->setPosition(Point(270,1440));
	}else{
		bgSpriteO->setPosition(Point(270,bgSpriteO->getPosition().y-v));
	}

	if(bgSpriteT->getPosition().y-v<-480)
	{
		bgSpriteT->setPosition(Point(270,-480));
	}
	if(bgSpriteT->getPosition().y==-480)
	{
		bgSpriteT->setPosition(Point(270,1440));
	}else{
		bgSpriteT->setPosition(Point(270,bgSpriteT->getPosition().y-v));
	}
	count++;
	if(count==150)
	{
		auto director = Director::getInstance();
		auto sched = director->getScheduler();
		rocketItem->setEnabled(true);
		no2Item->setEnabled(true);
		//添加金币
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::addStageUpdate),this,3,false);
		//开车的距离
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::distanceUpdate),this,0.01,false);
		//产生敌方车
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::enemyCarUpdate),this,1,false);
		//重置敌车位置
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::enemyCarPositionUpdate),this,0.01,false);
		//碰撞检查
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::collisionTestUpdate),this,0.01,false);
		//重置玩家的车
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::playerCarUpdate),this,0.01,false);
		if(StartLayer::gameMode == 0)
		{
			//重置玩家的车
			sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::timeUpdate),this,1,false);
		}
		//重力感应监听
		Device::setAccelerometerEnabled(true);
		if(isOnAcceleration==false)
		{
			isOnAcceleration = true;
			EventListenerAcceleration* listener =
					EventListenerAcceleration::create(				//设置重力感应回调方法
								CC_CALLBACK_2(GameLayer::onAcceleration, this));

			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	//添加到监听器
		}
	}
	if(count%35==0)
	{
		if(v<=playerCar->MAX_Speed)
		{
			v = playerCar->a*t;
			t++;
		}
	}
	if(count%3==0&&count>=35)
	{
		if(pointR<=playerCar->MAX_pointR)
		{
			pointR++;
			if(pointR>=180)
			{
				pointR=pointR-2;
			}
		}else
		{
			pointR=pointR-2;
		}
	}
	pointSprite->setRotation(pointR);
}
void GameLayer::gameOver()
{
	GameOverLayer::gold = gold ;
	GameOverLayer::distance = distance;
	this->unscheduleAllSelectors();
	int goldSum = myGetIntegerForKey(Constant::userGold);
	int doubleGoldCount = myGetIntegerForKey(Constant::userDoubleGold);
	if(doubleGoldCount >0)
	{
		gold = gold *2;
		doubleGoldCount = doubleGoldCount - 1;
		mySetIntegerForKey(Constant::userDoubleGold,doubleGoldCount);
	}
	mySetIntegerForKey(Constant::userGold,goldSum + gold+(int)(distance/50));
	crsm->goGameOverLayer();
}
int GameLayer::myGetIntegerForKey (std::string key)
{
	int result = UserDefault::getInstance()->getIntegerForKey(key.c_str());
	return result;
}
void GameLayer::mySetIntegerForKey(std::string key,int value)
{
	UserDefault::getInstance()->setIntegerForKey(key.c_str(),value);
}
