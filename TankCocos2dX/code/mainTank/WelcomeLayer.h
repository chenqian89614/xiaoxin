#ifndef _WelcomeLayer_H_
#define _WelcomeLayer_H_

#include "cocos2d.h"
#include "TankSceneManager.h"

USING_NS_CC;

class WelcomeLayer : public Layer
{
public:
	//����������
	TankSceneManager *tsm;
	//��ʼ������
	virtual bool init();
	//��ת���˵�����
	void toMenuLayer();

	CREATE_FUNC(WelcomeLayer);
};
#endif
