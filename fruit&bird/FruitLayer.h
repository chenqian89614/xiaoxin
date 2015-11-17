#ifndef __FruitLayer_H__
#define __FruitLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace ui;

class FruitLayer : public Layer
{
public:
	int count;
	int boss;
	bool stopFlag;
	bool bossFlag;
	bool gameFlag;
	bool readyFlag;
	bool overFlag;
	bool actionFlag;
	int height1;
	int height2;
	NodeGrid* effectNode;
	Sprite* bossSprite;
	//血条
	Slider* slider;
	LabelAtlas* pLabelAtlas;
	Sprite* overRank;
	MenuItemImage* relayItem;
	MenuItemImage* menuItem;
	Sprite* pauseBack;
	//声明暂停按钮精灵
	Sprite* pause;
	//
	Sprite* ready;
	//声明背景精灵
	Sprite* background;
	//声明地面精灵
	Sprite* floor;
	//声明柱子精灵
	Sprite* columnUnder1;
	Sprite* columnOn1;
	Sprite* columnUnder2;
	Sprite* columnOn2;
	//场景管理指针
	GameSceneManager* sceneManager;
	//存储水果对象
	vector<Sprite*>* fruit;
public:
	//初始化布景的方法
	virtual bool init();
	//开始游戏
	void startGame();
	//生成随机数方法
	int random();
	//初始化柱子
	void initColumn1();
	void initColumn2();
	//游戏结束
	void gameOver();
	//游戏失败
	void replay();
	void check();
	void moveObject();
	//播放音效
	void wingSound();
	void eatSound();
	//更改标志位
	void setFlag();
	//定时回调方法
	void update_fruit(float delta);
	void update_boss(float delta);
	void update_column(float delta);
	void menuCallback0(Ref* pSender);
	void menuCallback1(Ref* pSender);
	void menuCallback2(Ref* pSender);
	void menuCallback3(Ref* pSender);
	void menuCallback4(Ref* pSender);
	//复选框回调方法
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	//开始单点触控事件的处理方法
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchPause(Touch* touch, Event* event);
	CREATE_FUNC(FruitLayer);
};

#endif
