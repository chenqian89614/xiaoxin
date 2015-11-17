#ifndef _SetLayer_H_
#define _SetLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class SetLayer : public Layer
{
public:
	//场景管理指针
	GameSceneManager* sceneManager;
public:
	//初始化父类
	virtual bool init();
	//返回住菜单键
	void menuCallBack(Ref* pSender);
	//复选框
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	CREATE_FUNC(SetLayer);
};

#endif
