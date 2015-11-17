#ifndef __MusicLayer_H__
#define __MusicLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "../frameHelp/MusicLayerHelp.h"
#include "../frameHelp/SpriteManager.h"

using namespace cocos2d;

class MusicLayer : public cocos2d::Layer
{
public :
	GameSceneManager *gsm;
	Size visibleSize;
	Point origin;
	Director* director;
	SpriteManager* sh;//精灵管理类  指针
	MusicLayerHelp* mlh;//MusicLayer帮助类指针

	virtual bool init();//初始化的方法

	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(MusicLayer);
};

#endif
