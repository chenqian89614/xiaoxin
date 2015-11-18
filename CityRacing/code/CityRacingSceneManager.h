#ifndef __CityRacingSceneManager_H__
#define __CityRacingSceneManager_H__

#include "cocos2d.h"
using namespace cocos2d;
//���ڴ�����������
class CityRacingSceneManager
{
public:
	//��������ָ��
	Scene* startScene;
	Scene* chooseCarscene;
	Scene* gameScene;
	Scene* mainScene;
	Scene* levelScene;
	Scene* shopScene;
	Scene* gameOverSceen;
	Scene* PHBScene;
	Scene* helpScene;

	//������������ķ���
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
