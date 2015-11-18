#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class WelcomeLayer : public cocos2d::Layer
{
public:
	//Manager 对象的引用
	GameSceneManager* sceneManager;
	//初始化的方法
	virtual bool init();
	void musicLoad();
	//执行特效菜单的回调方法
	void goToLoad();
	//CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(WelcomeLayer);
};

#endif
