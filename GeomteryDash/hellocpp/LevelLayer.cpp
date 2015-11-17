#include "LevelLayer.h"
#include "../frameHelp/SpriteManager.h"
#include "Constant.h"

bool LevelLayer::init()
{
	//调用父类的初始化
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_LEVELLAYER);//设置节点的标签

    visibleSize = Director::getInstance()->getVisibleSize();//获取可见区域尺寸
	origin = Director::getInstance()->getVisibleOrigin();//获取可见区域原点坐标

	sh = new SpriteManager(this);//精灵管理类
	llh = new LevelLayerHelp(this);//帮助类
	llh->initCreateSprite();//初始化 创建精灵

	indexLevel = 1;

	return true;
}

