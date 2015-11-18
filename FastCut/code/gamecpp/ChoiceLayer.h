#ifndef __ChoiceLayer_H__
#define __ChoiceLayer_H__
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;
class ChoiceLayer : public cocos2d::Layer
{
public :
	GameSceneManager* gsm;
	Sprite* bgSprite;//��������
	Sprite* dibanSprite;//�װ徫��
	Sprite* music;//���־���
	Sprite* sound;//��������
	static bool isMusic;//�Ƿ񲥷����ֱ�־λ
	static bool isSound;//�Ƿ񲥷���Ч��־λ
    static int escChoiceCount;//��¼���·��ؼ��Ĵ���

	WelcomeLayer* wl;//��ӭ�����ָ��
	//��ʼ���ķ���
	virtual bool init();
	bool controlMusic(Touch* touch,Event* event);//�����������صķ���

	void onBack();//���ز˵��Ļص�����
	~ChoiceLayer();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(ChoiceLayer);
};

#endif
