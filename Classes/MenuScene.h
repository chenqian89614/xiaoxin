#ifndef _MenuScene_H_
#define _MenuScene_H_

#include "cocos2d.h"
#include "GameMusic.h"
#include "ui\UIWidget.h"

USING_NS_CC;
using namespace ui;

class MenuScene : public Layer{

public:
	static Scene* createScene();
	CREATE_FUNC(MenuScene);
	virtual bool init();

private:
	void loadUI();                                       //载入cocos制作的开始界面UI
	//void onClick(Ref* object, TouchEventType type);     //按键触发总函数，用tag判断触发事件
	void onstartClick(Ref* object, TouchEventType type);     //开始按键触发函数

private:
	GameMusic* _music;
	
}



#endif
