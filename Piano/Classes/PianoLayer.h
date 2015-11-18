#ifndef __PianoLayer_H__
#define __PianoLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

#include <map>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;
using namespace ui;

class PianoLayer : public cocos2d::Layer
{
public:
	bool musicFlag;						//播放音乐标志位
	bool pauseFlag;						//暂停标志位
	bool changeFlag;					//调度器标志位
	int temp[10];						//用于判断黑键是否处于点击状态数组
	int index;							//黑键所处第几号白键
	int degree;							//3D模型转动的角度
	int touchIndex[10];					//当前所点击白键的编号
	int blackIndex[10];					//当前所点击黑键的编号
	int instrumentNumber;				//记录乐器的编号
	int musicNum;						//加载音乐编号
	float percent;						//当前选择框所处的位置百分比
	float timeL;						//向左移动的时间
	float timeR;						//向右移动的时间
	string instrumentName;				//乐器名字
	Scheduler* schedRound;				//线程
	Slider* slider;						//拖拉条
	Size sSize;							//选择乐器框尺寸
	Size menuSize;						//背景框尺寸大小
	Size leftSize;						//左箭头精灵尺寸大小
	Size rightSize;						//右箭头精灵尺寸大小
	Size smallSize;						//小白键
	Size volumeSize;					//音量尺寸大小
	Size whiteSize;						//白键精灵尺寸大小
	Size blackSize;						//黑键精灵尺寸大小
	Size backSize;						//选键框尺寸大小
	Size sliderSize;					//拖拉条尺寸大小
	Sprite* menuBack;					//菜单背景框精灵
	Sprite* underside;					//底面精灵
	Sprite* selection;					//乐器背景精灵
	Sprite* instrument;					//乐器精灵
	Sprite* selectBack;					//选择框精灵
	Sprite* exit;						//退出精灵
	GameSceneManager* sceneManager;		//场景指针
	map<string, Sprite*> piano;			//白键容器
	map<string, Sprite*> piano_black;	//黑键容器
	map<string, Sprite*> select;		//选择菜单乐器容器
public:
    virtual ~PianoLayer();
	//初始化的方法
	virtual bool init();
	void changePic(int number);
	void deleteSelf();
	void sliderEvent(Ref *pSender, Slider::EventType type);
	void percentUpdate();

	//退出触摸开始回调方法
	bool onTouchExitBegan(Touch* touch, Event* event);
	//选择框触摸回调方法
	bool onTouchSelectBegan(Touch* touch, Event* event);
	void onTouchSelectMoved(Touch* touch, Event* event);
	//向左按钮触摸回调方法
	bool onTouchLeftBegan(Touch* touch, Event* event);
	void onTouchLeftEnded(Touch* touch, Event* event);
	//向右按钮触摸回调方法
	bool onTouchRightBegan(Touch* touch, Event* event);
	void onTouchRightEnded(Touch* touch, Event* event);
	//选择乐器触摸回调方法
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	//点击拖拉条设置位置
	bool onMyTouchBegan(Touch* touch, Event* event);
	//点击选择框
	bool onTouchBeganInstrument(Touch* touch, Event* event);
	void onTouchEndedInstrument(Touch* touch, Event* event);
	//开始多点触控事件的处理方法
	void onMyTouchesBegan(const std::vector<Touch*>& pTouches, Event *pEvent);
	//多点触控移动事件的处理方法
	void onMyTouchesMoved(const std::vector<Touch*>& pTouches, Event *pEvent);
	//多点触控结束事件的处理方法
	void onMyTouchesEnded(const std::vector<Touch*>& pTouches, Event *pEvent);
	//定时回调更新百分比
	void update(float delta);
    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作s
    CREATE_FUNC(PianoLayer);
};

#endif
