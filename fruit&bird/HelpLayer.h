#ifndef __HelpLayer_H__
#define __HelpLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class HelpLayer : public Layer
{
public:
	GameSceneManager* sceneManager;

	Sprite* (sp)[4];
	//索引
	int index=0;
	Point beganPoint=Point(0,0);
	Point endPoint = Point(0,0);
	bool moveFlag=false;
public:
	//初始化布景的方法
	virtual bool init();
	//返回
	void menuCallBack(Ref* pSender);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void setmoveFlag();
	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(HelpLayer);
};
#endif
