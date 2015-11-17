#ifndef _AboutLayer_H_
#define _AboutLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class AboutLayer : public Layer
{
public:
	//��������ָ��
	GameSceneManager* sceneManager;
public:
	//��ʼ������
	virtual bool init();
	//����ס�˵���
	void menuCallback(Ref* pSender);
	CREATE_FUNC(AboutLayer);
};

#endif
