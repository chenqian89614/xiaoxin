#ifndef _MenuLayer_H_
#define _MenuLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//所属scene
	Scene *scene;
	//3d精灵
	Sprite3D *sp3;
	int degree=0;
	//初始化方法
	virtual bool init();
	//初始化菜单
	void initMenu();
	//初始化3D精灵
	void init3D();
	//菜单按钮功能
	void gameStart();
	void gameHelp();
	void setSound();
	void gameExit();
	//定时回调方法
	void update();
	//跳转到菜单界面
	void toGameLayer();
	//初始化标题和图片
	static void initTitle(Layer *layer);

	CREATE_FUNC(MenuLayer);
};
#endif
