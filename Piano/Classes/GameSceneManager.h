#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"

using namespace cocos2d;

//用于创建场景的类
class GameSceneManager
{
public:
	Scene* logoScene;
	Scene* gameScene;
    Scene* loadScene;
public:
	//创建场景对象的方法
    void createScene();

    void goToGameScene();
    void goToLoadScene();
};

#endif
