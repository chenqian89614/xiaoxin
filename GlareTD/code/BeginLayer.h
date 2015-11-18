#ifndef __BeginLayer_H__
#define __BeginLayer_H__
#include "ChooseLayer.h"
#include "GameSceneManager.h"
#include "AchieveLayer.h"
#include "OpenLayer.h"
#include "AppMacros.h"

using namespace cocos2d;

class BeginLayer : public cocos2d::Layer
{
public:
	//����Scene
	Scene *scene;
	//����������
	GameSceneManager *man;
	Menu* pMenu;
	//��ʼ���ķ���
	virtual bool init();
	void oneMode(Object* pSender);
	void twoMode(Object* pSender);
	void setSence(Object* pSender);
	void helpSence(Object* pSender);

    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(BeginLayer);
};

#endif
