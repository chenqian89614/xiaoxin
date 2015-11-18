#ifndef __LevelLayer_H__
#define __LevelLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

//自定义的布景类
class LevelLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	Sprite* bgSprite;//指向背景精灵的指针
	Menu* menu1;
	Menu* menu2;
	Menu* menu3;

	WelcomeLayer* wl;//欢迎界面的指针

	//初始化的方法
	virtual bool init();
	void set1(Object* pSender);//去系列1场景的方法
	void set2(Object* pSender);//去系列2场景的方法
	void set3(Object* pSender);//去系列3场景的方法
	void onBack();//返回菜单的回调方法
//	void update();//定时回调变换菜单大小
	~LevelLayer();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(LevelLayer);
};
#endif
