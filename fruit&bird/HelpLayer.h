#ifndef __HelpLayer_H__
#define __HelpLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class HelpLayer : public Layer
{
public:
	GameSceneManager* sceneManager;

	Sprite* (sp)[4];
	//����
	int index=0;
	Point beganPoint=Point(0,0);
	Point endPoint = Point(0,0);
	bool moveFlag=false;
public:
	//��ʼ�������ķ���
	virtual bool init();
	//����
	void menuCallBack(Ref* pSender);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void setmoveFlag();
	//Cocos2d-x�ж����һ���꣬����ָ�����͵Ķ���
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(HelpLayer);
};
#endif
