#ifndef _PauseLayer_H_
#define _PauseLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class PauseLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//初始化方法
	virtual bool init();
	//菜单
	Menu *pauseMenu;
	Menu *soundsetMenu;
	//声音设置菜单项
	MenuItemImage *musicItem;
	MenuItemImage *effectItem;
	//跳转到soundset菜单
	void toSoundset();
	void toPause();
	//初始化菜单
	void initPauseMenu();
	void initSoundsetMenu();
	//菜单按钮功能
	void musicChange();
	void musicRefresh();
	void effectChange();
	void effectRefresh();
	//返回菜单
	void backMenu();
	//退出游戏
	void gameExit();
	//继续游戏
	void sendContinue();

	CREATE_FUNC(PauseLayer);
	virtual ~PauseLayer();
};
#endif
