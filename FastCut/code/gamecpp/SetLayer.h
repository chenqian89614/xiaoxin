#ifndef __SetLayer_H__
#define __SetLayer_H__
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

class SetLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
//	Sprite* bgSprite;//指向背景精灵的指针
//	Sprite* round1Marksprite;//第一关标记精灵
//	Sprite* round2Marksprite;//第二关标记精灵
	static int bgIdx;
	static int mark1Idx;
	static int mark2Idx;
	WelcomeLayer* wl;//欢迎界面的指针
	//初始化的方法
	virtual bool init();
	bool enterGame(Touch* touch,Event* event);//进入游戏的方法
	void onBack();//返回菜单的回调方法
	~SetLayer();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(SetLayer);

};
#endif
