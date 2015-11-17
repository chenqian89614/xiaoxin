#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class GameLayer : public Layer
{
public:
	Sprite* background;
	GameSceneManager* sceneManager;
public:
	//��ʼ�������ķ���
	virtual bool init();
	//��ȡ�����
	int random();
	//
	NodeGrid* effectNode;
	//
	void menuCallback0(Ref* pSender);
	void menuCallback1(Ref* pSender);
	void menuCallback2(Ref* pSender);
	//
	void initTitle();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(GameLayer);
};

#endif
