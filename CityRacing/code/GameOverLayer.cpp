#include "GameOverLayer.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include "StartLayer.h"
#include "ChooseLevelLayer.h"
#include "GameLayer.h"
#include "Constant.h"
int GameOverLayer::gold = 0;
int GameOverLayer::distance = 0;

bool GameOverLayer::init()
{
	//���ø���ĳ�ʼ��
	if (!Layer::init())
	{
		return false;
	}

	bgSpriteO = Sprite::create("scene1.jpg");
 	bgSpriteO->setPosition(270,480);
   	this->addChild(bgSpriteO,BGZORDER);

   	bgSpriteT = Sprite::create("scene1.jpg");
   	bgSpriteT->setPosition(270,1440);
   	this->addChild(bgSpriteT,BGZORDER+1);

	gameOverBg = Sprite::create("MenuBg.png");
	gameOverBg->setPosition(Point(270,480));
	this->addChild(gameOverBg,MENUZRODER);

	if(StartLayer::soundFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(	//��������
								"background.mp3",
								true
								);
	}


	if(GameLayer::isGameOver==true)
	{
		Sprite* pity = Sprite::create("Pity.png");
		pity->setPosition(Point(270,720));
		gameOverBg->addChild(pity,MENUZRODER);

		gameOverSprite[0] = Sprite::create("TryAgain.png");
		gameOverSprite[0]->setPosition(Point(270,340));
		gameOverBg->addChild(gameOverSprite[0],MENUZRODER);
	}else
	{
		Sprite* Congratulations = Sprite::create("Congratulations.png");
		Congratulations->setPosition(Point(270,720));
		gameOverBg->addChild(Congratulations,MENUZRODER);

		gameOverSprite[0] = Sprite::create("TryNext.png");
		gameOverSprite[0]->setPosition(Point(270,340));
		gameOverBg->addChild(gameOverSprite[0],MENUZRODER);
	}

	Sprite* Result = Sprite::create("Result.png");
	Result->setPosition(Point(270,520));
	gameOverBg->addChild(Result,MENUZRODER);

	LabelAtlas* lDistance = LabelAtlas::create(						//����һ��LabelAtlas����
			StringUtils::format("%d",GameOverLayer::distance),"upNum.png",20,23,'0');
	lDistance->setAnchorPoint(Point(0,0.5));			//����LabelAtlas����ê��
	lDistance->setPosition(								//����LabelAtlas����λ��
					Point(260,100));
	Result->addChild(lDistance,1);			//��LabelAtlas������ӵ�������

	LabelAtlas* lGold = LabelAtlas::create(						//����һ��LabelAtlas����
			StringUtils::format("%d",GameOverLayer::gold),"upNum.png",20,23,'0');
	lGold->setAnchorPoint(Point(0,0.5));			//����LabelAtlas����ê��
	lGold->setPosition(								//����LabelAtlas����λ��
						Point(240,50));
	Result->addChild(lGold,1);			//��LabelAtlas������ӵ�������

	Sprite* jiaSprite = Sprite::create("jia.png");
	jiaSprite->setPosition(Point(290,50));
	Result->addChild(jiaSprite,1);

	LabelAtlas* ewGold = LabelAtlas::create(
			StringUtils::format("%d",(int)(distance/50)),//=====================
					"upNum.png",20,23,'0');
	ewGold->setAnchorPoint(Point(0,0.5));
	ewGold->setPosition(Point(300,50));
	Result->addChild(ewGold,1);

	gameOverSprite[1] = Sprite::create("sp3.png");
	gameOverSprite[1]->setPosition(Point(270,260));
	gameOverBg->addChild(gameOverSprite[1],MENUZRODER);

	gameOverSprite[2] = Sprite::create("sp2.png");
	gameOverSprite[2]->setPosition(Point(270,180));
	gameOverBg->addChild(gameOverSprite[2],MENUZRODER);

	gameModeTemp = StartLayer::gameMode ;

	phbpx();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameOverLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,gameOverSprite[0]);
	for(int i=1;i<3;i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),gameOverSprite[i]);
	}

	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//����������ʱ�ص�
	sched->scheduleSelector(SEL_SCHEDULE(&GameOverLayer::bgUpdate),this,0.005,false);

	return true;
}
bool GameOverLayer::onTouchBegan(Touch* touch, Event* event)
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
		if(spriteTouch==gameOverSprite[0])
		{
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(GameOverLayer::continueMenuCallback,this)),
							NULL));
		}else if(spriteTouch==gameOverSprite[1])
		{
			spriteTouch->runAction(
					Sequence::create(
							ScaleTo::create(0.1,3),
							CallFunc::create(CC_CALLBACK_0(GameOverLayer::shopMenuCallback,this)),
							NULL));
		}else if(spriteTouch==gameOverSprite[2])
				{
					spriteTouch->runAction(
							Sequence::create(
									ScaleTo::create(0.1,3),
									CallFunc::create(CC_CALLBACK_0(GameOverLayer::garageMenuCallback,this)),
									NULL));
				}
		return true;
	}
	return false;
}
void GameOverLayer::onTouchEnded(Touch* touch, Event* event)
{
	spriteTouch->runAction(ScaleTo::create(0.1,1));
}
void GameOverLayer::continueMenuCallback()
{
	if(GameLayer::isGameOver == false&&StartLayer::gameModeLevel == 0)
	{
		if(ChooseLevelLayer::currLevel < 3)
		{
			ChooseLevelLayer::currLevel ++;
		}else
		{
			ChooseLevelLayer::currLevel = 1;
		}
		StartLayer::gameMode = 0;
	}
	crsm ->goGameLayer();
}
void GameOverLayer::garageMenuCallback()
{
	//�򳵵�״̬
	StartLayer::gameMode = 5;
	crsm ->goChooseCarLayer();
}
void GameOverLayer::shopMenuCallback()
{
	StartLayer::gameMode = 4;
	crsm ->goShopLayer();
}
int GameOverLayer::myGetIntegerForKey (std::string key)
{
	int result = UserDefault::getInstance()->getIntegerForKey(key.c_str());
	return result;
}
void GameOverLayer::mySetIntegerForKey(std::string key,int value)
{
	UserDefault::getInstance()->setIntegerForKey(key.c_str(),value);
}
void GameOverLayer::phbpx()
{
    int pInt=0;
    for(int i=0;i<5;i++)
    {
        pInt=myGetIntegerForKey(Constant::userRecord[i]);;
        if(pInt==0)
        {
        	mySetIntegerForKey(Constant::userRecord[i],GameOverLayer::distance);
            break;
        }
        if(GameOverLayer::distance==pInt)
        {
            break;
        }
        if(GameOverLayer::distance>pInt)
        {
            for(int j=4;j>i;j--)
            {
            	mySetIntegerForKey(
                		Constant::userRecord[j],
                			myGetIntegerForKey(Constant::userRecord[j-1]));
            }
            mySetIntegerForKey(Constant::userRecord[i],GameOverLayer::distance);
            break;
        }
    }
}
void GameOverLayer::bgUpdate()
{
	if(bgSpriteO->getPosition().y==1440)
	{
		bgSpriteO->setPosition(Point(270,-480));
	}else
	{
		bgSpriteO->setPosition(Point(270,bgSpriteO->getPosition().y+1));
	}

	if(bgSpriteT->getPosition().y==1440)
	{
		bgSpriteT->setPosition(Point(270,-480));
	}else
	{
		bgSpriteT->setPosition(Point(270,bgSpriteT->getPosition().y+1));
	}
}
