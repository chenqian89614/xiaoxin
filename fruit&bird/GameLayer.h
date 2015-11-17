#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class GameLayer : public Layer
{
public:
	Sprite* background;
	GameSceneManager* sceneManager;
public:
	//初始化布景的方法
	virtual bool init();
	//获取随机数
	int random();
	//
	NodeGrid* effectNode;
	//
	void menuCallback0(Ref* pSender);
	void menuCallback1(Ref* pSender);
	void menuCallback2(Ref* pSender);
	//
	void initTitle();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(GameLayer);
};

#endif
