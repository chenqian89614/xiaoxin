#ifndef _GameLayer_H_
#define _GameLayer_H_
#include "GameSceneManager.h"
#include "Weapon.h"
#include "DialogLayer.h"
#include "BulletSprite.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameLayer : public cocos2d::Layer
{
public:
	//构造函数
	GameLayer();
	//析构函数
	virtual ~GameLayer();
	//重载的父类的初始方法
	virtual bool init();
	Menu* pMenu;
	void zanTing(Object* pSender);
	//计算路径之前的一些容器的初始化
	void initForCalculate();
	//添加所有label
	void addLabel();
	//广度优先A*算法
    bool BFSAStar();
	//初始化去过未去过的数组
	void initVisitedArr();
	//释放内存
	void freeMemory();
	//声明计算路径的方法
    bool calculatePath();
	//打印最后的路径
	void printPath();
	//添加防御塔菜单精灵
	void addMenuSprite();
	//设置防御塔菜单精灵可见
	void setWeaponTrue();
    //准备方法--画圆型
    void ready();
    //声明怪从action数组里出来挨个走的方法
    void run();
    //创建多个怪
    void foundMonsters();
    //出怪的方法
    void monsterRun(Node* node);
    void removeSpriteAdd();
    //删除精灵的方法
    void removeSprite(Node* node);
    //将地图格子行列号转换为对应格子的贴图坐标
    Point fromColRowToXY(int col, int row);
    //将触控点位置转换为地图格子行列号
    Point fromXYToColRow(int xPos, int yPos);
	//出售防御塔的方法
	void sellWeapon(Weapon* weapon);
	//设置升级菜单精灵可见
	void setUpdateTrue();
	//设置升级金币
	void setValue();
	//触控开始的方法
    bool onTouchBegan(Touch *pTouch, Event *pEvent);
    //触控移动的方法
    void onTouchMoved(Touch *pTouch, Event *pEvent);
    //触控抬起的方法
    void onTouchEnded(Touch *pTouch, Event *pEvent);
    //出野怪时的特效
	void addParticle(Point point,float time);
	//野怪到终点时的特效
	void addParticle(Point point,int id,float time);
	//野怪死时的特效
	void addParticle1(Point point,int id,float time);
	//游戏结束时的爆炸特效
	void addParticle(Point point,int id,float time,float angle);
	void addParticle2(Point point,float time);
	//回调方法
	void menuCallbackItem0(Object *pSender);
	//攻击怪的方法
    void attack();
    //第一个防御塔攻击怪掉血的方法
	void fireBulletOne(int weap,int target,float dirction,Point position,float lengthVector);
	//第二个防御塔攻击怪掉血的方法
	void fireBulletTwo(int weap,int target,float dirction,Point position);
	//第三个防御塔攻击怪掉血的方法
	void fireBulletThree(int weap,int target,float dirction,Point position);
	//发射子弹的方法
	void runBullet();
	//怪掉血的方法
	void cutBloodOne(Node* node);
    //执行特效菜单的回调方法
    void playGameCallback();
    //游戏结束的方法
	void loseGame();
public:
	int bulletData[10];
	//声明指向DrawNode类对象的指针
	DrawNode* dn;
	//TMXLayer指针
	TMXLayer* tmxLayer;
	Point endWorld;
	//创建动作指针
	ProgressTimer *left;
	Sprite* particle;
	Sprite* bullet1;
	Sprite* cc;
	float TIME_MAIN;
	//半个图块的大小（即界面中路线的偏移量）此处要有一个调整值（参数为瓦片图片的半边宽，瓦片图片的半边高）
	Point trans;
	//当前分数的label
	LabelTTF *scoreL;
	//当前回合数的label
	LabelTTF *passL;
	//当前金钱
	LabelTTF *moneyL;
	//当前生命数
	LabelTTF *tenL;
	//显示升级武器所需金钱的label
	LabelTTF *uMoneyL;
	//显示出售武器获得的金钱的label
	LabelTTF *sMoneyL;
	//存放怪的数组
	Array* arrMon;
	//存放防御塔
	Array* arrWeap;
	//存放菜单防御塔精灵
	Array* arrMenu;
	//存放action动作
	Array* arrAction;
	//存放跟踪
	Array* arrBullet;
	//存放升级的菜单按钮精灵
	Array* arrSellUpdate;
	//设置世界坐标系
	Point startWorld;
	//怪运动标志位
	bool isMonsterRun ;
	//创建怪的标志位
	bool isfoundMonster;
	//场景管理制指针
	GameSceneManager* man;
	//算法计算完毕的标志位
	bool isCaulateOver;
	//声明表示生命值的对象
	int ten;
	//玩家的金币
	int money;
	//开始标志精灵
	Sprite* startSprite;
	//野怪精灵对象
	Sprite *ygSprite;
	//目标精灵
	Sprite* targetSprite;
	//地图的row
	int row;
	//地图的col
	int col;
	//以竖放向来看（从左至右，从上至下）以下为动态二维数组的创建
	int** MAP_DATA;
	//存放路径的数组
	vector <Point > way;
	vector <int> bulletArray;
	//记录路径长度
	int** length;
	//广度优先所用队列
	queue<int(*)[2]>* myQueue;
	//结果路径记录
	map<string, int(*)[2]>* hm;
	//typedef自定义类型
	typedef vector<int(*)[2]>* INTPVECTORP;
	//第一次点击在菜单位置标志位
	bool touchMove = false;
	//在touchEnd里是否移除防御塔的标志位
	bool removeWeap;
	//多少批怪计数
	int pass;
	//当前总得分数
	int score;
	//升级的武器
	Weapon* updateWeapon;
	//武器升级的标志位
	bool WeaponUpdate;
	//声明游戏结束的标志位
	bool GameOver;
	//暂停游戏的标志位
	static bool isPause;

	//声明创建防御塔时的光圈精灵对象
	Weapon* trSprite;
	//声明四个菜单防御塔的精灵对象
	Weapon *onePlayer;
	Weapon *twoPlayer;
	Weapon *threePlayer;
	Weapon *fourPlayer;

	CREATE_FUNC(GameLayer);
};

#endif
