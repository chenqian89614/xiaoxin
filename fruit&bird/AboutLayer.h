#ifndef _AboutLayer_H_
#define _AboutLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class AboutLayer : public Layer
{
public:
	//场景管理指针
	GameSceneManager* sceneManager;
public:
	//初始化父类
	virtual bool init();
	//返回住菜单键
	void menuCallback(Ref* pSender);
	CREATE_FUNC(AboutLayer);
};

#endif
