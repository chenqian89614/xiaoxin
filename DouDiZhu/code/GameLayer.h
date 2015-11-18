#ifndef __PokerLayer_H__
#define __PokerLayer_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PokerSceneManager.h"
#include "PuKe.h"

using namespace cocos2d;
using namespace std;
using namespace ui;

class GameLayer : public cocos2d::Layer
{
public:
	//用于显示时间的
	LabelTTF* timeLabel;
	//地主头像
	Sprite *dizhuHeadImage[3];
	//农民头像
	Sprite *nongminHeadImage[3];
	//玩家图标
	Sprite *unKnow[3];
	//有牌权状态
	Sprite *actKnow[3];
	//未得到牌权状态
	Sprite *deKnow[3];
	//牌的背景图，包括剩余三张的和玩家的
	Sprite *poke[5];
	//准备手势
	Sprite *ready[3];
	//不出
	Sprite *buchu[3];
	//加倍字样
	Sprite *bei2;			//加倍
	//=====为每个玩家创建字样===
	Sprite *playerSprite[5];
	Sprite *nextPlayerSprite[5];
	Sprite *lastPlayerSprite[5];
	//========背景框
	Sprite *setBack;		//设置背景框
	Sprite *yesOrNo;		//离开背景框
	Sprite *mask[54];		//选中背景框
	//不能触摸的精灵
	Sprite *chuSprite;		//出牌灰色
	Sprite *resetSprite;	//重选灰色
	//用于翻牌的精灵===
	//三张牌的精灵
	Sprite* firstCard;
	Sprite* secondCard;
	Sprite* thirdCard;
	//游戏结束
	Sprite* gameOverSprite[4];
	//王炸图片
	Sprite* wangDropSprite;
	//炸弹
	Sprite* zhaDropSprite;
	Sprite* planeSprite;
    //三张牌的反面以及共有的正面图
    Texture2D* pzm;		//牌正面图
    Texture2D* pfm;		//牌反面图
    //三张牌，当前正反面
    Texture2D* zm;		//当前牌精灵正面图
    Texture2D* fm;		//当前牌精灵反面图
    //临时三张牌的X坐标，锁定坐标
    float firstX;
    float secondX;
    float thirdX;
	//每张牌的旋转角度
    float angle=0;
    //每个牌的列和行
    int firstRow;
    int firstCol;
    int secondRow;
    int secondCol;
    int thirdRow;
    int thirdCol;
	//=============菜单
	Menu *orderMenu;		//叫地主
	Menu *noOrderMenu;		//不叫
	Menu *readyMenu;		//准备
	Menu *qdzMenu;			//抢地主
	Menu *bqMenu;			//不抢地主
	Menu *chuMenu;			//出牌
	Menu *resetMenu;		//重选
	Menu *buChuMenu;		//不出
	Menu *tiShiMenu;		//提示
	//vector
	std::vector<Sprite*> *tempCardVector0;	//
	std::vector<Sprite*> *tempCardVector1;	//
	std::vector<Sprite*> *tempCardVector2;	//
	std::vector<Sprite*> *vecPuKe;		//	存放本家扑克id的容器
	//animate 王炸
	Animate *animateWang;
	SpriteFrame *SpriteFrameWang[10];
	Sprite *wangSprite;
	//Animate 炸弹
	Animate *animateZha;
	SpriteFrame *SpriteFrameZha[9];
	Sprite *zhaSprite;

	LabelAtlas *bLabelAtlas;
	LabelAtlas *labelAtlas;//当前玩家的LabelAtlas,id=0
	LabelAtlas *lastLabelAtlas;//上一玩家LabelAtlas，id=2
	LabelAtlas *nextLabelAtlas;//下一玩家LabelAtlas，id=1
	bool checkCreate = false;//是否创建复选框
	bool exit = false;//是否创建离开对话框
	bool set = false;//用于判断设置背景框是否可见
	bool first = true;//是否第一次按下返回键
	bool animZha=false;//删除换帧精灵标志位

	double beginX;
	double beginY;
	double moveX;
	double moveY;



	int iCount=0;//扑克
	int rulePuKe=0;
	int array[17];
	PuKe*(puke) [54];
	PuKe*(player) [20];
	PuKe*(last) [20];
	PuKe*(next) [20];

public:
	PokerSceneManager *psm;
	//添加游戏中用到的精灵
	void addSprite();
	//添加LabelAltals
	void addLabel();
	//添加菜单项
	void addMenuItem();
	//开始叫地主
	void addOrderOrNo();
	//添加抢地主和不抢地主
	void addQiangOrNo();
	//添加定时回调
	void addUpdate();
	//设置三张牌旋转
	void createRotate();
	//王炸换帧精灵
	void initWang();

	void initZhaDan();
	//初始化扑克，分割
	void initPuKe();
	//设置倍数顺序执行
	void setBeiMove();

	//初始化的方法
	virtual bool init();
	int random();
	void preloadMuiscOrEffect();
	//播放音效
	void playOrderOrRob();
	//游戏开始，按钮的创建
	void playGameBtn();
	//想服务器发送一些出牌前的判断
	void isChuPai();
	//画已经出的牌
	void HadCard();
	//删除换帧精灵
	void removeAnimSprite();
	//设置飞机的位置
	void setPlaneMess();

	//touch
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	//call back
	void menuReadyCallback(Ref* sender);
	void menuSetCallback(Ref* sender);
	void menuExitCallback(Ref* sender);//离开游戏
	void menuQiangCallback(Ref* sender);//抢地主事件处理方法
	void menuNoQiangCallback(Ref* sender);//不抢地主事件处理方法
	void menuChaCallback(Ref* sender);//2倍设置位置以及显示
	void menuPlayCallback(Ref* sender);//开始游戏,出牌
	void menuResetCallback(Ref* sender);//重选
	void menuBuChuCallback(Ref* sender);//不出回调方法
	void menuTishi(Ref* sender);	//tishi

	void menuOkCallback(Ref* sender);
	void menuCancelCallback(Ref* sender);
	void menuOrderCallback(Ref* sender);//叫
	void menuNoOrderCallback(Ref* sender);//不叫
	void gameOver(Ref* sender);	//游戏结束
	//复选框回调方法
	void menuEffectCallback(Ref* pSender,CheckBox::EventType type);
	void menuMusicCallback(Ref* pSender,CheckBox::EventType type);

	//=========定时回调方法==============
	//定时回调17次，发牌
	void update_puke();
	//绘制其他玩家的状态
	void updateDrawOther(float dt);
	//定时回调用于牌的旋转
	void updateRotate(float ft);
	//绘制其他玩家手牌数目、
	void updateDrawOtherCards();
	//画本家牌
	void updatePuke(float dt);
	//获取系统时间
	void getSystemTime(float dt);
	//播放各种音效
	void updatePlayEffect(float dt);
	void gameDataReset();
    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(GameLayer);
};

#endif
