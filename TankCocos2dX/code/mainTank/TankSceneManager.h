#ifndef  _TankSceneManager_H_
#define  _TankSceneManager_H_

#include "cocos2d.h"

USING_NS_CC;

class TankSceneManager
{
public:
	//创建场景对象的方法
	static Scene* WelcomeCreate();
	//跳转到菜单界面
	void toMenuLayer();
	//跳转到声音设置界面
	void toSoundsetLayer();
	//跳转到游戏帮助界面
	void toHelpLayer();
	//跳转到游戏界面
	void toGameLayer();
	//跳转到选择界面
	void toSelectLayer();
	//返回菜单
	static void backMenuLayer();
	//生成背景精灵
	static Sprite* getGround();
};
#endif
