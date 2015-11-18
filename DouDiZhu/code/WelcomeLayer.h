#ifndef __WelcomeLayer_H__
#define __WelcomeLayer_H__

#include "cocos2d.h"
#include "PokerSceneManager.h"
using namespace cocos2d;

class WelcomeLayer : public cocos2d::Layer
{
public:
	PokerSceneManager *psm;
	LabelTTF* msgLabel;
    //Label* msgLabel;
    Menu *startMenu;
	Sprite *startImage;
	//��ʼ���ķ���
	void gotoGame();
	void jinruGame(float ft);
	virtual bool init();
	void backMusic();
	//��Ӳ˵���
	void addMenu();
	//��Ϸ��ʼͬʱ���ӵ�������
	void menuStartCallback(Ref* sender);
	//�����˵��ص�����
	void menuHelpCallback(Ref* sender);
	//���ڲ˵��ص�����
	void menuAboutCallback(Ref* sender);\
	//�˳���Ϸ
	void menuExitCallback(Ref* sender);
    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(WelcomeLayer);
};

#endif
