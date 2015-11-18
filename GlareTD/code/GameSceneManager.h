#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"

//���ڴ�����������
class GameSceneManager
{
public:
	//������������ķ���
    static cocos2d::Scene* createScene();
    //�л������������ķ���
    void toHelpLayer();
    //�л����������ķ���
    void toBeginLayer();
    //�л���ѡ�س����ķ���
    void toChooseLayer();
    //�л����÷ּ�¼��������
    void toAchieveLayer();
    //�л�����Ϸ�����ķ���
    void toGameLayer();
};

#endif
