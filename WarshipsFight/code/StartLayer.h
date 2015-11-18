#ifndef __StartLayer_H__
#define __StartLayer_H__

#include "cocos2d.h"
#include "WarshipsFightSceneManager.h"
using namespace cocos2d;

class StartLayer : public cocos2d::Layer
{
public:
	WarshipsFightSceneManager* wfsm;
	Sprite* aboutTTSp;
	Sprite* bwSp[6];
	Sprite* czcdSp;
	MenuItemImage* startItem ;
	MenuItemImage* aboutItem;
	MenuItemImage* helpItem;
	MenuItemImage* bselItem;
	MenuItemImage* closeItem;

	Sprite3D* plane3D;
	Sprite3D* palne3D;
	int deltaDis = 24;
	float deltaAngle = 0;
	bool upFlag = false;
	Sprite3D* earth3D;
	bool selAbout = false;
	LabelAtlas* sdsLabel;
	LabelAtlas* moneyLabel;
	int helpIndex = 0;
	Sprite* spHelp;
	bool showPNG = false;

	Point currPoint;
	int deltaAngleY = 0;
	bool helpFlag = false;
	Sprite3D* helpCube;
	int helpCubeLastAngle = 0;

	//��ʼ���ķ���
	virtual bool init();
	void initSound();
	void initMenuItem();
	void selBTCallback();
	void clearCallback();
	void startCallback();
	void aboutCallback();
	void helpCallback();
	void closeMenuCallback();
	void firstEnter();
	void setBWPosition();
	void sureCallback();
	void cancleCallback();
	void ball3DRotateUpdate();
	void gameCloseCallback();
	//���������ķ���
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

    //Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
    //��������Ӧ�ĳ�ʼ�����ͷŹ���
    CREATE_FUNC(StartLayer);
};

#endif
