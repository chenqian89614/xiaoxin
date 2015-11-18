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

#define CELL_BORDER        (28)	//�����α߳�
#define CELL_HEIGHT        (50)	//�����θ�����ͼ�߶� �������α߳�����sin(60)���Ƶõ�

enum
{
	kTagTileMap
};

//���������㷨��������������Ķ�ά����
int sequenceZ[2][6][2] = 	//col, row
{
		{//ż����
				{-1, -1},
				{0, -1},
				{1, 0},
				{-1, 0},
				{-1, 1},
				{0, 1}
		},
		{//������
				{1, -1},
				{0, -1},
				{-1, 0},
				{1, 0},
				{0, 1},
				{1, 1}
		}
};
//������row, col
static int source[]={5, 15};
//Ŀ�ĵ��row, col
static int targetAll[1][2] ={{3, 2}};

bool GameLayer::isPause=false;
//������col, row
int* target;
//0����δȥ����1����ȥ��
int** visited;
//A*�����ȼ�����
typedef int(*INTPARR)[2];
//A*�����ȼ����������еıȽ������ڲ������ˣ�������������ΪC++�еĺ�������
struct cmp
{
	bool operator()(INTPARR o1, INTPARR o2)
	{
		int* t1 = o1[1];
		int* t2 = o2[1];

		//���ؿ��޾���
		int a = visited[o2[0][1]][o2[0][0]]+abs(t1[0]-target[0])+abs(t1[1]-target[1]);
		int b = visited[o2[0][1]][o2[0][0]]+abs(t2[0]-target[0])+abs(t2[1]-target[1]);

		return a>b;
	}
};
//A*�����ȼ�����
priority_queue<INTPARR,vector<INTPARR>,cmp>* astarQueue;
GameLayer::GameLayer(){}
//��������
GameLayer::~GameLayer()
{
	//�ͷ��ڴ�
	freeMemory();
	//�ͷŵ�ͼ
	for(int i=0;i<row;i++)
	{
		delete []MAP_DATA[i];
	}
	delete []MAP_DATA;
}

//��ʼ����
bool GameLayer::init()
{
	//���ø���ĳ�ʼ��
	if ( !Layer::init() )
	{
		return false;
	}

	//����һ��������󣬰���background.pngͼƬ
	auto gbsprite = Sprite::create("back.png");
	//���þ�������λ��
	gbsprite->setPosition(Point(400,240));
	//��������ӵ�������
	this->addChild(gbsprite,BACKGROUND_LEVEL_CGQ);

	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_button_press.mp3"
	);

    //�������A*�㷨
	astarQueue = NULL;
	hm = NULL;
	//��ȡ��ǰ��Ļ�Ĵ�С
	auto winSize = Director::getInstance()->getWinSize();
	//����TMX��ͼ
	auto map = TMXTiledMap::create("MyTilesMap"+
			StringUtils::format("%d",ChooseLayer::modeLevel)+".tmx");
	//���õ�ͼ��ê��
    map->setAnchorPoint(Point(0,1.0));
	//���õ�ͼλ��
    map->setPosition(Point(0, winSize.height-3));
	//����ͼ��ӵ�������
	addChild(map,BACKGROUND_LEVEL_CGQ, kTagTileMap);
	//��õ�ͼ�Ŀ�Ⱥ͸߶�
	int mapWidth = map->getMapSize().width;
	int mapHeight = map->getMapSize().height;
	//����ͼ�Ŀ�Ⱥ͸߶�����Ϊ��ά������к���
	row = mapWidth;
	col = mapHeight;
	//������̬��ά����
	MAP_DATA = new int*[row];
	for(int i = 0; i<row; i++)
	{
		MAP_DATA[i] = new int[col];
	}

	//�õ���ͼ�е�layer
	tmxLayer = map->layerNamed("Layer 0");
	//���һ��ͼ���е�����ֵ
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			//�õ�layer��ÿһ��ͼ���gid
			unsigned int gid = tmxLayer->tileGIDAt(Point(i, j));
			//ͨ��gid�õ���ͼ���е����Լ�,���Լ������Լ�ֵ�Ե���ʽ���ڵ�
			auto tiledic = map->propertiesForGID(gid);
			//ͨ�����õ�value
			const String mvalue = tiledic.asValueMap()["value"].asString();
			//��mvalueת����int����
			int mv = mvalue.intValue();
			//��ʼ����ͼ�е�����
			MAP_DATA[i][j] = mv;

		}
	}
	//���ÿ���ݣ������Ҫ�Ե�ͼ���зŴ����Сʱ���Ϳ���ʹ��
	auto children = tmxLayer->getChildren();
	SpriteBatchNode* child = NULL;
	for(Object* object:children)
	{
		child = static_cast<SpriteBatchNode*>(object);
		child->getTexture()->setAntiAliasTexParameters();
	}
	//��õ���ͼ��Ĵ�С��Ϊ���ڻ���ʱ�õ�ƫ������������Ƴ����������а��ͼ���ƫ�Ʋ�
	auto m_tamara = tmxLayer->tileAt(Point(0,0));
	auto texture = m_tamara->getTexture();
	auto blockSize = texture->getContentSize();
	trans = Point(blockSize.width/4,blockSize.height/2);

	//��������ͣ����ť����
	MenuItemImage *zanTingItem = MenuItemImage::create
	(
		"zanting.png",		//ƽʱ��ͼƬ
		"zanting.png",		//ѡ��ʱ��ͼ
		CC_CALLBACK_1(GameLayer::zanTing, this)
	);
	//������ͣ�˵���ť��λ��
	zanTingItem->setPosition(Point(40,140));

	//������ͣ�˵�����
	pMenu = Menu::create(zanTingItem,NULL);
	//���ò˵���λ��
	pMenu->setPosition(Point(0,0));
	//���˵���ӵ�������
	this->addChild(pMenu,DASHBOARD_LEVEL_CGQ);

	//�����յ㾫��
	targetSprite = Sprite::create("target.png");
	//���þ����λ��
	auto end = tmxLayer->positionAt(Point(targetAll[0][1],targetAll[0][0]));
	endWorld = tmxLayer->convertToWorldSpaceAR(Point(end.x+trans.x,end.y+trans.y));
	targetSprite->setPosition(endWorld);
	//���յ㾫�������ӵ�������
	this->addChild(targetSprite,GAME_LEVEL_CGQ+1);
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_swish.mp3"
	);
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_creep_die_0.mp3"
	);
	//������Ϸ��������Ч��Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_game_over.mp3"
	);
	//���ص�������̨�����ӵ�����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_rocket_launch.mp3"
	);
	//���ص�һ����̨�����ӵ�����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_minigun_hit.mp3"
	);
	//���صڶ�����̨�����ӵ�����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect
	(
		"sf_laser_beam.mp3"
	);

    //������Źֵ�����
    arrMon = Array::create();
    arrMon ->retain();
	//������Ź�action������
    arrAction = Array::create();
    arrAction ->retain();
    //�����������������
    arrWeap = Array::create();
    arrWeap ->retain();
    //������������˵�����
    arrMenu = Array::create();
    arrMenu ->retain();
    //������Ź�Bullet������
    arrBullet = Array::create();
    arrBullet ->retain();
    //������Ž�Ǯ������
    arrSellUpdate = Array::create();
    arrSellUpdate ->retain();

	//�������label
	addLabel();
	//��ӷ������˵�����
	addMenuSprite();
	//��ʼ���ܽ����
	money = 280;
	//��ʼ������ֵ
	ten = 18;
	//��ʼ��ʱ�䳣��
    TIME_MAIN=0.7 ;
	//��ʼ������������
	updateWeapon = NULL;
	//�����������ı�־λ
	WeaponUpdate = false;
	//��ʼ����Ϸ�����ı�־λΪfalse
	GameOver=false;
	//��ʼ��Ұ���ƶ��ı�־λΪfalse
	isMonsterRun = false;
	//��ʼ�������ֵı�־λ
	isfoundMonster = false;
    //�Ƴ��������������ı�־λ
    removeWeap = false;
    //��ʼ����Ϸ�йֵ�������
    pass = 0;
    //��ʼ���ܷ���Ϊ0
    score = 0;
	//���ö�ʱ�ص�ָ�������ɻ�
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//��ʱ����run����������Ϊ��λ
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::run), this, 1.0, false);
	//��ʱ����runBullet����������Ϊ��λ
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::runBullet), this, 0.002f, false);
	//��ʱ����attack����������Ϊ��λ
	sched->scheduleSelector(SEL_SCHEDULE(&GameLayer::attack), this, 0.3f, false);

	//�������㴥������
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//�����´�����
	listener->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	//��ʼ����ʱ�ص�onTouchMoved����
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	//��ʼ����ʱ�ص�onTouchEnded����
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//��ʼ������·���ı�־λΪfalse
	isCaulateOver = false;
	//�õ�Ŀ���
	target = targetAll[0];
	//����·��
	if(calculatePath())
	{
		printPath();
	}
	//��ʼ����������ֵķ�����Ȼ�����ready����
	foundMonsters();

	return true;
}

void GameLayer::zanTing(Object* pSender)
{
	//������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_button_press.mp3");
	//�ж�����Ч���ı�־λ
	if(!isPause)
	{
		//��ͣ��������
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		//��ȡ����
		Director *director = Director::getInstance();
		//����ִ����ͣ���ֵĹ���
		director->pause();
		//������ͣ����
		DialogLayer* dialogLayer = DialogLayer::create();
		//����λ��
		dialogLayer->setPosition(Point(0,0));
		//��ӵ�������
		this->addChild(dialogLayer,6);
		//��ͣ���ı�־λ
		isPause=true;
	}
}

//����·���ķ���
bool GameLayer::calculatePath()
{
	//�ͷ��ڴ�
	freeMemory();
	//��ʼ�������б�
	initForCalculate();
	//��ʼ����ͼ
	initVisitedArr();
	//��A*�㷨����·��
	bool b=BFSAStar();
	return b;
}

//�ͷ��ڴ�
void GameLayer::freeMemory()
{
	//���hm�еļ�ֵ��
	if(hm != NULL)
	{
		hm->clear();
		delete hm;
		hm = NULL;
	}
	//��չ������A*�����е�ָ��
	if(astarQueue != NULL)
	{
		while(!astarQueue->empty())
		{
			astarQueue->pop();
		}
		delete astarQueue;
		astarQueue = NULL;
	}
	//�ͷŷ�������
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

//����֮ǰ��ʼ���������õ�������
void GameLayer::initForCalculate()
{
	//������̬��ά����
	visited = new int*[row];
	for(int i = 0; i<row; i++)
	{
		visited[i] = new int[col];
	}
	//A*���ȼ����бȽ���
	astarQueue = new priority_queue<INTPARR,vector<INTPARR>,cmp>();//A*�����ȼ�����
	//���·����¼
	hm = new map<string,int(*)[2]>();
}

//��ʼ��ȥ��δȥ��������
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

//�������A*�㷨BFSAStar
bool GameLayer::BFSAStar()
{
	//����һ����־λ
	bool flag = true;
	string str1;
	string str2;
	//��ʼ״̬
	int(*start)[2] = new int[2][2];
	start[0][0] = source[0];
	start[0][1] = source[1];
	start[1][0] = source[0];
	start[1][1] = source[1];
	//����ʼ��Ž�A*�����ȼ�������
	astarQueue->push(start);
	while(flag)
	{
		//���ջ����
		if(astarQueue->empty())
		{
			return false;
		}
		//�Ӷ���ȡ����
		int(*currentEdge)[2] = astarQueue->top();
		astarQueue->pop();
		//ȡ���˱ߵ�Ŀ�ĵ�
		int* tempTarget = currentEdge[1];
		//�ж�Ŀ�ĵ��Ƿ�ȥ������ȥ����ֱ�ӽ����´�ѭ��
		if(visited[tempTarget[1]][tempTarget[0]] != 0)
		{
			continue;
		}
		visited[tempTarget[1]][tempTarget[0]] = visited[currentEdge[0][1]][currentEdge[0][0]]+1;
		str1 = StringUtils::format("%d", tempTarget[0]);
		str2 = StringUtils::format("%d", tempTarget[1]);
		//��¼Ŀ�ĵ�ĸ��ڵ�
		hm->insert(map<string,int(*)[2]>::value_type(str1+":"+str2,currentEdge));
		//�ж��Ƿ��ҵ�Ŀ�ĵ�
		if(tempTarget[0] == target[0] && tempTarget[1] == target[1])
		{
			isCaulateOver= true;
			return isCaulateOver;
		}
		//�����п��ܵı������ȼ�����
		int currCol = tempTarget[0];
		int currRow = tempTarget[1];
		int(*sequence)[2] = NULL;
		//���ݵ�ǰͼ�������ż������ȷ�������ķ���
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
				//������ά����
				int(*tempEdge)[2] = new int[2][2];
				//����Ϊ��һ��Ŀ���
				tempEdge[0][0] = tempTarget[0];
				tempEdge[0][1] = tempTarget[1];
				tempEdge[1][0] = currCol+j;
				tempEdge[1][1] = currRow+i;
				//����ά������ӽ�A*�����ȼ�������
				astarQueue->push(tempEdge);
			}
		}
	}
}

//��ӡ���·��
void GameLayer::printPath()
{
	//�����ǰ��·��
	way.clear();

	string str1;
	string str2;
	//�������յ��������·��
	map<string, int(*)[2]>::iterator iter;
	int* temp = target;
	while(true)
	{
		str1 = StringUtils::format("%d", temp[0]);
		str2 = StringUtils::format("%d", temp[1]);
		string key = str1+":"+str2;
		//Ѱ�Ҷ�Ӧ��ֵ
		iter = hm->find(key);
		int(*tempA)[2] = iter->second;
		//�鵽Ԫ��
		if(iter != hm->end())
		{
			//�õ���ʼ�������
			Point start = tmxLayer->positionAt(Point(tempA[0][1],tempA[0][0]));
			//�õ�Ŀ��������
			Point end = tmxLayer->positionAt(Point(tempA[1][1],tempA[1][0]));
			//����ʼ��ת������������ϵ��
			Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
			//��Ŀ���ת����ʵ������ϵ��
			Point endWorld = tmxLayer->convertToWorldSpaceAR(Point(end.x+trans.x,end.y+trans.y));
			//��Ŀ�����ӵ�·����
			way.push_back(endWorld);
			CCLOG("endWorld.x=%f,endWorld.y=%f",endWorld.x,endWorld.y);
			//�Ŷ��ܶ�
			glLineWidth( 3.0f );
			//����·��
			cocos2d::ccDrawColor4F(0.0f, 0.0f, 0.0f, 1.0f);
			cocos2d::ccDrawLine(startWorld, endWorld);
		}
		//�ж��з񵽳�����
		if(tempA[0][0]==source[0]&&tempA[0][1]==source[1])
		{
			break;
		}
		//�߶ε��������
		temp = tempA[0];
	}
}

//��Ұ��ǰ��׼������
void GameLayer::ready()
{
	//������㾫��
	startSprite = Sprite::create("start.png");
	//���þ����λ��
	auto start = tmxLayer->positionAt(Point(source[1],source[0]));
	startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
	startSprite->setPosition(startWorld);
	//�����������ӵ�������
	this->addChild(startSprite,5);

	//����㾫������Ӱٷֱȶ�����Ч
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

//��Ұ��ǰ׼�������Ļص�����
void GameLayer::playGameCallback()
{
	//�Ƴ�����
	this->removeChild(left);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_swish.mp3");
	//���ƶ��ı�־λ����Ϊtrue
	isMonsterRun=true;
}

//��Ұ��ʱ��ʼ��Ҫ���ŵ�������Ч
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

//����ͼ�������к�ת��Ϊ��Ӧ���ӵ���ͼ����
Point GameLayer::fromColRowToXY(int col, int row)//��ڲ���//���ſ���x��y
{
	row++;
	Point start = tmxLayer->positionAt(Point(col,row));//���ſ���x��y
	Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
	return startWorld;
}
//�����ص�λ��ת��Ϊ��ͼ�������к�
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
	//8 �ǵ�ͼ����������0��ʼ����ʵ�ʿ�������Ҫ���ݾ�������޸�
	return ccp(j-1,9-i);
}

//ѡ���Ѿ����ڵ�ͼ�еķ�������������в���
bool GameLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	//move��ʱ��began����
	if(touchMove)
	{
		return false;
	}
	//�õ���ǰ���ص������
	Point point = pTouch->getLocation();
	//���������������
	if(!WeaponUpdate)
	{
		//������ŷ������˵����������
		for(int k = 0; k<arrMenu->count(); k++)
		{
			//�õ��������˵�����
			Weapon* pWeapon =(Weapon*)arrMenu->objectAtIndex(k);
			//��ȡ������������
			Point pp = pWeapon->getPosition();
			//����ǵ���˵�������
			if(abs(point.x- pp.x)<32&&abs(point.y- pp.y)<32)
			{
				//�õ�������Ĳ˵���������id
				int id = pWeapon->id;
				//�õ���װ�÷���������Ľ��
				int tempValue=pWeapon->value;
				//�õ����ص�ĵ�ͼ�����к�
				Point ccpxy = fromXYToColRow((int)point.x,(int)point.y);
				//�����к�ת��Ϊ��Ӧ�ĵ�ͼ��Ƭ������
				Point ccp = fromColRowToXY(ccpxy.x,ccpxy.y);
				//���Ǯ����
				if(money<tempValue)
				{
					return false;
				}
				//���ݵõ��Ĳ˵���������id����һ��������
				Weapon *oneTa =Weapon::create(id);
				//���÷�������λ��
				oneTa->setPosition(ccp);
				//����������ӵ�������
				this->addChild(oneTa,6);
				//���÷�����
				s_dic.setObject(oneTa, pTouch->getID());
				//���������ƶ��ı�־λ����Ϊtrue
				touchMove=true;

				return true;
			}
		}
	}else{
		//ѭ�����鿴ѡ������������ǳ���
		for(int k=0;k<arrSellUpdate->count();k++)
		{
			std::string overStr = "$";
			//����һ����ʱ������������¼����������ʱ����Ľ����
			int tempValue=updateWeapon->upValue;
			//���������
			if(abs(point.x-730)<32&&abs(point.y-408)<32)
			{
				//���Ǯ��������
				if(money<tempValue)
				{
					return false;
				}
				//�ܵĽ������ȥ��������������Ľ����
				money-=tempValue;
				//��int �͵�����ת����string�͵� Ȼ��set
				char a[6];
				snprintf(a, 6, "%d",money);
				//���µ�ǰ�ܽ����
				moneyL->setString((overStr+a).c_str());
				//����update����
				updateWeapon->update();

				return true;
			}
			//����ǳ��۷�����
			if(abs(point.x-730)<32&&abs(point.y-68)<32)
			{
				//�ܵĽ��������Ҫ���۷��������õĽ����
				money+=updateWeapon->sellValue;
				char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
				snprintf(a, 6, "%d",money);
				//�����ܵĽ����
				moneyL->setString((overStr+a).c_str());
				//����sellWeapon���������۷�����
				sellWeapon(updateWeapon);

				return true;
			}
		}
	}
	//��������ӷ�����������
	int k = 0;
	for(; k<arrWeap->count(); k++)
	{
		//�õ�ָ���ӷ�������ָ��
		Weapon* pWeapon =(Weapon*)arrWeap->objectAtIndex(k);
		//��ȡ��λ��
		Point ccWeapon = pWeapon->getPosition();
		//����ǵ�����ӷ�����
		if(abs(point.x-ccWeapon.x)<32&&abs(point.y-ccWeapon.y)<32)
		{
			Point ccpxy = fromXYToColRow((int)ccWeapon.x,(int)ccWeapon.y);
			//����Ѿ�ѡ����һ��������
			if(WeaponUpdate)
			{
				//����Ϊ���ɼ�
				(updateWeapon->getChildByTag(1))->setVisible(false);
			}
			//��ѡ�еķ�������Ҫ������
			updateWeapon=pWeapon;
			//ʹ�÷�����������ť�ɼ�
			setUpdateTrue();
			//�ƶ���־λ��Ϊfalse
			touchMove=false;

			return true;
		}
	}
	if(k==arrWeap->count())
	{
		//���÷������˵�����ɼ�
		setWeaponTrue();
		//�����ƶ��ı�־
		touchMove=false;
	}
	return false;
}

//�����ƶ��������ķ���
void GameLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	//������������λ�ã����Ƿ���·�����У����������¼���·��
	if(!touchMove)
	{
		return ;
	}
	//�õ���ǰ����λ�õ�����
	Point point = pTouch->getLocation();
	//���ݲ˵���������id����һ����ʾ������������Χ�ľ������
	Weapon* trSprite = (Weapon*)s_dic.objectForKey(pTouch->getID());
	//���ñ�ʾ������������Χ�ľ���ɼ�
	(trSprite->getChildByTag(1))->setVisible(true);
	//�õ����ص��Ӧ�ĵ�ͼ�����к�
	Point ccpxy = fromXYToColRow((int)point.x,(int)point.y);
	//�������к�ת��Ϊ��Ӧ��ͼ������
	Point ccp = fromColRowToXY(ccpxy.x,ccpxy.y);
	//���þ��������                     ���
	trSprite->setPosition(ccp);
}

//����̧��
void GameLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	//���������˵��������ı�־λΪfalse�򷵻�
	if(!touchMove)
	{
		return;
	}
	//��ȡ���ص�λ�õ�����
	Point point = pTouch->getLocation();
	//����һ����ʾ������Χ�ľ������
	Weapon* trSprite = (Weapon*)s_dic.objectForKey(pTouch->getID());
	//���ñ�ʾ������Χ�ľ��鲻�ɼ�
	(trSprite->getChildByTag(1))->setVisible(false);
	//�õ����ص��Ӧ�ĵ�ͼ�����к�
	Point ccpxy = fromXYToColRow((int)point.x,(int)point.y);
	//���õ�ͼ�����к�ת���ɶ�Ӧ��ͼ������
	Point ccp = fromColRowToXY(ccpxy.x,ccpxy.y);
	//������������õ�ͼ���ǵ�ͼ��ǽ
	if(MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]!=0)
	{
		//�Ƴ���������־λ�趨Ϊtrue
		removeWeap = true;
	}else//������õ�λ��Ϊ���Է��õ�λ��
	{
		int i=0;
		//ѭ��·�����飬�����Ƿ�Ϊ·���е�
		for(;i<way.size();i++)
		{
			//�õ�·���е�ÿ����
			Point ccpWay = (Point)way.at(i);
			//�����ǰ�ŷ������ĸ���Ϊ·���е�
			if(ccp.x==ccpWay.x&&ccp.y==ccpWay.y)
			{
				//���¼���·�����ѵ�ǰ������Ϊ���Էŷ������ֲ�������
				MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]=1;
				//����·������
				bool isCaulate=calculatePath();
				//��������ҵ�·��
				if(isCaulate)
				{
					//�ѻ�û���˸��ӵĹ����way����,�����µ�way
					printPath();
					//������Źֵ�����
					for(int j=0;j<arrMon->count();j++)
					{
						//�õ���ǰ�Ĺ�
						Monsters* mon = (Monsters*)arrMon->objectAtIndex(j);
						//�ڼ���·��
						int wayat = way.size()-i;
						//�����û�о����÷ŷ������ĸ���(-2Ϊ�Ӿ���ʱ���ϵĹ�ϵ���Ǿ�������)
						if(mon->way<wayat-2)
						{	//���µ�·������
							mon->selfWay=way;
						}
					}
					//���Ƴ��������ı�־λ����Ϊfalse
					removeWeap=false;
					//�ѷ�������ǰ���ĸ������и���Ч�������
					trSprite->pointColRow=ccpxy;
					break;
				}else
				{
					//���û�ҵ�·��,��ԭ����������Ϊ�ֿ�����
					MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]=0;
					//�Ƴ���������־λ�趨Ϊtrue
					removeWeap = true;

					break;
				}
			}
		}
		//ѭ��·��������ɣ���ǰ���Ӳ���·����������
		if(i==way.size())
		{
			//����·���еģ��Ѹø�����ΪҰ�ֲ�����
			MAP_DATA[(int)ccpxy.x][(int)(ccpxy.y+1)]=1;
			//�Ƴ��������ľ���ı�־λ����Ϊfalse
			removeWeap=false;
			//�ѷ�������ǰ���ĸ������и�������
			trSprite->pointColRow=ccpxy;
		}
	}
	//����Ƴ��������������
	if(removeWeap)
	{
		this->removeChild(trSprite);
	}
	else
	{	//�ɹ����������
		int tempValue=trSprite->value;
		money-=tempValue;
		std::string overStr = "$";
		char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
		snprintf(a, 6, "%d",money);
		moneyL->setString((overStr+a).c_str());
		//�����������������ӵ����������������
		arrWeap->addObject(trSprite);
	}
	//Ϊ����began�߽��ƶ��ı�־λ����Ϊfalse
	touchMove=false;
}

//���������˵�����ɼ�
void GameLayer::setUpdateTrue()
{
	//������Ų˵�������������
	for(int i=0;i<arrMenu->count();i++)
	{
		//�õ�ָ��˵���������ָ��
		Weapon* weapon = (Weapon*)arrMenu->objectAtIndex(i);
		//���ò˵����������ɼ�
		weapon->setVisible(false);
	}
	//������Ž�ҵ�����
	for(int j=0;j<arrSellUpdate->count();j++)
	{
		//�õ�ָ�������˵���ָ��
		Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(j);
		//�������˵�����Ϊ�ɼ�
		update->setVisible(true);
	}
	//����ʾ���������������ı���ǩ����Ϊ�ɼ�
	uMoneyL->setVisible(true);
	//����ʾ����������ʱ���������ı���ǩ����Ϊ�ɼ�
	sMoneyL->setVisible(true);
	//�����������ı�־λ����Ϊtrue
	WeaponUpdate = true;
	if(updateWeapon!=NULL)
	{
		//����Χ����Ϊ�ɼ�
		(updateWeapon->getChildByTag(1))->setVisible(true);
		//���Ҫ�����ķ������ĵȼ�Ϊ4������߼�
		if(updateWeapon->level==4)
		{	//������ͷ��ʾ�����Ľ�Ҳ��ɼ�
			uMoneyL->setVisible(false);
		}
		//���ʣ��Ǯ��������
		if(money<updateWeapon->upValue||updateWeapon->level==4||updateWeapon->updateMark==true)
		{	//������ͷ||��������
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
		//����������Ǯ
		setValue();
	}
}

//���÷������˵�����ɼ�
void GameLayer::setWeaponTrue()
{
	//������Ų˵�������������
	for(int i=0;i<arrMenu->count();i++)
	{
		//�õ�����ڲ˵������������еķ���������
		Weapon* weapon = (Weapon*)arrMenu->objectAtIndex(i);
		//��������Ϊ�ɼ�
		weapon->setVisible(true);
	}
	//������Ž�ҵ�����
	for(int j=0;j<arrSellUpdate->count();j++)
	{
		Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(j);
		update->setVisible(false);
	}
	uMoneyL->setVisible(false);
	sMoneyL->setVisible(false);
	//���������µı�־λ����Ϊfalse
	WeaponUpdate = false;
	//����ɸ��µķ�����Ϊ��
	if(updateWeapon!=NULL)
	{
		//����������Χ�Ĺ�Ȧ������Ϊ���ɼ�
		(updateWeapon->getChildByTag(1))->setVisible(false);
	}
}

//���������Ľ��
void GameLayer::setValue()
{
	std::string overStr = "$";
	char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
	snprintf(a, 6, "%d",updateWeapon->sellValue);
	sMoneyL->setString((overStr+a).c_str());
	char b[6];//��int �͵ķ���ת����string�͵� Ȼ��set
	snprintf(b, 6, "%d",updateWeapon->upValue);
	uMoneyL->setString((overStr+b).c_str());
}

//���������ķ���
void GameLayer::sellWeapon(Weapon* weapon)
{
	//��ȡ�������ڸ��ӵ�����
	Point tempxy = weapon->getPosition();
	//�Ӵ�ŷ��������������Ƴ�
	arrWeap->removeObject(weapon);
	//��layer���Ƴ�
	this->removeChild(weapon);
	//�õ��õ�ͼ���ӵ����к�
	Point ccpxy =fromXYToColRow((int)tempxy.x,(int)tempxy.y);
	//�ѵ�ͼ������Ϊ������
	MAP_DATA[(int)ccpxy .x][(int)(ccpxy.y)]=0;
	//�����·���������Ϊ��
	updateWeapon=NULL;
	//��Ϸ��ҵĽ�Ǯ��
	setWeaponTrue();
}

//Ұ�ֵ��յ�ʱ����Ч
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

//Ұ����ʱ����Ч
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

//�ڶ���������������ʱ���õ���Ч
void GameLayer::addParticle(Point point,int id,float time,float angle)
{
	if(!DialogLayer::isParticle)
	{
		return;
	}
	std::string picTable[6]={"red.png","yellow.png","blue.png","white.png","red.png","blue.png"};
	//����������������ɻ�����
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

//�ִ�action���������������
void GameLayer::run()
{
	//�����Ϸ�����򷵻�
	if(GameOver)
	{
		return;
	}
	//�����������˵��������ò˵���͸����
	for(int k=0;k<arrMenu->count();k++)
	{
		//ָ�����������ָ��
		Weapon* pWeapon =(Weapon*)arrMenu->objectAtIndex(k);
		//�����ǰ�����С�ڰ�װ����ʱ��Ҫ�Ľ��
		if(money<pWeapon->value)
		{
			//���÷���������Ϊ���ɴ��ز��߰���
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(100));
			pWeapon->runAction(act);

		}else
		{
			//�����ǰ��������ڰ�װ������ʱ��Ҫ�Ľ���������÷���������Ϊ�ɼ��ɴ���
			ActionInterval *act0=FadeTo::create(0.1f,(GLubyte)(255));
			pWeapon->runAction(act0);

		}
	}
	//�������������Ϊ��
	if(updateWeapon!=NULL)
	{
		setValue();
		//���Ҫ�����������ĵȼ��Ѿ�Ϊ4������߼�
		if(updateWeapon->level==4)
		{	//������ͷ��ʾ�����Ľ�Ҳ��ɼ�
			uMoneyL->setVisible(false);
		}
		//�����ǰ�ܽ����С�������������������Ѿ���������߼����������ı�־λΪtrue
		if(money<updateWeapon->upValue||updateWeapon->level==4||updateWeapon->updateMark==true)
		{
			//����һ��ָ���Ž�Ǯ�����ָ��
			Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(1);
			//����ʾ�����ļ�ͷ��ť����Ϊ���ɴ���
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(100));
			update->runAction(act);
			//����ʾ������$�ı���ǩ����Ϊ���ɴ���
			ActionInterval *act1=FadeTo::create(0.1f,(GLubyte)(100));
			uMoneyL->runAction(act1);
		}else
		{
			//����������Ϊ�ɴ��ؿ�����
			Sprite* update = (Sprite*)arrSellUpdate->objectAtIndex(1);
			ActionInterval *act=FadeTo::create(0.1f,(GLubyte)(255));
			update->runAction(act);
			ActionInterval *act1=FadeTo::create(0.1f,(GLubyte)(255));
			uMoneyL->runAction(act1);
		}
	}

	//��������ֵı�־λΪtrue�����������
	if(isfoundMonster)
	{
		//�����Ź����Ź�action�����鶼Ϊ0�����������
		if(arrMon->count()==0&&arrAction->count()==0)
		{
			//�غ����Լ�
			pass++;
			char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
			snprintf(a, 6, "%d",pass+1);
			passL->setString(a);
			//���ù��˶�
			isMonsterRun=false;
			//currMon++;
			//���ô�������ֵķ���
			foundMonsters();
		}
	}
	//�����Ź�action������Ϊ�������������
	if(arrAction->count()==0)
	{
		return;
	}

	//�õ���ʼ������꣬���ſ���x��y
	Point start = tmxLayer->positionAt(Point(source[1],source[0]));
	//���������ת������������ϵ��
	Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
	//������ƶ��ı�־λΪtrue
	if(isMonsterRun)
	{
		//����ʼ�㴦���������Ч������Ϊ�����ʱ����
		this->addParticle(startWorld,1.0);
	}
}

//���ƶ����յ�
void GameLayer::monsterRun(Node* node)
{
	Monsters* monster=(Monsters*) node ;
	//������Ϊ�ɼ�
	monster->setVisible(true);
	//���Ұ���Ѿ��ߵĲ�������ԭ��·���ĳ���
	if(monster->way==monster->selfWay.size())
	{
		//�������ֵ����0
		if(ten>0)
		{
			//����ֵ�Լ�
			ten--;
			//������Ч
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
		}
		//���Ұ�ֵ��յ�ʱ����Ч
		this->addParticle(monster->getPosition(),monster->id,3.0);
		char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
		snprintf(a, 6, "%d",ten);
		//���ñ�ʾ����ֵ���ı���ǩ
		tenL->setString(a);
		//Ұ�ֵ��յ���Ƴ�����
		this->removeChild(monster);
		//�Ƴ������еĹ�
		arrMon->removeObject(monster);
		if(ten<=0)//ʧ��
		{
			GameOver=true;
			this->loseGame();
		}
	}

	//������Ѿ��ߵ�·������С��Ҫ��·�����ܳ���
	if(monster->way<monster->selfWay.size())
	{
		//Ұ���ߵĲ����Լ�
		monster->way++;
		//��ȡҰ�ֵ�ǰ��λ�õ�
		Point crrPosition=monster->getPosition();
		//�õ���һ��Ҫ�ߵĵ������
		Point tarPosition=monster->selfWay.at(monster->selfWay.size()-monster->way);
		//�õ��ֵ�ǰ������ͼ���ӵ����кŵ�xֵ
		int crrpoint_x=(int)(fromXYToColRow((int)crrPosition.x,(int)crrPosition.y).x);
		//�õ��ֵ�ǰ������ͼ���ӵ����кŵ�yֵ
		int crrpoint_y=(int)(fromXYToColRow((int)crrPosition.x,(int)crrPosition.y).y);
		//�õ���һ��Ҫ�ߵĵ��xֵ
		int tarpoint_x=(int)(fromXYToColRow((int)tarPosition.x,(int)tarPosition.y).x);
		//�õ���һ��Ҫ�ߵĵ��yֵ
		int tarpoint_y=(int)(fromXYToColRow((int)tarPosition.x,(int)tarPosition.y).y);
		//����һ�������
		Point zhong;
		//�õ��ֵ�ǰ������һĿ�����е��x����
		zhong.x=(tarPosition.x+crrPosition.x)/2;
		//�õ��ֵ�ǰ������һĿ�����е��y����
		zhong.y=(tarPosition.y+crrPosition.y)/2;
		//����һ��������ʾʱ��ĳ���
		float time1=this->TIME_MAIN/2;
		float time2=this->TIME_MAIN/2;
		//���Ϊ�ڶ���Ұ��
		if(monster->id==2)
		{
			Point vacter;
			vacter.x=tarPosition.x-crrPosition.x;
			vacter.y=tarPosition.y-crrPosition.y;
			float dirction=ccpToAngle(vacter);
			monster->setRotation(-(dirction*180/3.1415926));
			monster->refresh(dirction);
		}
		//������ǰ����Ŀ�����е��Լ�һ��ʱ���MoveTo
		ActionInterval* act1=MoveTo::create(time1,zhong);
		//����Ŀ��㼰һ��ʱ���MoveTo
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
	//����һ��ָ��ֶ������������һ���ֵ�ָ��
	Monsters* mon = (Monsters*)arrAction->lastObject();
	//�ѹ���ӵ���������
	arrMon->addObject(mon);
	//���ù��ƶ����յ�ķ���
	monsterRun(mon);
	//�ƶ��ֶ��������еĹ�
	arrAction->removeLastObject();
	if(!DialogLayer::isParticle)
	{
		//ɾ����Ч�������
		this->removeChild(cc,true);
	}
}

//��������ֵķ���
void GameLayer::foundMonsters()
{
	//����ĳ���
	int id = pass%5;

	for(int i=0;i<10;i++)
	{
		//����һ���ֶ���
		Monsters* mon = Monsters::create(id+1,way);
		//�õ�����ʼλ�õ�����,���ſ���x,y
		Point start = tmxLayer->positionAt(Point(source[1],source[0]));
		//����ʼ�������ת������������ϵ��
		Point startWorld = tmxLayer->convertToWorldSpaceAR(Point(start.x+trans.x,start.y+trans.y));
		//���ùֵĳ�ʼλ��
		mon->setPosition(startWorld);
		//��ʼʱ������Ϊ���ɼ�
		mon->setVisible(false);
		//������ӵ�������
		this->addChild(mon,6);
		//�ѹ���ӵ�action������
		arrAction->addObject(mon);
		if(id>2)//��������
		{
			break;
		}
	}
	//�������ֵı�־λ����Ϊtrue
	isfoundMonster=true;
	//����ready����
	ready();
}

//�����ֵķ���
void GameLayer::attack()
{
	//����ֲ��ƶ�������Ϸ����
	if(!isMonsterRun||GameOver)
	{
		return;
	}
	//�������Թֵ�ɨ��
	for(int i=0;i<arrWeap->count();i++)
	{
		if(((Weapon*)arrWeap->objectAtIndex(i))->fire)
		{
			for(int j=0;j<arrMon->count();j++)
			{
				//�õ�ָ��ֶ����ָ��
				Monsters* monster = (Monsters*)arrMon->objectAtIndex(j);
				//�õ�ָ���������ָ��
				Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(i);
				//��ȡ��������ǰ��λ������
				Point pointWeapon=weapon->getPosition();
				//��ȡҰ�ֵ�ǰ��λ������
				Point pointMonster=monster->getPosition();
				//����һ������   Ϊ��ʹ������ָ���
				Point anglePoint;
				anglePoint.x=pointMonster.x-pointWeapon.x;
				anglePoint.y=pointMonster.y-pointWeapon.y;
				//����������������Ӧ�ĽǶ�
				float angle = ccpToAngle(anglePoint);
				//�����
				float distance = sqrt((pointMonster.x-pointWeapon.x)*(pointMonster.x-pointWeapon.x)
						+(pointMonster.y-pointWeapon.y)*(pointMonster.y-pointWeapon.y));
				//����һ�������ӵ��뿪��������λ�õı���
				Point bulletPoint;
				//�ӵ�����������λ��  ���Ƿ���������
				bulletPoint.x=(pointMonster.x-pointWeapon.x)*25/distance+pointWeapon.x;
				bulletPoint.y=(pointMonster.y-pointWeapon.y)*25/distance+pointWeapon.y;
				//��Cocos2dx�ṩ�ĺ����������ĳ���
				float lengthVector=ccpLength(Point(pointWeapon.x-pointMonster.x,pointWeapon.y-pointMonster.y));
				//������󳤶��ڷ������Ĺ�����Χ��
				if(lengthVector<=weapon->confines)
				{
					//��������ת
					weapon->setRotation(-(angle*180/3.1415926));
					//�ı�������Ƕ�����
					weapon->angle=angle*180/3.1415926;
					//��һ��������������ʱ���ü�Ѫ�ķ���
					if(weapon->id==1)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
						(
							"sf_minigun_hit.mp3"
						);
						fireBulletOne(i,j,angle,bulletPoint,lengthVector);
						break;
					}
					//�ڶ���������������ʱ���ü�Ѫ�ķ���
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
					//������������������ʱ���ü�Ѫ�ķ���
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

					//���ĸ��������Ĺ���
					else if(weapon->id==4)
					{
						//��ʼ������������ת�Ƕ�
						weapon->setRotation(0);
						//��ʼ���������ĽǶ�
						weapon->angle=0;
						//����һ���ӵ�����
						Sprite* bullet = Sprite::create("ring_blue.png");
						float bulletX=bullet->getContentSize().width/2;
						//����ı���
						float scaleX=weapon->confines/bulletX;
						//�����ӵ���λ��
						bullet->setPosition(weapon->getPosition());
						//���ӵ���ӵ�������
						this->addChild(bullet,4);
						//�����ӵ���͸����
						bullet->setOpacity(80);
						//�����ӵ�Ϊ�ɼ�
						bullet->setVisible(true);
						//����һ���������Ч
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
						//�ֵ�Ѫ
						monster->cutBlood(weapon->hurt);
						//����ֵ�ѪС��0
						if(monster->blood<=0)
						{
							//�õ��ֵ�λ��
							Point pointMonster=monster->getPosition();
							//�õ��ֵ�·��
							vector <Point > tempSelfWay = monster->selfWay;
							//�õ����Ѿ��ߵ�·��
							int tempWay = monster->way;
							//����ֵ�idΪ3
							if(monster->id==3)
							{
								//����ê��
								Point Achorpoint=(Point(0.5,0.4));
								for(int i=0;i<2;i++)
								{
									//���������µĹ�
									Monsters* mon = Monsters::create(6,tempSelfWay);
									//�¹��õ��Ϲ��Ѿ��ߵ�·��
									mon->way=tempWay;
									//���ùֵ�λ��
									mon->setPosition(pointMonster);
									//���ùֵ�ê��
									mon->setAnchorPoint(Achorpoint);
									Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
									//�ѹ���ӵ���������
									arrMon->addObject(mon);
									//������ӵ�������
									this->addChild(mon,6);
									//���ù��ƶ����յ�ķ���
									monsterRun(mon);
								}
							}
							//����һ����ʱ��Ź������ҵı���
							int tempMoney = monster->id*10;
							//�ܵĽ����������ʱ���õĵ��ڵ�ǰ�ܵĽ��
							money+=tempMoney;
							//����һ����ʱ��Ź��������÷����ı���
							int tempScore = monster->id*15;
							//�ܵķ���������ʱ���õĵ��ڵ�ǰ�ܵķ���
							score+=tempScore;
							//����ʱ���һ����Ч
							this->addParticle1(monster->getPosition(),monster->id,1);
							//������Ч
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
							//ɾ�������еĹ�
							this->removeChild(monster);
							//ɾ���������еĹ�
							arrMon->removeObject(monster);
							std::string overStr = "$";
							char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
							snprintf(a, 6, "%d",money);
							//������ʾ��ҵ��ı���ǩ
							moneyL->setString((overStr+a).c_str());
							char b[6];//��int �͵ķ���ת����string�͵� Ȼ��set
							snprintf(b, 6, "%d",score);
							//������ʾ�ܷ������ı���ǩ
							scoreL->setString(b);
						}
					}
				}
			}
		}
	}
}

//��һ������������
void GameLayer::fireBulletOne(int weap,int target,float dirction,Point position,float lengthVector)
{
	if(this->bulletData[target]==0)
	{
		this->bulletData[target]=1;
	}
	//��ȡҪ�����Ĺֶ���
	Monsters* monster = (Monsters*)arrMon->objectAtIndex(target);
	//��ȡ����������Ϣ
	Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(weap);
	//�����ӵ���������������ĵȼ��й�
	int count[4]={1,2,3,3};
	//�����ӵ����ӳ�
	float delay[3]={0.01,0.1,0.05};
    
	//���ݷ������ĵȼ���ȷ��Ҫ�����ӵ���������λ��
    Point* positionByLevel=new Point[count[weapon->level-1]];
    
	//����������ĵȼ�Ϊ1��ȷ��ÿ���ӵ��ĳ�ʼλ��
	if(weapon->level==1)
	{
		positionByLevel[0]=position;
	}
	//����������ĵȼ�Ϊ2�����������ӵ�
	else if(weapon->level==2)
	{
		//���������ӵ�ƫ��10��
		Point vacter1=ccpForAngle(dirction+(10*3.1415926/180));
		Point vacter2=ccpForAngle(dirction-(10*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		vacter2=ccpNormalize(vacter2);
		//ȷ���ӵ��ĳ�ʼ����λ��
		positionByLevel[0]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,26));
		positionByLevel[1]=ccpAdd(weapon->getPosition(),ccpMult(vacter2,26));
	}
	//����������ĵȼ�Ϊ3������4��
	else if(weapon->level==3||weapon->level==4)
	{
		//���������ӵ�ƫ��10��
		Point vacter1=ccpForAngle(dirction+(20*3.1415926/180));
		Point vacter2=ccpForAngle(dirction-(20*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		vacter2=ccpNormalize(vacter2);
		//ȷ���ӵ��ĳ�ʼ����λ��
		positionByLevel[0]=position;
		positionByLevel[1]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,26));
		positionByLevel[2]=ccpAdd(weapon->getPosition(),ccpMult(vacter2,26));
	}
	//�����ӵ����ӵ�ֱ���ƶ��������ٶȿ����ֲ�ƫ��
	for(int i=0;i<count[weapon->level-1];i++)
	{
		//����һ���ӵ�����
		BulletSprite* bullet = BulletSprite::create("bullet.png",weapon->hurt,target);
		//�����ӵ���λ��
		bullet->setPosition(positionByLevel[i]);
		//���ӵ���ӵ�������
		this->addChild(bullet,4);
		//����һ��ʱ�����
		float timeTo=lengthVector/weapon->confines;
		//����һ������
		ActionInterval* act=MoveTo::create(timeTo/5,monster->getPosition());
		//˳��ִ��
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

//�ֵ�Ѫ�ķ���
void GameLayer::cutBloodOne(Node*node)
{
	//�õ��ӵ�������Ŀ���
	Monsters* monster=(Monsters*)arrMon->objectAtIndex(((BulletSprite*)node)->target);
	//����cutBlood�����ùּ�Ѫ
	monster->cutBlood(((BulletSprite*)node)->hurt);
	if(monster->blood<=0)
	{
		//����һ����ʱ������Źֵ�·��
		vector <Point > tempSelfWay = monster->selfWay;
		//����һ����ʱ������Ÿ����Ѿ��ߵ�·��
		int tempWay = monster->way;
		//��ȡ�ֵ�λ��
		Point pointMonster=monster->getPosition();
		//�����ֹ�����ᴴ�������¹�
		if(monster->id==3)
		{
			Point Achorpoint=(Point(0.5,0.4));
			//���������µĹֶ���
			for(int i=0;i<2;i++)
			{
				//�����ֶ���
				Monsters* mon = Monsters::create(6,tempSelfWay);
				//�õ������Ѿ��ߵ�·��
				mon->way=tempWay;
				//�����¹ֵ�λ��
				mon->setPosition(pointMonster);
				//����ê��
				Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
				//�����¹ֵ�ê��
				mon->setAnchorPoint(Achorpoint);
				//�ѹ���ӵ���������
				arrMon->addObject(mon);
				//���½�����������ӵ�������
				this->addChild(mon,6);
				//���ù��ƶ����յ�ķ���
				monsterRun(mon);
			}
		}
		//����һ����ʱ������Ź���ʱ�õ��Ľ��
		int tempMoney = monster->id*10;
		//�ܵĽ�������Ϲ������õĽ�������ڵ�ǰ���ܽ����
		money+=tempMoney;
		//����һ����ʱ������Ź���ʱ�õ��ķ���
		int tempScore = monster->id*15;
		//�ܵķ������Ϲ���ʱ�õ��ķ������ڵ�ǰ�ܵķ���
		score+=tempScore;
		//��ӹ���ʱ����Ч
		this->addParticle1(monster->getPosition(),monster->id,1.0);
		//�����Ч
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
		//ɾ���ֶ���
		this->removeChild(monster);
		//ɾ�������еĹ�
		arrMon->removeObject(monster);
		char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
		snprintf(a, 6, "%d",money);
		std::string overStr = "$";
		//������ʾ��ǰ�ܽ�������ı���ǩ
		moneyL->setString((overStr+a).c_str());
		char b[6];//��int �͵ķ���ת����string�͵� Ȼ��set
		snprintf(b, 6, "%d",score);
		//������ʾ��ǰ�ܷ������ı���ǩ
		scoreL->setString(b);
	}
	//ɾ���ӵ�����
	this->removeChild(node);
}


//�ڶ����������Ĺ���
void GameLayer::fireBulletTwo(int weap,int target,float dirction,Point position)
{
	//�õ�Ŀ��Ұ��
	Monsters* monster = (Monsters*)arrMon->objectAtIndex(target);
	//�õ�������
	Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(weap);
	//��ȡҰ�ֵ�ǰ��λ��
	Point pointMonster=monster->getPosition();
	//��ȡ��������ǰ��λ��
	Point pointWeapon=weapon->getPosition();
	//����ӵ�����ͼƬ������
	std::string bullet[4]={"weapon2-1.png","weapon2-2.png","weapon2-3.png","weapon2-4.png"};
	//����һ���ӵ��������
	bullet1 = Sprite::create(bullet[weapon->level-1].c_str());
	//�����ӵ���ê��
	bullet1 ->setAnchorPoint(Point(0,0.5));
	//�����ӵ���λ��
	bullet1->setPosition(position);
	//���ӵ���ӵ�������
	this->addChild(bullet1,4);
	//�����ӵ��Ķ�����Ч
	bullet1->setRotation(-(dirction*180/3.1415926));
	bullet1 -> runAction(
				Sequence::create(
						DelayTime::create(0.1),
						CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSprite,this)),
						NULL
						)
				);
	//������Źֵ����飬�������б����������Ĺ�
	for(int k=0;k<arrMon->count();k++)
	{
		//�õ������еĹ�
		Monsters * mon= (Monsters*)arrMon->objectAtIndex(k);
		float x1=position.x;
		float y1=position.y;
		//�õ��ֵ�ǰ��x,y����
		float x2=pointMonster.x;
		float y2=pointMonster.y;
		//��ȡ�ֵ�ǰ��x,y����
		float x3=(mon->getPosition()).x;
		float y3=(mon->getPosition()).y;
		float slope = (y2-y1)/(x2-x1);
		//�ж��Ƿ��ڼ����
		if((x2-x1)*(x3-x1)>0&&(y2-y1)*(y3-y1)>0)
		{
			float monsterDistance=(y1-y2-slope*x1+slope*x3)/
					(sqrt(slope*slope+1));
			if(monsterDistance<30)
			{
				//���ùּ�Ѫ�ķ���
				mon->cutBlood(weapon->hurt);
				//���һ���ֱ�����ʱ����Ч
				this->addParticle(mon->getPosition(),monster->id,0.5,dirction*180/3.1415926);
			}
		}
		//�����ûѪ����ɾ��
		if(mon->blood<=0)
		{	//��ȡҰ�ֵ�λ��
			Point pointMonster=monster->getPosition();
			//��ȡ�ֵ�ǰ�ߵ�·��
			vector <Point > tempSelfWay = mon->selfWay;
			//��ȡ���Ѿ��ߵ�·��
			int tempWay = mon->way;
			//����ֵ�idΪ3
			if(monster->id==3)
			{
				//���ùֵ�ê��
				Point Achorpoint=(Point(0.5,0.4));
				for(int i=0;i<2;i++)
				{
					//����2���µĹ�
					Monsters* mon = Monsters::create(6,tempSelfWay);
					//���Ѿ��ߵ�·�������¹�
					mon->way=tempWay;
					//�����¹ֵ�λ��
					mon->setPosition(pointMonster);
					//�����¹ֵ�ê��
					mon->setAnchorPoint(Achorpoint);
					Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
					//�ѹ���ӵ���������
					arrMon->addObject(mon);
					//������ӵ�������
					this->addChild(mon,6);
					//���ù��ƶ����յ�ķ���
					monsterRun(mon);
				}
			}
			//�������õ���Ӧ�Ľ��
			int tempMoney = mon->id*10;
			//�ܵĽ����Ҫ���Ϲ�����õ��Ľ����
			money+=tempMoney;
			//�������õ���Ӧ�ķ���
			int tempScore = monster->id*15;
			//�ܵķ���Ҫ���Ϲ�����ķ���
			score+=tempScore;
			//�����Ч
			this->addParticle1(mon->getPosition(),monster->id,3.0);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
			//�Ƴ��ֶ���
			this->removeChild(mon);
			//�Ƴ������еĹ�
			arrMon->removeObject(mon);
			std::string overStr = "$";
			char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
			snprintf(a, 6, "%d",money);
			moneyL->setString((overStr+a).c_str());
			char b[6];//��int �͵ķ���ת����string�͵� Ȼ��set
			snprintf(b, 6, "%d",score);
			scoreL->setString(b);
		}
	}
	//����Weapon���з����ӵ��ķ���
	weapon->fireing();
}

//�������������Ĺ���
void GameLayer::fireBulletThree(int weap,int target,float dirction,Point position)
{
	//�Ӵ�Źֵ��������õ���
	Monsters* monster = (Monsters*)arrMon->objectAtIndex(target);
	//�Ӵ�ŷ��������������õ�������
	Weapon* weapon = (Weapon*)arrWeap->objectAtIndex(weap);
	int count[4]={1,2,2,3};
    Point* positionByLevel=new Point[count[weapon->level-1]];
    
	float angle[count[weapon->level-1]];
	//�����ǰ�������ĵȼ�Ϊ1
	if(weapon->level==1)
	{
		Point vacter1=ccpForAngle(dirction-(15*3.1415926/180));
		vacter1=ccpNormalize(vacter1);
		positionByLevel[0]=ccpAdd(weapon->getPosition(),ccpMult(vacter1,36));
		angle[0]=dirction;
	}
	//�����ǰ�������ĵȼ�Ϊ3����Ϊ2
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
	//�����������ǰ�ĵȼ�Ϊ4
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
	//���ݵ�ǰ�������ĵȼ������õ����������������ӵ�������
	for(int i=0;i<count[weapon->level-1];i++)
	{
		//����һ���ӵ�����
		BulletSprite* bullet = BulletSprite::create("bullet2.png",weapon->hurt,target);
		//�����ӵ���λ��
		bullet->setPosition(positionByLevel[i]);
		//�����ӵ�����ת
		bullet->setRotation(-(angle[i]*180/3.1415926));
		//�����ӵ�����ת
		bullet->angle = -(angle[i]*180/3.1415926);
		//���ӵ���ӵ�������
		this->addChild(bullet,4);
		//���ӵ���ӵ��ӵ�������
		arrBullet->addObject(bullet);
	}
}

//�����ӵ��ķ���
void GameLayer::runBullet()
{
	//�������ӵ�������ĳ���Ϊ0������Ϸ�����򷵻�
	if(arrBullet->count()==0||GameOver)
	{
		return;
	}
	//�����㷨
	for(int i=0;i<arrBullet->count();i++)
	{
		//����ӵ�����
		BulletSprite *bullet = (BulletSprite*)arrBullet->objectAtIndex(i);
		//�仯����
		Point vecter;
		//��ȡ�ӵ���λ������
		Point position=bullet->getPosition();
		//���û�й���仯������Ϊ0
		if(arrMon->count()==0)
		{
			vecter.x=0;
			vecter.y=0;
		}
		//����ӵ����й������е�Ŀ�����
		else if(bullet->target>arrMon->count())
		{
			//��ȡ�ֶ���
			Monsters* monster=(Monsters*)arrMon->objectAtIndex(1);
			//Ұ�ֵ�ǰλ�õĺ�����-�ӵ���ǰλ�õĺ�����
			vecter.x=monster->getPosition().x-bullet->getPosition().x;
			//Ұ�ֵ�ǰλ�õ�������-�ӵ���ǰλ�õ�������
			vecter.y=monster->getPosition().y-bullet->getPosition().y;
			//���������ӵ���������ľ���С��20�����Ŀ���
			if(ccpLength(vecter)<20)
			{
				//Ұ�ּ�Ѫ
				monster->cutBlood(bullet->hurt);
				//������Ѿ�û��Ѫ�ˣ���ɾ����
				if(monster->blood<=0)
				{
					//��ȡ�ֵ�ǰλ�õ������
					Point pointMonster=monster->getPosition();
					//��·�����¸���
					vector <Point > tempSelfWay = monster->selfWay;
					//����ֵ���ʱ·���ĳ���
					int tempWay = monster->way;
					//����ֵ�idΪ3
					if(monster->id==3)
					{
						//����ê��
						Point Achorpoint=(Point(0.5,0.4));
						//����3�йֱ���������������µ�С��
						for(int i=0;i<2;i++)
						{
							//�����µ�С��
							Monsters* mon = Monsters::create(6,tempSelfWay);
							//�ѵ�ǰ�Ѿ��ߵ�·�����µĹ�
							mon->way=tempWay;
							//���ùֵ�λ��
							mon->setPosition(pointMonster);
							//����ê��
							mon->setAnchorPoint(Achorpoint);
							//����ê��
							Achorpoint=Point(Achorpoint.x+0.2,Achorpoint.y+0.2);
							//�ѹ���ӵ���������
							arrMon->addObject(mon);
							//������ӵ�������
							this->addChild(mon,6);
							//���ù��ƶ����յ�ķ���
							monsterRun(mon);
						}
					}
					//�õ�������õ��Ľ����
					int tempMoney = monster->id*10;
					//�ܵĽ�������Ϲ�����Ľ�������ڵ�ǰ�����
					money+=tempMoney;
					//�õ�������õ��ķ���
					int tempScore = monster->id*15;
					//�ܵķ������Ϲ�����ķ������ڵ�ǰ����
					score+=tempScore;
					//��ӹ���ʱ����Ч
					this->addParticle1(monster->getPosition(),monster->id,3.0);
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
					//ɾ���ֶ���
					this->removeChild(monster);
					//ɾ�������еĹ�
					arrMon->removeObject(monster);
					char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
					snprintf(a, 6, "%d",money);
					std::string overStr = "$";
					//���ý����
					moneyL->setString((overStr+a).c_str());
					char b[6];//��int �͵ķ���ת����string�͵� Ȼ��set
					snprintf(b, 6, "%d",score);
					//���÷���
					scoreL->setString(b);
				}
				//ɾ���ӵ������е��ӵ�
				arrBullet->removeObject(bullet);
				//ɾ���ӵ�����
				this->removeChild(bullet);

				return;
			}
		}
		else
		{
			//��ȡ�ӵ�ָ���Ұ�ֶ���
			Monsters* monster=(Monsters*)arrMon->objectAtIndex(bullet->target);
			//Ұ�ֵ�ǰλ�õĺ�����-�ӵ���ǰλ�õĺ�����
			vecter.x=monster->getPosition().x-bullet->getPosition().x;
			//Ұ�ֵ�ǰλ�õ�������-�ӵ���ǰλ�õ�������
			vecter.y=monster->getPosition().y-bullet->getPosition().y;
			//���������ӵ���������ľ���С��20�����Ŀ���
			if(ccpLength(vecter)<20)
			{
				monster->cutBlood(bullet->hurt);
				//�����ûѪ����ɾ��
				if(monster->blood<=0)
				{
					//��ȡ�ֵ�ǰ��λ��
					Point pointMonster=monster->getPosition();
					//�õ��ֵ�ǰ�ߵ�·��
					vector <Point > tempSelfWay = monster->selfWay;
					//�õ����Ѿ��ߵ�·��
					int tempWay = monster->way;
					//�����ֹ�����ᴴ�������¹�
					if(monster->id==3)
					{
						//����ê��
						Point Achorpoint=(Point(0.5,0.4));
						//ͨ��forѭ�����������µĹ�
						for(int i=0;i<2;i++)
						{
							//����id��·�������µĹ�
							Monsters* mon = Monsters::create(6,tempSelfWay);
							//�õ�����Ѿ��ߵ�·
							mon->way=tempWay;
							//�����¹ֵ�λ��
							mon->setPosition(pointMonster);
							//����ê��
							mon->setAnchorPoint(Achorpoint);
							Achorpoint=ccp(Achorpoint.x+0.2,Achorpoint.y+0.2);
							//���¹���ӵ���������
							arrMon->addObject(mon);
							//���¹���ӵ�������
							this->addChild(mon,6);
							//���ù��ƶ����յ�ķ���
							monsterRun(mon);
						}
					}
					//����һ����ʱ��Ź��������ý�ҵı���
					int tempMoney = monster->id*10;
					//�����ܵĽ����
					money+=tempMoney;
					//����һ����ʱ��Ź��������÷����ı���
					int tempScore = monster->id*15;
					//�����ܵķ���
					score+=tempScore;
					//��ӹ���ʱ����Ч
					this->addParticle1(monster->getPosition(),monster->id,3.0);
					//���Ź���ʱ����Ч
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sf_creep_die_0.mp3");
					//ɾ���ֶ���
					this->removeChild(monster);
					//ɾ���������еĹ�
					arrMon->removeObject(monster);
					char a[6];//��int �͵ķ���ת����string�͵� Ȼ��set
					snprintf(a, 6, "%d",money);
					std::string overStr = "$";
					moneyL->setString((overStr+a).c_str());
					char b[6];//��int �͵ķ���ת����string�͵� Ȼ��set
					snprintf(b, 6, "%d",score);
					scoreL->setString(b);
				}
				//ɾ���ӵ������е��ӵ�
				arrBullet->removeObject(bullet);
				//ɾ���ӵ�����
				this->removeChild(bullet);

				return;
			}
		}
		//�ж��ӵ��Ƿ񳬳���Ļ�������������ɾ��
		if(position.x>800||position.y>480||position.x<0||position.y<0)
		{
			//ɾ���ӵ������е��ӵ�
			arrBullet->removeObject(bullet);
			//ɾ���ӵ�����
			this->removeChild(bullet);

			return;
		}
		Point vector = ccpForAngle ((bullet->angle)*3.1415926/180);
		Point speed=ccpMult(ccpNormalize(ccp(vecter.x+vector.x/15,vecter.y+vector.y/15)),6);
		bullet->setPosition(ccpAdd(bullet->getPosition(),speed));
		float angle = ccpToAngle(speed);
		bullet->setRotation(-(angle*180/3.1415926));
		//�����ӵ��ĽǶ�
		bullet->angle=angle;
	}
}

//ɾ�������������ľ������
void GameLayer::removeSprite(Node*node)
{
	this->removeChild(node);
}

//��ӷ������������
void GameLayer::addMenuSprite()
{
	//��ӱ�ʾ��ҷ��ŵľ������
	Sprite* sell = Sprite::create("sell.png");
	//�����������鰴ť
	onePlayer = Weapon::create("button_0.png",1);
	twoPlayer = Weapon::create("button_1.png",2);
	threePlayer = Weapon::create("button_2.png",3);
	fourPlayer = Weapon::create("button_3.png",4);
	//������ʾ������ͷ�ľ������
	Sprite* update = Sprite::create("update.png");
	//����������ťΪ���ɼ�
	update->setVisible(false);
	//���ñ�ʾ���������������Ұ�ťΪ���ɼ�
	sell->setVisible(false);

	//����������������λ��
	sell->setPosition(Point(730,68));
	onePlayer->setPosition(Point(750,136));
	twoPlayer->setPosition(Point(750,204));
	threePlayer->setPosition(Point(750,272));
	fourPlayer->setPosition(Point(750,340));
	update->setPosition(Point(730,408));

	//��4�������˵���ť��ӵ�������
	this->addChild(onePlayer, 3);
	this->addChild(twoPlayer, 3);
	this->addChild(threePlayer, 3);
	this->addChild(fourPlayer, 3);
	//�����������ӵ�������
	this->addChild(sell, 3);
	this->addChild(update, 3);

	//��4�������˵���ť��ӵ���Ӧ��������
	arrMenu->addObject(onePlayer);
	arrMenu->addObject(twoPlayer);
	arrMenu->addObject(threePlayer);
	arrMenu->addObject(fourPlayer);
	//����Ҿ��������ӵ���Ӧ��������
	arrSellUpdate->addObject(sell);
	//���������������ӵ�������
	arrSellUpdate->addObject(update);
}

//�������label
void GameLayer::addLabel()
{
	//����һ��tempScore�ı���ǩ����ʱ������
	scoreL = LabelTTF::create("0", "Arial",28);
	//����һ����Ч������
	ActionInterval *act= RotateBy::create(0.1,-90);
	scoreL->runAction(act);
	//���ñ�ǩ�������ɫ
	scoreL->setColor (ccc3(255,255,255));
	//�����ı���ǩ��λ��
	scoreL->setPosition(Point(40,60));
	//���ı���ǩ��ӵ�������
	this->addChild(scoreL,3);

	//����һ��������ʾ�غ������ı���ǩ
	passL = LabelTTF::create("1", "Arial",28);
	//���ö����ļ��
	ActionInterval *act1= RotateBy::create(0.1,-90);
	passL->runAction(act1);
	//���ñ�ǩ�������ɫ
	passL->setColor (ccc3(255,255,255));
	//�����ı���ǩ��λ��
	passL->setPosition(Point(40,240));
	//���ı���ǩ��ӵ�������
	this->addChild(passL,3);

	//����һ��������ʾ��Ǯ���ı���ǩ
	moneyL = LabelTTF::create("$280", "Arial",28);
	//����һ����Ч������
	ActionInterval *act2= RotateBy::create(0.1,-90);
	moneyL->runAction(act2);
	//���ñ�ǩ�������ɫ
	moneyL->setColor (ccc3(255,255,255));
	//�����ı���ǩ��λ��
	moneyL->setPosition(Point(40,410));
	//���ı���ǩ��ӵ�������
	this->addChild(moneyL,3);

	//����һ��������ʾ����ֵ��ten�ı���ǩ
	tenL = LabelTTF::create("18", "Arial",28);
	//����һ����Ч������
	ActionInterval *act3= RotateBy::create(0.1,-90);
	tenL->runAction(act3);
	//���ñ�ǩ�������ɫ
	tenL->setColor (ccc3(255,255,255));
	//���ſ���x��y
	Point tar = tmxLayer->positionAt(Point(targetAll[0][1],targetAll[0][0]));
	//��Ŀ��������ת������������ϵ��
	Point targetWorld = tmxLayer->convertToWorldSpaceAR(Point(tar.x+trans.x,tar.y+trans.y));
	//�����ı���ǩ��λ��
	tenL->setPosition(targetWorld);
	//���ı���ǩ��ӵ�������
	this->addChild(tenL,6);

	//����һ��updateMoney�ı���ǩ
	uMoneyL = LabelTTF::create("$", "Arial",28);
	//���ı���ǩ����Ϊ���ɼ�
	uMoneyL->setVisible(false);
	//����������һ����Ч
	ActionInterval *act4= RotateBy::create(0.1,-90);
	uMoneyL->runAction(act4);
	//���ñ�ǩ�������ɫ
	uMoneyL->setColor (ccc3(255,255,255));
	//�����ı���ǩ��λ��
	uMoneyL->setPosition(Point(760,408));
	//���ı���ǩ��ӵ�������
	this->addChild(uMoneyL,3);

	//����һ��sellMoney�ı���ǩ
	sMoneyL = LabelTTF::create("$", "Arial",28);
	//���ı���ǩ����Ϊ���ɼ�
	sMoneyL->setVisible(false);
	//����һ����Ч������
	ActionInterval *act5= RotateBy::create(0.1,-90);
	sMoneyL->runAction(act5);
	//���ñ�ǩ�������ɫ
	sMoneyL->setColor (ccc3(255,255,255));
	//�����ı���ǩ��λ��
	sMoneyL->setPosition(Point(760,68));
	//���ı���ǩ��ӵ�������
	this->addChild(sMoneyL,3);
}

//Ұ�ֵ��յ�ʱ����Ч
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
		//����һ��������Ч�ľ���
		Sprite* particle= Sprite::create("white.png");
		//����ê��
		particle->setAnchorPoint(Point(0,0.5));
		//����λ��
		particle->setPosition(point);
		//���ô�С
		particle->setScale(1.0);
		particle->setRotation(-(angle+angleVar));
		Point vocter=ccpForAngle((angle+angleVar)*3.1415926/180);
		int lange=rand()%200;
		angle+=11;
		//�����������ӵ�������
		this->addChild(particle,5);
		//˳��ִ�ж���
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

	//����һ����Ч�������
	cc = Sprite::create("fire1.png");
	//����һ�����ֵĶ���
	ActionInterval *act1=FadeIn::create(time*4/3);
	//����һ�������Ķ���
	ActionInterval *activeFade1=FadeOut::create(time*4/3);
	//���ö���ִ�е�λ��
	cc->setPosition(point);
	//���þ���Ĵ�С
	cc->setScale(6.0);
	//��������ӵ�������
	this->addChild(cc,6);
	//˳��ִ�ж���
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

//��Ϸ����ʱ���õķ���
void GameLayer::loseGame()
{
	//������Ϸ��������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
	(
		"sf_game_over.mp3"
	);
	//���üƷְ�
	AchieveLayer* al = new AchieveLayer();
	al->saveScore(score);
	//��������������
	for(int i=0;i<arrWeap->count();i++)
	{
		//����һ�����4��ʱ���һά����
		int a[4]={4,2,1,3};
		//�õ���ǰ�ķ���������
		Weapon* weap=(Weapon*)arrWeap->objectAtIndex(i);
		//��ӱ�ը����Ч
		this->addParticle1(weap->getPosition(),a[weap->id-1],5.0);
		//ɾ������������
		this->removeChild(weap,true);
	}
	//ɾ�������������е����ж���
	arrWeap->removeAllObjects();

	//������Źֵ�����
	for(int i=0;i<arrMon->count();i++)
	{
		//�õ���ǰ�����й�
		Monsters* mon=(Monsters*)arrMon->objectAtIndex(i);
		//��ӱ�ը��Ч
		this->addParticle1(mon->getPosition(),mon->id,5.0);
		//ɾ���ֶ���
		this->removeChild(mon,true);
	}
	//ɾ����Ź������е����йֶ���
	arrMon->removeAllObjects();
	//ɾ�����д���ڹֶ��������еĶ���
	arrAction->removeAllObjects();

	//�������д���ӵ�������
	for(int i=0;i<arrBullet->count();i++)
	{
		//�õ��ӵ�����
		BulletSprite* bullet=(BulletSprite*)arrBullet->objectAtIndex(i);
		//��ӱ�ը��Ч
		this->addParticle1(bullet->getPosition(),1,5.0);
		//ɾ���ӵ�����
		this->removeChild(bullet,true);
	}
	//ɾ���ӵ������е����ж���
	arrBullet->removeAllObjects();
	//�����Ч
	this->addParticle2(endWorld,5.0);

    //����һ��������󣬡���߷�����
    Sprite *gameOverSprite = Sprite::create("gameOver.png");
	//���þ�������λ��
    gameOverSprite->setPosition(Point(850,240));
	//������������ӵ�������
	this->addChild(gameOverSprite,GAME_LEVEL_CGQ+4);
	gameOverSprite->runAction(MoveTo::create(4.0f,Point(400,240)));
	//ֹͣ�������ֵĲ���
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic
	(
		"bg_music.mp3"
	);
}
