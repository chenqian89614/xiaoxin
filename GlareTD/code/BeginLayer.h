#ifndef __BeginLayer_H__
#define __BeginLayer_H__
#include "ChooseLayer.h"
#include "GameSceneManager.h"
#include "AchieveLayer.h"
#include "OpenLayer.h"
#include "AppMacros.h"

using namespace cocos2d;

class BeginLayer : public cocos2d::Layer
{
public:
	//所属Scene
	Scene *scene;
	//所属管理者
	GameSceneManager *man;
	Menu* pMenu;
	//初始化的方法
	virtual bool init();
	void oneMode(Object* pSender);
	void twoMode(Object* pSender);
	void setSence(Object* pSender);
	void helpSence(Object* pSender);

    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(BeginLayer);
};

#endif
