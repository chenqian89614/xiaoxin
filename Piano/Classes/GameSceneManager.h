#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"

using namespace cocos2d;

//���ڴ�����������
class GameSceneManager
{
public:
	Scene* logoScene;
	Scene* gameScene;
    Scene* loadScene;
public:
	//������������ķ���
    void createScene();

    void goToGameScene();
    void goToLoadScene();
};

#endif
