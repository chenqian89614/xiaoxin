#ifndef __WarshipsFightSceneManager_H__
#define __WarshipsFightSceneManager_H__

#include "cocos2d.h"

using namespace cocos2d;
//���ڴ�����������
class WarshipsFightSceneManager
{
public:
	Scene* StartScene;
	Scene* ChooseLevelScene;
	Scene* GameScene;
	Scene* upgradeScene;

	//������������ķ���
    void createScene();
    void goChooseLevelScene();
    void goGameScene();
    void goStartScene();
    void goPpgradeScene();
};

#endif
