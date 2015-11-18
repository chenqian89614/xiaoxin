#ifndef _GameLayer_H_
#define _GameLayer_H_
#include "cocos2d.h"
#include "WarshipsFightSceneManager.h"
#include "WarShipObject.h"
#include "HKMJObject.h"
#include "Weapon.h"
#include <list>
#include <queue>
using namespace cocos2d;
class GameLayer :public Layer
{
public:
	WarshipsFightSceneManager* wfsm;		//声明指向场景管理器的指针
	TMXTiledMap* map;						//声明指向地图对象的指针
	Point firstTouchPoint;					//第一次被触摸的点
	Point mapPoint;							//地图的坐标
	Point touchPoint ;						//触摸的坐标
	MenuItemImage* jjbgSp[5];				//声明军舰背景精灵菜单项
	MenuItemImage* shipWeapon [3];			//导弹菜单项
	Sprite* selectedSp;						//选中框的精灵对象
	int selectIndex = -1;					//选中军舰的索引
	Sprite* lifeBarSp [20];					//基地的血条
	HKMJObject* playerHKMJ;					//玩家基地对象
	bool selectItem = false;				//是否选中军舰的标志位
	int** Map_DATA;							//地图数据
	TMXLayer *colliLayer;					//地图碰撞检测层
	int row;								//行号
	int col;								//列好
	std::vector<Point>* path;				//储存行驶路径的向量
	std::vector<Point>* tempPath;			//储存行驶路径的向量
	WarShipObject* lastTouchSprite ;		//上一次点击的军舰对象
	WarShipObject* currTouchSprite ;		//当前点击的军舰对象
	bool selectShip = false;				//标志是否选中军舰的标志位
	Animate* anmiAc[2];						//精灵帧动画
	int waveNum = 1;						//敌军进攻的波数
	Label* labelWaveIndex;					//显示波数的文本标签
	int enemyShipCount = 10;				//敌船的总数
	bool isGameOver = false;				//游戏是否结束
	bool gameResult = false;				//游戏的胜利或者失败
	int myGold = 3000;						//最初玩家金钱
	LabelAtlas* moneyLabel;					//显示玩家金钱的文本标签
	int sdsNum = 0;							//杀敌数
	int currLevelSds = 0;					//当前关卡
	int curGetGold = 0;						//获得金币
	LabelAtlas* sdsLabel;					//显示杀敌数的文本标签
	//暂停菜单项
	MenuItemImage* puaseMenu;
	//暂停背景
	Sprite* gamePausebb;
	//海洋背景
	Sprite* oceanbg1Sp[2];
	//必杀技冷却精灵
	Sprite* coolSp [2];
	Sprite* (weaponeSprite) [2];			//导弹冷却精灵对象
	Sprite* (ShipCoolSprite) [5];			//军舰冷却精灵对象
	bool coolSpb = false;

	bool coolSpp = false;
	//结果路径记录
	std::map<std::string, int(*)[2]>* hm;
	//广度优先所用队列
	std::queue<int(*)[2]>* myQueue;
	//半个图块的大小（即界面中路线的偏移量）此处要有一个调整值（参数为瓦片图片的半边宽，瓦片图片的半边高）
	Point trans;

	std::vector<Weapon*>* 	allWeaponVCT;			//武器
	std::vector<Weapon*>* 	delWeaponVCT;			//武器

	std::vector<WarShipObject*>* 	allShipVCT;	//所有军舰
	std::vector<WarShipObject*>* 	delShipVCT;
    
	int resultSequence [8][2];				//储存方向优先顺序的数组

	Sprite3D* plane3D[2];					//3D飞机精灵对象
	bool planeFlag = false;					//飞机飞行的标志位
	int step = 1;							//飞机飞行阶段

	//初始化布景方法
	virtual bool init();
	void initMiscellaneous();
	void initSound();
	void initListenerTouchAndCallback();
	void initRaning();
	//爆炸换帧精灵
	void initBoomFrame();
	void initBigBoomFrame();
	void expansionRing();
	//初始化军舰选项的方法
	void initJJItem();
	//初始化地图
	void initTMXMap();
	//初始化海洋背景
	void initOceanBg();
	//初始化航母
	void initHKMJ();
	//初始话地图碰撞检测的数组
	void initTMXPZJCArray();
	//初始化路径搜索数组
	void initVisitedArr();
	//初始化暂停菜单项
	void initPauseMenu();
	void puaseCallback();
	void backCallback();
	//添加我方军舰的方法
	void addWarShip(Point touchPoint ,int seleteNum);
	//触摸监听的方法
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	bool onShipTouchBegan(Touch* touch, Event* event);
	void onShipTouchEnded(Touch* touch, Event* event);
	//点击菜单项切换选中船只的方法
	void jjbgSpCallback0();
	void jjbgSpCallback1();
	void jjbgSpCallback2();
	void jjbgSpCallback3();
	void jjbgSpCallback4();
	//切换武器方法
	void shipWeaponCallback0();
	void shipWeaponCallback1();
	//取消菜单项
	void shipWeaponCallback2();
	//搜索船只路径
	void searchPath(WarShipObject* warShip);
	//广度优先算法寻径
	void BFSCalPath(WarShipObject* wso);
	void transformBTMapandVector(WarShipObject* wso);
	void createFiniteTimeActionByVector(WarShipObject* warShip);
	//
//	void moveFlagCallback();
	void transformPath();//放到储存行驶路径的向量中
	//指定点装换为格子行列号的方法
	Point touchPointToRowCol(Point touchPoint);
	//获取方向转向
	int orderDirection(float dx,float dy);
	//给船只添加监听
	void addTouchListener(WarShipObject* WarShipSprite);
	//点击军舰出现的精灵
	void warShipAddChild(WarShipObject* wso);

	//显示当前选中的船只的导弹
	void showWarShipItem(WarShipObject* wsoSprite);
	//添加导弹
	bool addWeapon(int selectIndex,Point startPoint,Point finalPoint,WarShipObject* ship,int launchForm);
	//添加瞄准船只的精灵
	void addAimSprite();
	//添加显示船只攻击范围的精灵
	void addSaveSprite(WarShipObject* wsoSprite);
	//添加错误提示
	void addWrongPrompt(Point locationMap);
	//添加敌船
	void addEnemyShip();
	//对搜索路径的方向优先顺序进行重新排序
	void randomSort();
	//更新武器冷却时间的定时回调方法
	void weaponsCoolTimeUpdate();
	//删除船只的方法
	void removeShipUpdate();
	//游戏开始的回调方法
	void startCallback();
	//游戏开始前倒计时的方法
	void gameStartDJS();
	//定时更新武器状态的方法
	void weaponeStateUpdate();
	//计算导弹Z坐标的方法
	float callPointZ(float x,Weapon* weaponSp);
	//计算导弹Y坐标的方法
	float callPointY(float x,Weapon* weaponSp);
	//计算导弹在运行过程中的旋转角度的方法
	float callDegree(float x,Weapon* weaponSp);
	//导弹到达指定位置后，判断在冲击范围内是否在船只能被摧毁的方法
	void destroyEnemyShip(Weapon* weapone);
	//删除船只时播放的爆炸效果的方法
	void removeShipPlayEffect(Point tempP);
	//计算船只
	void calNearestSmartIn();
	//计算两个船只距离的方法
	float dis(WarShipObject* d1,WarShipObject* d2);
	//计算两点之间的距离
	float callTwoPointDis(Point startPoint,Point EndPoint);
	//当敌船在航母周围时
	void enemyShipAtHKMJUpdate();
	//航空母舰掉血
	void reduceBlood();
	//游戏结束的方法               1为游戏失败，0为胜利
	void gameOver();
	//重新开始或继续游戏
	void restartCallback();
	//退出游戏，回主菜单
	void tcCallback();
	//海洋效果滚屏
	void oceanUpdate();
	//瞬间杀死全部敌船
	void desAllEnemyShip();
	//航空母舰的必杀技冷却定时回调
	void playerHKMJCoolTimeUpdate();
	//航空母舰的必杀技，飞机
	void planeFlyAtShip();
	void planeUpdate();
	void RecoveryStateCallback();
	void playSound();
	CREATE_FUNC(GameLayer);
};

#endif
