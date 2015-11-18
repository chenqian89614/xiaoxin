#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class WelcomeLayer : public cocos2d::Layer
{
public:
	//Manager ���������
	GameSceneManager* sceneManager;
	//��ʼ���ķ���
	virtual bool init();
	void musicLoad();
	//ִ����Ч�˵��Ļص�����
	void goToLoad();
	//CCPlatformMacros.h�ļ��ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(WelcomeLayer);
};

#endif
