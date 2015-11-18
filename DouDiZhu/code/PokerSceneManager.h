#ifndef __PokerSceneManager_H__
#define __PokerSceneManager_H__

#include "cocos2d.h"
using namespace cocos2d;

//用于创建场景的类
class PokerSceneManager
{
public:
	Scene* firstScene;
	Scene* gameScene;
	Scene* welScene;
	Scene* aboutScene;
	Scene* helpScene;
	void createScene();
	void goGame();
	void goAbout();
	void goWelcome();
	void playEffect();
	void goHelp();
};

#endif
