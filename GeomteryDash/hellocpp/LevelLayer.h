#ifndef __LevelLayer_H__
#define __LevelLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "../frameHelp/LevelLayerHelp.h"
#include "../frameHelp/SpriteManager.h"

using namespace cocos2d;

class LevelLayer : public cocos2d::Layer
{
public :
	GameSceneManager *gsm;
	Size visibleSize;
	Point origin;
	Director* director;
	SpriteManager* sh;//精灵管理类  指针
	LevelLayerHelp* llh;//LevelLayer帮助类指针

	int indexLevel;//关卡界面索引

	virtual bool init();//初始化的方法

	//Cocos2d-x中定义的一个宏，创建指定类型的对象
	//并做好相应的初始化与释放工作
	CREATE_FUNC(LevelLayer);
};

#endif
