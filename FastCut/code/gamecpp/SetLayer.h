#ifndef __SetLayer_H__
#define __SetLayer_H__
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

class SetLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
//	Sprite* bgSprite;//ָ�򱳾������ָ��
//	Sprite* round1Marksprite;//��һ�ر�Ǿ���
//	Sprite* round2Marksprite;//�ڶ��ر�Ǿ���
	static int bgIdx;
	static int mark1Idx;
	static int mark2Idx;
	WelcomeLayer* wl;//��ӭ�����ָ��
	//��ʼ���ķ���
	virtual bool init();
	bool enterGame(Touch* touch,Event* event);//������Ϸ�ķ���
	void onBack();//���ز˵��Ļص�����
	~SetLayer();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(SetLayer);

};
#endif
