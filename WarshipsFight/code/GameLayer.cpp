#include "GameLayer.h"
#include "cocos2d.h"
#include "HKMJObject.h"
#include "WarShipObject.h"
#include "Weapon.h"
#include "AppMacros.h"
#include <list>
#include <queue>
#include "ChooseLevelLayer.h"
#include "Constant.h"
using namespace cocos2d;

int** visited;
int* target;
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    
    for(int i=0;i<2;i++)
    {
          Weapon* weaponSp = Weapon::create(i,Point(0,0),2);
    }    
    
	//����һЩ������
	allWeaponVCT = new std::vector<Weapon*>();
	delWeaponVCT = new std::vector<Weapon*>();

	allShipVCT =new std::vector<WarShipObject*>();	//���о���
	delShipVCT =new std::vector<WarShipObject*>();

	path = new std::vector<Point>();
	tempPath = new std::vector<Point>();
	//��ʼ����ͼ�е�
	initTMXMap();
	initTMXPZJCArray();
	initHKMJ();
	initJJItem();
	initBoomFrame();
	initBigBoomFrame();
	initPauseMenu();
	map->runAction(
		Sequence::create(
				MoveBy::create(2,Point((1136-960),0)),
				MoveBy::create(2,Point(0,-(768-540))),
				MoveBy::create(2,Point(-(1136-960),0)),
				MoveBy::create(2,Point(0,(768-540))),
				CallFunc::create(CC_CALLBACK_0(GameLayer::gameStartDJS,this)),
				CallFunc::create(CC_CALLBACK_0(GameLayer::initListenerTouchAndCallback,this)),
				NULL
		));
	initSound();
	initOceanBg();
	initMiscellaneous();
	if(ChooseLevelLayer::bacMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()//���ű�������
								->playBackgroundMusic("sound_bgm_battlefield.mp3");
	}
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("coolpic.png");
	//���������ȴ�ľ���
	for(int i = 0;i<2;i++)
	{
		weaponeSprite[i] = Sprite::createWithTexture(texture1);
		weaponeSprite[i]->setTextureRect(Rect(0, 0, 90, 0));
		weaponeSprite[i]->setAnchorPoint(Point(0.5,1));
		weaponeSprite[i]->setPosition(Point(55+i*100,105));
		this->addChild(weaponeSprite[i],100);
	}
	//��Ӵ�ֻ��ȴʱ��ľ���
	for(int i = 0;i<5;i++)
	{
		ShipCoolSprite[i] = Sprite::createWithTexture(texture1);
		ShipCoolSprite[i]->setTextureRect(Rect(0, 0, 90, 0));
		ShipCoolSprite[i]->setAnchorPoint(Point(0.5,1));
		ShipCoolSprite[i]->setPosition(Point(55+i*100,105));
		this->addChild(ShipCoolSprite[i],100);
	}

	initRaning();
	return true;
}
void GameLayer::initListenerTouchAndCallback()
{
	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouch->setSwallowTouches(false);
	//��ʼ����ʱ�ص�onTouchBegan����
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	//��ʼ����ʱ�ص�onTouchMoved����
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch,map);

	//��ʱ�ص�
	auto director = Director::getInstance();
	Scheduler* sched = director->getScheduler();
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::calNearestSmartIn),this,0.1,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::weaponsCoolTimeUpdate),this,0.1,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::removeShipUpdate),this,0.1,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::weaponeStateUpdate),this,0.01f,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::enemyShipAtHKMJUpdate),this,0.01f,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::oceanUpdate),this,0.01f,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::playerHKMJCoolTimeUpdate),this,3.0f,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::planeUpdate),this,0.01f,false);
}
void GameLayer::initRaning()
{
	ParticleSystemQuad* psq;
	if(ChooseLevelLayer::levelNum == 1)
	{
		psq = ParticleSystemQuad::create("snow.plist");//���ļ��м�������ϵͳ

	}else if(ChooseLevelLayer::levelNum == 2)
	{
		psq = ParticleSystemQuad::create("raining.plist");//���ļ��м�������ϵͳ

	}else if(ChooseLevelLayer::levelNum == 3)
	{
		psq = ParticleSystemQuad::create("snow.plist");//���ļ��м�������ϵͳ

	}else if(ChooseLevelLayer::levelNum == 4)
	{
		psq = ParticleSystemQuad::create("raining.plist");//���ļ��м�������ϵͳ

	}
	psq->retain();								//��������
	psq->setBlendAdditive(true);					//���û�Ϸ�ʽΪ����
	psq->setPosition(Point(480,270));
	this->addChild(psq, 10);		//�򲼾����еľ����������ϵͳ
}

void GameLayer::initMiscellaneous()
{
	Sprite* moneySp = Sprite::create("money.png");
	moneySp->setPosition(Point(940,520));
	this->addChild(moneySp,ITEM);

	Sprite* sdsSp = Sprite::create("sds.png");
	sdsSp->setPosition(Point(940,490));
	this->addChild(sdsSp,ITEM);

	moneyLabel = LabelAtlas::create(				//����һ��LabelAtlas����
								 "3000","labelatlas.png",15,19,'0');
	moneyLabel->setAnchorPoint(Point(1,0.5));
	moneyLabel->setPosition(Point(moneySp->getPosition().x-20,moneySp->getPosition().y));
	this->addChild(moneyLabel,ITEM);

	sdsNum = UserDefault::getInstance()->getIntegerForKey(Constant::SHADISHU.c_str());
	std::string sLabel = StringUtils::format("%d",sdsNum);

	sdsLabel = LabelAtlas::create(				//����һ��LabelAtlas����
			sLabel,"labelatlas.png",15,19,'0');
	sdsLabel->setAnchorPoint(Point(1,0.5));
	sdsLabel->setPosition(Point(sdsSp->getPosition().x-20,sdsSp->getPosition().y));
	this->addChild(sdsLabel,ITEM);
}
void GameLayer::initOceanBg()
{
	Sprite* oceanbg0Sp = Sprite::create("oceanbg0.png");
	oceanbg0Sp->setPosition(Point(568,384));
	map->addChild(oceanbg0Sp,-1);
	for(int i=0;i<2;i++)
	{
		oceanbg1Sp[i] = Sprite::create("oceanbg1.png");
		oceanbg1Sp[i]->setPosition(Point(568-i*1136,384));
		map->addChild(oceanbg1Sp[i],0);
	}
}
void GameLayer::initSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()							//������Ч
						->preloadBackgroundMusic("sound_bgm_battlefield.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_explode_general.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_nuclear.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_missile.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_star_1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_star_2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_star_3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_break.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_error.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("sound_sfx_destination.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//��ʹ��Ч
						->preloadEffect("flyby2.wav");
}
void GameLayer::initPauseMenu()
{
	puaseMenu = MenuItemImage::create(
				"pause.png",
				"pausep.png",
				CC_CALLBACK_0(GameLayer::puaseCallback, this)
		);
	puaseMenu->setPosition(Point(30,510));

	//����һ���˵�����
	Menu* menu = Menu::create(puaseMenu,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	this->addChild(menu, 10);
}
void GameLayer::puaseCallback()
{
	playSound();

	isGameOver = true;
	for(int i =0;i<5;i++)
	{
		jjbgSp[i]->setEnabled(false);
	}
	for(int i =0;i<3;i++)
	{
		shipWeapon[i]->setEnabled(false);
	}
	puaseMenu->setEnabled(false);
	Director::getInstance()->pause();
	gamePausebb = Sprite::create("btmbb.png");
	gamePausebb->setPosition(Point(480,270));
	this->addChild(gamePausebb,10);

	Sprite* gameOverttSp = Sprite::create("pausett.png");
	gameOverttSp->setPosition(Point(480,410));
	gamePausebb->addChild(gameOverttSp,12);

	Sprite* gameOverbbSp = Sprite::create("bbp.png");
	gameOverbbSp->setAnchorPoint(Point(0,1));
	gameOverbbSp->setPosition(Point(0,0));
	gameOverttSp->addChild(gameOverbbSp,9);

	MenuItemImage* backItem = MenuItemImage::create(
			"back.png",
			"backp.png",
			CC_CALLBACK_0(GameLayer::backCallback, this)
	);
	backItem->setPosition(Point(230,90));

	MenuItemImage* restartItem = MenuItemImage::create(
			"cxks.png",
			"cxksp.png",
			CC_CALLBACK_0(GameLayer::restartCallback, this)
	);
	restartItem->setPosition(Point(90,90));

	MenuItemImage* tcItem = MenuItemImage::create(
			"tc.png",
			"tcp.png",
			CC_CALLBACK_0(GameLayer::tcCallback, this)
	);
	tcItem->setPosition(Point(370,90));

	//����һ���˵�����
	Menu* menu = Menu::create(backItem,restartItem,tcItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	gameOverbbSp->addChild(menu, 2);
}
void GameLayer::backCallback()
{
	playSound();
	isGameOver = false;
	for(int i =0;i<5;i++)
	{
		jjbgSp[i]->setEnabled(true);
	}
	for(int i =0;i<3;i++)
	{
		shipWeapon[i]->setEnabled(true);
	}
	this->removeChild(gamePausebb);
	puaseMenu->setEnabled(true);
	Director::getInstance()->resume();
}
void GameLayer::gameStartDJS()
{
	if(waveNum == 1)
	{
		Sprite* waveSp= Sprite::create("wave.png");
		waveSp->setPosition(Point(380,520));
		this->addChild(waveSp,100);

		Sprite* bsSp= Sprite::create("bs.png");
		bsSp->setPosition(Point(460,520));
		this->addChild(bsSp,100);

		labelWaveIndex = Label::createWithTTF(
						StringUtils::format("%d/5",waveNum),"FZKATJW.ttf",50
				);
		labelWaveIndex->setPosition(Point(540,520));
		labelWaveIndex->enableOutline(Color4B(0,0,0,255),2);
		this->addChild(labelWaveIndex,100);
	}else
	{
		labelWaveIndex->setString(StringUtils::format("%d/5",waveNum));
	}
	Sprite* sp1 = Sprite::create("nextFlag0.png");
	sp1->setPosition(Point(50,270));
	this->addChild(sp1,100);
	sp1->runAction(
			Sequence::create(
				Repeat::create(
					Sequence::create(
						ScaleTo::create(0.5,1.1),
						ScaleTo::create(0.5,0.9),
						NULL),
						10),
						RemoveSelf::create(true),
						NULL
	));

	ProgressTo* actionTo = ProgressTo::create(10, 100);		//����һ�����������0%��100%�Ķ���
	ProgressTimer* radialPT = ProgressTimer::create(			//����һ����װ�ž����ProgressTimer����
								 Sprite::create("nextFlag1.png"));
	radialPT->setPosition(Point(55, 270)); 	//���ð�װ�ž����ProgressTimer�����λ��
	radialPT->setMidpoint(Point(0.5f, 0.5f)); 	//���ðٷֱ�Ч���Ĳο���
	radialPT->setType(ProgressTimer::Type::RADIAL);	//����Ϊ�뾶ģʽ
	this->addChild(radialPT,101);				//����װ�ž����ProgressTimer������ӵ�������

	radialPT->runAction(
			Sequence::create(
					Spawn::create(
							actionTo->clone(),
							Repeat::create(
									Sequence::create(
										ScaleTo::create(0.5,1.1),
										ScaleTo::create(0.5,0.9),
										NULL
										),
								10),NULL
					),
					CallFunc::create(CC_CALLBACK_0(GameLayer::startCallback,this)),
					RemoveSelf::create(true),
					NULL
					));		//�ظ�ִ�аٷֱȶ���
	Sprite* shipWaveSp = Sprite::create("shipwave.png");
	shipWaveSp->setAnchorPoint(Point(0,0.5));
	shipWaveSp->setPosition(Point(960,270));
	this->addChild(shipWaveSp,7);
	shipWaveSp->runAction(
			Sequence::create(
					MoveTo::create(10,Point(-530,270))
					,RemoveSelf::create(true)
					,NULL
			)
	);

	Label* waveIndex = Label::createWithTTF(
					StringUtils::format("%d",waveNum),"FZKATJW.ttf",60
			);
	waveIndex->setTextColor(Color4B(255,0,0,255));
	waveIndex->enableOutline(Color4B(255,255,255,255),1);
	waveIndex->setPosition(Point(105,35));
	shipWaveSp->addChild(waveIndex,2);
}
void GameLayer::startCallback()
{
	enemyShipCount = 10;
	//��ӵд�
	addEnemyShip();
	waveNum = waveNum + 1;
}
void GameLayer::initBoomFrame()
{
	std::string sa[6]={						//�����ж���ͼƬ��·��������������
		"boom1.png","boom2.png","boom3.png",
		"boom4.png","boom5.png","boom6.png"
	};
	Vector<SpriteFrame*> animFrames;		//������Ŷ���֡���б����

	SpriteFrame *f0=SpriteFrame::create(sa[0],
						Rect(0,0,104,102));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f0);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f1=SpriteFrame::create(sa[1],
						Rect(0,0,107,102));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f1);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f2=SpriteFrame::create(sa[2],
						Rect(0,0,97,95));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f2);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f3=SpriteFrame::create(sa[3],
						Rect(0,0,93,92));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f3);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f4=SpriteFrame::create(sa[4],
						Rect(0,0,53,54));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f4);				//����һ�ζ����е�����֡��ŵ�������

	SpriteFrame *f5=SpriteFrame::create(sa[5],
						Rect(0,0,53,53));	//��ȡ�˶����е�ָ������֡
	animFrames.pushBack(f5);				//����һ�ζ����е�����֡��ŵ�������

	Animation *anmi=Animation::createWithSpriteFrames
			(animFrames, 0.1f);					//����ָ�򶯻������ָ��
	anmiAc[1]=Animate::create(anmi);			//����������������
	anmiAc[1]->retain();						//��Ϊ��ʱ���ã����Ա������ã���ֹ���Զ��ͷ�
}
void GameLayer::initBigBoomFrame()
{
	std::string sa[4]={						//�����ж���ͼƬ��·��������������
		"bigBoom1.png","bigBoom2.png",
		"bigBoom3.png","bigBoom4.png"
	};
	Vector<SpriteFrame*> animFrames;		//������Ŷ���֡���б����
	for(int i=0;i<4;i++)
	{
		SpriteFrame *f0=SpriteFrame::create(sa[i],
							Rect(0,0,166,160));	//��ȡ�˶����е�ָ������֡
		animFrames.pushBack(f0);				//����һ�ζ����е�����֡��ŵ�������
	}
	Animation *anmi=Animation::createWithSpriteFrames
			(animFrames, 0.2f);					//����ָ�򶯻������ָ��
	anmiAc[0]=Animate::create(anmi);			//����������������
	anmiAc[0]->retain();						//��Ϊ��ʱ���ã����Ա������ã���ֹ���Զ��ͷ�
}
void GameLayer::expansionRing()
{
	Sprite* ringSp = Sprite::create("bigBoom5.png");
	ringSp->setPosition(Point(568,384));
	map->addChild(ringSp,1000);
	ringSp->runAction(
			Sequence::create(
					ScaleTo::create(2,3),
					RemoveSelf::create(true),
					NULL));

	std::vector<WarShipObject*>::iterator allShip ;
	for(allShip =allShipVCT->begin();allShip!= allShipVCT->end();)
	{
		if((*allShip)->shipType == 2)
		{
			(*allShip)->lifeValue =0;
		}
		allShip++;
	}
}
//��ʼ��TMX��ͼ�ķ���
void GameLayer::initTMXMap()
{
	std::string mapPath =StringUtils::format("map_%d.tmx",ChooseLevelLayer::levelNum);
	//����TMX��ͼ
	map = TMXTiledMap::create(mapPath);

	//��ȡ������ײ���Ĳ�
	colliLayer=map->layerNamed ("pzjcLayer");

	//������ײ���㲻�ɼ�
	colliLayer->setVisible(false);
	map->setAnchorPoint(Point(1,0));
	map->setPosition(Point(960,0));
	//��TMX��ͼ��ӽ�����
	this->addChild(map, 0);
	mapPoint = map->getPosition();
	int mapWidth = map->getMapSize().width;
	int mapHeight = map->getMapSize().height;
	row = mapWidth;		//71
	col = mapHeight;   	//48
	//��õ���ͼ��Ĵ�С��Ϊ���ڻ���ʱ�õ�ƫ������������Ƴ����������а��ͼ���ƫ�Ʋ�
	auto m_tamara = colliLayer->tileAt(Point(0,0));
	auto texture = m_tamara->getTexture();
	auto blockSize = texture->getContentSize();
	trans = Point(0,blockSize.height/2);
}
void GameLayer::initTMXPZJCArray()
{
	//������̬��ά����
	Map_DATA = new int* [row];
	for(int i = 0; i<row; i++)
	{
		Map_DATA[i] = new int[col];
	}
	//���һ��ͼ���е�����ֵ
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			//�õ�layer��ÿһ��ͼ���gid
			unsigned int gid = colliLayer->tileGIDAt(Point(i,j));
			//ͨ��gid�õ���ͼ���е����Լ�,���Լ������Լ�ֵ�Ե���ʽ���ڵ�
			auto tiledic = map->propertiesForGID(gid);
			//ͨ�����õ�value
			const String mvalue = tiledic.asValueMap()["sfpz"].asString();
			//��mvalueת����int����
			int mv = mvalue.intValue();
			//��ʼ����ͼ�е�����
			Map_DATA[i][j] = mv;
		}
	}
	//��������
	visited = new int*[row];
	for(int i = 0; i<row; i++)
	{
		visited[i] = new int[col];
	}
	initVisitedArr();
}
//��ʼ��Ѱ��������-----��������Ϊû���߹�
void GameLayer::initVisitedArr()
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			visited[i][j] = 0;
		}
	}
}
bool GameLayer::onShipTouchBegan(Touch* touch, Event* event)
{
	if(isGameOver == true)
	{
		return false;
	}
	return true;
}
void GameLayer::onShipTouchEnded(Touch* touch, Event* event)
{
	WarShipObject* targetSp = static_cast<WarShipObject*>(	//��ȡ��ǰ�������󣬲�ת��Ϊ��������
							event->getCurrentTarget());
	Point locationSp = targetSp->convertToNodeSpace(touch->getLocation());//��ȡ��ǰ����
	Size sizeSp = targetSp->getContentSize();			//��ȡ����Ĵ�С
	Rect rectSp = Rect(0,0,sizeSp.width, sizeSp.height);//����һ�����ζ������С�뾫����ͬ
	if(rectSp.containsPoint(locationSp))
	{
		//���ô�ֻ��ȴʱ�䲻�ɼ�
		for(int k = 0;k<5;k++)
		{
			ShipCoolSprite[k]->setVisible(false);
		}
		//�жϵ�ǰ����Ĵ�ֻ�Ƿ�Ϊ�ϴε���Ĵ�ֻ
		if(lastTouchSprite == targetSp&&targetSp->shipType == 1)
		{
			if(targetSp->state == 0)
			{
				targetSp->state = 1;		//���Ϊѡ��״̬
				showWarShipItem(targetSp);
				warShipAddChild(targetSp);
				selectShip = true;
			}
			lastTouchSprite = targetSp;
			currTouchSprite = targetSp;
		}else if(lastTouchSprite != targetSp&&targetSp->shipType == 1)
		{	//����Ϊ�ϴε���Ĵ�ֻ
			if(lastTouchSprite != NULL)
			{
				lastTouchSprite->state = 0;
				showWarShipItem(lastTouchSprite);
				lastTouchSprite->removeChildByTag(DWPTAG);
				lastTouchSprite->removeChildByTag(DWSPRITETAG);
				lastTouchSprite->removeChildByTag(COMPASSSPRITE);
				lastTouchSprite->removeChildByTag(BQSPRITETAG);
				selectShip = false;
			}
			targetSp->state = 1;//���Ϊѡ��״̬
			showWarShipItem(targetSp);
			warShipAddChild(targetSp);
			selectShip = true;
			lastTouchSprite = targetSp;
			currTouchSprite = targetSp;
		}
	}
}
//��Ӵ�ֻ���Ӿ���---��ΧȦ----��׼��
void GameLayer::warShipAddChild(WarShipObject* wsoSprite)
{
	Size size = wsoSprite->getContentSize();
	Sprite* compassSprite = Sprite::create("compass.png");
	compassSprite->setPosition(Point(size.width/2,size.height/2));
	wsoSprite->addChild(compassSprite,1,COMPASSSPRITE);
	compassSprite->runAction(RepeatForever::create(RotateBy::create(8,360)));

	Sprite* bqSprite = Sprite::create("bq.png");
	bqSprite->setAnchorPoint(Point(0,0));
	bqSprite->setPosition(Point(size.width/2,size.height/2));
	wsoSprite->addChild(bqSprite,1,BQSPRITETAG);

	addSaveSprite(wsoSprite);
}
//��ʾ��ǰӦ����ʾ����
void GameLayer::showWarShipItem(WarShipObject* wsoSprite)
{
	bool flag ;
	if(wsoSprite->state == 0)
	{
		flag = true;
	}else if(wsoSprite->state == 1)
	{
		flag = false;
	}
	for(int i = 0;i<5;i++)
	{
		jjbgSp[i] ->setVisible(flag);
	}
	shipWeapon [0] -> setVisible(!flag);
	shipWeapon [2] -> setVisible(!flag);
	if(wsoSprite->itemCount == 2)
	{
		shipWeapon[1]->setVisible(!flag);
	}
}
void GameLayer::addTouchListener(WarShipObject* WarShipSprite)
{
	//����һ�����㴥������
	EventListenerTouchOneByOne* listenerTouchShip = EventListenerTouchOneByOne::create();
	//�����´�����
	listenerTouchShip->setSwallowTouches(false);
	//��ʼ����ʱ�ص�onTouchBegan����]
	listenerTouchShip->onTouchBegan = CC_CALLBACK_2(GameLayer::onShipTouchBegan, this);
	//��������ʱ�ص�onTouchEnded����
	listenerTouchShip->onTouchEnded = CC_CALLBACK_2(GameLayer::onShipTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouchShip,WarShipSprite);
}
//��Ӿ����ķ���
void GameLayer::addWarShip(Point touchPoint ,int seleteNum)
{
	//��������װ��Ϊ�������к�
	Point tempPoint ;
	tempPoint = touchPointToRowCol(touchPoint);
	//�жϵ���ĸ����Ƿ�����
	if(Map_DATA[(int)tempPoint.x][(int)tempPoint.y] == 1)
	{

		addWrongPrompt(touchPoint);
		return;
	}
	int myGoldTemp = myGold-(selectIndex+1)*400;
	if(myGoldTemp < 0)
	{
		addWrongPrompt(touchPoint);
		moneyLabel->runAction(
				Sequence::create(
						ScaleTo::create(1,2),
						ScaleTo::create(1,1),
						NULL
				));
		return ;
	}
	myGold = myGoldTemp;
	std::string restMoney = StringUtils::format("%d",myGold);
	moneyLabel->setString(restMoney);

	Sprite* MZSprite = Sprite::create("MZ.png");
	MZSprite->setPosition(touchPoint);
	map->addChild(MZSprite,10);
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
										->playEffect("sound_sfx_destination.mp3");
	}

	MZSprite->runAction(
			Sequence::create(
					ScaleTo::create(0.5,1.2),
					ScaleTo::create(0.5,0.9),
					RemoveSelf::create(true),
					NULL)
	);


	//���ߣ���������ΪĿ���
	int targetAll[1][2] =
	{
			{(int)tempPoint.y ,(int)tempPoint.x}
	};
	target = targetAll[0];
	//����һ����ֻ
	WarShipObject* wso = WarShipObject::create(
			StringUtils::format("warShip%d.png",seleteNum),Point(1120,368),seleteNum,1);

	//����ǰ��ֻ��ֵ��������˳��
	for(int i = 0;i<8;i++)
	{
		for(int j = 0;j<2;j++)
		{
			wso->sequence[i][j] = SEQUENCEZARRAY[i][j];
		}
	}
	wso->shipNum = seleteNum;
	//���ô�ֻ��Ŀ���
	wso->targetRow = tempPoint.y;
	wso->targetCol = tempPoint.x;
	map->addChild(wso,10);

	//����ֻ��Ӽ���
	addTouchListener(wso);
	//��ӵ����д�ֻ����
	allShipVCT->push_back(wso);
	//��������·���ķ�������������·��
	searchPath(wso);
	//��ȴʱ�临��ֵ
	switch(seleteNum)
	{
	case 0:
		playerHKMJ->coolTime0 = 104;
		break;
	case 1:
		playerHKMJ->coolTime1 = 104;
		break;
	case 2:
		playerHKMJ->coolTime2 = 104;
		break;
	case 3:
		playerHKMJ->coolTime3 = 104;
		break;
	case 4:
		playerHKMJ->coolTime4 = 104;
		break;
	}
}
//�����������·���ķ�������˳��
void GameLayer::randomSort()
{
	int tempSequence[8][2] =
		{
			{0,1},{-1, 0},{1, 0},
			{0,-1},{-1, 1},
			{-1, -1},{1, -1},{1, 1}
		};

	for(int i = 0;i<8;i++)
	{
		for(int j = 0;j<2;j++)
		{
			resultSequence[i][j] = -2;
		}
	}
	int hNum [8];
	for(int i = 0;i<8;i++)
	{
		hNum[i] = -1;
	}
	for(int i = 0;i<8;i++)
	{
		bool hadNumFlag = false;
		int random = rand()%8;
		for(int j = 0;j<8;j++)
		{
			if(hNum[j] == random)
			{
				hadNumFlag = true;
				break;
			}
		}
		if(hadNumFlag == true)
		{
			i = i - 1;
			continue;
		}
		hNum [i] =random;
		for(int k = 0;k<2;k++)
		{
			resultSequence[i][k] = tempSequence[random][k];
		}
	}
}
//����·��
void GameLayer::searchPath(WarShipObject* wso)
{
	BFSCalPath(wso);
	wso->warShipPath = path;
	createFiniteTimeActionByVector(wso);
}
//��������װ��Ϊ�������к�
Point GameLayer::touchPointToRowCol(Point touchPoint)
{
	Point resultPoint;
	int row = (int)touchPoint.x/CELLSIZE + ((((int)touchPoint.x)%CELLSIZE == 0)?0:1);
	int col = (int)(MAPWIDTH-touchPoint.y)/CELLSIZE + (((int)(MAPWIDTH-touchPoint.y)%CELLSIZE == 0)?0:1);
	resultPoint = Point(row,col);
	return resultPoint;
}
//��������㷨
void GameLayer::BFSCalPath(WarShipObject* wso)
{
	myQueue = new std::queue<int(*)[2]>();
	hm =new std::map<std::string, int(*)[2]>();
	hm->clear();
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			visited[i][j] = 0;
		}
	}

	bool flag = true;
	//���濪ʼ���Ŀ��������
	int (*start)[2] = new int[2][2];
	if((wso->targetRow != -1&&wso->targetCol != -1 && wso->state == 1))
	{
		wso->initRow = wso->targetRow;
		wso->initCol = wso->targetCol;
	}
	//������ʼ��
	start[0][0] = wso->initRow;
	start[0][1] = wso->initCol;
	//����Ŀ���
	start[1][0] = wso->initRow;
	start[1][1] = wso->initCol;

	//����ʼ��Ž�������
	myQueue->push(start);
	while(flag)
	{
		//ȡ�����е�
		int(*currentEdge)[2] = myQueue->front();
		//���������е�����
		myQueue->pop();
		//��ȡĿ���-------�±�Ϊ1
		int* tempTarget = currentEdge[1];
		//�ж�Ŀ����Ƿ���ʹ�
		if(visited[tempTarget[1]][tempTarget[0]] == 1)
		{
			continue;
		}
		//���Ŀ�ĵ�Ϊ�ѷ��ʹ�
		visited[tempTarget[1]][tempTarget[0]] = 1;
		//������ת�����ַ���
		std::string str1;
		std::string str2;
		str1 = StringUtils::format("%d", tempTarget[0]);
		str2 = StringUtils::format("%d", tempTarget[1]);
		//��¼����ʱĿ�ĵصĵ�ĸ��ڵ�
		hm->insert(std::map<std::string,int(*)[2]>::value_type(str1+":"+str2,currentEdge));
		//�ж��Ƿ��ҵ�Ŀ���
		if(tempTarget[0]==target[0] && tempTarget[1]==target[1])
		{
			break;
		}
		//�����п��ܵĵ�����к������
		int currCol = tempTarget[0];
		int currRow = tempTarget[1];
		int(*sequence)[2] = NULL;
		sequence = ((wso->sequence));

		//ѭ��8�������������
		for(int m = 0; m<8; m++)
		{
			int* rc = sequence[m];
			int i = rc[1];
			int j = rc[0];
			if(i==0 && j==0)
			{
				continue;
			}
			//����������ڵ�ͼ��Χ���������һ���ļ���
			if(currRow+i>=0 && currRow+i<row && currCol+j>=0 && currCol+j<col &&
					Map_DATA[currRow+i][currCol+j]!=1)
			{
				//������ά����
				int (*tempEdge)[2] = new int[2][2];
				tempEdge[0][0] = tempTarget[0];
				tempEdge[0][1] = tempTarget[1];
				tempEdge[1][0] = currCol+j;
				tempEdge[1][1] = currRow+i;
				//����ά������ӽ�������
				myQueue->push(tempEdge);
			}
		}
	}
	transformBTMapandVector(wso);
}
void GameLayer::transformBTMapandVector(WarShipObject* wso)
{
	tempPath->clear();
	std::string str1;
	std::string str2;
//	auto tar = colliLayer->positionAt(Point(target[1],target[0]));//
	//�������յ��������·��
	std::map<std::string, int(*)[2]>::iterator iter;	//����map����������
	int* temp = target;									//��¼�յ�
	while(true)
	{
//		double xx;
//		double yy;
		//������ת�����ַ���
		str1 = StringUtils::format("%d", temp[0]);
		str2 = StringUtils::format("%d", temp[1]);
		std::string key = str1+":"+str2;
		iter = hm->find(key);
		int (*tempA)[2] = iter->second;
		//������ҵ���Ԫ��
		Point start;
		Point end;
		if(iter != hm->end())
		{
			//�������еõ�colliLayer�и�ͼ���λ��
			start = colliLayer->positionAt(Point(tempA[0][1],tempA[0][0]));
			//�������еõ�colliLayer�и�ͼ���λ��
			end = colliLayer->positionAt(Point(tempA[1][1],tempA[1][0]));

			start.x = start.x+trans.x;
			start.y = start.y+trans.y;
			end.x = end.x+trans.x;
			end.y = end.y+trans.y;
			tempPath->push_back(end);
		}
		//�ж��з񵽳�����
		if(tempA[0][0]==wso->initRow&&tempA[0][1]==wso->initCol)
		{
			tempPath->push_back(start);
			break;
		}
		temp = tempA[0];//�߶ε��������
	}
	transformPath();
}
//�ŵ�������ʻ·����������
void GameLayer::transformPath()
{
	path ->clear();
	std::vector<Point>::iterator tempPoint;
	for(tempPoint = tempPath->end()-1;tempPoint != tempPath->begin()-1;tempPoint--)
	{
		path->push_back(*tempPoint);
	}
}
void GameLayer::createFiniteTimeActionByVector(WarShipObject* warShip)
{
	//����������¼��ǰ��·������
	int countTemp=1;
	FiniteTimeAction* preAc;
	Point lastPoint=warShip->getPosition();
	Point currPoint=warShip->startPoint;
    int forCount = 0;
	std::vector<Point>::iterator tempPoint;
	for(tempPoint = warShip->warShipPath->begin();tempPoint != warShip->warShipPath->end();tempPoint++)
	{
        if(forCount == 0){
            lastPoint  =(*tempPoint);
            forCount++;
            continue;
        }
		currPoint=(*tempPoint);
		float dx=currPoint.x-lastPoint.x;
		float dy=currPoint.y-lastPoint.y;
		float dis =(float)sqrt(dx*dx+dy*dy);
		float moveT=0;
		moveT = dis/warShip->speed;
		int tempRotation = orderDirection(dx,dy);
		if(warShip->rotation != tempRotation)
		{
            
			warShip->rotation = tempRotation;
			RotateTo* rtemp = RotateTo::create(0.5,warShip->rotation);

			if(countTemp==1)
			{
				preAc=rtemp;
			}else if(countTemp>1)
			{
				preAc=Sequence::createWithTwoActions(preAc,rtemp);
			}
			MoveTo* mtemp=MoveTo::create(moveT,*tempPoint);
			preAc=Sequence::createWithTwoActions(preAc,mtemp);
		}else
		{
			if(countTemp==1)
			{
				MoveTo* mtemp=MoveTo::create(moveT,*tempPoint);
				preAc=mtemp;
			}
			else if(countTemp>1)
			{
				MoveTo* mtemp=MoveTo::create(moveT,*tempPoint);
				preAc=Sequence::createWithTwoActions(preAc,mtemp);
			}
		}
		countTemp++;
		lastPoint=currPoint;
	}
	warShip->runAction(Sequence::create(
			preAc,NULL));
}
//��ȡ��ת�Ƕȵķ���
int  GameLayer::orderDirection(float dx,float dy)
{
	if(dx == 0 && dy>0)
	{
		return 90;
		//��
	}else if(dx == 0 && dy<0)
	{
		return -90;
		//��
	}else if(dy == 0 && dx >0)
	{
		return 180;
		//��
	}else if(dy == 0 && dx <0)
	{
		return 0;
		//��
	}else if(dx <0 && dy >0)
	{
		return 45;
		//����
	}else if(dx >0 && dy >0)
	{
		return 135;
		//����
	}
	else if(dx <0 && dy <0)
	{
		return -45;
		//����
	}
	else if(dx >0 && dy <0)
	{
		return -135;
		//����
	}
	return 0;
}
//��������ֻ����ȴʱ��Ļص�����
void GameLayer::weaponsCoolTimeUpdate()
{
	std::vector<WarShipObject*>::iterator tWarShip ;
	for(tWarShip = allShipVCT->begin();tWarShip != allShipVCT->end();tWarShip++)
	{
		if((*tWarShip)->weapon0CoolTime > 0)
		{
			(*tWarShip)->weapon0CoolTime --;
		}
		if((*tWarShip)->weapon1CoolTime > 0)
		{
			(*tWarShip)->weapon1CoolTime --;
		}
	}
	if(currTouchSprite != NULL)
	{
		weaponeSprite[0]->setVisible(true);
		weaponeSprite[1]->setVisible(true);
		weaponeSprite[0]->setTextureRect(Rect(0, 0, 90, currTouchSprite->weapon0CoolTime));
		weaponeSprite[1]->setTextureRect(Rect(0, 0, 90, currTouchSprite->weapon1CoolTime));
	}else
	{
		weaponeSprite[0]->setVisible(false);
		weaponeSprite[1]->setVisible(false);
	}
	if(playerHKMJ->coolTime0 >0)
	{
		playerHKMJ->coolTime0--;
		ShipCoolSprite[0]->setTextureRect(Rect(0, 0, 90, playerHKMJ->coolTime0));
	}
	if(playerHKMJ->coolTime1 >0)
	{
		playerHKMJ->coolTime1--;
		ShipCoolSprite[1]->setTextureRect(Rect(0, 0, 90, playerHKMJ->coolTime1));
	}
	if(playerHKMJ->coolTime2 >0)
	{
		playerHKMJ->coolTime2--;
		ShipCoolSprite[2]->setTextureRect(Rect(0, 0, 90, playerHKMJ->coolTime2));
	}
	if(playerHKMJ->coolTime3 >0)
	{
		playerHKMJ->coolTime3--;
		ShipCoolSprite[3]->setTextureRect(Rect(0, 0, 90, playerHKMJ->coolTime3));
	}
	if(playerHKMJ->coolTime4 >0)
	{
		playerHKMJ->coolTime4--;
		ShipCoolSprite[4]->setTextureRect(Rect(0, 0, 90, playerHKMJ->coolTime4));
	}
}
//��ӵ���
bool GameLayer::addWeapon(int selectIndex,Point startPoint,Point finalPoint,WarShipObject* ship,int launchForm)
{
    CCLOG("ADDWEAPON -------START");
	//�ж�ѡ���Ϊ����1����2
	if(selectIndex == 0)
	{
		if(ship->weapon0CoolTime != 0)
		{
			return false;
		}
	}else if(selectIndex == 1)
	{
		if(ship->weapon1CoolTime != 0)
		{
			return false;
		}
	}
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
									->playEffect("sound_sfx_missile.mp3");
	}

	//������������������ӵ�������
	Point pShip = startPoint;
	Weapon* weaponSp = Weapon::create(selectIndex,pShip,launchForm);
    weaponSp->retain();
	weaponSp->weaponFromShip = ship;
	weaponSp->power = ship->attackPower;
	weaponSp->targetPoint = finalPoint;
	switch(selectIndex)
	{
	case 0:		weaponSp->setScale(0.03);	break;
	case 1:   	weaponSp->setScale(0.4);	break;
	}

	weaponSp->setPositionZ(50);
	map->addChild(weaponSp,WQTAG);
	allWeaponVCT->push_back(weaponSp); //===��ӵ�����������

	weaponSp->startPoint = pShip;
	weaponSp->targetPoint = finalPoint;
	weaponSp->currX = weaponSp->startPoint.x;
	weaponSp->currY = weaponSp->startPoint.y;
	float midx = 0;
	float midy = 0;
	//�жϷ��䷽��
	if(weaponSp->startPoint.x - weaponSp->targetPoint.x <0)
	{//����
		midx = fabs(weaponSp->targetPoint.x -weaponSp->startPoint.x)/2+weaponSp->startPoint.x;
		weaponSp->forwardLeft = false;
	}else
	{//����
		midx = fabs(weaponSp->startPoint.x -weaponSp->targetPoint.x)/2+weaponSp->targetPoint.x;
		weaponSp->forwardLeft = true;
	}
	midy = ZMAX;
	//��¼��ǰ���������ߵ��м��
	weaponSp->midx = midx;
	weaponSp->midy = midy;

	float a =0;
	// y = a*(x-x1)*(x-x2);

	//x-z���������
	//��a
	a = midy/((midx-weaponSp->startPoint.x)*(midx-weaponSp->targetPoint.x));
	weaponSp->a = a;
	weaponSp->degreeB = -a*(weaponSp->startPoint.x+weaponSp->targetPoint.x);

	//y =  k*x + b----------x-y��
	//б��
	float k = (weaponSp->startPoint.y-weaponSp->targetPoint.y)/(weaponSp->startPoint.x-weaponSp->targetPoint.x);
	//b
	float b = weaponSp->startPoint.y-k*weaponSp->startPoint.x;

	//��¼�ڵ����������Ϣ
	weaponSp ->k = k;
	weaponSp ->b = b;

	//����ת�Ƕ�
	float dir = (float)atan(weaponSp->k);
	if(weaponSp->forwardLeft == true)
	{
		weaponSp->rotationZ = 180 + dir/PI*180 ;
	}else
	{
		weaponSp->rotationZ = dir/PI*180 ;
	}
	weaponSp->rotationZ = -weaponSp->rotationZ;
	if(weaponSp->rotationZ < 0 &&weaponSp->rotationZ > -90)
	{
		weaponSp->rotationZ = 270 + 90 + weaponSp->rotationZ ;
	}else if(weaponSp->rotationZ < -90 &&weaponSp->rotationZ > -180)
	{
		weaponSp->rotationZ = 180 + weaponSp->rotationZ ;
	}else if(weaponSp->rotationZ < -180 &&weaponSp->rotationZ > -270)
	{
		weaponSp->rotationZ = 180 + weaponSp->rotationZ ;
	}
	//���õ�ǰ�����������ȴʱ��
	if(selectIndex == 0)
	{
		ship->weapon0CoolTime = 104;
	}else if(selectIndex == 1)
	{
		ship->weapon1CoolTime = 104;
	}
    CCLOG("ADDWEAPON -------END");
	return true;
}
float GameLayer::callPointZ(float x,Weapon* weaponSp)
{
	float result = 0;
	result = weaponSp->a*(x-weaponSp->startPoint.x)*(x-weaponSp->targetPoint.x);
	return result;
}
float GameLayer::callPointY(float x,Weapon* weaponSp)
{
	float result = 0;
	result = weaponSp->k*x+weaponSp->b;
	return result;
}
float GameLayer::callDegree(float x,Weapon* weaponSp)
{
	float result = 0;
	//��΢��  y= a*x*x + b*x +c
//	result = 2*weaponSp->a*x+weaponSp->degreeB;

	float k = (weaponSp->midy - weaponSp->currZ)/(weaponSp->midx - weaponSp->currX);
	result = k*2;
	return result;
}
float GameLayer::callTwoPointDis(Point startPoint,Point EndPoint)
{
	float result = 0;
	float dx = startPoint.x - EndPoint.x;
	float dy = startPoint.y - EndPoint.y;
	result = sqrt(dx*dx+dy*dy);
	return result;
}
void GameLayer::weaponeStateUpdate()
{
	std::vector<Weapon*>::iterator tWeapone ;
	for(tWeapone = allWeaponVCT->begin();tWeapone != allWeaponVCT->end();)
	{
		(*tWeapone)->count ++;
		if((*tWeapone)->count % 20 == 0)
		{
			(*tWeapone)->step = (*tWeapone)->step +1;
		}
		if((*tWeapone)->forwardLeft == false)
		{
			(*tWeapone)->currX = (*tWeapone)->currX+(*tWeapone)->step;
		}else if((*tWeapone)->forwardLeft == true)
		{
			(*tWeapone)->currX = (*tWeapone)->currX-(*tWeapone)->step;
		}

		float z = callPointZ((*tWeapone)->currX,(*tWeapone));
		float y = callPointY((*tWeapone)->currX,(*tWeapone));
		float degree = callDegree((*tWeapone)->currX,(*tWeapone));
		(*tWeapone)->currZ = z;
		(*tWeapone)->setPositionX((*tWeapone)->currX);
		(*tWeapone)->setPositionY(y);
		(*tWeapone)->setPositionZ(z);

		float direction=(float)atan(degree);
		float angleY =0;

		if((*tWeapone)->forwardLeft == true)
		{
			angleY = 90 - direction/PI*180 ;
		}else
		{
			angleY = 270 - direction/PI*180;
		}
		(*tWeapone)->setRotation3D(Vertex3F(-90,angleY,(*tWeapone)->rotationZ));
		if((*tWeapone)->forwardLeft == true&&(*tWeapone)->currX <= (*tWeapone)->targetPoint.x)
		{
			delWeaponVCT->push_back((*tWeapone));
			tWeapone = allWeaponVCT->erase(tWeapone);
			continue;
		}else if((*tWeapone)->forwardLeft == false&&(*tWeapone)->currX >= (*tWeapone)->targetPoint.x)
		{
			delWeaponVCT->push_back((*tWeapone));
			tWeapone = allWeaponVCT->erase(tWeapone);
			continue;
		}
		tWeapone++;
	}
	std::vector<Weapon*>::iterator delWeapone ;
	for(delWeapone = delWeaponVCT->begin();delWeapone != delWeaponVCT->end();)
	{
		destroyEnemyShip((*delWeapone));
		removeShipPlayEffect((*delWeapone)->getPosition());
		map->removeChild((*delWeapone),true);
		delWeapone = delWeaponVCT->erase(delWeapone);
	}
}
void GameLayer::destroyEnemyShip(Weapon* weapone)
{
	Point wp = weapone->getPosition();
	std::vector<WarShipObject*>::iterator eship ;
	for(eship = allShipVCT->begin();eship != allShipVCT->end();)
	{
		Point ep = (*eship)->getPosition();
		float dx = ep.x - wp.x;
		float dy = ep.y - wp.y;
		float dis = sqrt(dx*dx+dy*dy);
		if(((weapone->launchForm == 2)&&((*eship)->shipType == 1))
				||((weapone->launchForm == 1)&&((*eship)->shipType == 2)))
		{
			if(dis < ATTACKRANGE)
			{
				(*eship)->lifeValue = (*eship)->lifeValue - weapone->power;

				if((*eship)->lifeValue <= 0 && weapone->weaponFromShip->shipType == 1)
				{
					weapone->weaponFromShip->junxian += 1;
					if(weapone->weaponFromShip->junxian % 4 == 0)
					{
						if(weapone->weaponFromShip->junxian/4 <= 3)
						{
							int jxdj = weapone->weaponFromShip->junxian/4;
							weapone->weaponFromShip->removeChildByTag(JUNXIANSPTAG);
							std::string path = StringUtils::format("junx%d.png",jxdj);
							Sprite* junxianSp = Sprite::create(path.c_str());
							Size size = weapone->weaponFromShip->getContentSize();
							junxianSp->setPosition(Point(size.width,size.height));
							weapone->weaponFromShip->addChild(junxianSp,10,JUNXIANSPTAG);
						}
					}
				}
			}
		}
		eship++;
	}
}

//������ĵط�ΪС��������ʾX
void GameLayer::addWrongPrompt(Point locationMap)
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
										->playEffect("sound_sfx_error.mp3");
	}

	Sprite* wrongSp = Sprite::create("wrong.png");
	wrongSp->setPosition(locationMap);
	map->addChild(wrongSp,10);
	wrongSp->runAction(
			Sequence::create(
					Repeat::create(
							Sequence::create(
									ScaleTo::create(0.5,1.5),
									ScaleTo::create(0.5,0.5),
									NULL
							),
							2),
					Spawn::create(
							ScaleTo::create(0.5,0.1),
							FadeOut::create(0.5),
							NULL
					),
					RemoveSelf::create(true),
					NULL));
}
void GameLayer::playerHKMJCoolTimeUpdate()
{
	if(playerHKMJ->coolTimeBSJ != 100)
	{
		playerHKMJ->coolTimeBSJ = playerHKMJ->coolTimeBSJ +1;
	}else
	{
		playerHKMJ->coolTimeBSJ = 100;
		coolSpb = false;
		playerHKMJ->hkmjSprite->removeChild(coolSp[0],true);
	}
	if(coolSpb == true)
	{
		coolSp[0]->setTextureRect(Rect(0, 0, playerHKMJ->coolTimeBSJ/2, 37));
	}

	if(playerHKMJ->coolTimePlane != 100)
	{
		playerHKMJ->coolTimePlane = playerHKMJ->coolTimePlane +5;
	}else
	{
		playerHKMJ->coolTimePlane = 100;
		coolSpp = false;
		playerHKMJ->hkmjSprite->removeChild(coolSp[1],true);
	}
	if(coolSpp == true)
	{
		coolSp[1]->setTextureRect(Rect(0, 0, (playerHKMJ->coolTimePlane*0.9)/2, 37));
	}
}
void GameLayer::desAllEnemyShip()
{
	playerHKMJ->coolTimeBSJ = 0;
	Sprite* sp = Sprite::create();
	sp->setPosition(Point(1136/2,768/2));
	map->addChild(sp,1000);

	sp->runAction(
			Sequence::create(
					anmiAc[0],
					CallFunc::create(CC_CALLBACK_0(GameLayer::expansionRing,this)),
					RemoveSelf::create(true),
					NULL));

	playerHKMJ->hkmjSprite->removeChildByTag(HKMJITEMSPTAG);
	playerHKMJ->hkmjSprite->removeChildByTag(PLANEITEMSPTAG);

	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("yulei.png");
	coolSp[0] = Sprite::createWithTexture(texture);
	coolSp[0]->setTextureRect(Rect(0, 0, playerHKMJ->coolTimeBSJ/2, 37));
	coolSp[0]->setPosition(Point(40,-30));
	playerHKMJ->hkmjSprite->addChild(coolSp[0],20);

	coolSpb = true;					//��ʾ������ȴ��
	playerHKMJ->openMenu = false;	//��ʾ���ܷ�����
}
void GameLayer::planeFlyAtShip()
{
	playerHKMJ->coolTimePlane = 0;
	planeFlag = true;
	for(int i =0;i<2;i++)
	{
		plane3D[i] = Sprite3D::create("zdj3D.obj");
		plane3D[i]->setTexture("HE162R.jpg");
		plane3D[i]->setPosition(Point(1240,100+i*500));
		plane3D[i]->setScale(0.007f);
		plane3D[i]->setRotation3D(Vertex3F(90,0,90));
		map->addChild(plane3D[i],30);
	}
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
							->playEffect("flyby2.wav");
	}
	playerHKMJ->hkmjSprite->removeChildByTag(PLANEITEMSPTAG);
	playerHKMJ->hkmjSprite->removeChildByTag(HKMJITEMSPTAG);
	playerHKMJ->openMenu = false;
	coolSpp = true;

	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("planeMenu.png");
	coolSp[1] = Sprite::createWithTexture(texture);
	coolSp[1]->setTextureRect(Rect(0, 0, (playerHKMJ->coolTimePlane*0.9)/2, 47));
	coolSp[1]->setPosition(Point(40,-80));
	playerHKMJ->hkmjSprite->addChild(coolSp[1],20);
}
void GameLayer::planeUpdate()
{
	if(planeFlag == true)
	{
		switch(step)
		{
			case 1:
				plane3D[0]->setPosition(Point(plane3D[0]->getPosition().x-4,plane3D[0]->getPosition().y));
				plane3D[1]->setPosition(Point(plane3D[1]->getPosition().x-4,plane3D[1]->getPosition().y));
				if(plane3D[0]->getPosition().x<=200)
				{
					step = 2;
				}
			break;
			case 2:
					plane3D[0]->setPosition(Point(plane3D[0]->getPosition().x-4,plane3D[0]->getPosition().y + 4));
					plane3D[1]->setPosition(Point(plane3D[1]->getPosition().x-4,plane3D[1]->getPosition().y - 4));
					if(plane3D[0]->getPosition().x<=100&&plane3D[0]->getRotation3D().z>=180)
					{
						step = 3;
					}else
					{
						plane3D[0]->setRotation3D(Vertex3F(90,plane3D[0]->getRotation3D().y - 2,plane3D[0]->getRotation3D().z + 2 ));
						plane3D[1]->setRotation3D(Vertex3F(90,plane3D[1]->getRotation3D().y + 2,plane3D[1]->getRotation3D().z - 2 ));
					}
			break;
			case 3:
					plane3D[0]->setPosition(Point(plane3D[0]->getPosition().x+4,plane3D[0]->getPosition().y + 4));
					plane3D[1]->setPosition(Point(plane3D[1]->getPosition().x+4,plane3D[1]->getPosition().y - 4));
					if(plane3D[0]->getPosition().x>=200&&plane3D[0]->getRotation3D().z>=270)
					{
						step = 4;
					}else
					{
						plane3D[0]->setRotation3D(Vertex3F(90,plane3D[0]->getRotation3D().y + 2,plane3D[0]->getRotation3D().z + 2 ));
						plane3D[1]->setRotation3D(Vertex3F(90,plane3D[1]->getRotation3D().y - 2,plane3D[1]->getRotation3D().z - 2 ));
					}
			break;
			case 4:
				plane3D[0]->setPosition(Point(plane3D[0]->getPosition().x+4,plane3D[0]->getPosition().y));
				plane3D[1]->setPosition(Point(plane3D[1]->getPosition().x+4,plane3D[1]->getPosition().y));
			break;
		}
		std::vector<WarShipObject*>::iterator eship ;
		for(eship = allShipVCT->begin();eship != allShipVCT->end();)
		{
			if((*eship)->shipType == 2)
			{
				Point ePoint = (*eship)->getPosition();
				Point pPoint0 = plane3D[0]->getPosition();
				Point pPoint1 = plane3D[1]->getPosition();
				float dx0 = pPoint0.x-ePoint.x;
				float dy0 = pPoint0.y-ePoint.y;
				float dis0 = sqrt(dx0*dx0+dy0*dy0);

				float dx1 = pPoint1.x-ePoint.x;
				float dy1 = pPoint1.y-ePoint.y;
				float dis1 = sqrt(dx1*dx1+dy1*dy1);
				if(dis0 < R/2||dis1 < R/2)
				{
					(*eship)->lifeValue = 0;
				}
			}
			eship++;
		}
		if(plane3D[0]->getPosition().x>1500&&plane3D[1]->getPosition().x>1500)
		{
			planeFlag = false;
			step = 1;
			map->removeChild(plane3D[0],true);
			map->removeChild(plane3D[1],true);
		}
	}

}
bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	if(isGameOver == true)
	{
		return false;
	}
	TMXTiledMap* targetMap = static_cast<TMXTiledMap*>(	//��ȡ��ǰ�������󣬲�ת��Ϊ��������
								event->getCurrentTarget());
	firstTouchPoint = touch->getLocation();
	Point locationMap = targetMap->convertToNodeSpace(touch->getLocation());//��ȡ��ǰ����

	if(fabs(locationMap.x-1050)<= 25&&fabs(locationMap.y-270) <= 25)
	{
		playSound();
		if(playerHKMJ->openMenu == false)
		{
			if(playerHKMJ->coolTimeBSJ == 100)
			{
				playerHKMJ->openMenu = true;
				MenuItemImage* HKMJItem = MenuItemImage::create(
						"yulei.png",
						"yuleip.png",
						CC_CALLBACK_0(GameLayer::desAllEnemyShip, this));
				HKMJItem->setPosition(Point(40,-10));

				//����һ���˵�����
				Menu* menu = Menu::create(HKMJItem,NULL);
				//������λ��
				menu->setPosition(Point::ZERO);
				//������ӵ�������
				playerHKMJ->hkmjSprite->addChild(menu,20,HKMJITEMSPTAG);

				HKMJItem->runAction(MoveBy::create(0.3,Point(0,-20)));
			}
			if(playerHKMJ->coolTimePlane == 100)
			{
				playerHKMJ->openMenu = true;
				MenuItemImage* planeItem = MenuItemImage::create(
						"planeMenu.png",
						"planeMenup.png",
						CC_CALLBACK_0(GameLayer::planeFlyAtShip, this));
				planeItem->setPosition(Point(40,-10));

				//����һ���˵�����
				Menu* menu = Menu::create(planeItem,NULL);
				//������λ��
				menu->setPosition(Point::ZERO);
				//������ӵ�������
				playerHKMJ->hkmjSprite->addChild(menu,20,PLANEITEMSPTAG);

				planeItem->runAction(MoveBy::create(0.3,Point(0,-80)));
			}
		}else
		{
			playerHKMJ->hkmjSprite->removeChildByTag(PLANEITEMSPTAG);
			playerHKMJ->hkmjSprite->removeChildByTag(HKMJITEMSPTAG);
			playerHKMJ->openMenu = false;
		}
		return false;
	}

	Size mapSize = map->getContentSize();
	//��Ӵ�ֻ
	if(selectItem == true&& (selectIndex >=0&&selectIndex <=4))
	{//����ҷ���ֻ
		if(locationMap.y<40||locationMap.x>mapSize.width-40||locationMap.y>mapSize.height-40||locationMap.x<40)
		{
			addWrongPrompt(locationMap);
			return false;
		}
		//�鿴��ֻ�Ƿ�����ȴ��
		switch(selectIndex)
		{
		case 0:
			if(playerHKMJ->coolTime0 != 0)
			{
				selectIndex = -1;
				selectedSp->setVisible(false);
				selectItem = false;
				return false;
			}
			break;
		case 1:
			if(playerHKMJ->coolTime1 != 0)
			{
				selectIndex = -1;
				selectedSp->setVisible(false);
				selectItem = false;
				return false;
			}
			break;
		case 2:
			if(playerHKMJ->coolTime2 != 0)
			{
				selectIndex = -1;
				selectedSp->setVisible(false);
				selectItem = false;
				return false;
			}
			break;
		case 3:
			if(playerHKMJ->coolTime3 != 0)
			{
				selectIndex = -1;
				selectedSp->setVisible(false);
				selectItem = false;
				return false;
			}
			break;
		case 4:
			if(playerHKMJ->coolTime4 != 0)
			{
				selectIndex = -1;
				selectedSp->setVisible(false);
				selectItem = false;
				return false;
			}
			break;
		}
		addWarShip(targetMap->convertToNodeSpace(touch->getLocation()),selectIndex);
		selectIndex = -1;
		selectedSp->setVisible(false);
		selectItem = false;
	}else if(selectIndex == 5||selectIndex == 6 )
	{//�����ڵ�
		addWeapon(selectIndex-5,
				lastTouchSprite->getPosition(),
				targetMap->convertToNodeSpace(touch->getLocation()),
				lastTouchSprite,1
				);
		selectIndex = -2;
		selectedSp->setVisible(false);
		selectItem = false;
	}
	//������������ƶ�
	if(selectShip == true && selectIndex == -1)
	{
		Point tempPoint ;
		tempPoint = touchPointToRowCol(targetMap->convertToNodeSpace(touch->getLocation()));
		//ֹͣ��ǰ���ڽ��еĶ���
		lastTouchSprite->stopAllActions();
		//��ȡ��ǰ�����λ��
		Point shipCP = lastTouchSprite->getPosition();
		//��X,Y����ת��Ϊ���ӵ����к�
		Point shipRC = touchPointToRowCol(shipCP);
		lastTouchSprite->targetRow = (int)(shipRC.y - 1);
		lastTouchSprite->targetCol = (int)(shipRC.x - trans.x);
		//�жϵ���ĵط��Ƿ�����------�Ƿ�Ϊ��ͼ�еĵ���
		if(Map_DATA[(int)tempPoint.x][(int)tempPoint.y] == 1)
		{
			addWrongPrompt(locationMap);
			return false;
		}else
		{
			Sprite* MZSprite = Sprite::create("MZ.png");
			MZSprite->setPosition(targetMap->convertToNodeSpace(touch->getLocation()));
			map->addChild(MZSprite,10);

			MZSprite->runAction(
					Sequence::create(
							ScaleTo::create(0.5,1.2),
							ScaleTo::create(0.5,0.9),
							RemoveSelf::create(true),
							NULL)
			);
			if(ChooseLevelLayer::froMusicFlag == true)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()
												->playEffect("sound_sfx_destination.mp3");
			}
		}
		//Ŀ���
		int targetAll[1][2] =
		{
				{(int)tempPoint.y ,(int)tempPoint.x}
		};
		//����Ŀ���
		target = targetAll[0];
		//Ѱ��·��
		searchPath(lastTouchSprite);
		//���õ�ǰ�����Ŀ��������к�
		lastTouchSprite->targetRow = tempPoint.y;
		lastTouchSprite->targetCol = tempPoint.x;
		//������ѡ��״̬---------0Ϊ��ѡ��
		lastTouchSprite->state = 0;
		//��ʾ
		showWarShipItem(lastTouchSprite);
		//ɾ����ֻ���Ϲҵľ���
		lastTouchSprite->removeChildByTag(DWPTAG);
		lastTouchSprite->removeChildByTag(DWSPRITETAG);
		lastTouchSprite->removeChildByTag(COMPASSSPRITE);
		lastTouchSprite->removeChildByTag(BQSPRITETAG);
		lastTouchSprite = NULL;
		//����ѡ��״̬Ϊδѡ�д�ֻ
		selectShip = false;
		//��ʾ��ֻ��ȴ����
		for(int k = 0;k<5;k++)
		{
			ShipCoolSprite[k]->setVisible(true);
		}
		currTouchSprite = NULL;
		return false;
	}
	//�ж��Ƿ�����ͼ
	Size sizeMap = targetMap->getContentSize();			//��ȡ����Ĵ�С
	Rect rectMap = Rect(0,0,sizeMap.width, sizeMap.height);//����һ�����ζ������С�뾫����ͬ
	if(rectMap.containsPoint(locationMap))
	{
		return true;
	}else
	{
		return false;
	}
}
void GameLayer::onTouchMoved(Touch* touch, Event* event)
{
	//�ƶ���ͼ
	float deltaX = touch->getLocation().x-firstTouchPoint.x;
	float pointX = mapPoint.x+deltaX;

	float deltaY = touch->getLocation().y-firstTouchPoint.y;
	float pointY = mapPoint.y+deltaY;

	if(pointX>=960&&pointX<=1136)
	{
		map->setPosition(pointX,map->getPosition().y);
	}
	if(pointY <=0&&pointY >=-228)
	{
		map->setPosition(map->getPosition().x,pointY);
	}
}
void GameLayer::onTouchEnded(Touch* touch, Event* event)
{
	mapPoint = map->getPosition();
}
//���һ���д�
void GameLayer::addEnemyShip()
{
	//����һ��1-8�������
	srand((unsigned)time(NULL));
	for(int i=0;i<10;i++)
	{
		int index = rand()%(waveNum*2)+1;
		int pointY = 20+(rand()%500+1);
		int tempY = pointY/16*16;
		WarShipObject* enemyShip = WarShipObject::create(
				StringUtils::format("E%d.png",index),
				Point(16,tempY),
				index,2);

		enemyShip->isMoved = true;
		//���õд���Ѫ��
		enemyShip->lifeValue = waveNum*100+index*50;
		map->addChild(enemyShip,10+i);
		//����ֻ���ڴ����д�ֻ������
		allShipVCT->push_back(enemyShip);
		randomSort();
		for(int i = 0;i<8;i++)
		{
			for(int j = 0;j<2;j++)
			{
				enemyShip->sequence[i][j] = resultSequence[i][j];
			}
		}
		int row;
		int col;
		if(i <5)
		{
			row = 25;
			col = 63+i;
		}else
		{
			row = 35;
			col = 63+i-5;
		}
		enemyShip->enemyShipTargetRow = row;
		enemyShip->enemyShipTargetCol = col;
		int targetAll[1][2] =
		{
				{row,col}
		};
		target = targetAll[0];
		searchPath(enemyShip);
		enemyShip->isMoved = true;
	}
}
void GameLayer::removeShipPlayEffect(Point tempP)
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
								->playEffect("sound_sfx_nuclear.mp3");
	}

	Sprite* sp = Sprite::create();
	sp->setPosition(tempP);
	map->addChild(sp ,100);
	sp->runAction(
			Sequence::create(
					anmiAc[1]->clone(),
					RemoveSelf::create(true),
					NULL
			));
}
void GameLayer::removeShipUpdate()
{
	std::vector<WarShipObject*>::iterator allShip ;
	for(allShip =allShipVCT->begin();allShip!= allShipVCT->end();)
	{
		if((*allShip)->lifeValue <= 0)
		{
			if((*allShip)->shipType == 2)
			{
				if(ChooseLevelLayer::froMusicFlag == true)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()
												->playEffect("sound_sfx_break.mp3");
				}

				enemyShipCount = enemyShipCount - 1;
				sdsNum ++;
				std::string sdsString = StringUtils::format("%d",sdsNum);
				sdsLabel->setString(sdsString);

				currLevelSds ++;

				myGold = myGold + ((*allShip)->shipNum+1)*30;
				std::string smyGold = StringUtils::format("%d",myGold);
				moneyLabel->setString(smyGold);

				if(enemyShipCount == 0)
				{

					if(waveNum <= 5)
					{
						gameStartDJS();
					}else
					{
						gameResult = true;
						isGameOver = true;
						gameOver();
					}
				}
			}
			delShipVCT->push_back((*allShip));
			allShip = allShipVCT->erase(allShip);
			continue;
		}
		allShip++;
	}
	std::vector<WarShipObject*>::iterator adelShip ;
	for(adelShip =delShipVCT->begin();adelShip!= delShipVCT->end();)
	{
		removeShipPlayEffect((*adelShip)->getPosition());
		map->removeChild((*adelShip),true);
		adelShip = delShipVCT->erase(adelShip);
	}
}
//��ʼ����ĸ
void GameLayer::initHKMJ()
{
	playerHKMJ = new HKMJObject(1050,270);
	map->addChild(playerHKMJ->hkmjSprite,30);

	ParticleSystemQuad* psqOne = ParticleSystemQuad::create("tji.plist");//���ļ��м�������ϵͳ
	psqOne->setPositionType(ParticleSystem::PositionType::RELATIVE);
	psqOne->retain();								//��������
	psqOne->setBlendAdditive(true);				//���û�Ϸ�ʽΪ����
	psqOne->setScale(0.5);
	psqOne->setPosition(Point(37,35));
	playerHKMJ->hkmjSprite->addChild(psqOne, 3);		//�򲼾����еľ����������ϵͳ
	psqOne->runAction(
			RepeatForever::create(
					RotateBy::create(0.2,-30)
				));
	ParticleSystemQuad* psqTwo = ParticleSystemQuad::create("tji.plist");//���ļ��м�������ϵͳ
	psqTwo->setPositionType(ParticleSystem::PositionType::RELATIVE);
	psqTwo->retain();								//��������
	psqTwo->setBlendAdditive(true);				//���û�Ϸ�ʽΪ����
	psqTwo->setScale(0.5);
	psqTwo->setRotation(180);
	psqTwo->setPosition(Point(37,35));
	playerHKMJ->hkmjSprite->addChild(psqTwo, 3);		//�򲼾����еľ����������ϵͳ
	psqTwo->runAction(
				RepeatForever::create(
						RotateBy::create(0.2,-30)
					));

	int tempi = 0;
	for(int i =0;i<20;i++)
	{
		if(i%2==0)
		{
			lifeBarSp[i] = Sprite::create("lifeBarY.png");
			lifeBarSp[i]->setPosition(Point(0+tempi*8,100));
			playerHKMJ->hkmjSprite->addChild(lifeBarSp[i],0);
		}else if(i%2==1)
		{
			lifeBarSp[i] = Sprite::create("lifeBarG.png");
			lifeBarSp[i]->setPosition(Point(0+tempi*8,100));
			playerHKMJ->hkmjSprite->addChild(lifeBarSp[i],1);
			tempi ++;
		}
	}
}
//��ʼ������ѡ��
void GameLayer::initJJItem()
{
	jjbgSp[0] = MenuItemImage::create(
			"jjbg.png",
			"jjbg.png",
			CC_CALLBACK_0(GameLayer::jjbgSpCallback0, this)
	);
	jjbgSp[0]->setPosition(Point(55+0*100,50));

	jjbgSp[1] = MenuItemImage::create(
			"jjbg.png",
			"jjbg.png",
			CC_CALLBACK_0(GameLayer::jjbgSpCallback1, this)
	);
	jjbgSp[1]->setPosition(Point(55+1*100,50));

	jjbgSp[2] = MenuItemImage::create(
			"jjbg.png",
			"jjbg.png",
			CC_CALLBACK_0(GameLayer::jjbgSpCallback2, this)
	);
	jjbgSp[2]->setPosition(Point(55+2*100,50));

	jjbgSp[3] = MenuItemImage::create(
			"jjbg.png",
			"jjbg.png",
			CC_CALLBACK_0(GameLayer::jjbgSpCallback3, this)
	);
	jjbgSp[3]->setPosition(Point(55+3*100,50));

	jjbgSp[4] = MenuItemImage::create(
			"jjbg.png",
			"jjbg.png",
			CC_CALLBACK_0(GameLayer::jjbgSpCallback4, this)
	);
	jjbgSp[4]->setPosition(Point(55+4*100,50));

	shipWeapon [0] = MenuItemImage::create(
				"jjbg.png",
				"jjbg.png",
				CC_CALLBACK_0(GameLayer::shipWeaponCallback0, this)
		);
	shipWeapon [0]->setPosition(Point(55+0*100,50));
	shipWeapon [0]->setVisible(false);

	shipWeapon [1] = MenuItemImage::create(
				"jjbg.png",
				"jjbg.png",
				CC_CALLBACK_0(GameLayer::shipWeaponCallback1, this)
		);
	shipWeapon [1]->setPosition(Point(55+1*100,50));
	shipWeapon [1]->setVisible(false);

	shipWeapon [2] = MenuItemImage::create(
				"cancleg.png",
				"cancleg.png",
				CC_CALLBACK_0(GameLayer::shipWeaponCallback2, this)
		);
	shipWeapon [2]->setPosition(Point(85+8*100,65));
	shipWeapon [2]->setVisible(false);

	//����һ���˵�����
	Menu* menu = Menu::create(
			jjbgSp[0],jjbgSp[1],jjbgSp[2],
			jjbgSp[3],jjbgSp[4],shipWeapon [0],
			shipWeapon [1],shipWeapon [2],NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	this->addChild(menu, 2);

	//��ʼ������
	for(int i =0 ;i<2;i++)
	{
		Sprite* itemSp = Sprite::create(StringUtils::format("wq%d.png",i));
		itemSp->setPosition(Point(45,52));
		shipWeapon[i]->addChild(itemSp,2);
	}

	for(int i =0 ;i<5;i++)
	{
		Sprite* jjSp = Sprite::create(StringUtils::format("jj%d.png",i));
		jjSp->setPosition(Point(45,52));
		jjbgSp[i]->addChild(jjSp,2);
		Sprite* jinbiSp = Sprite::create("jinbi.png");
		jinbiSp->setPosition(Point(20,15));
		jjbgSp[i]->addChild(jinbiSp,2);
		Label* jjPriceLable = Label::createWithTTF(
				StringUtils::format("%d",(i+1)*400),"FZKATJW.ttf",20
		);
		jjPriceLable->setPosition(Point(60,15));
		jjbgSp[i]->addChild(jjPriceLable,2);
	}

	Label* jjName0 = Label::createWithTTF(
			"\u767b\u9646\u8247","FZKATJW.ttf",15
	);
	jjName0->setAnchorPoint(Point(0,0.5));
	jjName0->setPosition(Point(20,95));
	jjbgSp[0]->addChild(jjName0,2);

	Label* jjName1 = Label::createWithTTF(
			"\u96f7\u9706\u8230","FZKATJW.ttf",15
	);
	jjName1->setAnchorPoint(Point(0,0.5));
	jjName1->setPosition(Point(20,95));
	jjbgSp[1]->addChild(jjName1,2);

	Label* jjName2 = Label::createWithTTF(
			"\u6218\u795e\u8230","FZKATJW.ttf",15
	);
	jjName2->setAnchorPoint(Point(0,0.5));
	jjName2->setPosition(Point(20,95));
	jjbgSp[2]->addChild(jjName2,2);

	Label* jjName3 = Label::createWithTTF(
			"\u731b\u79bd\u8230","FZKATJW.ttf",15
	);
	jjName3->setAnchorPoint(Point(0,0.5));
	jjName3->setPosition(Point(20,95));
	jjbgSp[3]->addChild(jjName3,2);

	Label* jjName4 = Label::createWithTTF(
			"\u96f7\u795e\u822a\u6bcd","FZKATJW.ttf",15
	);
	jjName4->setAnchorPoint(Point(0,0.5));
	jjName4->setPosition(Point(20,95));
	jjbgSp[4]->addChild(jjName4,12);

	 selectedSp = Sprite::create("selected.png");
	 selectedSp->setVisible(false);
	 this->addChild(selectedSp,2);
}
//����0�Ļص�����
void GameLayer::shipWeaponCallback0()
{
	playSound();

	if(selectItem == true&&selectIndex == 5)
	{
		lastTouchSprite->removeChildByTag(DWPTAG);
		addSaveSprite(lastTouchSprite);
		selectItem = false;
		selectIndex = -1;
		selectedSp->setVisible(false);
	}else
	{
		selectedSp->setVisible(true);
		selectedSp->setPosition(shipWeapon[0]->getPosition());
		selectIndex = 5;
        lastTouchSprite->removeChildByTag(DWPTAG);
        lastTouchSprite->removeChildByTag(DWSPRITETAG);
		addAimSprite();
		selectItem = true;
	}
}
//����1�Ļص�����
void GameLayer::shipWeaponCallback1()
{
	playSound();

	if(selectItem == true&&selectIndex == 6)
	{
		lastTouchSprite->removeChildByTag(DWPTAG);
		addSaveSprite(lastTouchSprite);
		selectItem = false;
		selectIndex = -1;
		selectedSp->setVisible(false);
	}else
	{
		selectedSp->setVisible(true);
		selectedSp->setPosition(shipWeapon[1]->getPosition());
		selectIndex = 6;
		lastTouchSprite->removeChildByTag(DWPTAG);
		lastTouchSprite->removeChildByTag(DWSPRITETAG);
		addAimSprite();
		selectItem = true;
	}
}
//�����ĵ���׼��
void GameLayer::addAimSprite()
{
	Sprite* dwp = Sprite::create("dwp.png");
	lastTouchSprite->removeChildByTag(DWSPRITETAG);
	Size size = lastTouchSprite->getContentSize();
	dwp->setPosition(size.width/2,size.height/2);
	lastTouchSprite->addChild(dwp,-1,DWPTAG);
	dwp->runAction(RepeatForever::create(RotateBy::create(4,360)));
}
//����СȦ
void GameLayer::addSaveSprite(WarShipObject* wsoSprite)
{
	Size size = wsoSprite->getContentSize();
	Sprite* DWSprite = Sprite::create("dw.png");
	DWSprite->setPosition(Point(size.width/2,size.height/2));
	wsoSprite->addChild(DWSprite,-1,DWSPRITETAG);
	DWSprite->runAction(RepeatForever::create(RotateBy::create(4,360)));
}
//ȡ���˵���Ļص�����
void GameLayer::shipWeaponCallback2()
{
	playSound();

	lastTouchSprite->state = 0;
	showWarShipItem(lastTouchSprite);
	lastTouchSprite->removeChildByTag(DWPTAG);
	lastTouchSprite->removeChildByTag(DWSPRITETAG);
	lastTouchSprite->removeChildByTag(COMPASSSPRITE);
	lastTouchSprite->removeChildByTag(BQSPRITETAG);
	selectShip = false;
	selectItem = false;
	selectedSp->setVisible(false);
	selectIndex = -1;
	currTouchSprite = NULL;
	lastTouchSprite = NULL;
	for(int k = 0;k<5;k++)
	{
		ShipCoolSprite[k]->setVisible(true);
	}
}
//�������0�Ļص�����
void GameLayer::jjbgSpCallback0()
{
	playSound();

	if(selectItem == true&&selectIndex == 0)
	{
		selectItem = false;
		selectIndex = -1;
		selectedSp->setVisible(false);
	}else
	{
		selectedSp->setVisible(true);
		selectedSp->setPosition(jjbgSp[0]->getPosition());
		selectIndex = 0;
		selectItem = true;
	}
}
//�������1�Ļص�����
void GameLayer::jjbgSpCallback1()
{
	playSound();

	if(selectItem == true&&selectIndex == 1)
	{
		selectItem = false;
		selectIndex = -1;
		selectedSp->setVisible(false);
	}else
	{
		selectedSp->setVisible(true);
		selectedSp->setPosition(jjbgSp[1]->getPosition());
		selectIndex = 1;
		selectItem = true;
	}
}
//�������2�Ļص�����
void GameLayer::jjbgSpCallback2()
{
	playSound();

	if(selectItem == true&&selectIndex == 2)
	{
		selectItem = false;
		selectIndex = -1;
		selectedSp->setVisible(false);
	}else
	{
		selectedSp->setVisible(true);
		selectedSp->setPosition(jjbgSp[2]->getPosition());
		selectIndex = 2;
		selectItem = true;
	}
}
//�������3�Ļص�����
void GameLayer::jjbgSpCallback3()
{
	playSound();
	if(selectItem == true&&selectIndex == 3)
	{
		selectItem = false;
		selectIndex = -1;
		selectedSp->setVisible(false);
	}else
	{
		selectedSp->setVisible(true);
		selectedSp->setPosition(jjbgSp[3]->getPosition());
		selectIndex = 3;
		selectItem = true;
	}
}
//�������4�Ļص�����
void GameLayer::jjbgSpCallback4()
{
	playSound();

	if(selectItem == true&&selectIndex == 4)
	{
		selectItem = false;
		selectIndex = -1;
		selectedSp->setVisible(false);
	}else
	{
		selectedSp->setVisible(true);
		selectedSp->setPosition(jjbgSp[4]->getPosition());
		selectIndex = 4;
		selectItem = true;
	}
}
//�����ļ����ӷ���
void GameLayer::calNearestSmartIn()
{
	std::vector<WarShipObject*>* enemyShipVCT =new std::vector<WarShipObject*>();	//���о���
	std::vector<WarShipObject*>* playerShipVCT =new std::vector<WarShipObject*>();

	std::vector<WarShipObject*>::iterator distemp ;
	for(distemp = allShipVCT->begin();distemp != allShipVCT->end();distemp++)
	{
		//����Ϊ�д�
		if((*distemp)->shipType == 2)
		{
			enemyShipVCT->push_back((*distemp));
		}else
		{
			playerShipVCT->push_back((*distemp));
		}
	}
	std::vector<WarShipObject*>::iterator enemytemp ;
	for(enemytemp = enemyShipVCT->begin();enemytemp != enemyShipVCT->end();enemytemp++)
	{
		if((*enemytemp)->lifeValue <= 0)
		{
			continue;
		}
		int countTT = 0;
		std::vector<WarShipObject*>::iterator playertemp ;
		for(playertemp = playerShipVCT->begin();playertemp != playerShipVCT->end();playertemp++)
		{
			if((*playertemp)->lifeValue <= 0)
			{
				continue;
			}
			float distance = dis((*playertemp),(*enemytemp));
			if(distance < R)
			{
				countTT = 1;
				if((*enemytemp)->isMoved == true)
				{
					(*enemytemp)->stopAllActions();	//ֹͣ�д��˶�
					(*enemytemp)->isMoved = false;	//��־�д����ɶ�
				}
				Point myTempPoint = (*playertemp)->getPosition();
				Point eTempPoint = (*enemytemp)->getPosition();
				addWeapon(0,eTempPoint,myTempPoint,(*enemytemp),2);

				if((*playertemp)->shipNum == 3||(*playertemp)->shipNum == 4)
				{
					Sprite* bulletSp = Sprite::create("weapon2.png");
					bulletSp->setPosition(myTempPoint);
					map->addChild(bulletSp,15);

					if(ChooseLevelLayer::froMusicFlag == true)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()
											->playEffect("sound_sfx_explode_general.mp3");
					}
					bulletSp->runAction(
						Sequence::create(
								MoveTo::create(0.1,eTempPoint),
								RemoveSelf::create(true),
								NULL
							));
						//����ֵ����
						(*enemytemp)->lifeValue = (*enemytemp)->lifeValue - (*playertemp)->attackPower;
				}
				//����
				if((*enemytemp)->lifeValue <= 0)
				{
					if((*enemytemp)->isDie == false)
					{
						(*playertemp)->junxian ++;
						if((*playertemp)->junxian % 4 == 0)
						{
							if((*playertemp)->junxian/4 <= 3)
							{
								Sprite* junxianSp ;
								if((*playertemp)->junxian/4 == 1)
								{
									if(ChooseLevelLayer::froMusicFlag == true)
									{
										CocosDenshion::SimpleAudioEngine::getInstance()
														->playEffect("sound_sfx_star_1.mp3");
									}

									junxianSp = Sprite::create("junx1.png");
								}else
								{
									if(ChooseLevelLayer::froMusicFlag == true)
									{
										std::string musicPath = StringUtils::format("sound_sfx_star_%d.mp3",(*playertemp)->junxian/4);
										CocosDenshion::SimpleAudioEngine::getInstance()
															->playEffect(musicPath.c_str());
									}

									(*playertemp)->removeChildByTag(JUNXIANSPTAG);
									std::string path = StringUtils::format("junx%d.png",(*playertemp)->junxian/4);
									junxianSp = Sprite::create(path.c_str());
								}
								Size size = (*playertemp)->getContentSize();
								junxianSp->setPosition(Point(size.width,size.height));
								(*playertemp)->addChild(junxianSp,10,JUNXIANSPTAG);
							}
							(*playertemp)->attackPower = (*playertemp)->attackPower + 50;
						}
					}
					(*enemytemp)->isDie = true;
				}
			}
		}
		if(countTT == 0)
		{
			//�����ڴ����Χ������ǰ�з�����Ϊֹͣ����״̬���� ��������·������Ŀ��ص�
			if((*enemytemp)->isMoved == false)
			{
				(*enemytemp)->isMoved = true;
				Point eTempPoint = (*enemytemp)->getPosition();
				Point RC = touchPointToRowCol(eTempPoint);
				(*enemytemp)->initRow = (int)RC.y;
				(*enemytemp)->initCol = (int)RC.x;
				int targetAll[1][2] =
				{
						(*enemytemp)->enemyShipTargetRow,(*enemytemp)->enemyShipTargetCol
				};
				target = targetAll[0];
				searchPath((*enemytemp));
			}
		}
	}
}
//�������������ķ���
float GameLayer::dis(WarShipObject* d1,WarShipObject* d2)
{
	float a=d1->getPosition().x-d2->getPosition().x;
	float b=d1->getPosition().y-d2->getPosition().y;
	return sqrt(a*a+b*b);
}
void GameLayer::enemyShipAtHKMJUpdate()
{
	std::vector<WarShipObject*>::iterator tempEnemy;
	for(tempEnemy = allShipVCT->begin();tempEnemy != allShipVCT->end();tempEnemy++)
	{
		if(isGameOver == true)
		{
			return;
		}
		if((*tempEnemy)->shipType == 2)
		{
			Point pEnemyPoint = (*tempEnemy)->getPosition();
			Point pHMPoint = playerHKMJ->hkmjSprite->getPosition();
			float dis = sqrt((pEnemyPoint.x-pHMPoint.x)*(pEnemyPoint.x-pHMPoint.x)
										+(pEnemyPoint.y-pHMPoint.y)*(pEnemyPoint.y-pHMPoint.y));
			if(dis <= R)
			{
				if(isGameOver == true)
				{
					return;
				}
				bool b = addWeapon(0,pEnemyPoint,pHMPoint,(*tempEnemy),2);
				if(b == true&&isGameOver == false)
				{
					(*tempEnemy)->runAction(
							Sequence::createWithTwoActions(
									DelayTime::create(1.5f),
									CallFunc::create(CC_CALLBACK_0(GameLayer::reduceBlood,this))
									)
					);
				}
			}
		}
	}
}
void GameLayer::RecoveryStateCallback()
{
	auto director = Director::getInstance();
	Scheduler* sched = director->getScheduler();
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::calNearestSmartIn),this,0.1,false);
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::weaponsCoolTimeUpdate),this,0.1,false);
	isGameOver = false;
}
void GameLayer::reduceBlood()
{
	playerHKMJ->lifeValue =playerHKMJ->lifeValue - 1;
	if(playerHKMJ->lifeValue >=0)
	{
		lifeBarSp[playerHKMJ->lifeValue]->runAction(RemoveSelf::create(true));
	}
	if(playerHKMJ->lifeValue ==10&&playerHKMJ->qhFlag == false)
	{
		playerHKMJ->qhFlag = true;
		//ֹͣ��ȴʱ��ص�
		this->unschedule(SEL_SCHEDULE(&GameLayer::weaponsCoolTimeUpdate));
		//ֹͣѰ���ص�
		this->unschedule(SEL_SCHEDULE(&GameLayer::calNearestSmartIn));
		isGameOver = true;
		std::vector<WarShipObject*>::iterator allShipTemp ;
		for(allShipTemp =allShipVCT->begin();allShipTemp!= allShipVCT->end();)
		{
			//ֹͣ���ô�ֻ�Ķ���
			(*allShipTemp)->stopAllActions();
			(*allShipTemp)->isMoved = false;
			allShipTemp++;
		}

		Point wolrdMapPoint = map->getPosition();
		map->runAction(
				Sequence::create(
						MoveTo::create(1,Point(960,0)),
						DelayTime::create(1.5),
						MoveTo::create(1,wolrdMapPoint),
						CallFunc::create(CC_CALLBACK_0(GameLayer::RecoveryStateCallback,this)),
						NULL
				));

		ParticleSystemQuad* psq = ParticleSystemQuad::create("huoyan.plist");//���ļ��м�������ϵͳ
		psq->setPositionType(ParticleSystem::PositionType::RELATIVE);
		psq->retain();								//��������
		psq->setBlendAdditive(true);				//���û�Ϸ�ʽΪ����
		psq->setScale(0.4);
		psq->setPosition(Point(48,45));
		playerHKMJ->hkmjSprite->addChild(psq, 3);		//�򲼾����еľ����������ϵͳ
	}
	if(playerHKMJ->lifeValue == 0)
	{
		map->runAction(MoveTo::create(1,Point(960,0)));
		gameResult = false;
		isGameOver = true;
		removeShipPlayEffect(playerHKMJ->hkmjSprite->getPosition());
		map->removeChild(playerHKMJ->hkmjSprite);
		gameOver();
	}
}
void GameLayer::gameOver()
{
	this->unschedule(SEL_SCHEDULE(&GameLayer::playerHKMJCoolTimeUpdate));
	puaseMenu->setEnabled(false);
	UserDefault::getInstance()->setIntegerForKey(Constant::SHADISHU.c_str(),sdsNum);

	for(int i=0;i<5;i++)
	{
		jjbgSp[i]->setEnabled(false);
	}
	setTouchEnabled(false);

	std::string menuPathO ;
	std::string menuPathT ;
	Sprite* gameOverttSp;
	Sprite* gameOverbbSp;
	if(gameResult == false)
	{
		gameOverttSp = Sprite::create("titlesb.png");
		gameOverttSp->setPosition(Point(480,430));
		this->addChild(gameOverttSp,12);
		menuPathO = "cxks.png";
		menuPathT = "cxksp.png";

		gameOverbbSp = Sprite::create("bbq.png");
		gameOverbbSp->setAnchorPoint(Point(0,1));
		gameOverbbSp->setPosition(Point(0,0));
		gameOverttSp->addChild(gameOverbbSp,9);

		int index = rand()%4;
		Sprite* gameOvertsSp = Sprite::create(StringUtils::format("ts%d.png",index));
		gameOvertsSp->setPosition(Point(170,260));
		gameOverbbSp->addChild(gameOvertsSp,5);

		int temp = UserDefault::getInstance()->getIntegerForKey(Constant::LOSECOUNT.c_str());
		UserDefault::getInstance()->setIntegerForKey(Constant::LOSECOUNT.c_str(),temp+1);
	}else if(gameResult == true)
	{
		int tempMoney = UserDefault::getInstance()->getIntegerForKey(Constant::COUNTGOLD.c_str());
		UserDefault::getInstance()->setIntegerForKey(Constant::COUNTGOLD.c_str(),myGold+tempMoney);

		//��¼�ܽ�Ǯ
		int zqs = UserDefault::getInstance()->getIntegerForKey(Constant::GETGOLDCOUNT.c_str());
		UserDefault::getInstance()->setIntegerForKey(Constant::GETGOLDCOUNT.c_str(),zqs+myGold);
		//������Ϸ
		int number = UserDefault::getInstance()->getIntegerForKey(Constant::LEVELNUM.c_str());

		if(ChooseLevelLayer::levelNum == number && ChooseLevelLayer::levelNum < 4)
		{
			UserDefault::getInstance()->setIntegerForKey(Constant::LEVELNUM.c_str(),ChooseLevelLayer::levelNum+1);
		}

		if(currLevelSds >= 50)
		{
			std::string ss = StringUtils::format("LEVEL%d",ChooseLevelLayer::levelNum);
			UserDefault::getInstance()->setIntegerForKey(ss.c_str(),11);
		}else if(currLevelSds >= 25)
		{
			std::string ss = StringUtils::format("LEVEL%d",ChooseLevelLayer::levelNum);
			UserDefault::getInstance()->setIntegerForKey(ss.c_str(),1);
		}else
		{
			std::string ss = StringUtils::format("LEVEL%d",ChooseLevelLayer::levelNum);
			UserDefault::getInstance()->setIntegerForKey(ss.c_str(),0);
		}

		int temp = UserDefault::getInstance()->getIntegerForKey(Constant::WINCOUNT.c_str());
		UserDefault::getInstance()->setIntegerForKey(Constant::WINCOUNT.c_str(),temp+1);

		gameOverttSp = Sprite::create("titlesl.png");
		gameOverttSp->setPosition(Point(480,430));
		this->addChild(gameOverttSp,12);
		menuPathO = "jx.png";
		menuPathT = "jxp.png";

		gameOverbbSp = Sprite::create("bbq.png");
		gameOverbbSp->setAnchorPoint(Point(0,1));
		gameOverbbSp->setPosition(Point(0,0));
		gameOverttSp->addChild(gameOverbbSp,9);

		int starnum = playerHKMJ->lifeValue / 8 + 1;

		int divideLine = gameOverbbSp->getContentSize().width / (starnum+1);
		if(ChooseLevelLayer::froMusicFlag == true)
		{
			std::string musicPath = StringUtils::format("sound_sfx_star_%d.mp3",starnum);

			CocosDenshion::SimpleAudioEngine::getInstance()		//��ʹ��Ч
										->playEffect(musicPath.c_str());
		}

		for(int i=0;i<starnum;i++)
		{
			Sprite* gameOvertrSp = Sprite::create("star.png");
			gameOvertrSp->setPosition(Point(divideLine+i*divideLine-30*(1-i),260));
			gameOvertrSp->setScale(2.0f);
			gameOverbbSp->addChild(gameOvertrSp,5);

			gameOvertrSp->runAction(
					Spawn::create(
							MoveTo::create(1.0f,Point(divideLine+i*divideLine,260)),
							ScaleTo::create(1.0f,1),
							NULL)
			);
		}
	}

	MenuItemImage* restartItem = MenuItemImage::create(
			menuPathO,
			menuPathT,
			CC_CALLBACK_0(GameLayer::restartCallback, this)
	);
	restartItem->setPosition(Point(80,100));

	MenuItemImage* tcItem = MenuItemImage::create(
			"tc.png",
			"tcp.png",
			CC_CALLBACK_0(GameLayer::tcCallback, this)
	);
	tcItem->setPosition(Point(260,95));

	//����һ���˵�����
	Menu* menu = Menu::create(restartItem,tcItem,NULL);
	//������λ��
	menu->setPosition(Point::ZERO);
	//������ӵ�������
	gameOverbbSp->addChild(menu, 2);
}
//���¿�ʼ�ص�
void GameLayer::restartCallback()
{
	playSound();
	isGameOver = false;
	if(gameResult == false)//���¿�ʼ��Ϸ
	{
		Director::getInstance()->resume();
		this->removeAllChildren();
		selectIndex = -1;
		selectItem = false;
		waveNum = 1;
		enemyShipCount = 10;
		isGameOver = false;
		myGold = 3000;
		init();
	}else if(gameResult == true)
	{
		Director::getInstance()->resume();
		wfsm->goChooseLevelScene();
	}
}
void GameLayer::tcCallback()
{
	playSound();
	 Director::getInstance()->resume();
	//�������˵�
	wfsm->goStartScene();
}
//��ˮ�ƶ�
void GameLayer::oceanUpdate()
{
	if(oceanbg1Sp[0]->getPosition().x >=1704)
	{
		oceanbg1Sp[0]->setPosition(Point(-567,384));
	}else
	{
		oceanbg1Sp[0]->setPosition(Point(oceanbg1Sp[0]->getPosition().x+1,384));
	}

	if(oceanbg1Sp[1]->getPosition().x >=1704)
	{
		oceanbg1Sp[1]->setPosition(Point(-567,384));
	}else
	{
		oceanbg1Sp[1]->setPosition(Point(oceanbg1Sp[1]->getPosition().x+1,384));
	}
}
void GameLayer::playSound()
{
	if(ChooseLevelLayer::froMusicFlag == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()
								->playEffect("sound_sfx_click.mp3");
	}
}
