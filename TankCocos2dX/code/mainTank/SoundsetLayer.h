#ifndef _SoundsetLayer_H_
#define _SoundsetLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class SoundsetLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//初始化方法
	virtual bool init();
	//初始化菜单
	void initMenu();
	//菜单子项
	MenuItemImage *musicItem;
	MenuItemImage *effectItem;
	//菜单按钮功能
	void musicChange();
	void musicRefresh();
	void effectChange();
	void effectRefresh();
	//跳转到菜单界面
	void toMenuLayer();

	CREATE_FUNC(SoundsetLayer);
};
#endif
