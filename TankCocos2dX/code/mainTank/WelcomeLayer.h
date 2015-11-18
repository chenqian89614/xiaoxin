#ifndef _WelcomeLayer_H_
#define _WelcomeLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class WelcomeLayer : public Layer
{
public:
	//场景管理器
	TankSceneManager *tsm;
	//初始化方法
	virtual bool init();
	//跳转到菜单界面
	void toMenuLayer();

	CREATE_FUNC(WelcomeLayer);
};
#endif
