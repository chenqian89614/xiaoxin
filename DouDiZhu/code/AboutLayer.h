#ifndef __AboutLayer_H__
#define __AboutLayer_H__

#include "PokerSceneManager.h"


class AboutLayer : public cocos2d::Layer
{
public:
	PokerSceneManager* psm;

public:
	//初始化的方法
	virtual bool init();
	//返回
	void menuReturnCallback(Ref* sender);

	CREATE_FUNC(AboutLayer);
};

#endif
