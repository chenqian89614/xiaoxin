#ifndef __BirdLayer_H__
#define __BirdLayer_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "GameSceneManager.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace ui;

class BirdLayer : public Layer
{
public:
	int columnNumber;
	//暂停标志位
	bool stopFlag;
	bool runFlag = false;
	//记录分数
	int count = 0;
	//穿过的柱子标志位
	bool columnFlag1;
	bool columnFlag2;
	//游戏开始标志位
	bool gameFlag;
	//游戏准备标志位
	bool readyFlag;
	//游戏结束标志位
	bool overFlag;
	//声明网格
	NodeGrid* effectNode;
	LabelAtlas* pLabelAtlas;
	Sprite* overRank;
	MenuItemImage* replayItem;
	MenuItemImage* menuItem;
	Sprite* pause;
	//声明背景精灵
	Sprite *background;
	//声明地面精灵
	Sprite *floor;
	//声明柱子精灵
	Scale9Sprite* columnUnder1;
	Scale9Sprite* columnOn1;
	Scale9Sprite* columnUnder2;
	Scale9Sprite* columnOn2;
	//声明小鸟精灵
	Sprite* bird;
	//声明ready精灵
	Sprite* ready;
	Sprite* pauseBack;
	//动画动作数组
	Animate* animAc;
	//场景管理指针
	GameSceneManager* sceneManager;
public:
	//初始化布景的方法
	virtual bool init();
	//初始化小鸟
	void initBird();
	//开始游戏
	void startGame();
	//游戏结束
	void gameOver();
	//小鸟运动
	void birdRun();
	//播放声音
	void wingSound();
	void pointSound();
	void hitSound();
	void dieSound();
	//滚动地面
	void update_column(float delta);
	//更新小鸟检测碰撞
	void update_bird(float delta);
	//游戏结束界面运动
	void moveObject();
	//初始化柱
	void initColumn1();
	void initColumn2();
	//生成随机数
	int random();
	//菜单
	void menuCallbackItem0(Ref* pSender);
	void menuCallbackItem1(Ref* pSender);
	void menuCallbackItem2(Ref* pSender);
	void menuCallbackItem3(Ref* pSender);
	void menuCallbackItem4(Ref* pSender);
	//复选框回调方法
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	//重玩界面
	void replay();
	//开始单点触控事件的处理方法
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchPause(Touch* touch, Event* event);
	void setRunFlag1();
	void setRunFlag2();

    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(BirdLayer);
};

#endif
