#include "GameLayer.h"
#include "BulletSprite.h"
#include "ChooseLayer.h"
#include "DialogLayer.h"
#include "AchieveLayer.h"
#include "AppDelegate.h"
#include "AppMacros.h"
#include "Weapon.h"

using namespace cocos2d;
using namespace std;
static Dictionary s_dic;

#define CELL_BORDER        (28)	//Áù±ßĞÎ±ß³¤
#define CELL_HEIGHT        (50)	//Áù±ßĞÎ¸ñ×ÓÌùÍ¼¸ß¶È ÓÉÁù±ßĞÎ±ß³¤³ËÒÔsin(60)½üËÆµÃµ½

enum
{
	kTagTileMap
};

//ÓÃÀ´½øĞĞËã·¨ËÑË÷µÄÁù¸ö·½ÏòµÄ¶şÎ¬Êı×é
int sequenceZ[2][6][2] = 	//col, row
{
		{//Å¼ÊıĞĞ
				{-1, -1},
				{0, -1},
				{1, 0},
				{-1, 0},
				{-1, 1},
				{0, 1}
		},
		{//ÆæÊıĞĞ
				{1, -1},
				{0, -1},
				{-1, 0},
				{1, 0},
				{0, 1},
				{1, 1}
		}
};
//³ö·¢µãrow, col
static int source[]={5, 15};
//Ä¿µÄµãµÄrow, col
static int targetAll[1][2] ={{3, 2}};

bool GameLayer::isPause=false;
//½áÊøµãcol, row
int* target;
//0´ú±íÎ´È¥¹ı£¬1´ú±íÈ¥¹ı
int** visited;
//A*ÓÃÓÅÏÈ¼¶¶ÓÁĞ
typedef int(*INTPARR)[2];
//A*ÓÃÓÅÏÈ¼¶¶ÓÁĞÈİÆ÷ÖĞµÄ±È½ÏÆ÷£¬ÄÚ²¿ÖØÔØÁË£¨£©²Ù×÷·û£¬´ËÎªC++ÖĞµÄº¯Êı¶ÔÏó
struct cmp
{
	bool operator()(INTPARR o1, INTPARR o2)
	{
		int* t1 = o1[1];
		int* t2 = o2[1];

		//ÃÅÌØ¿¨ÂŞ¾àÀë
		int a = visited[o2[0][1]][o2[0][0]]+abs(t1[0]-target[0])+abs(t1[1]-target[1]);
		int b = visited[o2[0][1]][o2[0][0]]+abs(t2[0]-target[0])+abs(t2[1]-target[1]);

		return a>b;
	}
};
//A*ÓÃÓÅÏÈ¼¶¶ÓÁĞ
priority_queue<INTPARR,vector<INTPARR>,cmp>* astarQueue;
GameLayer::GameLayer(){}
//Îö¹¹º¯Êı
GameLayer::~GameLayer()
{
	//ÊÍ·ÅÄÚ´æ
	freeMemory();
	//ÊÍ·ÅµØÍ¼
	for(int i=0;i<row;i++)
	{
		delete []MAP_DATA[i];
	}
	delete []MAP_DATA;
}

//³õÊ¼·½·¨
bool GameLayer::init()
{
	//µ÷ÓÃ¸¸ÀàµÄ³õÊ¼»¯
	if ( !Layer::init() )
	{
		return false;
	}

	//´´½¨Ò»¸ö¾«Áé¶ÔÏó£¬°üº¬background.pngÍ¼Æ¬
	auto gbsprite = Sprite::create("back.png");
	//ÉèÖÃ¾«Áé¶ÔÏóµÄÎ»ÖÃ
	gbsprite->setPosition(Point(400,240));
	//½«¾«ÁéÌí¼Óµ½²¼¾°ÖĞ
	this->addChild(gbsprite,BACKGROUND_LEVEL_CGQ);

	//¼ÓÔØÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_button_press.mp3"
	);

    //¹ã¶ÈÓÅÏÈA*Ëã·¨
	astarQueue = NULL;
	hm = NULL;
	//»ñÈ¡µ±Ç°ÆÁÄ»µÄ´óĞ¡
	auto winSize = Director::getInstance()->getWinSize();
	//¼ÓÔØTMXµØÍ¼
	auto map = TMXTiledMap::create("MyTilesMap"+
			StringUtils::format("%d",ChooseLayer::modeLevel)+".tmx");
	//ÉèÖÃµØÍ¼µÄÃªµã
    map->setAnchorPoint(Point(0,1.0));
	//ÉèÖÃµØÍ¼Î»ÖÃ
    map->setPosition(Point(0, winSize.height-3));
	//½«µØÍ¼Ìí¼Óµ½²¼¾°ÖĞ
	addChild(map,BACKGROUND_LEVEL_CGQ, kTagTileMap);
	//»ñµÃµØÍ¼µÄ¿í¶ÈºÍ¸ß¶È
	int mapWidth = map->getMapSize().width;
	int mapHeight = map->getMapSize().height;
	//½«µØÍ¼µÄ¿í¶ÈºÍ¸ß¶ÈÉèÖÃÎª¶şÎ¬Êı×éµÄĞĞºÍÁĞ
	row = mapWidth;
	col = mapHeight;
	//´´½¨¶¯Ì¬¶şÎ¬Êı×é
	MAP_DATA = new int*[row];
	for(int i = 0; i<row; i++)
	{
		MAP_DATA[i] = new int[col];
	}

	//µÃµ½µØÍ¼ÖĞµÄlayer
	tmxLayer = map->layerNamed("Layer 0");
	//»ñµÃÒ»¸öÍ¼ËØÖĞµÄÊôĞÔÖµ
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			//µÃµ½layerÖĞÃ¿Ò»¸öÍ¼¿éµÄgid
			unsigned int gid = tmxLayer->tileGIDAt(Point(i, j));
			//Í¨¹ıgidµÃµ½¸ÃÍ¼¿éÖĞµÄÊôĞÔ¼¯,ÊôĞÔ¼¯ÖĞÊÇÒÔ¼üÖµ¶ÔµÄĞÎÊ½´æÔÚµÄ
			auto tiledic = map->propertiesForGID(gid);
			//Í¨¹ı¼üµÃµ½value
			const String mvalue = tiledic.asValueMap()["value"].asString();
			//½«mvalue×ª»»³Éint±äÁ¿
			int mv = mvalue.intValue();
			//³õÊ¼»¯µØÍ¼ÖĞµÄÊı¾İ
			MAP_DATA[i][j] = mv;

		}
	}
	//ÉèÖÃ¿¹¾â³İ£¬Èç¹ûĞèÒª¶ÔµØÍ¼½øĞĞ·Å´ó»òËõĞ¡Ê±£¬¾Í¿ÉÒÔÊ¹ÓÃ
	auto children = tmxLayer->getChildren();
	SpriteBatchNode* child = NULL;
	for(Object* object:children)
	{
		child = static_cast<SpriteBatchNode*>(object);
		child->getTexture()->setAntiAliasTexParameters();
	}
	//»ñµÃµ¥¸öÍ¼¿éµÄ´óĞ¡£¬ÎªÁËÔÚ»æÖÆÊ±µÃµ½Æ«ÒÆÁ¿£¬·ñÔò»æÖÆ³öÀ´µÄÏßÌõÓĞ°ë¸öÍ¼¿éµÄÆ«ÒÆ²î
	auto m_tamara = tmxLayer->tileAt(Point(0,0));
	auto texture = m_tamara->getTexture();
	auto blockSize = texture->getContentSize();
	trans = Point(blockSize.width/4,blockSize.height/2);

	//´´½¨¡°ÔİÍ£¡±°´Å¥¾«Áé
	MenuItemImage *zanTingItem = MenuItemImage::create
	(
		"zanting.png",		//Æ½Ê±µÄÍ¼Æ¬
		"zanting.png",		//Ñ¡ÖĞÊ±µÄÍ¼
		CC_CALLBACK_1(GameLayer::zanTing, this)
	);
	//ÉèÖÃÔİÍ£²Ëµ¥°´Å¥µÄÎ»ÖÃ
	zanTingItem->setPosition(Point(40,140));

	//´´½¨ÔİÍ£²Ëµ¥¶ÔÏó
	pMenu = Menu::create(zanTingItem,NULL);
	//ÉèÖÃ²Ëµ¥µÄÎ»ÖÃ
	pMenu->setPosition(Point(0,0));
	//½«²Ëµ¥Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(pMenu,DASHBOARD_LEVEL_CGQ);

	//´´½¨ÖÕµã¾«Áé
	targetSprite = Sprite::create("target.png");
	//ÉèÖÃ¾«ÁéµÄÎ»ÖÃ
	auto end = tmxLayer->positionAt(Point(targetAll[0][1],targetAll[0][0]));
	endWorld = tmxLayer->convertToWorldSpaceAR(Point(end.x+trans.x,end.y+trans.y));
	targetSprite->setPosition(endWorld);
	//½«ÖÕµã¾«Áé¶ÔÏóÌí¼Óµ½²¼¾°ÖĞ
	this->addChild(targetSprite,GAME_LEVEL_CGQ+1);
	//¼ÓÔØÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_swish.mp3"
	);
	//¼ÓÔØÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_creep_die_0.mp3"
	);
	//¼ÓÔØÓÎÏ·½áÊøµÄÒôĞ§ÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_game_over.mp3"
	);
	//¼ÓÔØµÚÈı¸öÅÚÌ¨·¢Éä×Óµ¯µÄÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_rocket_launch.mp3"
	);
	//¼ÓÔØµÚÒ»¸öÅÚÌ¨·¢Éä×Óµ¯µÄÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_minigun_hit.mp3"
	);
	//¼ÓÔØµÚ¶ş¸öÅÚÌ¨·¢Éä×Óµ¯µÄÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_laser_beam.mp3"
	);

    //´´½¨´æ·Å¹ÖµÄÊı×é
    arrMon = Array::create();
    arrMon ->retain();
	//´´½¨´æ·Å¹ÖactionµÄÊı×é
    arrAction = Array::create();
    arrAction ->retain();
    //´´½¨´æ·ÅÎäÆ÷µÄÊı×é
    arrWeap = Array::create();
    arrWeap ->retain();
    //´´½¨´æ·ÅÎäÆ÷²Ëµ¥Êı×é
    arrMenu = Array::create();
    arrMenu ->retain();
    //´´½¨´æ·Å¹ÖBulletµÄÊı×é
    arrBullet = Array::create();
    arrBullet ->retain();
    //´´½¨´æ·Å½ğÇ®µÄÊı×é
    arrSellUpdate = Array::create();
    arrSellUpdate ->retain();

	//Ìí¼ÓËùÓĞlabel
	addLabel();
	//Ìí¼Ó·ÀÓùËş²Ëµ¥¾«Áé
	addMenuSprite();
	//³õÊ¼µÄ×Ü½ğ±ÒÊı
	money = 280;
	//³õÊ¼»¯ÉúÃüÖµ
	ten = 18;
	//³õÊ¼»¯Ê±¼ä³£Á¿
    TIME_MAIN=0.7 ;
	//³õÊ¼»¯Éı¼¶µÄÎäÆ÷
	updateWeapon = NULL;
	//Éı¼¶·ÀÓùËşµÄ±êÖ¾Î»
	WeaponUpdate = false;
	//³õÊ¼»¯ÓÎÏ·½áÊøµÄ±êÖ¾Î»Îªfalse
	GameOver=false;
	//³õÊ¼»¯Ò°¹ÖÒÆ¶¯µÄ±êÖ¾Î»Îªfalse
	isMonsterRun = false;
	//³õÊ¼»¯´´½¨¹ÖµÄ±êÖ¾Î»
	isfoundMonster = false;
    //ÒÆ³ı·ÀÓùËş¾«Áé¶ÔÏóµÄ±êÖ¾Î»
    removeWeap = false;
    //³õÊ¼»¯ÓÎÏ·ÖĞ¹ÖµÄÅú´ÎÊı
    pass = 0;
    //³õÊ¼»¯×Ü·ÖÊıÎª0
    score = 0;
	//ÉèÖÃ¶¨Ê±»Øµ÷Ö¸¶¨·½·¨¸É»î
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//¶¨Ê±µ÷ÓÃrun·½·¨£¬ÒÔÃëÎªµ¥Î»
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::run), this, 1.0, false);
	//¶¨Ê±µ÷ÓÃrunBullet·½·¨£¬ÒÔÃëÎªµ¥Î»
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::runBullet), this, 0.002f, false);
	//¶¨Ê±µ÷ÓÃattack·½·¨£¬ÒÔÃëÎªµ¥Î»
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::attack), this, 0.3f, false);

	//´´½¨µ¥µã´¥Ãş¼àÌı
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//ÉèÖÃÏÂ´«´¥Ãş
	listener->setSwallowTouches(true);
	//¿ªÊ¼´¥ÃşÊ±»Øµ÷onTouchBegan·½·¨
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	//¿ªÊ¼´¥ÃşÊ±»Øµ÷onTouchMoved·½·¨
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	//¿ªÊ¼´¥ÃşÊ±»Øµ÷onTouchEnded·½·¨
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	//Ìí¼Óµ½¼àÌıÆ÷
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//³õÊ¼»¯¼ÆËãÂ·¾¶µÄ±êÖ¾Î»Îªfalse
	isCaulateOver = false;
	//ÄÃµ½Ä¿±êµã
	target = targetAll[0];
	//»æÖÆÂ·¾¶
	if(calculatePath())
	{
		printPath();
	}
	//³õÊ¼»¯´´½¨¶à¸ö¹ÖµÄ·½·¨£¬È»ºóµ÷ÓÃready·½·¨
	foundMonsters();

	return true;
}

void GameLayer::zanTing(Object* pSender)
{
	//²¥·ÅÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//ÅĞ¶ÏÁ£×ÓĞ§¹ûµÄ±êÖ¾Î»
	if(!isPause)
	{
		//ÔİÍ£±³¾°ÒôÀÖ
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		//»ñÈ¡µ¼Ñİ
		Director *director = Director::getInstance();
		//µ¼ÑİÖ´ĞĞÔİÍ£ÒôÀÖµÄ¹¤×÷
		director->pause();
		//´´½¨ÔİÍ£½çÃæ
		DialogLayer* dialogLayer = DialogLayer::create();
		//ÉèÖÃÎ»ÖÃ
		dialogLayer->setPosition(Point(0,0));
		//Ìí¼Óµ½²¼¾°ÖĞ
		this->addChild(dialogLayer,6);
		//ÔİÍ£¼üµÄ±êÖ¾Î»
		isPause=true;
	}
}

//¼ÆËãÂ·¾¶µÄ·½·¨
bool GameLayer::calculatePath()
{
	//ÊÍ·ÅÄÚ´æ
	freeMemory();
	//³õÊ¼»¯ËÑË÷ÁĞ±í
	initForCalculate();
	//³õÊ¼»¯µØÍ¼
	initVisitedArr();
	//ÓÃA*Ëã·¨ËÑË÷Â·¾¶
	bool b=BFSAStar();
	return b;
}

//ÊÍ·ÅÄÚ´æ
void GameLayer::freeMemory()
{
	//Çå¿ÕhmÖĞµÄ¼üÖµ¶Ô
	if(hm != NULL)
	{
		hm->clear();
		delete hm;
		hm = NULL;
	}
	//Çå¿Õ¹ã¶ÈÓÅÏÈA*¶ÓÁĞÖĞµÄÖ¸Õë
	if(astarQueue != NULL)
	{
		while(!astarQueue->empty())
		{
			astarQueue->pop();
		}
		delete astarQueue;
		astarQueue = NULL;
	}
	//ÊÍ·Å·ÃÎÊÊı×é
	if(visited != NULL)
	{
		for(int i=0;i<row;i++)
		{
			delete []visited[i];
		}
		delete []visited;
		visited = NULL;
	}
	isCaulateOver = false;
}

//¼ÆËãÖ®Ç°³õÊ¼»¯¼ÆËãÖĞÓÃµ½µÄÈİÆ÷
void GameLayer::initForCalculate()
{
	//´´½¨¶¯Ì¬¶şÎ¬Êı×é
	visited = new int*[row];
	for(int i = 0; i<row; i++)
	{
		visited[i] = new int[col];
	}
	//A*ÓÅÏÈ¼¶¶ÓÁĞ±È½ÏÆ÷
	astarQueue = new priority_queue<INTPARR,vector<INTPARR>,cmp>();//A*ÓÃÓÅÏÈ¼¶¶ÓÁĞ
	//½á¹ûÂ·¾¶¼ÇÂ¼
	hm = new map<string,int(*)[2]>();
}

//³õÊ¼»¯È¥¹ıÎ´È¥¹ıµÄÊı×é
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

//¹ã¶ÈÓÅÏÈA*Ëã·¨BFSAStar
bool GameLayer::BFSAStar()
{
	//¶¨ÒåÒ»¸ö±êÖ¾Î»
	bool flag = true;
	string str1;
	string str2;
	//¿ªÊ¼×´Ì¬
	int(*start)[2] = new int[2][2];
	start[0][0] = source[0];
	start[0][1] = source[1];
	start[1][0] = source[0];
	start[1][1] = source[1];
	//½«¿ªÊ¼µã·Å½øA*ÓÃÓÅÏÈ¼¶¶ÓÁĞÖĞ
	astarQueue->push(start);
	while(flag)
	{
		//Èç¹ûÕ»²»¿Õ
		if(astarQueue->empty())
		{
			return false;
		}
		//´Ó¶ÓÊ×È¡³ö±ß
		int(*currentEdge)[2] = astarQueue->top();
		astarQueue->pop();
		//È¡³ö´Ë±ßµÄÄ¿µÄµã
		int* tempTarget = currentEdge[1];
		//ÅĞ¶ÏÄ¿µÄµãÊÇ·ñÈ¥¹ı£¬ÈôÈ¥¹ıÔòÖ±½Ó½øÈëÏÂ´ÎÑ­»·
		if(visited[tempTarget[1]][tempTarget[0]] != 0)
		{
			continue;
		}
		visited[tempTarget[1]][tempTarget[0]] = visited[currentEdge[0][1]][currentEdge[0][0]]+1;
		str1 = StringUtils::format("%d", tempTarget[0]);
		str2 = StringUtils::format("%d", tempTarget[1]);
		//¼ÇÂ¼Ä¿µÄµãµÄ¸¸½Úµã
		hm->insert(map<string,int(*)[2]>::value_type(str1+":"+str2,currentEdge));
		//ÅĞ¶ÏÊÇ·ñÕÒµ½Ä¿µÄµã
		if(tempTarget[0] == target[0] && tempTarget[1] == target[1])
		{
			isCaulateOver= true;
			return isCaulateOver;
		}
		//½«ËùÓĞ¿ÉÄÜµÄ±ßÈëÓÅÏÈ¼¶¶ÓÁĞ
		int currCol = tempTarget[0];
		int currRow = tempTarget[1];
		int(*sequence)[2] = NULL;
		//¸ù¾İµ±Ç°Í¼¿éµÄÆæÊıÅ¼ÊıĞĞÀ´È·¶¨ËÑË÷µÄ·½Ïò
		if(currRow%2 == 0)
		{
			sequence = sequenceZ[0];
		}else
		{
			sequence = sequenceZ[1];
		}
		for(int m = 0; m<6; m++)
		{
			int* rc = sequence[m];
			int i = rc[1];
			int j = rc[0];

			if(i==0 && j==0)
			{
				continue;
			}
			if(currRow+i>=0 && currRow+i<row && currCol+j>=0 && currCol+j<col &&
					MAP_DATA[currRow+i][currCol+j]!=1)
			{
				//´´½¨¶şÎ¬Êı×é
				int(*tempEdge)[2] = new int[2][2];
				//ÉèÖÃÎªÏÂÒ»¸öÄ¿±êµã
				tempEdge[0][0] = tempTarget[0];
				tempEdge[0][1] = tempTarget[1];
				tempEdge[1][0] = currCol+j;
				tempEdge[1][1] = currRow+i;
				//½«¶şÎ¬Êı×éÌí¼Ó½øA*ÓÃÓÅÏÈ¼¶¶ÓÁĞÖĞ
				astarQueue->push(tempEdge);
			}
		}
	}
}

//´òÓ¡½á¹ûÂ·¾¶
void GameLayer::printPath()
{
	//Çå³ıÒÔÇ°µÄÂ·¾¶
	way.clear();

	string str1;
	string str2;
	//»æÖÆ×îÖÕµÄËÑË÷½á¹ûÂ·¾¶
	map<string, int(*)[2]>::iterator iter;
	int* temp = target;
	while(true)
	{
		str1 = StringUtils::format("%d", temp[0]);
		str2 = StringUtils::format("%d", temp[1]);
		string key = str1+":"+str2;
		//Ñ°ÕÒ¶ÔÓ¦µÄÖµ
		iter = hm->find(key);
		int(*tempA)[2] = iter->second;
		//²éµ½ÔªËØ
		if(iter != hm->end())
		{
			//ÄÃµ½ÆğÊ¼µãµÄ×ø±ê
			Point start = tmxLayer->positionAt(Point(tempA[0][1],tempA[0][0]));
			//ÄÃµ½Ä¿±êµãµÄ×ø±ê
			Point end = tmxLayer->positionAt(Point(tempA[1][1],tempA[1][0]));
			//½«ÆğÊ¼µã×ª»»µ½ÊÀ½ç×ø±êÏµÖĞ
			Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
			//½«Ä¿±êµã×ª»»µ½Êµ¼Ê×ø±êÏµÖĞ
			Point endWorld = tmxLayer->convertToWorldSpaceAR(Point(end.x+trans.x,end.y+trans.y));
			//½«Ä¿±êµãÌí¼Óµ½Â·¾¶ÖĞ
			way.push_back(endWorld);
			CCLOG("endWorld.x=%f,endWorld.y=%f",endWorld.x,endWorld.y);
			//ÅÅ¶ÓÃÜ¶È
			glLineWidth( 3.0f );
			//»æÖÆÂ·¾¶
			cocos2d::ccDrawColor4F(0.0f, 0.0f, 0.0f, 1.0f);
			cocos2d::ccDrawLine(startWorld, endWorld);
		}
		//ÅĞ¶ÏÓĞ·ñµ½³ö·¢µã
		if(tempA[0][0]==source[0]&&tempA[0][1]==source[1])
		{
			break;
		}
		//Ïß¶ÎµÄÆğµãÊı×é
		temp = tempA[0];
	}
}

//³öÒ°¹ÖÇ°µÄ×¼±¸·½·¨
void GameLayer::ready()
{
	//´´½¨Æğµã¾«Áé
	startSprite = Sprite::create("start.png");
	//ÉèÖÃ¾«ÁéµÄÎ»ÖÃ
	auto start = tmxLayer->positionAt(Point(source[1],source[0]));
	startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
	startSprite->setPosition(startWorld);
	//½«¾«Áé¶ÔÏóÌí¼Óµ½²¼¾°ÖĞ
	this->addChild(startSprite,5);

	//ÔÚÆğµã¾«ÁéÉÏÌí¼Ó°Ù·Ö±È¶¯×÷ÌØĞ§
	ProgressTo *to1 = ProgressTo::create(6, 100);
	left = ProgressTimer::create(Sprite::create("ring2.png"));
	left->setType( ProgressTimer::Type::RADIAL);
	left->setRotation(-90);
	this->addChild(left,5);
	left->setPosition(startWorld);
	left->runAction(
			Sequence::create(to1,
			CallFuncN::create(CC_CALLBACK_0(GameLayer::playGameCallback, this)),
			NULL
			)
	);

}

//³öÒ°¹ÖÇ°×¼±¸·½·¨µÄ»Øµ÷·½·¨
void GameLayer::playGameCallback()
{
	//ÒÆ³ı¾«Áé
	this->removeChild(left);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_swish.mp3");
	//¹ÖÒÆ¶¯µÄ±êÖ¾Î»ÉèÖÃÎªtrue
	isMonsterRun=true;
}

//³öÒ°¹ÖÊ±ÆğÊ¼µãÒª²¥·ÅµÄÁ½¸öÌØĞ§
void GameLayer::addParticle(Point point,float time)
{
	if(DialogLayer::isParticle)
	{
		int countVar=rand()%5;
		for(int i=0;i<35+countVar;i++)
		{
			float angleVar=rand()%360;
			int lengthVar=rand()%10;
			int countVar=rand()%10;
			int spriteLength=rand()%5;

			particle=Sprite::create("white1.png");
			particle->setAnchorPoint(Point(0,0.5));
			particle->setRotation(-angleVar);
			this->addChild(particle,5);

			Point vocter=ccpForAngle(angleVar*3.1415926/180);
			Point monPointOne = ccpAdd(ccpMult(vocter,(float)(lengthVar+30)),point);
			particle->setPosition(monPointOne);
			particle->setScale(0.7);
			particle->runAction(
						Sequence::create(
								Spawn::createWithTwoActions
								(
									MoveTo::create(time*3/7.0,point),
									FadeIn::create(time/5.0)
								),
								CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
								NULL
								)
						);
		}

		cc = Sprite::create("fire1.png");
		ActionInterval *act=FadeIn::create(time*4/5);
		ActionInterval *activeFade=FadeOut::create(time*4/5);
		cc->setPosition(point);
		this->addChild(cc,6);
		cc->setScale(2.0);
		cc->runAction(Sequence::create(
				Spawn::createWithTwoActions
							(
								act,
								activeFade
							),
							CallFuncN::create(CC_CALLBACK_0(GameLayer::removeSpriteAdd,this)),
							NULL
				)
		);
	}else{
		removeSpriteAdd();
	}
}

//½«µØÍ¼¸ñ×ÓĞĞÁĞºÅ×ª»»Îª¶ÔÓ¦¸ñ×ÓµÄÌùÍ¼×ø±ê
Point GameLayer::fromColRowToXY(int col, int row)//Èë¿Ú²ÎÊı//ºá×Å¿´µÄx£¬y
{
	row++;
	Point start = tmxLayer->positionAt(Point(col,row));//ºá×Å¿´µÄx£¬y
	Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
	return startWorld;
}
//½«´¥¿ØµãÎ»ÖÃ×ª»»ÎªµØÍ¼¸ñ×ÓĞĞÁĞºÅ
Point GameLayer::fromXYToColRow(int xPos, int yPos)
{
    #define GRID_WIDTH        (CELL_BORDER*1.5f)
    #define GRID_HEIGHT       (CELL_HEIGHT/2)
	#define TEMP_1            ((GRID_WIDTH*GRID_WIDTH - GRID_HEIGHT*GRID_HEIGHT)/2.f)
    #define TEMP_2            ((GRID_WIDTH*GRID_WIDTH + GRID_HEIGHT*GRID_HEIGHT)/2.f)

	int i = (int)floor(yPos/GRID_HEIGHT);
	int y = (int)(yPos-i*GRID_HEIGHT);

	int j = (int)floor(xPos/GRID_WIDTH);
	int x = (int)(xPos-j*GRID_WIDTH);

	if(((i+j)&1)!=0)
	{
		if(x*GRID_WIDTH-y*GRID_HEIGHT > TEMP_1) j++;
	}
	else
	{
		if(x*GRID_WIDTH+y*GRID_HEIGHT > TEMP_2) j++;
	}

	i = (int)floor((i+(1-(j&1)))/2);
	//8 ÊÇµØÍ¼×ÜĞĞÊı£¬´Ó0¿ªÊ¼Êı£¬Êµ¼Ê¿ª·¢ÖĞĞèÒª¸ù¾İ¾ßÌåÇé¿öĞŞ¸Ä
	return ccp(j-1,9-i);
}

//Ñ¡ÖĞÒÑ¾­·ÅÔÚµØÍ¼ÖĞµÄ·ÀÓùËş²¢¶ÔÆä½øĞĞ²Ù×÷
bool GameLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	//moveµÄÊ±ºòbegan²»×ß
	if(touchMove)
	{
		return false;
	}
	//ÄÃµ½µ±Ç°´¥¿ØµãµÄ×ø±ê
	Point point = pTouch->getLocation();
	//Èç¹û·ÀÓùËş²»Éı¼¶
	if(!WeaponUpdate)
	{
		//±éÀú´æ·Å·ÀÓùËş²Ëµ¥¾«ÁéµÄÊı×é
		for(int k = 0; k<arrMenu->count(); k++)
		{
			//ÄÃµ½·ÀÓùËş²Ëµ¥¾«Áé
			Weapon* pWeapon =(Weapon*)arrMenu->objectAtIndex(k);
			//»ñÈ¡·ÀÓùËşµÄ×ø±ê
			Point pp = pWeapon->getPosition();
			//Èç¹ûÊÇµã»÷²Ëµ¥·ÀÓùËş
			if(abs(point.x- pp.x)<32&&abs(point.y- pp.y)<32)
			{
				//µÃµ½µã»÷µ½µÄ²Ëµ¥·ÀÓùËşµÄid
				int id = pWeapon->id;
				//µÃµ½°²×°¸Ã·ÀÓùËşËùĞèµÄ½ğ±Ò
				int tempValue=pWeapon->value;
				//ÄÃµ½´¥¿ØµãµÄµØÍ¼µÄĞĞÁĞºÅ
				Point ccpxy = fromXYToColRow((int)point.x,(int)point.y);
				//½«ĞĞÁĞºÅ×ª»»Îª¶ÔÓ¦µÄµØÍ¼ÌùÆ¬µÄ×ø±ê
				Point ccp = fromColRowToXY(ccpxy.x,ccpxy.y);
				//Èç¹ûÇ®²»¹»
				if(money<tempValue)
				{
					return false;
				}
				//¸ù¾İµÃµ½µÄ²Ëµ¥·ÀÓùËşµÄid´´½¨Ò»¸ö·ÀÓùËş
				Weapon *oneTa =Weapon::create(id);
				//ÉèÖÃ·ÀÓùËşµÄÎ»ÖÃ
				oneTa->setPosition(ccp);
				//½«·ÀÓùËşÌí¼Óµ½²¼¾°ÖĞ
				this->addChild(oneTa,6);
				//ÉèÖÃ·ÀÓùËş
				s_dic.setObject(oneTa, pTouch->getID());
				//½«·ÀÓùËşÒÆ¶¯µÄ±êÖ¾Î»ÉèÖÃÎªtrue
				touchMove=true;

				return true;
			}
		}
	}else{
		//Ñ­»·Êı×é¿´Ñ¡ÔñµÄÊÇÉı¼¶»¹ÊÇ³öÊÛ
		for(int k=0;k<arrSellUpdate->count();k++)
		{
			std::string overStr = "$";
			//¶¨ÒåÒ»¸öÁÙÊ±±äÁ¿£¬ÓÃÀ´¼ÇÂ¼·ÀÓùËş¸üĞÂÊ±ËùĞèµÄ½ğ±ÒÊı
			int tempValue=updateWeapon->upValue;
			//Èç¹ûÊÇÉı¼¶
			if(abs(point.x-730)<32&&abs(point.y-408)<32)
			{
				//Èç¹ûÇ®²»¹»Éı¼¶
				if(money<tempValue)
				{
					return false;
				}
				//×ÜµÄ½ğ±ÒÊı¼õÈ¥Éı¼¶·ÀÓùËşËùĞèµÄ½ğ±ÒÊı
				money-=tempValue;
				//°Ñint ĞÍµÄÊı¾İ×ª»»³ÉstringĞÍµÄ È»ºóset
				char a[6];
				snprintf(a, 6, "%d",money);
				//¸üĞÂµ±Ç°×Ü½ğ±ÒÊı
				moneyL->setString((overStr+a).c_str());
				//µ÷ÓÃupdate·½·¨
				updateWeapon->update();

				return true;
			}
			//Èç¹ûÊÇ³öÊÛ·ÀÓùËş
			if(abs(point.x-730)<32&&abs(point.y-68)<32)
			{
				//×ÜµÄ½ğ±ÒÊı¼ÓÉÏÒª³öÊÛ·ÀÓùËşËùµÃµÄ½ğ±ÒÊı
				money+=updateWeapon->sellValue;
				char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
				snprintf(a, 6, "%d",money);
				//¸üĞÂ×ÜµÄ½ğ±ÒÊı
				moneyL->setString((overStr+a).c_str());
				//µ÷ÓÃsellWeapon·½·¨£¬³öÊÛ·ÀÓùËş
				sellWeapon(updateWeapon);

				return true;
			}
		}
	}
	//±éÀú´æ·Å×Ó·ÀÓùËşµÄÊı×é
	int k = 0;
	for(; k<arrWeap->count(); k++)
	{
		//ÄÃµ½Ö¸Ïò×Ó·ÀÓùËşµÄÖ¸Õë
		Weapon* pWeapon =(Weapon*)arrWeap->objectAtIndex(k);
		//»ñÈ¡ÆäÎ»ÖÃ
		Point ccWeapon = pWeapon->getPosition();
		//Èç¹ûÊÇµã»÷ÁË×Ó·ÀÓùËş
		if(abs(point.x-ccWeapon.x)<32&&abs(point.y-ccWeapon.y)<32)
		{
			Point ccpxy = fromXYToColRow((int)ccWeapon.x,(int)ccWeapon.y);
			//Èç¹ûÒÑ¾­Ñ¡ÖĞÁËÒ»¸ö·ÀÓùËş
			if(WeaponUpdate)
			{
				//ÉèÖÃÎª²»¿É¼û
				(updateWeapon->getChildByTag(1))->setVisible(false);
			}
			//°ÑÑ¡ÖĞµÄ·ÀÓùËş¸øÒªÉı¼¶µÄ
			updateWeapon=pWeapon;
			//Ê¹µÃ·ÀÓùËşÉı¼¶°´Å¥¿É¼û
			setUpdateTrue();
			//ÒÆ¶¯±êÖ¾Î»ÉèÎªfalse
			touchMove=false;

			return true;
		}
	}
	if(k==arrWeap->count())
	{
		//ÉèÖÃ·ÀÓùËş²Ëµ¥¾«Áé¿É¼û
		setWeaponTrue();
		//´¥¿ØÒÆ¶¯µÄ±êÖ¾
		touchMove=false;
	}
	return false;
}

//´¥¿ØÒÆ¶¯·ÀÓùËşµÄ·½·¨
void GameLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	//·ÀÓùËşµÄÎïÀíÎ»ÖÃ£¬¿´ÊÇ·ñÔÚÂ·¾¶µ±ÖĞ£¬ÈôÔÚÔòÖØĞÂ¼ÆËãÂ·¾¶
	if(!touchMove)
	{
		return ;
	}
	//µÃµ½µ±Ç°´¥¿ØÎ»ÖÃµÄ×ø±ê
	Point point = pTouch->getLocation();
	//¸ù¾İ²Ëµ¥·ÀÓùËşµÄid´´½¨Ò»¸ö±íÊ¾·ÀÓùËş¹¥»÷·¶Î§µÄ¾«Áé¶ÔÏó
	Weapon* trSprite = (Weapon*)s_dic.objectForKey(pTouch->getID());
	//ÉèÖÃ±íÊ¾·ÀÓùËş¹¥»÷·¶Î§µÄ¾«Áé¿É¼û
	(trSprite->getChildByTag(1))->setVisible(true);
	//ÄÃµ½´¥¿Øµã¶ÔÓ¦µÄµØÍ¼µÄĞĞÁĞºÅ
	Point ccpxy = fromXYToColRow((int)point.x,(int)point.y);
	//½«¸ÃĞĞÁĞºÅ×ª»»Îª¶ÔÓ¦ÌùÍ¼µÄ×ø±ê
	Point ccp = fromColRowToXY(ccpxy.x,ccpxy.y);
	//ÉèÖÃ¾«Áé¶ÔÏóµÄÎ                     »ÖÃ
	trSprite->setPosition(ccp);
}

//´¥¿ØÌ§Æğ
void GameLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	//Èç¹ûµã»÷µ½²Ëµ¥·ÀÓùËşµÄ±êÖ¾Î»ÎªfalseÔò·µ»Ø
	if(!touchMove)
	{
		return;
	}
	//»ñÈ¡´¥¿ØµãÎ»ÖÃµÄ×ø±ê
	Point point = pTouch->getLocation();
	//´´½¨Ò»¸ö±íÊ¾¹¥»÷·¶Î§µÄ¾«Áé¶ÔÏó
	Weapon* trSprite = (Weapon*)s_dic.objectForKey(pTouch->getID());
	//ÉèÖÃ±íÊ¾¹¥»÷·¶Î§µÄ¾«Áé²»¿É¼û
	(trSprite->getChildByTag(1))->setVisible(false);
	//µÃµ½´¥¿Øµã¶ÔÓ¦µÄµØÍ¼µÄĞĞÁĞºÅ
	Point ccpxy = fromXYToColRow((int)point.x,(int)point.y);
	//½«¸ÃµØÍ¼µÄĞĞÁĞºÅ×ª»»³É¶ÔÓ¦ÌùÍ¼µÄ×ø±ê
	Point ccp = fromColRowToXY(ccpxy.x,ccpxy.y);
	//Èç¹û·ÀÓùËş·ÅÖÃµÄÍ¼¿éÊÇµØÍ¼µÄÇ½
	if(MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]!=0)
	{
		//ÒÆ³ı·ÀÓùËş±êÖ¾Î»Éè¶¨Îªtrue
		removeWeap = true;
	}else//Èç¹û·ÅÖÃµÄÎ»ÖÃÎª¿ÉÒÔ·ÅÖÃµÄÎ»ÖÃ
	{
		int i=0;
		//Ñ­»·Â·¾¶Êı×é£¬¿´¿´ÊÇ·ñÎªÂ·¾¶ÖĞµÄ
		for(;i<way.size();i++)
		{
			//ÄÃµ½Â·¾¶ÖĞµÄÃ¿¸öµã
			Point ccpWay = (Point)way.at(i);
			//Èç¹ûµ±Ç°·Å·ÀÓùËşµÄ¸ñ×ÓÎªÂ·¾¶ÖĞµÄ
			if(ccp.x==ccpWay.x&&ccp.y==ccpWay.y)
			{
				//ÖØĞÂ¼ÆËãÂ·¾¶£¬°Ñµ±Ç°¸ñ×ÓÉèÎª¿ÉÒÔ·Å·ÀÓùËş¹Ö²»¿ÉÒÔ×ß
				MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]=1;
				//½øĞĞÂ·¾¶ËÑË÷
				bool isCaulate=calculatePath();
				//Èç¹ûÖØĞÂÕÒµ½Â·¾¶
				if(isCaulate)
				{
					//°Ñ»¹Ã»µ½´Ë¸ñ×ÓµÄ¹ÖÀïµÄway»»ÁË,´´½¨ĞÂµÄway
					printPath();
					//±éÀú´æ·Å¹ÖµÄÊı×é
					for(int j=0;j<arrMon->count();j++)
					{
						//ÄÃµ½µ±Ç°µÄ¹Ö
						Monsters* mon = (Monsters*)arrMon->objectAtIndex(j);
						//µÚ¼¸¸öÂ·¾¶
						int wayat = way.size()-i;
						//Èç¹û¹ÖÃ»ÓĞ¾­¹ı¸Ã·Å·ÀÓùËşµÄ¸ñ×Ó(-2ÎªÊÓ¾õºÍÊ±¼äÉÏµÄ¹ØÏµ²»ÊÇ¾ßÌåÊı¾İ)
						if(mon->way<wayat-2)
						{	//°ÑĞÂµÄÂ·¾¶¸ø¹Ö
							mon->selfWay=way;
						}
					}
					//½«ÒÆ³ı·ÀÓùËşµÄ±êÖ¾Î»ÉèÖÃÎªfalse
					removeWeap=false;
					//°Ñ·ÀÓùËşµ±Ç°´¦µÄ¸ñ×ÓĞĞÁĞ¸øÌØĞ§¾«Áé¶ÔÏó
					trSprite->pointColRow=ccpxy;
					break;
				}else
				{
					//Èç¹ûÃ»ÕÒµ½Â·¾¶,°ÑÔ­À´¸ñ×ÓÉèÖÃÎª¹Ö¿ÉÒÔ×ß
					MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]=0;
					//ÒÆ³ı·ÀÓùËş±êÖ¾Î»Éè¶¨Îªtrue
					removeWeap = true;

					break;
				}
			}
		}
		//Ñ­»·Â·¾¶Êı×éÍê³É£¬µ±Ç°¸ñ×Ó²»ÔÚÂ·¾¶µÄÊı×éÀï
		if(i==way.size())
		{
			//²»ÊÇÂ·¾¶ÖĞµÄ£¬°Ñ¸Ã¸ñ×ÓÉèÎªÒ°¹Ö²»¿É×ß
			MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]=1;
			//ÒÆ³ı·ÀÓùËşµÄ¾«ÁéµÄ±êÖ¾Î»ÉèÖÃÎªfalse
			removeWeap=false;
			//°Ñ·ÀÓùËşµ±Ç°´¦µÄ¸ñ×ÓĞĞÁĞ¸ø·ÀÓùËş
			trSprite->pointColRow=ccpxy;
		}
	}
	//Èç¹ûÒÆ³ı·ÀÓùËş¾«Áé¶ÔÏó
	if(removeWeap)
	{
		this->removeChild(trSprite);
	}
	else
	{	//³É¹¦¹ºÂò·ÀÓùËş
		int tempValue=trSprite->value;
		money-=tempValue;
		std::string overStr = "$";
		char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
		snprintf(a, 6, "%d",money);
		moneyL->setString((overStr+a).c_str());
		//½«·ÀÓùËş¾«Áé¶ÔÏóÌí¼Óµ½´æ·Å×ÓËşµÄÊı×éÖĞ
		arrWeap->addObject(trSprite);
	}
	//ÎªÁËÈÃbegan×ß½«ÒÆ¶¯µÄ±êÖ¾Î»ÉèÖÃÎªfalse
	touchMove=false;
}

//ÉèÖÃÉı¼¶²Ëµ¥¾«Áé¿É¼û
void GameLayer::setUpdateTrue()
{
	//±éÀú´æ·Å²Ëµ¥·ÀÓùËşµÄÊı×é
	for(int i=0;i<arrMenu->count();i++)
	{
		//ÄÃµ½Ö¸Ïò²Ëµ¥·ÀÓùËşµÄÖ¸Õë
		Weapon* weapon = (Weapon*)arrMenu->objectAtIndex(i);
		//ÉèÖÃ²Ëµ¥·ÀÓùËş²»¿É¼û
		weapon->setVisible(false);
	}
	//±éÀú´æ·Å½ğ±ÒµÄÊı×é
	for(int j=0;j<arrSellUpdate->count();j++)
	{
		//ÄÃµ½Ö¸ÏòÉı¼¶²Ëµ¥µÄÖ¸Õë
		Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(j);
		//½«Éı¼¶²Ëµ¥ÉèÖÃÎª¿É¼û
		update->setVisible(true);
	}
	//½«ÏÔÊ¾Éı¼¶ËùĞè½ğ±ÒÊıµÄÎÄ±¾±êÇ©ÉèÖÃÎª¿É¼û
	uMoneyL->setVisible(true);
	//½«ÏÔÊ¾Âôµô·ÀÓùËşÊ±½ğ±ÒÊÕÈëµÄÎÄ±¾±êÇ©ÉèÖÃÎª¿É¼û
	sMoneyL->setVisible(true);
	//·ÀÓùËşÉı¼¶µÄ±êÖ¾Î»ÉèÖÃÎªtrue
	WeaponUpdate = true;
	if(updateWeapon!=NULL)
	{
		//½«·¶Î§ÉèÖÃÎª¿É¼û
		(updateWeapon->getChildByTag(1))->setVisible(true);
		//Èç¹ûÒªÉı¼¶µÄ·ÀÓùËşµÄµÈ¼¶Îª4£¬¼´×î¸ß¼¶
		if(updateWeapon->level==4)
		{	//Éı¼¶µ½Í·±íÊ¾Éı¼¶µÄ½ğ±Ò²»¿É¼û
			uMoneyL->setVisible(false);
		}
		//Èç¹ûÊ£µÄÇ®²»¹»Éı¼¶
		if(money<updateWeapon->upValue||updateWeapon->level==4||updateWeapon->updateMark==true)
		{	//Éı¼¶µ½Í·||ÕıÔÚÉı¼¶
			Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(1);
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(100));
			update->runAction(act);
			ActionInterval *act1=FadeTo::create(0.1f,(GLubyte)(100));
			uMoneyL->runAction(act1);
		}else
		{
			Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(1);
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(255));
			update->runAction(act);
			ActionInterval *act1=FadeTo::create(0.1f,(GLubyte)(255));
			uMoneyL->runAction(act1);
		}
		//ÉèÖÃÉı¼¶µÄÇ®
		setValue();
	}
}

//ÉèÖÃ·ÀÓùËş²Ëµ¥¾«Áé¿É¼û
void GameLayer::setWeaponTrue()
{
	//±éÀú´æ·Å²Ëµ¥·ÀÓùËşµÄÊı×é
	for(int i=0;i<arrMenu->count();i++)
	{
		//ÄÃµ½´æ·ÅÔÚ²Ëµ¥·ÀÓùËşÊı×éÖĞµÄ·ÀÓùËş¶ÔÏó
		Weapon* weapon = (Weapon*)arrMenu->objectAtIndex(i);
		//½«ÆäÉèÖÃÎª¿É¼û
		weapon->setVisible(true);
	}
	//±éÀú´æ·Å½ğ±ÒµÄÊı×é
	for(int j=0;j<arrSellUpdate->count();j++)
	{
		Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(j);
		update->setVisible(false);
	}
	uMoneyL->setVisible(false);
	sMoneyL->setVisible(false);
	//·ÀÓùËş¸üĞÂµÄ±êÖ¾Î»ÉèÖÃÎªfalse
	WeaponUpdate = false;
	//Èç¹û¿É¸üĞÂµÄ·ÀÓùËşÎª¿Õ
	if(updateWeapon!=NULL)
	{
		//½«·ÀÓùËşÖÜÎ§µÄ¹âÈ¦¾«ÁéÉèÎª²»¿É¼û
		(updateWeapon->getChildByTag(1))->setVisible(false);
	}
}

//ÉèÖÃÉı¼¶µÄ½ğ±Ò
void GameLayer::setValue()
{
	std::string overStr = "$";
	char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
	snprintf(a, 6, "%d",updateWeapon->sellValue);
	sMoneyL->setString((overStr+a).c_str());
	char b[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
	snprintf(b, 6, "%d",updateWeapon->upValue);
	uMoneyL->setString((overStr+b).c_str());
}

//³öÊÛÎäÆ÷µÄ·½·¨
void GameLayer::sellWeapon(Weapon* weapon)
{
	//»ñÈ¡ÎäÆ÷ËùÔÚ¸ñ×ÓµÄĞĞÁĞ
	Point tempxy = weapon->getPosition();
	//´Ó´æ·Å·ÀÓùËşµÄÊı×éÖĞÒÆ³ı
	arrWeap->removeObject(weapon);
	//´ÓlayerÉÏÒÆ³ı
	this->removeChild(weapon);
	//ÄÃµ½¸ÃµØÍ¼¸ñ×ÓµÄĞĞÁĞºÅ
	Point ccpxy =fromXYToColRow((int)tempxy.x,(int)tempxy.y);
	//°ÑµØÍ¼¸ñ×ÓÉèÎª¿ÉÒÔ×ß
	MAP_DATA[(int)ccpxy .x][(int)(ccpxy.y)]=0;
	//½«¸üĞÂ·ÀÓùËşÉèÖÃÎª¿Õ
	updateWeapon=NULL;
	//ÓÎÏ·Íæ¼ÒµÄ½ğÇ®¼Ó
	setWeaponTrue();
}

//Ò°¹Öµ½ÖÕµãÊ±µÄÌØĞ§
void GameLayer::addParticle(Point point,int id,float time)
{
	if(!DialogLayer::isParticle)
	{
		return;
	}
	std::string picTable[6]={"red.png","yellow.png","blue.png","white.png","red.png","blue.png"};
	std::string picParticle[6]={"hong.png","orige.png","zi.png","liang.png","hong.png","zi.png"};
	int countVar=rand()%10;
	int angle=0;
	for(int i=0;i<55+countVar;i++)
	{
		float timeVar=(rand()%10)/10.0;
		float angleVar=(rand()%10)/10.0;
		Sprite* particle= Sprite::create(picTable[id-1].c_str());
		particle->setAnchorPoint(Point(0,0.5));
		particle->setPosition(point);
		particle->setScale(1.0);
		particle->setRotation(-(angle+angleVar));
		Point vocter=ccpForAngle((angle+angleVar)*3.1415926/180);
		int lange=rand()%200;
		angle+=11;
		this->addChild(particle,5);
		particle->runAction(
			Sequence::create(
					Spawn::createWithTwoActions
					(
						MoveBy::create(1+timeVar,Point((200+lange)*vocter.x,(200+lange)*vocter.y)),
						FadeOut::create(1+timeVar)
					),
					CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
					NULL
			)
		);
	}

	Sprite* ccp = Sprite::create(picParticle[id-1].c_str());
	ActionInterval *act=ScaleTo::create(0.5f,6);
	ActionInterval *activeFade=FadeOut::create(0.5f);
	ccp->setPosition(point);
	this->addChild(ccp,7);
	ccp->runAction(
		Sequence::create(
				Spawn::createWithTwoActions
				(
					act,
					activeFade
		),
		CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
		NULL
		)
	);

	cc = Sprite::create("fire1.png");
	ActionInterval *act1=FadeIn::create(time*4/9);
	ActionInterval *activeFade1=FadeOut::create(time*4/9);
	cc->setPosition(point);
	this->addChild(cc,6);
	cc->setScale(3.0);
	cc->runAction(Sequence::create(
			Spawn::createWithTwoActions
						(
							act1,
							activeFade1
						),
						CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
						NULL
			)
	);
}

//Ò°¹ÖËÀÊ±µÄÌØĞ§
void GameLayer::addParticle1(Point point,int id,float time)
{
	if(!DialogLayer::isParticle)
	{
		return;
	}
	std::string picTable[6]={"red.png","yellow.png","blue.png","white.png","red.png","blue.png"};
	std::string picParticle[6]={"hong.png","orige.png","zi.png","liang.png","hong.png","zi.png"};
	int countVar=rand()%10;
	int angle=0;
	for(int i=0;i<35+countVar;i++)
	{
		float timeVar=(rand()%10)/10.0;
		float angleVar=(rand()%10)/10.0;
		Sprite* particle= Sprite::create(picTable[id-1].c_str());
		particle->setAnchorPoint(Point(0,0.5));
		particle->setPosition(point);
		particle->setScale(0.8);
		particle->setRotation(-(angle+angleVar));
		Point vocter=ccpForAngle((angle+angleVar)*3.1415926/180);
		int lange=rand()%200;
		angle+=11;
		this->addChild(particle,5);
		particle->runAction(
			Sequence::create(
					Spawn::createWithTwoActions
					(
						MoveBy::create(1+timeVar,Point((200+lange)*vocter.x,(200+lange)*vocter.y)),
						FadeOut::create(1+timeVar)
					),
					CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
					NULL
			)
		);
	}
	Sprite* ccp = Sprite::create(picParticle[id-1].c_str());
	ActionInterval *act=ScaleTo::create(0.5f,6);
	ActionInterval *activeFade=FadeOut::create(0.5f);
	ccp->setPosition(point);
	this->addChild(ccp,6);
	ccp->runAction(
		Sequence::create(
				Spawn::createWithTwoActions
				(
					act,
					activeFade
		),
		CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
		NULL
		)
	);
}

//µÚ¶ş¸ö·ÀÓùËş¹¥»÷¹ÖÊ±µ÷ÓÃµÄÌØĞ§
void GameLayer::addParticle(Point point,int id,float time,float angle)
{
	if(!DialogLayer::isParticle)
	{
		return;
	}
	std::string picTable[6]={"red.png","yellow.png","blue.png","white.png","red.png","blue.png"};
	//ÓÃËæ»úÊıÉú³ÉÆ÷Éú³É»ğÑæÌõ
	int countVar=rand()%5;
	for(int i=0;i<16+countVar;i++)
	{
		float timeVar=(rand()%10)/1.0;
		float angleVar=rand()%90;
		angleVar=45-angleVar;
		Sprite* particle= Sprite::create(picTable[id-1].c_str());
		particle->setAnchorPoint(Point(0,0.5));
		particle->setPosition(point);
		particle->setScale(0.7);
		particle->setRotation(-(angle+angleVar));
		Point vocter=ccpForAngle((angle+angleVar)*3.1415926/180);
		int lange=rand()%300;
		this->addChild(particle,5);
		particle->runAction(
			Sequence::create(
					Spawn::createWithTwoActions
					(
						MoveBy::create(1+timeVar,Point((100+lange)*vocter.x,(100+lange)*vocter.y)),
						FadeOut::create(1+timeVar)
					),
					CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
					NULL
					)
				);
	}
}

//¹Ö´ÓactionÊı×éÀï³öÀ´°¤¸ö×ß
void GameLayer::run()
{
	//Èç¹ûÓÎÏ·½áÊøÔò·µ»Ø
	if(GameOver)
	{
		return;
	}
	//±éÀú·ÀÓùËş²Ëµ¥¾«ÁéÉèÖÃ²Ëµ¥µÄÍ¸Ã÷¶È
	for(int k=0;k<arrMenu->count();k++)
	{
		//Ö¸ÏòÎäÆ÷¶ÔÏóµÄÖ¸Õë
		Weapon* pWeapon =(Weapon*)arrMenu->objectAtIndex(k);
		//Èç¹ûµ±Ç°½ğ±ÒÊıĞ¡ÓÚ°²×°ÎäÆ÷Ê±ĞèÒªµÄ½ğ±Ò
		if(money<pWeapon->value)
		{
			//½«¸Ã·ÀÓùËşÉèÖÃÎª²»¿É´¥¿Ø²¢±ß°µµ­
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(100));
			pWeapon->runAction(act);

		}else
		{
			//Èç¹ûµ±Ç°½ğ±ÒÊı´óÓÚ°²×°·ÀÓùËşÊ±ĞèÒªµÄ½ğ±ÒÊı£¬½«¸Ã·ÀÓùËşÉèÖÃÎª¿É¼û¿É´¥¿Ø
			ActionInterval *act0=FadeTo::create(0.1f,(GLubyte)(255));
			pWeapon->runAction(act0);

		}
	}
	//Èç¹ûÉı¼¶ÎäÆ÷²»Îª¿Õ
	if(updateWeapon!=NULL)
	{
		setValue();
		//Èç¹ûÒªÉı¼¶µÄÎäÆ÷µÄµÈ¼¶ÒÑ¾­Îª4£¬¼´×î¸ß¼¶
		if(updateWeapon->level==4)
		{	//Éı¼¶µ½Í·±íÊ¾Éı¼¶µÄ½ğ±Ò²»¿É¼û
			uMoneyL->setVisible(false);
		}
		//Èç¹ûµ±Ç°×Ü½ğ±ÒÊıĞ¡ÓÚÉı¼¶ËùĞè½ğ±ÒÊı»òÕßÒÑ¾­Éı¼¶µ½×î¸ß¼¶»òÕßÉı¼¶µÄ±êÖ¾Î»Îªtrue
		if(money<updateWeapon->upValue||updateWeapon->level==4||updateWeapon->updateMark==true)
		{
			//ÉùÃ÷Ò»¸öÖ¸Ïò´æ·Å½ğÇ®Êı×éµÄÖ¸Õë
			Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(1);
			//½«±íÊ¾Éı¼¶µÄ¼ıÍ·°´Å¥ÉèÖÃÎª²»¿É´¥¿Ø
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(100));
			update->runAction(act);
			//½«±íÊ¾Éı¼¶µÄ$ÎÄ±¾±êÇ©ÉèÖÃÎª²»¿É´¥¿Ø
			ActionInterval *act1=FadeTo::create(0.1f,(GLubyte)(100));
			uMoneyL->runAction(act1);
		}else
		{
			//·ñÔò½«ÆäÉèÖÃÎª¿É´¥¿Ø¿ÉÉı¼¶
			Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(1);
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(255));
			update->runAction(act);
			ActionInterval *act1=FadeTo::create(0.1f,(GLubyte)(255));
			uMoneyL->runAction(act1);
		}
	}

	//Èç¹û´´½¨¹ÖµÄ±êÖ¾Î»ÎªtrueÔò×ßÏÂÃæ´úÂë
	if(isfoundMonster)
	{
		//Èç¹û´æ·Å¹ÖÓë´æ·Å¹ÖactionµÄÊı×é¶¼Îª0Ôò×ßÏÂÃæ´úÂë
		if(arrMon->count()==0&&arrAction->count()==0)
		{
			//»ØºÏÊı×Ô¼Ó
			pass++;
			char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
			snprintf(a, 6, "%d",pass+1);
			passL->setString(a);
			//²»ÈÃ¹ÖÔË¶¯
			isMonsterRun=false;
			//currMon++;
			//µ÷ÓÃ´´½¨¶à¸ö¹ÖµÄ·½·¨
			foundMonsters();
		}
	}
	//Èç¹û´æ·Å¹ÖactionµÄÊı×éÎª¿ÕÔò×ßÏÂÃæ´úÂë
	if(arrAction->count()==0)
	{
		return;
	}

	//ÄÃµ½ÆğÊ¼µãµÄ×ø±ê£¬ºá×Å¿´µÄx£¬y
	Point start = tmxLayer->positionAt(Point(source[1],source[0]));
	//½«Æğµã×ø±ê×ª»»µ½ÊÀ½ç×ø±êÏµÖĞ
	Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
	//Èç¹û¹ÖÒÆ¶¯µÄ±êÖ¾Î»Îªtrue
	if(isMonsterRun)
	{
		//ÔÚÆğÊ¼µã´¦Ìí¼ÓÁ½¸öÌØĞ§£¬²ÎÊıÎª×ø±êºÍÊ±¼ä¼ä¸ô
		this->addParticle(startWorld,1.0);
	}
}

//¹ÖÒÆ¶¯µ½ÖÕµã
void GameLayer::monsterRun(Node* node)
{
	Monsters* monster=(Monsters*) node ;
	//½«¹ÖÉèÎª¿É¼û
	monster->setVisible(true);
	//Èç¹ûÒ°¹ÖÒÑ¾­×ßµÄ²½ÊıµÈÓÚÔ­¶¨Â·¾¶µÄ³¤¶È
	if(monster->way==monster->selfWay.size())
	{
		//Èç¹ûÉúÃüÖµ´óÓÚ0
		if(ten>0)
		{
			//ÉúÃüÖµ×Ô¼õ
			ten--;
			//²¥·ÅÒôĞ§
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
		}
		//Ìí¼ÓÒ°¹Öµ½ÖÕµãÊ±µÄÌØĞ§
		this->addParticle(monster->getPosition(),monster->id,3.0);
		char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
		snprintf(a, 6, "%d",ten);
		//ÉèÖÃ±íÊ¾ÉúÃüÖµµÄÎÄ±¾±êÇ©
		tenL->setString(a);
		//Ò°¹Öµ½ÖÕµãºóÒÆ³ı¾«Áé
		this->removeChild(monster);
		//ÒÆ³ıÊı×éÖĞµÄ¹Ö
		arrMon->removeObject(monster);
		if(ten<=0)//Ê§°Ü
		{
			GameOver=true;
			this->loseGame();
		}
	}

	//Èç¹û¹ÖÒÑ¾­×ßµÄÂ·¾¶³¤¶ÈĞ¡ÓÚÒª×ßÂ·¾¶µÄ×Ü³¤¶È
	if(monster->way<monster->selfWay.size())
	{
		//Ò°¹Ö×ßµÄ²½Êı×Ô¼Ó
		monster->way++;
		//»ñÈ¡Ò°¹Öµ±Ç°µÄÎ»ÖÃµã
		Point crrPosition=monster->getPosition();
		//ÄÃµ½ÏÂÒ»¸öÒª×ßµÄµãµÄ×ø±ê
		Point tarPosition=monster->selfWay.at(monster->selfWay.size()-monster->way);
		//ÄÃµ½¹Öµ±Ç°Ëù´¦µØÍ¼¸ñ×ÓµÄĞĞÁĞºÅµÄxÖµ
		int crrpoint_x=(int)(fromXYToColRow((int)crrPosition.x,(int)crrPosition.y).x);
		//ÄÃµ½¹Öµ±Ç°Ëù´¦µØÍ¼¸ñ×ÓµÄĞĞÁĞºÅµÄyÖµ
		int crrpoint_y=(int)(fromXYToColRow((int)crrPosition.x,(int)crrPosition.y).y);
		//ÄÃµ½ÏÂÒ»¸öÒª×ßµÄµãµÄxÖµ
		int tarpoint_x=(int)(fromXYToColRow((int)tarPosition.x,(int)tarPosition.y).x);
		//ÄÃµ½ÏÂÒ»¸öÒª×ßµÄµãµÄyÖµ
		int tarpoint_y=(int)(fromXYToColRow((int)tarPosition.x,(int)tarPosition.y).y);
		//¶¨ÒåÒ»¸öµã±äÁ¿
		Point zhong;
		//ÄÃµ½¹Öµ±Ç°µãÓëÏÂÒ»Ä¿±êµãµÄÖĞµãµÄx×ø±ê
		zhong.x=(tarPosition.x+crrPosition.x)/2;
		//ÄÃµ½¹Öµ±Ç°µãÓëÏÂÒ»Ä¿±êµãµÄÖĞµãµÄy×ø±ê
		zhong.y=(tarPosition.y+crrPosition.y)/2;
		//¶¨ÒåÒ»¸öÓÃÀ´±íÊ¾Ê±¼äµÄ³£Á¿
		float time1=this->TIME_MAIN/2;
		float time2=this->TIME_MAIN/2;
		//Èç¹ûÎªµÚ¶şÅúÒ°¹Ö
		if(monster->id==2)
		{
			Point vacter;
			vacter.x=tarPosition.x-crrPosition.x;
			vacter.y=tarPosition.y-crrPosition.y;
			float dirction=ccpToAngle(vacter);
			monster->setRotation(-(dirction*180/3.1415926));
			monster->refresh(dirction);
		}
		//¸ø¶¨µ±Ç°µãÓëÄ¿±êµãµÄÖĞµãÒÔ¼°Ò»¸öÊ±¼äµÄMoveTo
		ActionInterval* act1=MoveTo::create(time1,zhong);
		//¸ø¶¨Ä¿±êµã¼°Ò»¸öÊ±¼äµÄMoveTo
		ActionInterval* act2=MoveTo::create(time2,tarPosition);
		Sequence* seqer = Sequence::create
								(
									act1,
									act2,
									CallFuncN::create(CC_CALLBACK_1(GameLayer::monsterRun,this)),
									NULL
								);
		monster->runAction(seqer);
	}
}

void GameLayer::removeSpriteAdd()
{
	//ÉùÃ÷Ò»¸öÖ¸Ïò¹Ö¶¯×÷Êı×éÖĞ×îºóÒ»¸ö¹ÖµÄÖ¸Õë
	Monsters* mon = (Monsters*)arrAction->lastObject();
	//°Ñ¹ÖÌí¼Óµ½¹ÖÊı×éÀï
	arrMon->addObject(mon);
	//µ÷ÓÃ¹ÖÒÆ¶¯µ½ÖÕµãµÄ·½·¨
	monsterRun(mon);
	//ÒÆ¶¯¹Ö¶¯×÷Êı×éÖĞµÄ¹Ö
	arrAction->removeLastObject();
	if(!DialogLayer::isParticle)
	{
		//É¾³ıÌØĞ§¾«Áé¶ÔÏó
		this->removeChild(cc,true);
	}
}

//´´½¨¶à¸ö¹ÖµÄ·½·¨
void GameLayer::foundMonsters()
{
	//Ëæ»úµÄ³ö¹Ö
	int id = pass%5;

	for(int i=0;i<10;i++)
	{
		//´´½¨Ò»¸ö¹Ö¶ÔÏó
		Monsters* mon = Monsters::create(id+1,way);
		//ÄÃµ½¹ÖÆğÊ¼Î»ÖÃµÄ×ø±ê,ºá×Å¿´µÄx,y
		Point start = tmxLayer->positionAt(Point(source[1],source[0]));
		//½«ÆğÊ¼µãµÄ×ø±ê×ª»»µ½ÊÀ½ç×ø±êÏµÖĞ
		Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
		//ÉèÖÃ¹ÖµÄ³õÊ¼Î»ÖÃ
		mon->setPosition(startWorld);
		//³õÊ¼Ê±½«¹ÖÉèÎª²»¿É¼û
		mon->setVisible(false);
		//½«¹ÖÌí¼Óµ½²¼¾°ÖĞ
		this->addChild(mon,6);
		//°Ñ¹ÖÌí¼Óµ½actionÊı×éÀï
		arrAction->addObject(mon);
		if(id>2)//Á½¸öµ¥¶À
		{
			break;
		}
	}
	//½«´´½¨¹ÖµÄ±êÖ¾Î»ÉèÖÃÎªtrue
	isfoundMonster=true;
	//µ÷ÓÃready·½·¨
	ready();
}

//¹¥»÷¹ÖµÄ·½·¨
void GameLayer::attack()
{
	//Èç¹û¹Ö²»ÒÆ¶¯»òÕßÓÎÏ·½áÊø
	if(!isMonsterRun||GameOver)
	{
		return;
	}
	//·ÀÓùËş¶Ô¹ÖµÄÉ¨Ãè
	for(int i=0;i<arrWeap->count();i++)
	{
		if(((Weapon*)arrWeap->objectAtIndex(i))->fire)
		{
			for(int j=0;j<arrMon->count();j++)
			{
				//ÄÃµ½Ö¸Ïò¹Ö¶ÔÏóµÄÖ¸Õë
				Monsters* monster = (Monsters*)arrMon->objectAtIndex(j);
				//ÄÃµ½Ö¸Ïò·ÀÓùËşµÄÖ¸Õë
				Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(i);
				//»ñÈ¡·ÀÓùËşµ±Ç°µÄÎ»ÖÃ×ø±ê
				Point pointWeapon=weapon->getPosition();
				//»ñÈ¡Ò°¹Öµ±Ç°µÄÎ»ÖÃ×ø±ê
				Point pointMonster=monster->getPosition();
				//¶¨ÒåÒ»¸öÏòÁ¿   ÎªÁËÊ¹·ÀÓùËşÖ¸Ïò¹Ö
				Point anglePoint;
				anglePoint.x=pointMonster.x-pointWeapon.x;
				anglePoint.y=pointMonster.y-pointWeapon.y;
				//¸ù¾İÏòÁ¿ÇóÏòÁ¿¶ÔÓ¦µÄ½Ç¶È
				float angle = ccpToAngle(anglePoint);
				//Çó¾àÀë
				float distance = sqrt((pointMonster.x-pointWeapon.x)*(pointMonster.x-pointWeapon.x)
						+(pointMonster.y-pointWeapon.y)*(pointMonster.y-pointWeapon.y));
				//¶¨ÒåÒ»¸öÉèÖÃ×Óµ¯Àë¿ª·ÀÓùËşµÄÎ»ÖÃµÄ±äÁ¿
				Point bulletPoint;
				//×Óµ¯³ö·ÀÓùËşµÄÎ»ÖÃ  ²»ÊÇ·ÀÓùËşÖĞÑë
				bulletPoint.x=(pointMonster.x-pointWeapon.x)*25/distance+pointWeapon.x;
				bulletPoint.y=(pointMonster.y-pointWeapon.y)*25/distance+pointWeapon.y;
				//ÓÃCocos2dxÌá¹©µÄº¯ÊıÇóÏòÁ¿µÄ³¤¶È
				float lengthVector=ccpLength(Point(pointWeapon.x-pointMonster.x,pointWeapon.y-pointMonster.y));
				//Èç¹ûËùÇó³¤¶ÈÔÚ·ÀÓùËşµÄ¹¥»÷·¶Î§ÄÚ
				if(lengthVector<=weapon->confines)
				{
					//·ÀÓùËşĞı×ª
					weapon->setRotation(-(angle*180/3.1415926));
					//¸Ä±ä·ÀÓùËş½Ç¶ÈÊôĞÔ
					weapon->angle=angle*180/3.1415926;
					//µÚÒ»¸ö·ÀÓùËş¹¥»÷¹ÖÊ±µ÷ÓÃ¼õÑªµÄ·½·¨
					if(weapon->id==1)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
						(
							"sf_minigun_hit.mp3"
						);
						fireBulletOne(i,j,angle,bulletPoint,lengthVector);
						break;
					}
					//µÚ¶ş¸ö·ÀÓùËş¹¥»÷¹ÖÊ±µ÷ÓÃ¼õÑªµÄ·½·¨
					else if(weapon->id==2)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
						(
							"sf_laser_beam.mp3"
						);
						fireBulletTwo(i,j,angle,bulletPoint);
						weapon->fireing();
						break;
					}
					//µÚÈı¸ö·ÀÓùËş¹¥»÷¹ÖÊ±µ÷ÓÃ¼õÑªµÄ·½·¨
					else if (weapon->id==3)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
						(
							"sf_rocket_launch.mp3"
						);
						fireBulletThree(i,j,angle,bulletPoint);
						weapon->fireing();
						break;
					}

					//µÚËÄ¸ö·ÀÓùËşµÄ¹¥»÷
					else if(weapon->id==4)
					{
						//³õÊ¼»¯·ÀÓùËşµÄĞı×ª½Ç¶È
						weapon->setRotation(0);
						//³õÊ¼»¯·ÀÓùËşµÄ½Ç¶È
						weapon->angle=0;
						//´´½¨Ò»¸ö×Óµ¯¶ÔÏó
						Sprite* bullet = Sprite::create("ring_blue.png");
						float bulletX=bullet->getContentSize().width/2;
						//À©´óµÄ±¶Êı
						float scaleX=weapon->confines/bulletX;
						//ÉèÖÃ×Óµ¯µÄÎ»ÖÃ
						bullet->setPosition(weapon->getPosition());
						//½«×Óµ¯Ìí¼Óµ½²¼¾°ÖĞ
						this->addChild(bullet,4);
						//ÉèÖÃ×Óµ¯µÄÍ¸Ã÷¶È
						bullet->setOpacity(80);
						//ÉèÖÃ×Óµ¯Îª¿É¼û
						bullet->setVisible(true);
						//ÉèÖÃÒ»¸ö¾«ÁéµÄÌØĞ§
						ActionInterval *act=ScaleTo::create(1.5f,scaleX);
						ActionInterval *activeFade=FadeOut::create(2.0f);
						bullet->runAction(
							Sequence::create(
						Spawn::createWithTwoActions
												(
													act,
													activeFade
												),
								CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
								NULL
								)

						);
						weapon->fireing();
						//¹ÖµôÑª
						monster->cutBlood(weapon->hurt);
						//Èç¹û¹ÖµÄÑªĞ¡ÓÚ0
						if(monster->blood<=0)
						{
							//ÄÃµ½¹ÖµÄÎ»ÖÃ
							Point pointMonster=monster->getPosition();
							//ÄÃµ½¹ÖµÄÂ·¾¶
							vector <Point > tempSelfWay = monster->selfWay;
							//ÄÃµ½¹ÖÒÑ¾­×ßµÄÂ·¾¶
							int tempWay = monster->way;
							//Èç¹û¹ÖµÄidÎª3
							if(monster->id==3)
							{
								//ÉèÖÃÃªµã
								Point Achorpoint=(Point(0.5,0.4));
								for(int i=0;i<2;i++)
								{
									//´´½¨Á½¸öĞÂµÄ¹Ö
									Monsters* mon = Monsters::create(6,tempSelfWay);
									//ĞÂ¹ÖÄÃµ½ÀÏ¹ÖÒÑ¾­×ßµÄÂ·¾¶
									mon->way=tempWay;
									//ÉèÖÃ¹ÖµÄÎ»ÖÃ
									mon->setPosition(pointMonster);
									//ÉèÖÃ¹ÖµÄÃªµã
									mon->setAnchorPoint(Achorpoint);
									Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
									//°Ñ¹ÖÌí¼Óµ½¹ÖÊı×éÀï
									arrMon->addObject(mon);
									//½«¹ÖÌí¼Óµ½²¼¾°ÖĞ
									this->addChild(mon,6);
									//µ÷ÓÃ¹ÖÒÆ¶¯µ½ÖÕµãµÄ·½·¨
									monsterRun(mon);
								}
							}
							//¶¨ÒåÒ»¸öÁÙÊ±´æ·Å¹ÖËÀºó½ğ±ÒµÄ±äÁ¿
							int tempMoney = monster->id*10;
							//×ÜµÄ½ğ±ÒÊı¼ÓÉÏÁÙÊ±ËùµÃµÄµÈÓÚµ±Ç°×ÜµÄ½ğ±Ò
							money+=tempMoney;
							//¶¨ÒåÒ»¸öÁÙÊ±´æ·Å¹ÖËÀºóËùµÃ·ÖÊıµÄ±äÁ¿
							int tempScore = monster->id*15;
							//×ÜµÄ·ÖÊı¼ÓÉÏÁÙÊ±ËùµÃµÄµÈÓÚµ±Ç°×ÜµÄ·ÖÊı
							score+=tempScore;
							//¹ÖËÀÊ±Ìí¼ÓÒ»¸öÌØĞ§
							this->addParticle1(monster->getPosition(),monster->id,1);
							//²¥·ÅÒôĞ§
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
							//É¾³ı³¡¾°ÖĞµÄ¹Ö
							this->removeChild(monster);
							//É¾³ı¹ÖÊı×éÖĞµÄ¹Ö
							arrMon->removeObject(monster);
							std::string overStr = "$";
							char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
							snprintf(a, 6, "%d",money);
							//¸üĞÂÏÔÊ¾½ğ±ÒµÄÎÄ±¾±êÇ©
							moneyL->setString((overStr+a).c_str());
							char b[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
							snprintf(b, 6, "%d",score);
							//¸üĞÂÏÔÊ¾×Ü·ÖÊıµÄÎÄ±¾±êÇ©
							scoreL->setString(b);
						}
					}
				}
			}
		}
	}
}

//µÚÒ»¸ö·ÀÓùËş¹¥»÷
void GameLayer::fireBulletOne(int weap,int target,float dirction,Point position,float lengthVector)
{
	if(this->bulletData[target]==0)
	{
		this->bulletData[target]=1;
	}
	//»ñÈ¡Òª¹¥»÷µÄ¹Ö¶ÔÏó
	Monsters* monster = (Monsters*)arrMon->objectAtIndex(target);
	//»ñÈ¡·ÀÓùËşµÄĞÅÏ¢
	Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(weap);
	//·¢Éä×Óµ¯µÄÊıÁ¿Óë·ÀÓùËşµÄµÈ¼¶ÓĞ¹Ø
	int count[4]={1,2,3,3};
	//¹¥»÷×Óµ¯µÄÑÓ³Ù
	float delay[3]={0.01,0.1,0.05};
    
	//¸ù¾İ·ÀÓùËşµÄµÈ¼¶À´È·¶¨Òª·¢Éä×Óµ¯µÄÊıÁ¿ºÍÎ»ÖÃ
    Point* positionByLevel=new Point[count[weapon->level-1]];
    
	//Èç¹û·ÀÓùËşµÄµÈ¼¶Îª1£¬È·¶¨Ã¿·¢×Óµ¯µÄ³õÊ¼Î»ÖÃ
	if(weapon->level==1)
	{
		positionByLevel[0]=position;
	}
	//Èç¹û·ÀÓùËşµÄµÈ¼¶Îª2£¬·¢ÉäÁ½·¢×Óµ¯
	else if(weapon->level==2)
	{
		//ÉèÖÃÁ½·¢×Óµ¯Æ«Àë10¶È
		Point vacter1=ccpForAngle(dirction+(10*3.1415926/180));
		Point vacter2=ccpForAngle(dirction-(10*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		vacter2=ccpNormalize(vacter2);
		//È·¶¨×Óµ¯µÄ³õÊ¼·¢ÉäÎ»ÖÃ
		positionByLevel[0]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,26));
		positionByLevel[1]=ccpAdd(weapon->getPosition(),ccpMult(vacter2,26));
	}
	//Èç¹û·ÀÓùËşµÄµÈ¼¶Îª3¼¶»òÕß4¼¶
	else if(weapon->level==3||weapon->level==4)
	{
		//ÉèÖÃÈı·¢×Óµ¯Æ«Àë10¶È
		Point vacter1=ccpForAngle(dirction+(20*3.1415926/180));
		Point vacter2=ccpForAngle(dirction-(20*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		vacter2=ccpNormalize(vacter2);
		//È·¶¨×Óµ¯µÄ³õÊ¼·¢ÉäÎ»ÖÃ
		positionByLevel[0]=position;
		positionByLevel[1]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,26));
		positionByLevel[2]=ccpAdd(weapon->getPosition(),ccpMult(vacter2,26));
	}
	//·¢Éä×Óµ¯£¬×Óµ¯Ö±ÏßÒÆ¶¯£¬µ÷½ÚËÙ¶È¿ÉÒÔÃÖ²¹Æ«²î
	for(int i=0;i<count[weapon->level-1];i++)
	{
		//´´½¨Ò»¸ö×Óµ¯¶ÔÏó
		BulletSprite* bullet = BulletSprite::create("bullet.png",weapon->hurt,target);
		//ÉèÖÃ×Óµ¯µÄÎ»ÖÃ
		bullet->setPosition(positionByLevel[i]);
		//½«×Óµ¯Ìí¼Óµ½²¼¾°ÖĞ
		this->addChild(bullet,4);
		//¶¨ÒåÒ»¸öÊ±¼ä±äÁ¿
		float timeTo=lengthVector/weapon->confines;
		//ÉùÃ÷Ò»¸ö¶¯×÷
		ActionInterval* act=MoveTo::create(timeTo/5,monster->getPosition());
		//Ë³ĞòÖ´ĞĞ
		Sequence* seqer = Sequence::create
						(
							DelayTime::create(delay[i]),
							act,
							CallFuncN::create(CC_CALLBACK_1(GameLayer::cutBloodOne,this)),
								NULL
						);
		bullet->runAction(seqer);
		weapon->fireing();
	}
}

//¹ÖµôÑªµÄ·½·¨
void GameLayer::cutBloodOne(Node*node)
{
	//ÄÃµ½×Óµ¯¹¥»÷µÄÄ¿±ê¹Ö
	Monsters* monster=(Monsters*)arrMon->objectAtIndex(((BulletSprite*)node)->target);
	//µ÷ÓÃcutBlood·½·¨ÈÃ¹Ö¼õÑª
	monster->cutBlood(((BulletSprite*)node)->hurt);
	if(monster->blood<=0)
	{
		//¶¨ÒåÒ»¸öÁÙÊ±±äÁ¿´æ·Å¹ÖµÄÂ·¾¶
		vector <Point > tempSelfWay = monster->selfWay;
		//¶¨ÒåÒ»¸öÁÙÊ±±äÁ¿´æ·Å¸¸¹ÖÒÑ¾­×ßµÄÂ·¾¶
		int tempWay = monster->way;
		//»ñÈ¡¹ÖµÄÎ»ÖÃ
		Point pointMonster=monster->getPosition();
		//µÚÈıÖÖ¹ÖËÀºó»á´´½¨Á½¸öĞÂ¹Ö
		if(monster->id==3)
		{
			Point Achorpoint=(Point(0.5,0.4));
			//´´½¨Á½¸öĞÂµÄ¹Ö¶ÔÏó
			for(int i=0;i<2;i++)
			{
				//´´½¨¹Ö¶ÔÏó
				Monsters* mon = Monsters::create(6,tempSelfWay);
				//ÄÃµ½¸¸¹ÖÒÑ¾­×ßµÄÂ·¾¶
				mon->way=tempWay;
				//ÉèÖÃĞÂ¹ÖµÄÎ»ÖÃ
				mon->setPosition(pointMonster);
				//ÉèÖÃÃªµã
				Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
				//ÉèÖÃĞÂ¹ÖµÄÃªµã
				mon->setAnchorPoint(Achorpoint);
				//°Ñ¹ÖÌí¼Óµ½¹ÖÊı×éÀï
				arrMon->addObject(mon);
				//½«ĞÂ½¨µÄÁ½¸ö¹ÖÌí¼Óµ½²¼¾°ÖĞ
				this->addChild(mon,6);
				//µ÷ÓÃ¹ÖÒÆ¶¯µ½ÖÕµãµÄ·½·¨
				monsterRun(mon);
			}
		}
		//¶¨ÒåÒ»¸öÁÙÊ±±äÁ¿´æ·Å¹ÖËÀÊ±µÃµ½µÄ½ğ±Ò
		int tempMoney = monster->id*10;
		//×ÜµÄ½ğ±ÒÊı¼ÓÉÏ¹ÖËÀËùµÃµÄ½ğ±ÒÊıµÈÓÚµ±Ç°µÄ×Ü½ğ±ÒÊı
		money+=tempMoney;
		//¶¨ÒåÒ»¸öÁÙÊ±±äÁ¿´æ·Å¹ÖËÀÊ±µÃµ½µÄ·ÖÊı
		int tempScore = monster->id*15;
		//×ÜµÄ·ÖÊı¼ÓÉÏ¹ÖËÀÊ±µÃµ½µÄ·ÖÊıµÈÓÚµ±Ç°×ÜµÄ·ÖÊı
		score+=tempScore;
		//Ìí¼Ó¹ÖËÀÊ±µÄÌØĞ§
		this->addParticle1(monster->getPosition(),monster->id,1.0);
		//Ìí¼ÓÒôĞ§
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
		//É¾³ı¹Ö¶ÔÏó
		this->removeChild(monster);
		//É¾³ıÊı×éÖĞµÄ¹Ö
		arrMon->removeObject(monster);
		char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
		snprintf(a, 6, "%d",money);
		std::string overStr = "$";
		//¸üĞÂÏÔÊ¾µ±Ç°×Ü½ğ±ÒÊıµÄÎÄ±¾±êÇ©
		moneyL->setString((overStr+a).c_str());
		char b[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
		snprintf(b, 6, "%d",score);
		//¸üĞÂÏÔÊ¾µ±Ç°×Ü·ÖÊıµÄÎÄ±¾±êÇ©
		scoreL->setString(b);
	}
	//É¾³ı×Óµ¯¶ÔÏó
	this->removeChild(node);
}


//µÚ¶ş¸ö·ÀÓùËşµÄ¹¥»÷
void GameLayer::fireBulletTwo(int weap,int target,float dirction,Point position)
{
	//ÄÃµ½Ä¿±êÒ°¹Ö
	Monsters* monster = (Monsters*)arrMon->objectAtIndex(target);
	//ÄÃµ½·ÀÓùËş
	Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(weap);
	//»ñÈ¡Ò°¹Öµ±Ç°µÄÎ»ÖÃ
	Point pointMonster=monster->getPosition();
	//»ñÈ¡·ÀÓùËşµ±Ç°µÄÎ»ÖÃ
	Point pointWeapon=weapon->getPosition();
	//´æ·Å×Óµ¯¾«ÁéÍ¼Æ¬µÄÊı×é
	std::string bullet[4]={"weapon2-1.png","weapon2-2.png","weapon2-3.png","weapon2-4.png"};
	//´´½¨Ò»¸ö×Óµ¯¾«Áé¶ÔÏó
	bullet1 = Sprite::create(bullet[weapon->level-1].c_str());
	//ÉèÖÃ×Óµ¯µÄÃªµã
	bullet1 ->setAnchorPoint(Point(0,0.5));
	//ÉèÖÃ×Óµ¯µÄÎ»ÖÃ
	bullet1->setPosition(position);
	//½«×Óµ¯Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(bullet1,4);
	//·¢Éä×Óµ¯µÄ¶¯×÷ÌØĞ§
	bullet1->setRotation(-(dirction*180/3.1415926));
	bullet1 -> runAction(
				Sequence::create(
						DelayTime::create(0.1),
						CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
						NULL
						)
				);
	//±éÀú´æ·Å¹ÖµÄÊı×é£¬¼ÆËãËùÓĞ±»¼¤¹âÅöµ½µÄ¹Ö
	for(int k=0;k<arrMon->count();k++)
	{
		//ÄÃµ½Êı×éÖĞµÄ¹Ö
		Monsters * mon= (Monsters*)arrMon->objectAtIndex(k);
		float x1=position.x;
		float y1=position.y;
		//ÄÃµ½¹Öµ±Ç°µÄx,y×ø±ê
		float x2=pointMonster.x;
		float y2=pointMonster.y;
		//»ñÈ¡¹Öµ±Ç°µÄx,y×ø±ê
		float x3=(mon->getPosition()).x;
		float y3=(mon->getPosition()).y;
		float slope = (y2-y1)/(x2-x1);
		//ÅĞ¶ÏÊÇ·ñÔÚ¼¤¹â²à
		if((x2-x1)*(x3-x1)>0&&(y2-y1)*(y3-y1)>0)
		{
			float monsterDistance=(y1-y2-slope*x1+slope*x3)/
					(sqrt(slope*slope+1));
			if(monsterDistance<30)
			{
				//µ÷ÓÃ¹Ö¼õÑªµÄ·½·¨
				mon->cutBlood(weapon->hurt);
				//Ìí¼ÓÒ»¸ö¹Ö±»»÷ÖĞÊ±µÄÌØĞ§
				this->addParticle(mon->getPosition(),monster->id,0.5,dirction*180/3.1415926);
			}
		}
		//Èç¹û¹ÖÃ»Ñª£¬ÔòÉ¾³ı
		if(mon->blood<=0)
		{	//»ñÈ¡Ò°¹ÖµÄÎ»ÖÃ
			Point pointMonster=monster->getPosition();
			//»ñÈ¡¹Öµ±Ç°×ßµÄÂ·¾¶
			vector <Point > tempSelfWay = mon->selfWay;
			//»ñÈ¡¹ÖÒÑ¾­×ßµÄÂ·¾¶
			int tempWay = mon->way;
			//Èç¹û¹ÖµÄidÎª3
			if(monster->id==3)
			{
				//ÉèÖÃ¹ÖµÄÃªµã
				Point Achorpoint=(Point(0.5,0.4));
				for(int i=0;i<2;i++)
				{
					//´´½¨2¸öĞÂµÄ¹Ö
					Monsters* mon = Monsters::create(6,tempSelfWay);
					//½«ÒÑ¾­×ßµÄÂ·¾¶´«¸øĞÂ¹Ö
					mon->way=tempWay;
					//ÉèÖÃĞÂ¹ÖµÄÎ»ÖÃ
					mon->setPosition(pointMonster);
					//ÉèÖÃĞÂ¹ÖµÄÃªµã
					mon->setAnchorPoint(Achorpoint);
					Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
					//°Ñ¹ÖÌí¼Óµ½¹ÖÊı×éÀï
					arrMon->addObject(mon);
					//½«¹ÖÌí¼Óµ½²¼¾°ÖĞ
					this->addChild(mon,6);
					//µ÷ÓÃ¹ÖÒÆ¶¯µ½ÖÕµãµÄ·½·¨
					monsterRun(mon);
				}
			}
			//¹ÖËÀºóºóµÃµ½¶ÔÓ¦µÄ½ğ±Ò
			int tempMoney = mon->id*10;
			//×ÜµÄ½ğ±ÒÊıÒª¼ÓÉÏ¹ÖËÀºóµÃµ½µÄ½ğ±ÒÊı
			money+=tempMoney;
			//¹ÖËÀºó»áµÃµ½¶ÔÓ¦µÄ·ÖÊı
			int tempScore = monster->id*15;
			//×ÜµÄ·ÖÊıÒª¼ÓÉÏ¹ÖËÀºóµÄ·ÖÊı
			score+=tempScore;
			//Ìí¼ÓÌØĞ§
			this->addParticle1(mon->getPosition(),monster->id,3.0);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
			//ÒÆ³ı¹Ö¶ÔÏó
			this->removeChild(mon);
			//ÒÆ³ıÊı×éÖĞµÄ¹Ö
			arrMon->removeObject(mon);
			std::string overStr = "$";
			char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
			snprintf(a, 6, "%d",money);
			moneyL->setString((overStr+a).c_str());
			char b[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
			snprintf(b, 6, "%d",score);
			scoreL->setString(b);
		}
	}
	//µ÷ÓÃWeaponÀàÖĞ·¢Éä×Óµ¯µÄ·½·¨
	weapon->fireing();
}

//µÚÈı¸ö·ÀÓùËşµÄ¹¥»÷
void GameLayer::fireBulletThree(int weap,int target,float dirction,Point position)
{
	//´Ó´æ·Å¹ÖµÄÊı×éÖĞÄÃµ½¹Ö
	Monsters* monster = (Monsters*)arrMon->objectAtIndex(target);
	//´Ó´æ·Å·ÀÓùËşµÄÊı×éÖĞÄÃµ½·ÀÓùËş
	Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(weap);
	int count[4]={1,2,2,3};
    Point* positionByLevel=new Point[count[weapon->level-1]];
    
	float angle[count[weapon->level-1]];
	//Èç¹ûµ±Ç°·ÀÓùËşµÄµÈ¼¶Îª1
	if(weapon->level==1)
	{
		Point vacter1=ccpForAngle(dirction-(15*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		positionByLevel[0]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,36));
		angle[0]=dirction;
	}
	//Èç¹ûµ±Ç°·ÀÓùËşµÄµÈ¼¶Îª3»òÕßÎª2
	else if(weapon->level==3||weapon->level==2)
	{
		Point vacter1=ccpForAngle(dirction+(15*3.1415926/180));
		Point vacter2=ccpForAngle(dirction-(15*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		vacter2=ccpNormalize(vacter2);
		positionByLevel[0]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,36));
		positionByLevel[1]=ccpAdd(weapon->getPosition(),ccpMult(vacter2,36));
		angle[0]=dirction+(15*3.1415926/180);
		angle[1]=dirction-(15*3.1415926/180);
	}
	//Èç¹û·ÀÓùËşµ±Ç°µÄµÈ¼¶Îª4
	else if(weapon->level==4)
	{
		//
		Point vacter1=ccpForAngle(dirction+(45*3.1415926/180));
		Point vacter2=ccpForAngle(dirction-(45*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		vacter2=ccpNormalize(vacter2);
		positionByLevel[0]=position;
		positionByLevel[1]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,36));
		positionByLevel[2]=ccpAdd(weapon->getPosition(),ccpMult(vacter2,36));
		angle[0]=dirction;
		angle[1]=dirction+(45*3.1415926/180);
		angle[2]=dirction-(45*3.1415926/180);
	}
	//¸ù¾İµ±Ç°·ÀÓùËşµÄµÈ¼¶À´ÉèÖÃµÚÈı¸ö·ÀÓùËş·¢Éä×Óµ¯µÄÊıÁ¿
	for(int i=0;i<count[weapon->level-1];i++)
	{
		//´´½¨Ò»¸ö×Óµ¯¶ÔÏó
		BulletSprite* bullet = BulletSprite::create("bullet2.png",weapon->hurt,target);
		//ÉèÖÃ×Óµ¯µÄÎ»ÖÃ
		bullet->setPosition(positionByLevel[i]);
		//ÉèÖÃ×Óµ¯µÄĞı×ª
		bullet->setRotation(-(angle[i]*180/3.1415926));
		//ÉèÖÃ×Óµ¯µÄĞı×ª
		bullet->angle = -(angle[i]*180/3.1415926);
		//½«×Óµ¯Ìí¼Óµ½²¼¾°ÖĞ
		this->addChild(bullet,4);
		//½«×Óµ¯Ìí¼Óµ½×Óµ¯Êı×éÖĞ
		arrBullet->addObject(bullet);
	}
}

//·¢Éä×Óµ¯µÄ·½·¨
void GameLayer::runBullet()
{
	//Èç¹û´æ·Å×Óµ¯µÄÊı×éµÄ³¤¶ÈÎª0»òÕßÓÎÏ·½áÊøÔò·µ»Ø
	if(arrBullet->count()==0||GameOver)
	{
		return;
	}
	//¸ú×ÙËã·¨
	for(int i=0;i<arrBullet->count();i++)
	{
		//»ñµÃ×Óµ¯¶ÔÏó
		BulletSprite *bullet = (BulletSprite*)arrBullet->objectAtIndex(i);
		//±ä»¯ÏòÁ¿
		Point vecter;
		//»ñÈ¡×Óµ¯µÄÎ»ÖÃ×ø±ê
		Point position=bullet->getPosition();
		//Èç¹ûÃ»ÓĞ¹ÖÔò±ä»¯ÏòÁ¿ÉèÎª0
		if(arrMon->count()==0)
		{
			vecter.x=0;
			vecter.y=0;
		}
		//Èç¹û×Óµ¯»÷ÖĞ¹ÖÊı×éÖĞµÄÄ¿±ê¶ÔÏó
		else if(bullet->target>arrMon->count())
		{
			//»ñÈ¡¹Ö¶ÔÏó
			Monsters* monster=(Monsters*)arrMon->objectAtIndex(1);
			//Ò°¹Öµ±Ç°Î»ÖÃµÄºá×ø±ê-×Óµ¯µ±Ç°Î»ÖÃµÄºá×ø±ê
			vecter.x=monster->getPosition().x-bullet->getPosition().x;
			//Ò°¹Öµ±Ç°Î»ÖÃµÄ×İ×ø±ê-×Óµ¯µ±Ç°Î»ÖÃµÄ×İ×ø±ê
			vecter.y=monster->getPosition().y-bullet->getPosition().y;
			//Èç¹û¼ÆËã³ö×Óµ¯Óë·ÀÓùËşµÄ¾àÀëĞ¡ÓÚ20Ôò»÷ÖĞÄ¿±ê¹Ö
			if(ccpLength(vecter)<20)
			{
				//Ò°¹Ö¼õÑª
				monster->cutBlood(bullet->hurt);
				//Èç¹û¹ÖÒÑ¾­Ã»ÓĞÑªÁË£¬ÔòÉ¾³ı¹Ö
				if(monster->blood<=0)
				{
					//»ñÈ¡¹Öµ±Ç°Î»ÖÃµÄ×ø±êµã
					Point pointMonster=monster->getPosition();
					//½«Â·¾¶ÖØĞÂ¸ø¹Ö
					vector <Point > tempSelfWay = monster->selfWay;
					//¶¨Òå¹ÖµÄÁÙÊ±Â·¾¶µÄ³¤¶È
					int tempWay = monster->way;
					//Èç¹û¹ÖµÄidÎª3
					if(monster->id==3)
					{
						//¶¨ÒåÃªµã
						Point Achorpoint=(Point(0.5,0.4));
						//µ±µÚ3ÖĞ¹Ö±ğ´òËÀºó»á²úÉúÁ½¸öĞÂµÄĞ¡¹Ö
						for(int i=0;i<2;i++)
						{
							//´´½¨ĞÂµÄĞ¡¹Ö
							Monsters* mon = Monsters::create(6,tempSelfWay);
							//°Ñµ±Ç°ÒÑ¾­×ßµÄÂ·¾¶¸øĞÂµÄ¹Ö
							mon->way=tempWay;
							//ÉèÖÃ¹ÖµÄÎ»ÖÃ
							mon->setPosition(pointMonster);
							//ÉèÖÃÃªµã
							mon->setAnchorPoint(Achorpoint);
							//ÉèÖÃÃªµã
							Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
							//°Ñ¹ÖÌí¼Óµ½¹ÖÊı×éÀï
							arrMon->addObject(mon);
							//½«¹ÖÌí¼Óµ½²¼¾°ÖĞ
							this->addChild(mon,6);
							//µ÷ÓÃ¹ÖÒÆ¶¯µ½ÖÕµãµÄ·½·¨
							monsterRun(mon);
						}
					}
					//ÄÃµ½¹ÖËÀºóµÃµ½µÄ½ğ±ÒÊı
					int tempMoney = monster->id*10;
					//×ÜµÄ½ğ±ÒÊı¼ÓÉÏ¹ÖËÀºóµÄ½ğ±ÒÊıµÈÓÚµ±Ç°½ğ±ÒÊı
					money+=tempMoney;
					//ÄÃµ½¹ÖËÀºóµÃµ½µÄ·ÖÊı
					int tempScore = monster->id*15;
					//×ÜµÄ·ÖÊı¼ÓÉÏ¹ÖËÀºóµÄ·ÖÊıµÈÓÚµ±Ç°·ÖÊı
					score+=tempScore;
					//Ìí¼Ó¹ÖËÀÊ±µÄÌØĞ§
					this->addParticle1(monster->getPosition(),monster->id,3.0);
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
					//É¾³ı¹Ö¶ÔÏó
					this->removeChild(monster);
					//É¾³ıÊı×éÖĞµÄ¹Ö
					arrMon->removeObject(monster);
					char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
					snprintf(a, 6, "%d",money);
					std::string overStr = "$";
					//ÉèÖÃ½ğ±ÒÊı
					moneyL->setString((overStr+a).c_str());
					char b[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
					snprintf(b, 6, "%d",score);
					//ÉèÖÃ·ÖÊı
					scoreL->setString(b);
				}
				//É¾³ı×Óµ¯Êı×éÖĞµÄ×Óµ¯
				arrBullet->removeObject(bullet);
				//É¾³ı×Óµ¯¾«Áé
				this->removeChild(bullet);

				return;
			}
		}
		else
		{
			//»ñÈ¡×Óµ¯Ö¸ÏòµÄÒ°¹Ö¶ÔÏó
			Monsters* monster=(Monsters*)arrMon->objectAtIndex(bullet->target);
			//Ò°¹Öµ±Ç°Î»ÖÃµÄºá×ø±ê-×Óµ¯µ±Ç°Î»ÖÃµÄºá×ø±ê
			vecter.x=monster->getPosition().x-bullet->getPosition().x;
			//Ò°¹Öµ±Ç°Î»ÖÃµÄ×İ×ø±ê-×Óµ¯µ±Ç°Î»ÖÃµÄ×İ×ø±ê
			vecter.y=monster->getPosition().y-bullet->getPosition().y;
			//Èç¹û¼ÆËã³ö×Óµ¯Óë·ÀÓùËşµÄ¾àÀëĞ¡ÓÚ20Ôò»÷ÖĞÄ¿±ê¹Ö
			if(ccpLength(vecter)<20)
			{
				monster->cutBlood(bullet->hurt);
				//Èç¹û¹ÖÃ»Ñª£¬ÔòÉ¾³ı
				if(monster->blood<=0)
				{
					//»ñÈ¡¹Öµ±Ç°µÄÎ»ÖÃ
					Point pointMonster=monster->getPosition();
					//ÄÃµ½¹Öµ±Ç°×ßµÄÂ·¾¶
					vector <Point > tempSelfWay = monster->selfWay;
					//ÄÃµ½¹ÖÒÑ¾­×ßµÄÂ·¾¶
					int tempWay = monster->way;
					//µÚÈıÖÖ¹ÖËÀºó»á´´½¨Á½¸öĞÂ¹Ö
					if(monster->id==3)
					{
						//ÉèÖÃÃªµã
						Point Achorpoint=(Point(0.5,0.4));
						//Í¨¹ıforÑ­»·´´½¨Á½¸öĞÂµÄ¹Ö
						for(int i=0;i<2;i++)
						{
							//¸ù¾İidºÍÂ·¾¶´´½¨ĞÂµÄ¹Ö
							Monsters* mon = Monsters::create(6,tempSelfWay);
							//ÄÃµ½´ó¹ÖÒÑ¾­×ßµÄÂ·
							mon->way=tempWay;
							//ÉèÖÃĞÂ¹ÖµÄÎ»ÖÃ
							mon->setPosition(pointMonster);
							//ÉèÖÃÃªµã
							mon->setAnchorPoint(Achorpoint);
							Achorpoint=ccp(Achorpoint.x+0.2,Achorpoint.y+0.2);
							//°ÑĞÂ¹ÖÌí¼Óµ½¹ÖÊı×éÀï
							arrMon->addObject(mon);
							//½«ĞÂ¹ÖÌí¼Óµ½²¼¾°ÖĞ
							this->addChild(mon,6);
							//µ÷ÓÃ¹ÖÒÆ¶¯µ½ÖÕµãµÄ·½·¨
							monsterRun(mon);
						}
					}
					//¶¨ÒåÒ»¸öÁÙÊ±´æ·Å¹ÖËÀºóËùµÃ½ğ±ÒµÄ±äÁ¿
					int tempMoney = monster->id*10;
					//¸üĞÂ×ÜµÄ½ğ±ÒÊı
					money+=tempMoney;
					//¶¨ÒåÒ»¸öÁÙÊ±´æ·Å¹ÖËÀºóËùµÃ·ÖÊıµÄ±äÁ¿
					int tempScore = monster->id*15;
					//¸üĞÂ×ÜµÄ·ÖÊı
					score+=tempScore;
					//Ìí¼Ó¹ÖËÀÊ±µÄÌØĞ§
					this->addParticle1(monster->getPosition(),monster->id,3.0);
					//²¥·Å¹ÖËÀÊ±µÄÒôĞ§
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
					//É¾³ı¹Ö¶ÔÏó
					this->removeChild(monster);
					//É¾³ı¹ÖÊı×éÖĞµÄ¹Ö
					arrMon->removeObject(monster);
					char a[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
					snprintf(a, 6, "%d",money);
					std::string overStr = "$";
					moneyL->setString((overStr+a).c_str());
					char b[6];//°Ñint ĞÍµÄ·ÖÊı×ª»»³ÉstringĞÍµÄ È»ºóset
					snprintf(b, 6, "%d",score);
					scoreL->setString(b);
				}
				//É¾³ı×Óµ¯Êı×éÖĞµÄ×Óµ¯
				arrBullet->removeObject(bullet);
				//É¾³ı×Óµ¯¶ÔÏó
				this->removeChild(bullet);

				return;
			}
		}
		//ÅĞ¶Ï×Óµ¯ÊÇ·ñ³¬³öÆÁÄ»£¬Èç¹û³¬³öÔò½«ÆäÉ¾³ı
		if(position.x>800||position.y>480||position.x<0||position.y<0)
		{
			//É¾³ı×Óµ¯Êı×éÖĞµÄ×Óµ¯
			arrBullet->removeObject(bullet);
			//É¾³ı×Óµ¯¶ÔÏó
			this->removeChild(bullet);

			return;
		}
		Point vector = ccpForAngle ((bullet->angle)*3.1415926/180);
		Point speed=ccpMult(ccpNormalize(ccp(vecter.x+vector.x/15,vecter.y+vector.y/15)),6);
		bullet->setPosition(ccpAdd(bullet->getPosition(),speed));
		float angle = ccpToAngle(speed);
		bullet->setRotation(-(angle*180/3.1415926));
		//ÉèÖÃ×Óµ¯µÄ½Ç¶È
		bullet->angle=angle;
	}
}

//É¾³ıËùÓĞÉùÃ÷¹ıµÄ¾«Áé¶ÔÏó
void GameLayer::removeSprite(Node*node)
{
	this->removeChild(node);
}

//Ìí¼Ó·ÀÓùËş¾«Áé¶ÔÏó
void GameLayer::addMenuSprite()
{
	//Ìí¼Ó±íÊ¾½ğ±Ò·ûºÅµÄ¾«Áé¶ÔÏó
	Sprite* sell = Sprite::create("sell.png");
	//ËÄÖÖÎäÆ÷¾«Áé°´Å¥
	onePlayer = Weapon::create("button_0.png",1);
	twoPlayer = Weapon::create("button_1.png",2);
	threePlayer = Weapon::create("button_2.png",3);
	fourPlayer = Weapon::create("button_3.png",4);
	//´´½¨±íÊ¾Éı¼¶¼ıÍ·µÄ¾«Áé¶ÔÏó
	Sprite* update = Sprite::create("update.png");
	//ÉèÖÃÉı¼¶°´Å¥Îª²»¿É¼û
	update->setVisible(false);
	//ÉèÖÃ±íÊ¾ÂôµôÎäÆ÷µÄÊÕÈë½ğ±Ò°´Å¥Îª²»¿É¼û
	sell->setVisible(false);

	//ÉèÖÃÁù¸ö¾«Áé¶ÔÏóµÄÎ»ÖÃ
	sell->setPosition(Point(730,68));
	onePlayer->setPosition(Point(750,136));
	twoPlayer->setPosition(Point(750,204));
	threePlayer->setPosition(Point(750,272));
	fourPlayer->setPosition(Point(750,340));
	update->setPosition(Point(730,408));

	//½«4¸öÎäÆ÷²Ëµ¥°´Å¥Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(onePlayer, 3);
	this->addChild(twoPlayer, 3);
	this->addChild(threePlayer, 3);
	this->addChild(fourPlayer, 3);
	//½«¾«Áé¶ÔÏóÌí¼Óµ½²¼¾°ÖĞ
	this->addChild(sell, 3);
	this->addChild(update, 3);

	//½«4¸öÎäÆ÷²Ëµ¥°´Å¥Ìí¼Óµ½ÏàÓ¦µÄÊı×éÀï
	arrMenu->addObject(onePlayer);
	arrMenu->addObject(twoPlayer);
	arrMenu->addObject(threePlayer);
	arrMenu->addObject(fourPlayer);
	//½«½ğ±Ò¾«Áé¶ÔÏóÌí¼Óµ½ÏàÓ¦µÄÊı×éÀï
	arrSellUpdate->addObject(sell);
	//½«Éı¼¶¾«Áé¶ÔÏóÌí¼Óµ½²¼¾°ÖĞ
	arrSellUpdate->addObject(update);
}

//Ìí¼ÓËùÓĞlabel
void GameLayer::addLabel()
{
	//´´½¨Ò»¸ötempScoreÎÄ±¾±êÇ©£¨ÁÙÊ±·ÖÊı£©
	scoreL = LabelTTF::create("0", "Arial",28);
	//´´½¨Ò»¸öÌØĞ§²¢²¥·Å
	ActionInterval *act= RotateBy::create(0.1,-90);
	scoreL->runAction(act);
	//ÉèÖÃ±êÇ©×ÖÌåµÄÑÕÉ«
	scoreL->setColor (ccc3(255,255,255));
	//ÉèÖÃÎÄ±¾±êÇ©µÄÎ»ÖÃ
	scoreL->setPosition(Point(40,60));
	//½«ÎÄ±¾±êÇ©Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(scoreL,3);

	//´´½¨Ò»¸öÓÃÓÚÏÔÊ¾»ØºÏÊıµÄÎÄ±¾±êÇ©
	passL = LabelTTF::create("1", "Arial",28);
	//ÉèÖÃ¶¯×÷µÄ¼ä¸ô
	ActionInterval *act1= RotateBy::create(0.1,-90);
	passL->runAction(act1);
	//ÉèÖÃ±êÇ©×ÖÌåµÄÑÕÉ«
	passL->setColor (ccc3(255,255,255));
	//ÉèÖÃÎÄ±¾±êÇ©µÄÎ»ÖÃ
	passL->setPosition(Point(40,240));
	//½«ÎÄ±¾±êÇ©Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(passL,3);

	//´´½¨Ò»¸öÓÃÓÚÏÔÊ¾½ğÇ®µÄÎÄ±¾±êÇ©
	moneyL = LabelTTF::create("$280", "Arial",28);
	//´´½¨Ò»¸öÌØĞ§²¢²¥·Å
	ActionInterval *act2= RotateBy::create(0.1,-90);
	moneyL->runAction(act2);
	//ÉèÖÃ±êÇ©×ÖÌåµÄÑÕÉ«
	moneyL->setColor (ccc3(255,255,255));
	//ÉèÖÃÎÄ±¾±êÇ©µÄÎ»ÖÃ
	moneyL->setPosition(Point(40,410));
	//½«ÎÄ±¾±êÇ©Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(moneyL,3);

	//´´½¨Ò»¸öÓÃÓÚÏÔÊ¾ÉúÃüÖµµÄtenÎÄ±¾±êÇ©
	tenL = LabelTTF::create("18", "Arial",28);
	//´´½¨Ò»¸öÌØĞ§²¢²¥·Å
	ActionInterval *act3= RotateBy::create(0.1,-90);
	tenL->runAction(act3);
	//ÉèÖÃ±êÇ©×ÖÌåµÄÑÕÉ«
	tenL->setColor (ccc3(255,255,255));
	//ºá×Å¿´µÄx£¬y
	Point tar = tmxLayer->positionAt(Point(targetAll[0][1],targetAll[0][0]));
	//½«Ä¿±êµãµÄ×ø±ê×ª»»µ½ÊÀ½ç×ø±êÏµÖĞ
	Point targetWorld = tmxLayer->convertToWorldSpaceAR(Point(tar.x+trans.x,tar.y+trans.y));
	//ÉèÖÃÎÄ±¾±êÇ©µÄÎ»ÖÃ
	tenL->setPosition(targetWorld);
	//½«ÎÄ±¾±êÇ©Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(tenL,6);

	//´´½¨Ò»¸öupdateMoneyÎÄ±¾±êÇ©
	uMoneyL = LabelTTF::create("$", "Arial",28);
	//½«ÎÄ±¾±êÇ©ÉèÖÃÎª²»¿É¼û
	uMoneyL->setVisible(false);
	//´´½¨²¢²¥·ÅÒ»¸öÌØĞ§
	ActionInterval *act4= RotateBy::create(0.1,-90);
	uMoneyL->runAction(act4);
	//ÉèÖÃ±êÇ©×ÖÌåµÄÑÕÉ«
	uMoneyL->setColor (ccc3(255,255,255));
	//ÉèÖÃÎÄ±¾±êÇ©µÄÎ»ÖÃ
	uMoneyL->setPosition(Point(760,408));
	//½«ÎÄ±¾±êÇ©Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(uMoneyL,3);

	//´´½¨Ò»¸ösellMoneyÎÄ±¾±êÇ©
	sMoneyL = LabelTTF::create("$", "Arial",28);
	//½«ÎÄ±¾±êÇ©ÉèÖÃÎª²»¿É¼û
	sMoneyL->setVisible(false);
	//´´½¨Ò»¸öÌØĞ§²¢²¥·Å
	ActionInterval *act5= RotateBy::create(0.1,-90);
	sMoneyL->runAction(act5);
	//ÉèÖÃ±êÇ©×ÖÌåµÄÑÕÉ«
	sMoneyL->setColor (ccc3(255,255,255));
	//ÉèÖÃÎÄ±¾±êÇ©µÄÎ»ÖÃ
	sMoneyL->setPosition(Point(760,68));
	//½«ÎÄ±¾±êÇ©Ìí¼Óµ½²¼¾°ÖĞ
	this->addChild(sMoneyL,3);
}

//Ò°¹Öµ½ÖÕµãÊ±µÄÌØĞ§
void GameLayer::addParticle2(Point point,float time)
{
	if(!DialogLayer::isParticle)
	{
		return;
	}
	int countVar=rand()%10;
	int angle=0;
	for(int i=0;i<55+countVar;i++)
	{
		float timeVar=(rand()%10)/10.0;
		float angleVar=(rand()%10)/10.0;
		//´´½¨Ò»¸ö·¢¹âÌØĞ§µÄ¾«Áé
		Sprite* particle= Sprite::create("white.png");
		//ÉèÖÃÃªµã
		particle->setAnchorPoint(Point(0,0.5));
		//ÉèÖÃÎ»ÖÃ
		particle->setPosition(point);
		//ÉèÖÃ´óĞ¡
		particle->setScale(1.0);
		particle->setRotation(-(angle+angleVar));
		Point vocter=ccpForAngle((angle+angleVar)*3.1415926/180);
		int lange=rand()%200;
		angle+=11;
		//½«¾«Áé¶ÔÏóÌí¼Óµ½²¼¾°ÖĞ
		this->addChild(particle,5);
		//Ë³ĞòÖ´ĞĞ¶¯×÷
		particle->runAction(
			Sequence::create(
					Spawn::createWithTwoActions
					(
						MoveBy::create(1+timeVar,Point((200+lange)*vocter.x,(200+lange)*vocter.y)),
						FadeOut::create(1+timeVar)
					),
					CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
					NULL
			)
		);
	}

	//´´½¨Ò»¸öÌØĞ§¾«Áé¶ÔÏó
	cc = Sprite::create("fire1.png");
	//ÉùÃ÷Ò»¸ö½¥ÏÖµÄ¶¯×÷
	ActionInterval *act1=FadeIn::create(time*4/3);
	//ÉùÃ÷Ò»¸ö½¥ÒşµÄ¶¯×÷
	ActionInterval *activeFade1=FadeOut::create(time*4/3);
	//ÉèÖÃ¶¯×÷Ö´ĞĞµÄÎ»ÖÃ
	cc->setPosition(point);
	//ÉèÖÃ¾«ÁéµÄ´óĞ¡
	cc->setScale(6.0);
	//½«¾«ÁéÌí¼Óµ½²¼¾°ÖĞ
	this->addChild(cc,6);
	//Ë³ĞòÖ´ĞĞ¶¯×÷
	cc->runAction(Sequence::create(
			Spawn::createWithTwoActions
						(
							act1,
							activeFade1
						),
						CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
						NULL
			)
	);
}

//ÓÎÏ·½áÊøÊ±µ÷ÓÃµÄ·½·¨
void GameLayer::loseGame()
{
	//²¥·ÅÓÎÏ·½áÊøµÄÒôĞ§
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
	(
		"sf_game_over.mp3"
	);
	//µ÷ÓÃ¼Æ·Ö°å
	AchieveLayer* al = new AchieveLayer();
	al->saveScore(score);
	//±éÀú·ÀÓùËşÊı×é
	for(int i=0;i<arrWeap->count();i++)
	{
		//ÉùÃ÷Ò»¸ö´æ·Å4¸öÊ±¼äµÄÒ»Î¬Êı×é
		int a[4]={4,2,1,3};
		//ÄÃµ½µ±Ç°µÄ·ÀÓùËş¶ÔÏó
		Weapon* weap=(Weapon*)arrWeap->objectAtIndex(i);
		//Ìí¼Ó±¬Õ¨µÄÌØĞ§
		this->addParticle1(weap->getPosition(),a[weap->id-1],5.0);
		//É¾³ı·ÀÓùËş¶ÔÏó
		this->removeChild(weap,true);
	}
	//É¾³ı·ÀÓùËşÊı×éÖĞµÄËùÓĞ¶ÔÏó
	arrWeap->removeAllObjects();

	//±éÀú´æ·Å¹ÖµÄÊı×é
	for(int i=0;i<arrMon->count();i++)
	{
		//ÄÃµ½µ±Ç°µÄËùÓĞ¹Ö
		Monsters* mon=(Monsters*)arrMon->objectAtIndex(i);
		//Ìí¼Ó±¬Õ¨ÌØĞ§
		this->addParticle1(mon->getPosition(),mon->id,5.0);
		//É¾³ı¹Ö¶ÔÏó
		this->removeChild(mon,true);
	}
	//É¾³ı´æ·Å¹ÖÊı×éÖĞµÄËùÓĞ¹Ö¶ÔÏó
	arrMon->removeAllObjects();
	//É¾³ıËùÓĞ´æ·ÅÔÚ¹Ö¶¯×÷Êı×éÖĞµÄ¶ÔÏó
	arrAction->removeAllObjects();

	//±éÀúËùÓĞ´æ·Å×Óµ¯µÄÊı×é
	for(int i=0;i<arrBullet->count();i++)
	{
		//ÄÃµ½×Óµ¯¶ÔÏó
		BulletSprite* bullet=(BulletSprite*)arrBullet->objectAtIndex(i);
		//Ìí¼Ó±¬Õ¨ÌØĞ§
		this->addParticle1(bullet->getPosition(),1,5.0);
		//É¾³ı×Óµ¯¾«Áé
		this->removeChild(bullet,true);
	}
	//É¾³ı×Óµ¯Êı×éÖĞµÄËùÓĞ¶ÔÏó
	arrBullet->removeAllObjects();
	//Ìí¼ÓÌØĞ§
	this->addParticle2(endWorld,5.0);

    //´´½¨Ò»¸ö¾«Áé¶ÔÏó£¬¡°×î¸ß·ÖÊı¡±
    Sprite *gameOverSprite = Sprite::create("gameOver.png");
	//ÉèÖÃ¾«Áé¶ÔÏóµÄÎ»ÖÃ
    gameOverSprite->setPosition(Point(850,240));
	//½«±³¾°¾«ÁéÌí¼Óµ½²¼¾°ÖĞ
	this->addChild(gameOverSprite,GAME_LEVEL_CGQ+4);
	gameOverSprite->runAction(MoveTo::create(4.0f,Point(400,240)));
	//Í£Ö¹±³¾°ÒôÀÖµÄ²¥·Å
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic
	(
		"bg_music.mp3"
	);
}
