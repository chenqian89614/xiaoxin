#ifndef  _OpenLayer_H_
#define  _OpenLayer_H_
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "BeginLayer.h"
#include "AppMacros.h"

using namespace cocos2d;

//�Զ���Ĳ�����
class OpenLayer : public cocos2d::Layer
{
public:
    //Manager ���������
    GameSceneManager *man;
	//��ʼ���ķ���
    virtual bool init();
    //ִ����Ч�˵��Ļص�����
    void playGameCallback();

    //CCPlatformMacros.h�ļ��ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(OpenLayer);
};

#endif
