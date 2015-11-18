#ifndef __WarshipsFightSceneManager_H__
#define __WarshipsFightSceneManager_H__

#include "cocos2d.h"

using namespace cocos2d;
//用于创建场景的类
class WarshipsFightSceneManager
{
public:
	Scene* StartScene;
	Scene* ChooseLevelScene;
	Scene* GameScene;
	Scene* upgradeScene;

	//创建场景对象的方法
    void createScene();
    void goChooseLevelScene();
    void goGameScene();
    void goStartScene();
    void goPpgradeScene();
};

#endif
