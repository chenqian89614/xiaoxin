#ifndef __CityRacingSceneManager_H__
#define __CityRacingSceneManager_H__

#include "cocos2d.h"
using namespace cocos2d;
//用于创建场景的类
class CityRacingSceneManager
{
public:
	//声明场景指针
	Scene* startScene;
	Scene* chooseCarscene;
	Scene* gameScene;
	Scene* mainScene;
	Scene* levelScene;
	Scene* shopScene;
	Scene* gameOverSceen;
	Scene* PHBScene;
	Scene* helpScene;

	//创建场景对象的方法
    cocos2d::Scene* createScene();
    void goStartLyaer();
    void goChooseCarLayer();
    void goGameLayer();
    void goMainLayer();
    void goChooseLevelLayer();
    void goShopLayer();
    void goGameOverLayer();
    void goPHBLayer();
    void goHelpLayer();
};
#endif
