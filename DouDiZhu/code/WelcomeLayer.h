#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "PokerSceneManager.h"
using namespace cocos2d;

class WelcomeLayer : public cocos2d::Layer
{
public:
	PokerSceneManager *psm;
	LabelTTF* msgLabel;
    //Label* msgLabel;
    Menu *startMenu;
	Sprite *startImage;
	//初始化的方法
	void gotoGame();
	void jinruGame(float ft);
	virtual bool init();
	void backMusic();
	//添加菜单项
	void addMenu();
	//游戏开始同时连接到服务器
	void menuStartCallback(Ref* sender);
	//帮助菜单回调方法
	void menuHelpCallback(Ref* sender);
	//关于菜单回调方法
	void menuAboutCallback(Ref* sender);\
	//退出游戏
	void menuExitCallback(Ref* sender);
    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(WelcomeLayer);
};

#endif
