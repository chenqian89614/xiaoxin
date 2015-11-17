#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"


using namespace cocos2d;

//���ڴ�����������
class GameSceneManager
{
public:
	//������������ķ���
    void createScene();
    void goFlyLayer();
    void goMenuLayer();
    void goLevelLayer();
    void goGameLayer(int index);
    void goMusicLayer();
    void goChoiceCubeLayer();
};
#endif

