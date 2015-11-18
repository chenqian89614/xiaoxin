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
    
	//创建一些列向量
	allWeaponVCT = new std::vector<Weapon*>();
	delWeaponVCT = new std::vector<Weapon*>();

	allShipVCT =new std::vector<WarShipObject*>();	//所有军舰
	delShipVCT =new std::vector<WarShipObject*>();

	path = new std::vector<Point>();
	tempPath = new std::vector<Point>();
	//初始化地图中的
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
		CocosDenshion::SimpleAudioEngine::getInstance()//播放背景音乐
								->playBackgroundMusic("sound_bgm_battlefield.mp3");
	}
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("coolpic.png");
	//添加武器冷却的精灵
	for(int i = 0;i<2;i++)
	{
		weaponeSprite[i] = Sprite::createWithTexture(texture1);
		weaponeSprite[i]->setTextureRect(Rect(0, 0, 90, 0));
		weaponeSprite[i]->setAnchorPoint(Point(0.5,1));
		weaponeSprite[i]->setPosition(Point(55+i*100,105));
		this->addChild(weaponeSprite[i],100);
	}
	//添加船只冷却时间的精灵
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
	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouch->setSwallowTouches(false);
	//开始触摸时回调onTouchBegan方法
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	//开始触摸时回调onTouchMoved方法
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch,map);

	//定时回调
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
		psq = ParticleSystemQuad::create("snow.plist");//从文件中加载粒子系统

	}else if(ChooseLevelLayer::levelNum == 2)
	{
		psq = ParticleSystemQuad::create("raining.plist");//从文件中加载粒子系统

	}else if(ChooseLevelLayer::levelNum == 3)
	{
		psq = ParticleSystemQuad::create("snow.plist");//从文件中加载粒子系统

	}else if(ChooseLevelLayer::levelNum == 4)
	{
		psq = ParticleSystemQuad::create("raining.plist");//从文件中加载粒子系统

	}
	psq->retain();								//保持引用
	psq->setBlendAdditive(true);					//设置混合方式为增加
	psq->setPosition(Point(480,270));
	this->addChild(psq, 10);		//向布景层中的精灵添加粒子系统
}

void GameLayer::initMiscellaneous()
{
	Sprite* moneySp = Sprite::create("money.png");
	moneySp->setPosition(Point(940,520));
	this->addChild(moneySp,ITEM);

	Sprite* sdsSp = Sprite::create("sds.png");
	sdsSp->setPosition(Point(940,490));
	this->addChild(sdsSp,ITEM);

	moneyLabel = LabelAtlas::create(				//创建一个LabelAtlas对象
								 "3000","labelatlas.png",15,19,'0');
	moneyLabel->setAnchorPoint(Point(1,0.5));
	moneyLabel->setPosition(Point(moneySp->getPosition().x-20,moneySp->getPosition().y));
	this->addChild(moneyLabel,ITEM);

	sdsNum = UserDefault::getInstance()->getIntegerForKey(Constant::SHADISHU.c_str());
	std::string sLabel = StringUtils::format("%d",sdsNum);

	sdsLabel = LabelAtlas::create(				//创建一个LabelAtlas对象
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
	CocosDenshion::SimpleAudioEngine::getInstance()							//背景音效
						->preloadBackgroundMusic("sound_bgm_battlefield.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_explode_general.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_nuclear.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_missile.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_star_1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_star_2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_star_3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_break.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_error.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
						->preloadEffect("sound_sfx_destination.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()							//即使音效
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

	//创建一个菜单对象
	Menu* menu = Menu::create(puaseMenu,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
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

	//创建一个菜单对象
	Menu* menu = Menu::create(backItem,restartItem,tcItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
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

	ProgressTo* actionTo = ProgressTo::create(10, 100);		//创建一个持续两秒从0%到100%的动作
	ProgressTimer* radialPT = ProgressTimer::create(			//创建一个包装着精灵的ProgressTimer对象
								 Sprite::create("nextFlag1.png"));
	radialPT->setPosition(Point(55, 270)); 	//设置包装着精灵的ProgressTimer对象的位置
	radialPT->setMidpoint(Point(0.5f, 0.5f)); 	//设置百分比效果的参考点
	radialPT->setType(ProgressTimer::Type::RADIAL);	//设置为半径模式
	this->addChild(radialPT,101);				//将包装着精灵的ProgressTimer对象添加到布景中

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
					));		//重复执行百分比动作
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
	//添加敌船
	addEnemyShip();
	waveNum = waveNum + 1;
}
void GameLayer::initBoomFrame()
{
	std::string sa[6]={						//将所有动画图片的路径储存在数组中
		"boom1.png","boom2.png","boom3.png",
		"boom4.png","boom5.png","boom6.png"
	};
	Vector<SpriteFrame*> animFrames;		//创建存放动画帧的列表对象

	SpriteFrame *f0=SpriteFrame::create(sa[0],
						Rect(0,0,104,102));	//获取此动画中的指定两个帧
	animFrames.pushBack(f0);				//将这一段动画中的两个帧存放到向量中

	SpriteFrame *f1=SpriteFrame::create(sa[1],
						Rect(0,0,107,102));	//获取此动画中的指定两个帧
	animFrames.pushBack(f1);				//将这一段动画中的两个帧存放到向量中

	SpriteFrame *f2=SpriteFrame::create(sa[2],
						Rect(0,0,97,95));	//获取此动画中的指定两个帧
	animFrames.pushBack(f2);				//将这一段动画中的两个帧存放到向量中

	SpriteFrame *f3=SpriteFrame::create(sa[3],
						Rect(0,0,93,92));	//获取此动画中的指定两个帧
	animFrames.pushBack(f3);				//将这一段动画中的两个帧存放到向量中

	SpriteFrame *f4=SpriteFrame::create(sa[4],
						Rect(0,0,53,54));	//获取此动画中的指定两个帧
	animFrames.pushBack(f4);				//将这一段动画中的两个帧存放到向量中

	SpriteFrame *f5=SpriteFrame::create(sa[5],
						Rect(0,0,53,53));	//获取此动画中的指定两个帧
	animFrames.pushBack(f5);				//将这一段动画中的两个帧存放到向量中

	Animation *anmi=Animation::createWithSpriteFrames
			(animFrames, 0.1f);					//创建指向动画对象的指针
	anmiAc[1]=Animate::create(anmi);			//创建动画动作对象
	anmiAc[1]->retain();						//因为暂时不用，所以保持引用，防止被自动释放
}
void GameLayer::initBigBoomFrame()
{
	std::string sa[4]={						//将所有动画图片的路径储存在数组中
		"bigBoom1.png","bigBoom2.png",
		"bigBoom3.png","bigBoom4.png"
	};
	Vector<SpriteFrame*> animFrames;		//创建存放动画帧的列表对象
	for(int i=0;i<4;i++)
	{
		SpriteFrame *f0=SpriteFrame::create(sa[i],
							Rect(0,0,166,160));	//获取此动画中的指定两个帧
		animFrames.pushBack(f0);				//将这一段动画中的两个帧存放到向量中
	}
	Animation *anmi=Animation::createWithSpriteFrames
			(animFrames, 0.2f);					//创建指向动画对象的指针
	anmiAc[0]=Animate::create(anmi);			//创建动画动作对象
	anmiAc[0]->retain();						//因为暂时不用，所以保持引用，防止被自动释放
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
//初始化TMX地图的方法
void GameLayer::initTMXMap()
{
	std::string mapPath =StringUtils::format("map_%d.tmx",ChooseLevelLayer::levelNum);
	//加载TMX地图
	map = TMXTiledMap::create(mapPath);

	//获取用于碰撞检测的层
	colliLayer=map->layerNamed ("pzjcLayer");

	//设置碰撞检测层不可见
	colliLayer->setVisible(false);
	map->setAnchorPoint(Point(1,0));
	map->setPosition(Point(960,0));
	//将TMX地图添加进布景
	this->addChild(map, 0);
	mapPoint = map->getPosition();
	int mapWidth = map->getMapSize().width;
	int mapHeight = map->getMapSize().height;
	row = mapWidth;		//71
	col = mapHeight;   	//48
	//获得单个图块的大小，为了在绘制时得到偏移量，否则绘制出来的线条有半个图块的偏移差
	auto m_tamara = colliLayer->tileAt(Point(0,0));
	auto texture = m_tamara->getTexture();
	auto blockSize = texture->getContentSize();
	trans = Point(0,blockSize.height/2);
}
void GameLayer::initTMXPZJCArray()
{
	//创建动态二维数组
	Map_DATA = new int* [row];
	for(int i = 0; i<row; i++)
	{
		Map_DATA[i] = new int[col];
	}
	//获得一个图素中的属性值
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			//得到layer中每一个图块的gid
			unsigned int gid = colliLayer->tileGIDAt(Point(i,j));
			//通过gid得到该图块中的属性集,属性集中是以键值对的形式存在的
			auto tiledic = map->propertiesForGID(gid);
			//通过键得到value
			const String mvalue = tiledic.asValueMap()["sfpz"].asString();
			//将mvalue转换成int变量
			int mv = mvalue.intValue();
			//初始化地图中的数据
			Map_DATA[i][j] = mv;
		}
	}
	//创建数组
	visited = new int*[row];
	for(int i = 0; i<row; i++)
	{
		visited[i] = new int[col];
	}
	initVisitedArr();
}
//初始化寻径的数组-----将其设置为没有走过
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
	WarShipObject* targetSp = static_cast<WarShipObject*>(	//获取当前触摸对象，并转化为精灵类型
							event->getCurrentTarget());
	Point locationSp = targetSp->convertToNodeSpace(touch->getLocation());//获取当前坐标
	Size sizeSp = targetSp->getContentSize();			//获取精灵的大小
	Rect rectSp = Rect(0,0,sizeSp.width, sizeSp.height);//创建一个矩形对象，其大小与精灵相同
	if(rectSp.containsPoint(locationSp))
	{
		//设置船只冷却时间不可见
		for(int k = 0;k<5;k++)
		{
			ShipCoolSprite[k]->setVisible(false);
		}
		//判断当前点击的船只是否为上次点击的船只
		if(lastTouchSprite == targetSp&&targetSp->shipType == 1)
		{
			if(targetSp->state == 0)
			{
				targetSp->state = 1;		//标记为选中状态
				showWarShipItem(targetSp);
				warShipAddChild(targetSp);
				selectShip = true;
			}
			lastTouchSprite = targetSp;
			currTouchSprite = targetSp;
		}else if(lastTouchSprite != targetSp&&targetSp->shipType == 1)
		{	//若不为上次点击的船只
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
			targetSp->state = 1;//标记为选中状态
			showWarShipItem(targetSp);
			warShipAddChild(targetSp);
			selectShip = true;
			lastTouchSprite = targetSp;
			currTouchSprite = targetSp;
		}
	}
}
//添加船只的子精灵---范围圈----瞄准点
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
//显示当前应该显示的项
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
	//创建一个单点触摸监听
	EventListenerTouchOneByOne* listenerTouchShip = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listenerTouchShip->setSwallowTouches(false);
	//开始触摸时回调onTouchBegan方法]
	listenerTouchShip->onTouchBegan = CC_CALLBACK_2(GameLayer::onShipTouchBegan, this);
	//触摸结束时回调onTouchEnded方法
	listenerTouchShip->onTouchEnded = CC_CALLBACK_2(GameLayer::onShipTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouchShip,WarShipSprite);
}
//添加军舰的方法
void GameLayer::addWarShip(Point touchPoint ,int seleteNum)
{
	//将触摸点装换为格子行列号
	Point tempPoint ;
	tempPoint = touchPointToRowCol(touchPoint);
	//判断点击的格子是否能走
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


	//能走，则设置其为目标点
	int targetAll[1][2] =
	{
			{(int)tempPoint.y ,(int)tempPoint.x}
	};
	target = targetAll[0];
	//创建一个船只
	WarShipObject* wso = WarShipObject::create(
			StringUtils::format("warShip%d.png",seleteNum),Point(1120,368),seleteNum,1);

	//给当前船只赋值方向优先顺序
	for(int i = 0;i<8;i++)
	{
		for(int j = 0;j<2;j++)
		{
			wso->sequence[i][j] = SEQUENCEZARRAY[i][j];
		}
	}
	wso->shipNum = seleteNum;
	//设置船只的目标点
	wso->targetRow = tempPoint.y;
	wso->targetCol = tempPoint.x;
	map->addChild(wso,10);

	//给船只添加监听
	addTouchListener(wso);
	//添加到所有船只里面
	allShipVCT->push_back(wso);
	//调用搜索路径的方法，搜索行走路径
	searchPath(wso);
	//冷却时间复赋值
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
//随机重置搜索路径的方向优先顺序
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
//搜索路径
void GameLayer::searchPath(WarShipObject* wso)
{
	BFSCalPath(wso);
	wso->warShipPath = path;
	createFiniteTimeActionByVector(wso);
}
//将触摸点装换为格子行列号
Point GameLayer::touchPointToRowCol(Point touchPoint)
{
	Point resultPoint;
	int row = (int)touchPoint.x/CELLSIZE + ((((int)touchPoint.x)%CELLSIZE == 0)?0:1);
	int col = (int)(MAPWIDTH-touchPoint.y)/CELLSIZE + (((int)(MAPWIDTH-touchPoint.y)%CELLSIZE == 0)?0:1);
	resultPoint = Point(row,col);
	return resultPoint;
}
//广度优先算法
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
	//储存开始点和目标点的数组
	int (*start)[2] = new int[2][2];
	if((wso->targetRow != -1&&wso->targetCol != -1 && wso->state == 1))
	{
		wso->initRow = wso->targetRow;
		wso->initCol = wso->targetCol;
	}
	//设置起始点
	start[0][0] = wso->initRow;
	start[0][1] = wso->initCol;
	//设置目标点
	start[1][0] = wso->initRow;
	start[1][1] = wso->initCol;

	//将开始点放进队列中
	myQueue->push(start);
	while(flag)
	{
		//取出所有点
		int(*currentEdge)[2] = myQueue->front();
		//弹出队列中的数据
		myQueue->pop();
		//获取目标点-------下标为1
		int* tempTarget = currentEdge[1];
		//判断目标点是否访问过
		if(visited[tempTarget[1]][tempTarget[0]] == 1)
		{
			continue;
		}
		//标记目的点为已访问过
		visited[tempTarget[1]][tempTarget[0]] = 1;
		//将数字转换成字符串
		std::string str1;
		std::string str2;
		str1 = StringUtils::format("%d", tempTarget[0]);
		str2 = StringUtils::format("%d", tempTarget[1]);
		//记录此临时目的地的点的父节点
		hm->insert(std::map<std::string,int(*)[2]>::value_type(str1+":"+str2,currentEdge));
		//判断是否找到目标点
		if(tempTarget[0]==target[0] && tempTarget[1]==target[1])
		{
			break;
		}
		//将所有可能的点的行列号入队列
		int currCol = tempTarget[0];
		int currRow = tempTarget[1];
		int(*sequence)[2] = NULL;
		sequence = ((wso->sequence));

		//循环8个方向进行搜索
		for(int m = 0; m<8; m++)
		{
			int* rc = sequence[m];
			int i = rc[1];
			int j = rc[0];
			if(i==0 && j==0)
			{
				continue;
			}
			//如果该行列在地图范围内则进行下一步的计算
			if(currRow+i>=0 && currRow+i<row && currCol+j>=0 && currCol+j<col &&
					Map_DATA[currRow+i][currCol+j]!=1)
			{
				//创建二维数组
				int (*tempEdge)[2] = new int[2][2];
				tempEdge[0][0] = tempTarget[0];
				tempEdge[0][1] = tempTarget[1];
				tempEdge[1][0] = currCol+j;
				tempEdge[1][1] = currRow+i;
				//将二维数组添加进队列中
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
	//绘制最终的搜索结果路径
	std::map<std::string, int(*)[2]>::iterator iter;	//声明map容器迭代器
	int* temp = target;									//记录终点
	while(true)
	{
//		double xx;
//		double yy;
		//将数字转换成字符串
		str1 = StringUtils::format("%d", temp[0]);
		str2 = StringUtils::format("%d", temp[1]);
		std::string key = str1+":"+str2;
		iter = hm->find(key);
		int (*tempA)[2] = iter->second;
		//如果查找到了元素
		Point start;
		Point end;
		if(iter != hm->end())
		{
			//根据行列得到colliLayer中该图块的位置
			start = colliLayer->positionAt(Point(tempA[0][1],tempA[0][0]));
			//根据行列得到colliLayer中该图块的位置
			end = colliLayer->positionAt(Point(tempA[1][1],tempA[1][0]));

			start.x = start.x+trans.x;
			start.y = start.y+trans.y;
			end.x = end.x+trans.x;
			end.y = end.y+trans.y;
			tempPath->push_back(end);
		}
		//判断有否到出发点
		if(tempA[0][0]==wso->initRow&&tempA[0][1]==wso->initCol)
		{
			tempPath->push_back(start);
			break;
		}
		temp = tempA[0];//线段的起点数组
	}
	transformPath();
}
//放到储存行驶路径的向量中
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
	//计数器，记录当前的路线条数
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
//获取旋转角度的方法
int  GameLayer::orderDirection(float dx,float dy)
{
	if(dx == 0 && dy>0)
	{
		return 90;
		//上
	}else if(dx == 0 && dy<0)
	{
		return -90;
		//下
	}else if(dy == 0 && dx >0)
	{
		return 180;
		//右
	}else if(dy == 0 && dx <0)
	{
		return 0;
		//左
	}else if(dx <0 && dy >0)
	{
		return 45;
		//左上
	}else if(dx >0 && dy >0)
	{
		return 135;
		//右上
	}
	else if(dx <0 && dy <0)
	{
		return -45;
		//左下
	}
	else if(dx >0 && dy <0)
	{
		return -135;
		//右下
	}
	return 0;
}
//武器、船只的冷却时间的回调方法
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
//添加导弹
bool GameLayer::addWeapon(int selectIndex,Point startPoint,Point finalPoint,WarShipObject* ship,int launchForm)
{
    CCLOG("ADDWEAPON -------START");
	//判断选择的为导弹1还是2
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

	//创建导弹，并将其添加到向量中
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
	allWeaponVCT->push_back(weaponSp); //===添加到导弹向量中

	weaponSp->startPoint = pShip;
	weaponSp->targetPoint = finalPoint;
	weaponSp->currX = weaponSp->startPoint.x;
	weaponSp->currY = weaponSp->startPoint.y;
	float midx = 0;
	float midy = 0;
	//判断发射方向
	if(weaponSp->startPoint.x - weaponSp->targetPoint.x <0)
	{//朝右
		midx = fabs(weaponSp->targetPoint.x -weaponSp->startPoint.x)/2+weaponSp->startPoint.x;
		weaponSp->forwardLeft = false;
	}else
	{//朝左
		midx = fabs(weaponSp->startPoint.x -weaponSp->targetPoint.x)/2+weaponSp->targetPoint.x;
		weaponSp->forwardLeft = true;
	}
	midy = ZMAX;
	//记录当前导弹抛物线的中间点
	weaponSp->midx = midx;
	weaponSp->midy = midy;

	float a =0;
	// y = a*(x-x1)*(x-x2);

	//x-z面的抛物线
	//求a
	a = midy/((midx-weaponSp->startPoint.x)*(midx-weaponSp->targetPoint.x));
	weaponSp->a = a;
	weaponSp->degreeB = -a*(weaponSp->startPoint.x+weaponSp->targetPoint.x);

	//y =  k*x + b----------x-y面
	//斜率
	float k = (weaponSp->startPoint.y-weaponSp->targetPoint.y)/(weaponSp->startPoint.x-weaponSp->targetPoint.x);
	//b
	float b = weaponSp->startPoint.y-k*weaponSp->startPoint.x;

	//记录在到导弹相关信息
	weaponSp ->k = k;
	weaponSp ->b = b;

	//求旋转角度
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
	//设置当前对象的武器冷却时间
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
	//求微分  y= a*x*x + b*x +c
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

//若点击的地方为小岛，则显示X
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

	coolSpb = true;					//表示正在冷却中
	playerHKMJ->openMenu = false;	//表示不能发大招
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
	TMXTiledMap* targetMap = static_cast<TMXTiledMap*>(	//获取当前触摸对象，并转化为精灵类型
								event->getCurrentTarget());
	firstTouchPoint = touch->getLocation();
	Point locationMap = targetMap->convertToNodeSpace(touch->getLocation());//获取当前坐标

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

				//创建一个菜单对象
				Menu* menu = Menu::create(HKMJItem,NULL);
				//设置其位置
				menu->setPosition(Point::ZERO);
				//将其添加到布景中
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

				//创建一个菜单对象
				Menu* menu = Menu::create(planeItem,NULL);
				//设置其位置
				menu->setPosition(Point::ZERO);
				//将其添加到布景中
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
	//添加船只
	if(selectItem == true&& (selectIndex >=0&&selectIndex <=4))
	{//添加我方船只
		if(locationMap.y<40||locationMap.x>mapSize.width-40||locationMap.y>mapSize.height-40||locationMap.x<40)
		{
			addWrongPrompt(locationMap);
			return false;
		}
		//查看船只是否在冷却中
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
	{//发射炮弹
		addWeapon(selectIndex-5,
				lastTouchSprite->getPosition(),
				targetMap->convertToNodeSpace(touch->getLocation()),
				lastTouchSprite,1
				);
		selectIndex = -2;
		selectedSp->setVisible(false);
		selectItem = false;
	}
	//点击船，让其移动
	if(selectShip == true && selectIndex == -1)
	{
		Point tempPoint ;
		tempPoint = touchPointToRowCol(targetMap->convertToNodeSpace(touch->getLocation()));
		//停止当前正在进行的动作
		lastTouchSprite->stopAllActions();
		//获取当前对象的位置
		Point shipCP = lastTouchSprite->getPosition();
		//将X,Y坐标转换为格子的行列号
		Point shipRC = touchPointToRowCol(shipCP);
		lastTouchSprite->targetRow = (int)(shipRC.y - 1);
		lastTouchSprite->targetCol = (int)(shipRC.x - trans.x);
		//判断点击的地方是否能走------是否为地图中的岛屿
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
		//目标点
		int targetAll[1][2] =
		{
				{(int)tempPoint.y ,(int)tempPoint.x}
		};
		//设置目标点
		target = targetAll[0];
		//寻找路径
		searchPath(lastTouchSprite);
		//设置当前对象的目标格子行列号
		lastTouchSprite->targetRow = tempPoint.y;
		lastTouchSprite->targetCol = tempPoint.x;
		//设置其选中状态---------0为不选中
		lastTouchSprite->state = 0;
		//显示
		showWarShipItem(lastTouchSprite);
		//删除船只身上挂的精灵
		lastTouchSprite->removeChildByTag(DWPTAG);
		lastTouchSprite->removeChildByTag(DWSPRITETAG);
		lastTouchSprite->removeChildByTag(COMPASSSPRITE);
		lastTouchSprite->removeChildByTag(BQSPRITETAG);
		lastTouchSprite = NULL;
		//设置选中状态为未选中船只
		selectShip = false;
		//显示船只冷却进度
		for(int k = 0;k<5;k++)
		{
			ShipCoolSprite[k]->setVisible(true);
		}
		currTouchSprite = NULL;
		return false;
	}
	//判断是否点击地图
	Size sizeMap = targetMap->getContentSize();			//获取精灵的大小
	Rect rectMap = Rect(0,0,sizeMap.width, sizeMap.height);//创建一个矩形对象，其大小与精灵相同
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
	//移动地图
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
//添加一波敌船
void GameLayer::addEnemyShip()
{
	//产生一个1-8的随机数
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
		//设置敌船的血量
		enemyShip->lifeValue = waveNum*100+index*50;
		map->addChild(enemyShip,10+i);
		//将船只放在存所有船只向量中
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
//初始化航母
void GameLayer::initHKMJ()
{
	playerHKMJ = new HKMJObject(1050,270);
	map->addChild(playerHKMJ->hkmjSprite,30);

	ParticleSystemQuad* psqOne = ParticleSystemQuad::create("tji.plist");//从文件中加载粒子系统
	psqOne->setPositionType(ParticleSystem::PositionType::RELATIVE);
	psqOne->retain();								//保持引用
	psqOne->setBlendAdditive(true);				//设置混合方式为增加
	psqOne->setScale(0.5);
	psqOne->setPosition(Point(37,35));
	playerHKMJ->hkmjSprite->addChild(psqOne, 3);		//向布景层中的精灵添加粒子系统
	psqOne->runAction(
			RepeatForever::create(
					RotateBy::create(0.2,-30)
				));
	ParticleSystemQuad* psqTwo = ParticleSystemQuad::create("tji.plist");//从文件中加载粒子系统
	psqTwo->setPositionType(ParticleSystem::PositionType::RELATIVE);
	psqTwo->retain();								//保持引用
	psqTwo->setBlendAdditive(true);				//设置混合方式为增加
	psqTwo->setScale(0.5);
	psqTwo->setRotation(180);
	psqTwo->setPosition(Point(37,35));
	playerHKMJ->hkmjSprite->addChild(psqTwo, 3);		//向布景层中的精灵添加粒子系统
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
//初始化军舰选项
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

	//创建一个菜单对象
	Menu* menu = Menu::create(
			jjbgSp[0],jjbgSp[1],jjbgSp[2],
			jjbgSp[3],jjbgSp[4],shipWeapon [0],
			shipWeapon [1],shipWeapon [2],NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	this->addChild(menu, 2);

	//初始化武器
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
//武器0的回调方法
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
//武器1的回调方法
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
//船中心的瞄准点
void GameLayer::addAimSprite()
{
	Sprite* dwp = Sprite::create("dwp.png");
	lastTouchSprite->removeChildByTag(DWSPRITETAG);
	Size size = lastTouchSprite->getContentSize();
	dwp->setPosition(size.width/2,size.height/2);
	lastTouchSprite->addChild(dwp,-1,DWPTAG);
	dwp->runAction(RepeatForever::create(RotateBy::create(4,360)));
}
//船的小圈
void GameLayer::addSaveSprite(WarShipObject* wsoSprite)
{
	Size size = wsoSprite->getContentSize();
	Sprite* DWSprite = Sprite::create("dw.png");
	DWSprite->setPosition(Point(size.width/2,size.height/2));
	wsoSprite->addChild(DWSprite,-1,DWSPRITETAG);
	DWSprite->runAction(RepeatForever::create(RotateBy::create(4,360)));
}
//取消菜单项的回调方法
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
//点击军舰0的回调方法
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
//点击军舰1的回调方法
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
//点击军舰2的回调方法
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
//点击军舰3的回调方法
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
//点击军舰4的回调方法
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
//聪明的计算子方法
void GameLayer::calNearestSmartIn()
{
	std::vector<WarShipObject*>* enemyShipVCT =new std::vector<WarShipObject*>();	//所有军舰
	std::vector<WarShipObject*>* playerShipVCT =new std::vector<WarShipObject*>();

	std::vector<WarShipObject*>::iterator distemp ;
	for(distemp = allShipVCT->begin();distemp != allShipVCT->end();distemp++)
	{
		//必须为敌船
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
					(*enemytemp)->stopAllActions();	//停止敌船运动
					(*enemytemp)->isMoved = false;	//标志敌船不可动
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
						//生命值减少
						(*enemytemp)->lifeValue = (*enemytemp)->lifeValue - (*playertemp)->attackPower;
				}
				//军衔
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
			//若不在打击范围，并当前敌法军舰为停止运行状态，则 重新搜索路径，到目标地点
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
//计算两个点距离的方法
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
		//停止冷却时间回调
		this->unschedule(SEL_SCHEDULE(&GameLayer::weaponsCoolTimeUpdate));
		//停止寻径回调
		this->unschedule(SEL_SCHEDULE(&GameLayer::calNearestSmartIn));
		isGameOver = true;
		std::vector<WarShipObject*>::iterator allShipTemp ;
		for(allShipTemp =allShipVCT->begin();allShipTemp!= allShipVCT->end();)
		{
			//停止所用船只的动作
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

		ParticleSystemQuad* psq = ParticleSystemQuad::create("huoyan.plist");//从文件中加载粒子系统
		psq->setPositionType(ParticleSystem::PositionType::RELATIVE);
		psq->retain();								//保持引用
		psq->setBlendAdditive(true);				//设置混合方式为增加
		psq->setScale(0.4);
		psq->setPosition(Point(48,45));
		playerHKMJ->hkmjSprite->addChild(psq, 3);		//向布景层中的精灵添加粒子系统
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

		//记录总金钱
		int zqs = UserDefault::getInstance()->getIntegerForKey(Constant::GETGOLDCOUNT.c_str());
		UserDefault::getInstance()->setIntegerForKey(Constant::GETGOLDCOUNT.c_str(),zqs+myGold);
		//继续游戏
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

			CocosDenshion::SimpleAudioEngine::getInstance()		//即使音效
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

	//创建一个菜单对象
	Menu* menu = Menu::create(restartItem,tcItem,NULL);
	//设置其位置
	menu->setPosition(Point::ZERO);
	//将其添加到布景中
	gameOverbbSp->addChild(menu, 2);
}
//重新开始回调
void GameLayer::restartCallback()
{
	playSound();
	isGameOver = false;
	if(gameResult == false)//重新开始游戏
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
	//返回主菜单
	wfsm->goStartScene();
}
//海水移动
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
