#ifndef __AboutLayer_H__
#define __AboutLayer_H__

#include "PokerSceneManager.h"


class AboutLayer : public cocos2d::Layer
{
public:
	PokerSceneManager* psm;

public:
	//��ʼ���ķ���
	virtual bool init();
	//����
	void menuReturnCallback(Ref* sender);

	CREATE_FUNC(AboutLayer);
};

#endif
