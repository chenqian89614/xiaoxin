#ifndef _ControlLayer_H_
#define _ControlLayer_H_

#include "cocos2d.h"
#include "BNJoyStick.h"
#include "TankSceneManager.h"
#include "GameLayer.h"

USING_NS_CC;

class ControlLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//游戏状态
	int state=0;
	//创建摇杆对象
	BNJoyStick *tankStick;
	BNJoyStick *gunStick;
	//菜单
	Menu *menu;
	//拿到游戏Layer指针
	GameLayer *gameLayer;
	//创建生命值、分数、得分、暂停的精灵
	LabelAtlas *healthLabel;
	LabelAtlas *scoreLabel;
	void initView();

	//获得GameLayer指针
	void getGameLayer(GameLayer*);
	//初始化方法
	virtual bool init();
	//初始化摇杆
	void initJoy();
	//定时任务
	void update();//更新界面
	void sendKey();//发送摇杆信息
	//发送暂停信息
	void sendPause();
	//跳转到暂停界面
	void toPauseLayer();
	//跳转到菜单界面
	void toMenuLayer();
	//返回游戏
	void backGameLayer();

	CREATE_FUNC(ControlLayer);
};
#endif
