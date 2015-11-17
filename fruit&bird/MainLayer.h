#ifndef _MainLayer_H_
#define _MainLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class MainLayer : public Layer
{
public:
	Sprite* backGround;
	//
	NodeGrid* effectNode;
	//�������ֱ�־λ
	static bool musicFlag;
	//��Ч��־λ
	static bool soundFlag;
	//��������ָ��
	GameSceneManager* sceneManager;
public:
	virtual bool init();
	int random();
	void menuCallBack0(Ref* pSender);
	void menuCallBack1(Ref* pSender);
	void menuCallBack2(Ref* pSender);
	void menuCallBack3(Ref* pSender);
	void menuCallBack4(Ref* pSender);
	void menuCallBack5(Ref* pSender);
	void initTitle();
	CREATE_FUNC(MainLayer);
};

#endif
