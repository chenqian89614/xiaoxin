#include "StartLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Constant.h"

//#include "cocostudio/CocoStudio.h"


//using namespace cocostudio;
using namespace cocos2d;

int StartLayer::gameMode = -1;
int StartLayer::gameModeLevel = -1 ;
bool StartLayer::soundFlag = true;
bool StartLayer::yxFlag = true;
bool StartLayer::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
	    return false;
	}
	isFirstEnter();
	initSoundYxFlag();
    //��ȡ�ɼ�����ߴ�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ�ɼ�����ԭ������
    Point origin = Director::getInstance()->getVisibleOrigin();

	//��������
	Sprite* bgSprite = Sprite::create("startbg.jpg");
	bgSprite->setPosition(Point(270,480));
	this->addChild(bgSprite,0);

	//���⾫��
	Sprite* ttSprite = Sprite::create("title.png");
	ttSprite->setPosition(Point(270,780));
	this->addChild(ttSprite,1);

	Sprite*(spbg) [6];
	for(int i=0;i<6;i++)
	{
		spbg[i] = Sprite::create("BNormal.png");
		spbg[i]->setPosition(Point(270,600-i*90));
		this->addChild(spbg[i],1);

		sp[i] = Sprite::create(
				StringUtils::format("sp%d.png",i));
		sp[i]->setPosition(Point(270,600-i*90));
		this->addChild(sp[i],2);
	}
	//������һ���˵���
	MenuItemImage* syItem = MenuItemImage::create(
			   "syBTN.png",	//ƽʱ��ͼƬ
			   "syBTP.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(StartLayer::settingBT, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	syItem->setPosition(Point(500,60));

	//������һ���˵���
	MenuItemImage* phItem = MenuItemImage::create(
			   "close.jpg",	//ƽʱ��ͼƬ
			   "closep.jpg",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(StartLayer::goPHB, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	phItem->setPosition(Point(40,60));

	//�����˵�����
	auto menu = Menu::create(syItem,phItem,NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(menu, 1);

	initMusicBT();
	initSound();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//��������
					"background.mp3",
					true
					);
	if(StartLayer::soundFlag == false)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(StartLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(StartLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,sp[0]);
	for(int i=1;i<6;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),sp[i]);
	}

	EventListenerKeyboard* JPlistener = EventListenerKeyboard::create();	//�������̼���
	JPlistener->onKeyReleased = CC_CALLBACK_2(				//�ͷż���
						StartLayer::onKeyReleased, this);
	_eventDispatcher->										//�����̼�����ӵ���������
				addEventListenerWithSceneGraphPriority(JPlistener, this);
	return true;
}
void StartLayer::initSoundYxFlag()
{
	int soundflag = UserDefault::getInstance()->getIntegerForKey(Constant::soundFlag.c_str());
	if(soundflag == 0)
	{
		StartLayer::soundFlag = true;
	}else
	{
		StartLayer::soundFlag = false;
	}
	int yxflag = UserDefault::getInstance()->getIntegerForKey(Constant::yxFlag.c_str());
	if(yxflag == 0)
	{
		StartLayer::yxFlag = true;
	}else
	{
		StartLayer::yxFlag = false;
	}
}
void StartLayer::isFirstEnter()
{
	int isFirst = UserDefault::getInstance()->getIntegerForKey(Constant::isFirstEnter.c_str());
	if(isFirst == 0)
	{
		UserDefault::getInstance()->setIntegerForKey(
				Constant::uesrDefunct[0].c_str(),1);
		for(int i = 1;i<8;i++)
		{
			UserDefault::getInstance()->setIntegerForKey(
							Constant::uesrDefunct[i].c_str(),0);
		}

		UserDefault::getInstance()->setIntegerForKey(
					Constant::uesrGKLock[0].c_str(),1);

		for(int i = 1;i<3;i++)
		{
			UserDefault::getInstance()->setIntegerForKey(
							Constant::uesrGKLock[i].c_str(),0);
		}

		UserDefault::getInstance()->setIntegerForKey(
							Constant::userGold.c_str(),0);
		UserDefault::getInstance()->setIntegerForKey(
							Constant::userRocketCount.c_str(),0);
		UserDefault::getInstance()->setIntegerForKey(
							Constant::userNo2tCount.c_str(),0);
		UserDefault::getInstance()->setIntegerForKey(
							Constant::userWDCount.c_str(),0);
		UserDefault::getInstance()->setIntegerForKey(
							Constant::userDoubleGold.c_str(),0);
		UserDefault::getInstance()->setIntegerForKey(
									Constant::soundFlag.c_str(),0);
		UserDefault::getInstance()->setIntegerForKey(
									Constant::yxFlag.c_str(),0);
		for(int i=0;i<5;i++)
		{
			UserDefault::getInstance()->setIntegerForKey(
							Constant::userRecord[i].c_str(),0);
		}
	}
    UserDefault::getInstance()->setIntegerForKey(
                                                 Constant::isFirstEnter.c_str(),1);
}

//��ʼ�����б������ּ���Ч
void StartLayer::initSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()
				->preloadBackgroundMusic("background.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
														   "boom.mp3"
														   );

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
														   "getCoin.mp3"
														   );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
														   "no2.mp3"
														   );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
														   "start.mp3"
														   );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
														   "daojishi.mp3"
														   );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
														   "start1.mp3"
														   );
}
void StartLayer::initMusicBT()
{
	//������һ���˵���
	musicOnItem = MenuItemImage::create(
			   "MusicOn.png",	//ƽʱ��ͼƬ
			   "MusicOff.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(StartLayer::setMusicVisible, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	musicOnItem->setPosition(Point(500,140));
	musicOnItem->setVisible(false);

	//������һ���˵���
	musicOffItem = MenuItemImage::create(
			   "MusicOff.png",	//ƽʱ��ͼƬ
			   "MusicOn.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(StartLayer::setMusicVisible, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	musicOffItem->setPosition(Point(500,140));
	musicOffItem->setVisible(false);

	//������һ���˵���
	soundOnItem = MenuItemImage::create(
			   "SoundOn.png",	//ƽʱ��ͼƬ
			   "SoundOff.png",	//ѡ��ʱ��ͼƬ
			   CC_CALLBACK_0(StartLayer::setSoundVisible, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	soundOnItem->setPosition(Point(500,220));
	soundOnItem->setVisible(false);

	//������һ���˵���
	soundOffItem = MenuItemImage::create(
			"SoundOff.png",	//ƽʱ��ͼƬ
			"SoundOn.png",	//ѡ��ʱ��ͼƬ
			CC_CALLBACK_0(StartLayer::setSoundVisible, this) //���ʱִ�еĻص�����
		);
	//������һ���˵����λ��
	soundOffItem->setPosition(Point(500,220));
	soundOffItem->setVisible(false);

	//�����˵�����
	auto menu = Menu::create(musicOffItem,musicOnItem,soundOnItem,soundOffItem,NULL);
	//���ò˵�λ��
	menu->setPosition(Point::ZERO);
	//���˵���ӵ�������
	this->addChild(menu, 1);
}
void StartLayer::settingBT()
{
	if(setFlag == false )
	{
		if(StartLayer::soundFlag == true)
		{
			soundOnItem->setVisible(true);
			soundOffItem->setVisible(false);
		}else
		{
			soundOffItem->setVisible(true);
			soundOnItem->setVisible(false);
		}

		if(StartLayer::yxFlag == true)
		{
			musicOnItem->setVisible(true);
			musicOffItem->setVisible(false);

		}else
		{
			musicOffItem->setVisible(true);
			musicOnItem->setVisible(false);

		}
	}else
	{
		soundOffItem->setVisible(false);
		soundOnItem->setVisible(false);
		musicOnItem->setVisible(false);
		musicOffItem->setVisible(false);
	}
	setFlag=!setFlag;
}
void StartLayer::setMusicVisible()
{
	if(StartLayer::yxFlag==true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
		musicOnItem->setVisible(false);
		musicOffItem->setVisible(true);
		UserDefault::getInstance()->setIntegerForKey(
										Constant::yxFlag.c_str(),1);
	}else if(StartLayer::yxFlag==false)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
		musicOnItem->setVisible(true);
		musicOffItem->setVisible(false);
		UserDefault::getInstance()->setIntegerForKey(
										Constant::yxFlag.c_str(),0);
	}
	StartLayer::yxFlag=!StartLayer::yxFlag;
}
void StartLayer::setSoundVisible()
{
	if(StartLayer::soundFlag==true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		soundOnItem->setVisible(false);
		soundOffItem->setVisible(true);
		UserDefault::getInstance()->setIntegerForKey(
										Constant::soundFlag.c_str(),1);
	}else if(StartLayer::soundFlag==false)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		soundOnItem->setVisible(true);
		soundOffItem->setVisible(false);
		UserDefault::getInstance()->setIntegerForKey(
										Constant::soundFlag.c_str(),0);
	}
	StartLayer::soundFlag=!StartLayer::soundFlag;
}
bool StartLayer::onTouchBegan(Touch* touch, Event* event)
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
		if(spriteTouch==sp[0])
		{
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(StartLayer::goLevelMode,this)),
							NULL));
		}else if(spriteTouch==sp[1]){
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(StartLayer::goSpeedMode,this)),
							NULL));
		}else if(spriteTouch==sp[2]){
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(StartLayer::goGarage,this)),
							NULL));
		}else if(spriteTouch==sp[3]){
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(StartLayer::goShop,this)),
							NULL));
		}else if(spriteTouch==sp[4]){
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(StartLayer::goRate,this)),
							NULL));
		}else if(spriteTouch==sp[5])
		{
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(StartLayer::goHelpLayer,this)),
							NULL));
		}
		return true;
	}else
	{
		return false;
	}
}
void StartLayer::goHelpLayer()
{
	//��ʱģʽ
	crsm->goHelpLayer();
}
void StartLayer::goLevelMode()
{
	//��ʱģʽ
	StartLayer::gameMode = 0;
	StartLayer::gameModeLevel = 0;
	crsm->goChooseLevelLayer();
}
void StartLayer::goSpeedMode()
{
	//����ģʽ
	StartLayer::gameMode = 1;
	StartLayer::gameModeLevel = 1 ;
	crsm->goChooseCarLayer();
}
void StartLayer::goGarage()
{
	//�򳵵�״̬
	StartLayer::gameMode = 2;
	crsm->goChooseCarLayer();
}
void StartLayer::goShop()
{
	StartLayer::gameMode = 3;
	crsm->goShopLayer();
}
void StartLayer::goRate()
{
	crsm->goPHBLayer();
}
void StartLayer::onTouchEnded(Touch* touch, Event* event)
{
	spriteTouch->runAction(ScaleTo::create(0.1,1));
}
void StartLayer::goPHB()
{
	Director::getInstance()->end();
}

