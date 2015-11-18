#ifndef __LevelLayer_H__
#define __LevelLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

//�Զ���Ĳ�����
class LevelLayer : public cocos2d::Layer
{
public:
	GameSceneManager* gsm;
	Sprite* bgSprite;//ָ�򱳾������ָ��
	Menu* menu1;
	Menu* menu2;
	Menu* menu3;

	WelcomeLayer* wl;//��ӭ�����ָ��

	//��ʼ���ķ���
	virtual bool init();
	void set1(Object* pSender);//ȥϵ��1�����ķ���
	void set2(Object* pSender);//ȥϵ��2�����ķ���
	void set3(Object* pSender);//ȥϵ��3�����ķ���
	void onBack();//���ز˵��Ļص�����
//	void update();//��ʱ�ص��任�˵���С
	~LevelLayer();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(LevelLayer);
};
#endif
