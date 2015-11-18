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
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
	    return false;
	}
    //��ȡ�ɼ�����ߴ�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ�ɼ�����ԭ������
    Point origin = Director::getInstance()->getVisibleOrigin();

    initYBP();

    int level = ChooseLevelLayer::currLevel + 1;
    if(level == 0)
    {
    	level = 1;
    }
   	//����������������
   	bgSpriteO = Sprite::create(StringUtils::format("scene%d.jpg",level));
 		bgSpriteO->setPosition(270,480);
   	this->addChild(bgSpriteO,BGZORDER);

   	bgSpriteT = Sprite::create(StringUtils::format("scene%d.jpg",level));
   	bgSpriteT->setPosition(270,1440);
   	this->addChild(bgSpriteT,BGZORDER+1);

   	distanceLabel = LabelAtlas::create(						//����һ��LabelAtlas����
							 "0","upNum.png",20,23,'0');
	distanceLabel->setAnchorPoint(Point(1,0.5));				//����LabelAtlas����ê��
	distanceLabel->setPosition(								//����LabelAtlas����λ��
						Point(360,910));
	this->addChild(distanceLabel,DJZORDER);						//��LabelAtlas������ӵ�������

	rocketLabel = LabelAtlas::create(						//����һ��LabelAtlas����
			StringUtils::format("%d",rocketCount)
			,"upNum.png",20,23,'0');
	rocketLabel->setAnchorPoint(Point(0.5,0.5));				//����LabelAtlas����ê��
	rocketLabel->setPosition(								//����LabelAtlas����λ��
					Point(90,100));
	this->addChild(rocketLabel,DJZORDER);						//��LabelAtlas������ӵ�������

	no2Label = LabelAtlas::create(							//����һ��LabelAtlas����
				 "0","upNum.png",20,23,'0');
	no2Label->setAnchorPoint(Point(0.5,0.5));				//����LabelAtlas����ê��
	no2Label->setPosition(Point(450,100));					//����LabelAtlas����λ��
	this->addChild(no2Label,DJZORDER);						//��LabelAtlas������ӵ�������
	no2Label->setString(StringUtils::format("%d",no2Count));

	goldLabel = LabelAtlas::create(				//����һ��LabelAtlas����
			 "0","upNum.png",20,23,'0');
	goldLabel->setAnchorPoint(Point(0,0.5));		//����LabelAtlas����ê��
	goldLabel->setPosition(							//����LabelAtlas����λ��
						Point(440,910));
	this->addChild(goldLabel,DJZORDER);						//��LabelAtlas������ӵ�������

	if(StartLayer::gameModeLevel == 0)
	{
		StartLayer::gameMode = 0;
		restTimeLabel = LabelAtlas::create(						//����һ��LabelAtlas����
				StringUtils::format("%d",restTime)
				,"upNum.png",20,23,'0');
		restTimeLabel->setPosition(								//����LabelAtlas����λ��
						Point(170,900));
		this->addChild(restTimeLabel,DJZORDER);						//��LabelAtlas������ӵ�������

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

   	//������һ���˵���
	pauseItem = MenuItemImage::create(
			   "pauseN.png",						//ƽʱ��ͼƬ
			   "pauseP.png",						//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(GameLayer::pauseMenuCallback, this)//���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	pauseItem->setPosition(Point(0,960));
	pauseItem->setAnchorPoint(Point(0,1));

	//�����˵�����
	auto menu = Menu::create(pauseItem,NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	//���˵���ӵ�������
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
   	//��ʼ����ҵĳ��ķ���
   	initPlyerCar();
   	initMusic();
   	//����ʱ�����ķ���
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
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile("silver.plist",
			"silver.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	std::string silver[10]=
	{								//���������Ķζ���8��ͼƬ������
		"silver1.png","silver10.png","silver2.png",
		"silver3.png","silver4.png","silver5.png",
		"silver6.png","silver7.png","silver8.png",
		"silver9.png"
	};
	Vector<SpriteFrame*> animFrames;									//������Ŷ���֡������
	for(int i=0;i<10;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(silver[i]));	  		//������֡��ӵ�������
	}
	Animation* anmi=Animation::createWithSpriteFrames(
		animFrames, 0.15f);  			//�����������󣬴�֡�����������������Ϊ0.5��
	anmiAc[1]=Animate::create(anmi);	//����������������
	anmiAc[1]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
}
void GameLayer::initBigFire()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile("big_fire.plist",
		"big_fire.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	std::string sa[4]=
	{								//���������Ķζ���8��ͼƬ������
		"big_fire1.png","big_fire2.png",
		"big_fire3.png","big_fire4.png"
	};
	Vector<SpriteFrame*> animFrames;									//������Ŷ���֡������
	for(int i=0;i<4;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//������֡��ӵ�������
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames, 0.5f);  			//�����������󣬴�֡�����������������Ϊ0.3��
	anmiAc[0]=Animate::create(anmi);	//����������������
	anmiAc[0]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
}
void GameLayer::initNo2()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile("no2h.plist",
		"no2h.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	std::string sa[4]=
	{								//���������Ķζ���8��ͼƬ������
		"no21.png","no22.png",
		"no23.png","no24.png"
	};
	Vector<SpriteFrame*> animFrames;									//������Ŷ���֡������
	for(int i=0;i<4;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//������֡��ӵ�������
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames,0.1f);  			//�����������󣬴�֡�����������������Ϊ0.3��
	anmiAc[5]=Animate::create(anmi);	//����������������
	anmiAc[5]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
}
void GameLayer::initBoomHZJL()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile("newboom.plist",
			"newboom.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	std::string newboom[7]=
	{								//���������Ķζ���8��ͼƬ������
		"newboom1.png","newboom2.png","newboom3.png",
		"newboom4.png","newboom5.png","newboom6.png",
		"newboom7.png"
	};
	std::string boom[7]=
	{								//���������Ķζ���8��ͼƬ������
		"boom1.png","boom2.png","boom3.png",
		"boom4.png","boom5.png","boom6.png",
		"boom7.png"
	};

	Vector<SpriteFrame*> animFrames;
	for(int i=0;i<7;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(newboom[i]));	  		//������֡��ӵ�������
	}
	Animation* anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//�����������󣬴�֡�����������������Ϊ0.5��
	anmiAc[3]=Animate::create(anmi);	//����������������
	anmiAc[3]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�

	animFrames.clear();
	sfc->addSpriteFramesWithFile("boom.plist",
				"boom.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	for(int i=0;i<7;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(boom[i]));	  		//������֡��ӵ�������
	}
	anmi=Animation::createWithSpriteFrames(
		animFrames, 0.15f);  			//�����������󣬴�֡�����������������Ϊ0.5��
	anmiAc[7]=Animate::create(anmi);	//����������������
	anmiAc[7]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
}
void GameLayer::initNo2Che()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile("no2f.plist",
			"no2f.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	std::string boom[3]=
	{								//���������Ķζ���8��ͼƬ������
		"1.png","2.png","3.png"
	};
	Vector<SpriteFrame*> animFrames;
	for(int i=0;i<3;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(boom[i]));	  		//������֡��ӵ�������
	}
	Animation* anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//�����������󣬴�֡�����������������Ϊ0.5��
	anmiAc[6]=Animate::create(anmi);	//����������������
	anmiAc[6]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
}
void GameLayer::initSpeedLine()
{
	std::string sa[6]={						//�����ж���ͼƬ��·��������������
		"speed1.png","speed2.png",
		"speed3.png","speed4.png",
		"speed5.png","speed6.png"
	};
	Vector<SpriteFrame*> animFrames;		//������Ŷ���֡���б����
	for(int i=0;i<6;i++)
	{

		SpriteFrame *f0=SpriteFrame::create(sa[i],
							Rect(0,0,540,960));	//��ȡ�˶����е�ָ������֡
		animFrames.pushBack(f0);				//����һ�ζ����е�����֡��ŵ�������
	}
	Animation *anmi=Animation::createWithSpriteFrames
			(animFrames, 0.05f);					//����ָ�򶯻������ָ��
	anmiAc[8]=Animate::create(anmi);			//����������������
	anmiAc[8]->retain();						//��Ϊ��ʱ���ã����Ա������ã���ֹ���Զ��ͷ�
}
void GameLayer::initPower()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile("power.plist",
		"power.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	std::string sa[3]=
	{								//���������Ķζ���8��ͼƬ������
		"power1.png","power2.png","power3.png"
	};
	Vector<SpriteFrame*> animFrames;									//������Ŷ���֡������
	for(int i=0;i<3;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//������֡��ӵ�������
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//�����������󣬴�֡�����������������Ϊ0.3��
	anmiAc[9]=Animate::create(anmi);	//����������������
	anmiAc[9]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
}

void GameLayer::initHJFire()
{
	SpriteFrameCache* sfc=SpriteFrameCache::getInstance();//��ȡ���徫��֡��ʵ��
	sfc->addSpriteFramesWithFile("firef.plist",
		"firef.png");			//������֡�ļ��Լ���Ӧ��ͼƬ��ӵ��ڴ���
	std::string sa[7]=
	{								//���������Ķζ���8��ͼƬ������
		"fire1.png","fire2.png","fire3.png",
		"fire4.png","fire5.png","fire6.png",
		"fire7.png"
	};
	Vector<SpriteFrame*> animFrames;									//������Ŷ���֡������
	for(int i=0;i<7;i++)
	{
		animFrames.pushBack(sfc->getSpriteFrameByName(sa[i]));	  		//������֡��ӵ�������
	}
	Animation *anmi=Animation::createWithSpriteFrames(
		animFrames, 0.1f);  			//�����������󣬴�֡�����������������Ϊ0.3��
	anmiAc[2]=Animate::create(anmi);	//����������������
	anmiAc[2]->retain();				//��Ϊ��ʱ���ã��������ã���ֹ���Զ��ͷ�
}

void GameLayer::gameDataReset()
{
	pointR=0;
	//�ٶ�
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//��������
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
	//��ȡ�ĵ�ǰ�����Ķ��󣬲�ת��Ϊ��������
	spriteTouch = static_cast<Sprite*>(event->getCurrentTarget());
	spriteTouch->retain();
	//��ȡ��ǰ����
	auto location = spriteTouch->convertToNodeSpace(touch->getLocation());
	//��ȡ����Ĵ�С
	auto size = spriteTouch->getContentSize();
	//����һ�����ζ������С�뾫����ͬ
	auto rect = Rect(0, 0, size.width, size.height);
	//�жϴ������Ƿ���Ŀ��ķ�Χ��
	if(rect.containsPoint(location)){
		Director::getInstance()->resume();
		pauseItem->setEnabled(true);
	if(StartLayer::soundFlag==true){
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//��������
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
	//���Ǳ������
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

	//����ָ�뾫�����
	pointSprite = Sprite::create("point.png");
	pointSprite->setAnchorPoint(Point(0.9,0.5));
	pointSprite->setPosition(Point(270,97));
	this->addChild(pointSprite,DJZORDER);

	//���Ǳ���
	Sprite* upSprite = Sprite::create("up.png");
	upSprite->setPosition(Point(300,910));
	this->addChild(upSprite,YBPZORDER);

	//������һ���˵���
	no2Item = MenuItemImage::create(
			   "no2N.png",						//ƽʱ��ͼƬ
			   "no2P.png",						//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(GameLayer::JSMenuCallback, this)//���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	no2Item->setPosition(Point(480,150));
	no2Item->setEnabled(false);
	//������һ���˵���
	rocketItem = MenuItemImage::create(
			   "rocketN.png",						//ƽʱ��ͼƬ
			   "rocketP.png",						//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(GameLayer::rocketMenuCallback, this)//���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	rocketItem->setPosition(Point(80,150));
	rocketItem->setEnabled(false);
	//�����˵�����
	auto menu = Menu::create(rocketItem,no2Item,NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(menu,DJZORDER);
}
void GameLayer::onAcceleration(Acceleration* acc, Event* unused_event)
{
	moveSpan = -acc->y*20;
	angle=moveSpan/20*40;
}
void GameLayer::playerCarUpdate()
{
	//��ҵĳ������ƶ�
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

	//��ҵĳ�������ת
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
	//���³���״̬
	playerCar->refresh();
}
void GameLayer::initPlyerCar()
{
	playerCar =new PlayerCar(
			(ChooseCarLayer::currCarNum+1)*10+ChooseCarLayer::currCarNum+1,
			270.0,350.0,0,
			ChooseCarLayer::currCarNum+5,
			//��̬���㳵������ٶ������ָ��Ƕ�
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
	//��ͨ
	Sprite* trafficSprite = Sprite::create("traffic.png");
	trafficSprite->setPosition(Point(270,650));
	this->addChild(trafficSprite,5,TRAFFICSPRITETAG);
	for(int i=0;i<3;i++)
	{
		//���
		redSprite[i] = Sprite::create("red.png");
		redSprite[i]->setPosition(Point(44,175-i*60));
		trafficSprite->addChild(redSprite[i],3);
		//�̵�
		Sprite* greenSprite = Sprite::create("green.png");
		greenSprite->setPosition(Point(44,175-i*60));
		trafficSprite->addChild(greenSprite,2);
	}
	//������ʱ�ص�������ʱ������ʱ��
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
			//���ö�ʱ�ص�ָ�������ɻ�
			auto director = Director::getInstance();
			auto sched = director->getScheduler();
			//����������ʱ�ص�
			sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::bgUpdate),this,0.001,false);
			if(StartLayer::yxFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("start1.mp3");
			}
			if(StartLayer::soundFlag==true){
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//��������
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
		//��β����==============begin
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
		//��β����==============end

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
	case 0://��ҵ���
		for(int i=0;i<10;i++)
		{
			Coin* coin = new Coin(130+newX,970+i*30);
			this->addChild(coin->coinSprite,COINZORDER);
			coin->refresh();
			coin->coinSprite->runAction(RepeatForever::create(anmiAc[1]->clone()));
			coinSpriteVCT->push_back(coin);
		}
		break;
	case 1://�������
		itemSprite = Sprite::create("item_rocket.png");
		itemSprite->setPosition(Point(130+newX,970));
		this->addChild(itemSprite,COINZORDER);
		//����������
		allItemSpriteVCT->push_back(itemSprite);
		currItemIndex = 1;
		break;
	case 2://���׵���
		itemSprite = Sprite::create("item_power.png");
		itemSprite->setPosition(Point(130+newX,970));
		this->addChild(itemSprite,COINZORDER);
		//����������
		allItemSpriteVCT->push_back(itemSprite);
		currItemIndex = 2;
		break;
	case 3://���ٵ���
		itemSprite = Sprite::create("item_no2.png");
		itemSprite->setPosition(Point(130+newX,970));
		this->addChild(itemSprite,COINZORDER);
		//����������
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
	//===============================================�����г�======begin
	//�����������Ƿ���Ļ����δ����Ļ������������λ��
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

	//����ɾ������Ļ�ĳ�
	std::vector<EnemyCar*>::iterator tempDelCar=delEnemyCarVCT->begin();
	while(tempDelCar!= delEnemyCarVCT->end())
	{
		this->removeChild((*tempDelCar)->enemyCarSprite,true);
		tempDelCar = delEnemyCarVCT->erase(tempDelCar);
	}
	//===============================================�����г�======end


	//=================================================�������========begin
	//����ɾ������Ļ�Ľ��
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
	//����ɾ������Ļ�Ľ��
	std::vector<Coin*>::iterator delCoinIterator=delCoinSpriteVCT->begin();
	while(delCoinIterator!= delCoinSpriteVCT->end())
	{
		this->removeChild((*delCoinIterator)->coinSprite,true);
		delCoinIterator = delCoinSpriteVCT->erase(delCoinIterator);
	}
//	=================================================�������========end

//===============��������=====================begin
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
	//����ɾ������Ļ�ĵ���
	std::vector<Sprite*>::iterator delItemIterator=delItemSpriteVCT->begin();
	while(delItemIterator!= delItemSpriteVCT->end())
	{
		this->removeChild((*delItemIterator),true);
		delItemIterator = delItemSpriteVCT->erase(delItemIterator);
	}

//===============��������=====================end

//	=================================================�������====begin
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
	//����ɾ��������Ļ����ег��Ļ��
	std::vector<Rocket*>::iterator delRocketIterator=delRocketSpriteVCT->begin();
	while(delRocketIterator!= delRocketSpriteVCT->end())
	{
		this->removeChild((*delRocketIterator)->rocketSprite,true);
		delRocketIterator = delRocketSpriteVCT->erase(delRocketIterator);
		rocketItem->setEnabled(true);
	}
	//===========================================�������========end
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
//���
				rocketCount++;
				rocketLabel->setString(StringUtils::format("%d",rocketCount));
				mySetIntegerForKey(Constant::userRocketCount,rocketCount);
				break;
			case 2:
//����
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
//����
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

	//��ҵĳ���г�����ײ���=========================begin
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
			Sprite* spriteFrame=Sprite::create();							//����Ӣ�۾������
			spriteFrame->setAnchorPoint(Point(0,0));						//����Ӣ�۾�������ê��
			spriteFrame->setPosition(
					Point(enemyCarSize.width/2,0));							//����Ӣ�۾������ĳ�ʼλ��
			(*tempCar)->enemyCarSprite->addChild(spriteFrame,2);			//��Ӣ�۾��������ӽ�����
			//����ײ���������ϵͳ
			addFireLZXT((*tempCar));

			//ִ�л�֡����
			spriteFrame->runAction(
							Sequence::create(
									anmiAc[0]->clone(),
									anmiAc[0]->clone(),
									NULL));

			if(playerCar->state != 1)
			{
				//ײ��������ֵ��5
				lifeValue = lifeValue-5;
			}
			//���õг�״̬Ϊ����ҵĳ�ײ
			(*tempCar)->state = 1;
			//������ǵĳ��ڵг���࣬��г���ײ��Ӧ����ƫת
			if(playerCarPoint.x<enemyCarPoint.x)
			{
				(*tempCar)->x = (*tempCar)->x+20;
				playerCar->x = playerCar->x-10;
				playerCar->refresh();
				//��������Ѫ��
				lifeSprite->setTextureRect(Rect(0, 0, lifeValue, 56));
			}else
			{//������ǵĳ��ڵг��Ҳ࣬��г���ײ��Ӧ����ƫת
				(*tempCar)->x = (*tempCar)->x-20;
				playerCar->x = playerCar->x+10;
				playerCar->refresh();
				//no2Sprite->setTextureRect(Rect(0, 0, 135, 57));
				//��������Ѫ��
				lifeSprite->setTextureRect(Rect(0, 0,lifeValue, 56));
			}
			//��ײ�󳯺��ƶ�
			(*tempCar)->y = (*tempCar)->y-50;
			//���õг����ٶ�
			(*tempCar)->speed = playerCar->MAX_Speed;
			(*tempCar)->refresh();
			//������ֵΪ0ʱ������Ϸ����
			if(lifeValue<=0)
			{
				isGameOver = true;
				Device::setAccelerometerEnabled(false);
				pauseItem->setEnabled(false);
				//====================��Ϸ����
				gameOver();
			}
		}
		tempCar++;
	}
	//��ҵĳ���г�����ײ���=========================end
}
void GameLayer::collisionTestPlayerCarAndCoin()
{
	Point playerCarPoint = playerCar->playerCarSprite->getPosition();
	Size playerCarSize = playerCar->playerCarSprite->getContentSize();

	//��ҵĳ����ҵ���ײ���=========================begin
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
	//��ҵĳ����ҵ���ײ���=========================end
}
void GameLayer::collisionTestRocketAndEnemyCar()
{
	//����͵г���ƽ��ײ��� ========================begin
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
				//��ըЧ������֡����
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
	//����͵г���ƽ��ײ��� ========================end
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
//����������ʱ�ص�����
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
		//��ӽ��
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::addStageUpdate),this,3,false);
		//�����ľ���
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::distanceUpdate),this,0.01,false);
		//�����з���
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::enemyCarUpdate),this,1,false);
		//���õг�λ��
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::enemyCarPositionUpdate),this,0.01,false);
		//��ײ���
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::collisionTestUpdate),this,0.01,false);
		//������ҵĳ�
		sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::playerCarUpdate),this,0.01,false);
		if(StartLayer::gameMode == 0)
		{
			//������ҵĳ�
			sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::timeUpdate),this,1,false);
		}
		//������Ӧ����
		Device::setAccelerometerEnabled(true);
		if(isOnAcceleration==false)
		{
			isOnAcceleration = true;
			EventListenerAcceleration* listener =
					EventListenerAcceleration::create(				//����������Ӧ�ص�����
								CC_CALLBACK_2(GameLayer::onAcceleration, this));

			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	//��ӵ�������
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
