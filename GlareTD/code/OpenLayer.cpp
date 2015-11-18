#include "OpenLayer.h"
#include "GameSceneManager.h"
#include "cocos2d.h"

#define pic_PRE_PATH_OpenLayer string("")

using namespace cocos2d;

//实现OpenLayer类中的init方法，初始化布景
bool OpenLayer::init()
{
    //调用父类的初始化
    if(!Layer::init())
    {
        return false;
    }

    //获取可见区域尺寸
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::sharedDirector()->getVisibleOrigin();
 

    //创建一个精灵对象，充当加载界面的精灵
	Sprite *bn = Sprite::create(pic_PRE_PATH_OpenLayer+string("open.png"));
	//设置精灵对象的位置
	bn->setPosition(Point(380,240));
	//把透明度设置为0
	bn->setOpacity(0);
	//将精灵添加到布景中
	this->addChild(bn,BACKGROUND_LEVEL_CGQ);
	ActionInterval *act=FadeIn::create(2.6f);
	ActionInterval *act2=act->reverse();
	bn->runAction(Sequence::create(
	act,
	act2,
	CallFunc::create(CC_CALLBACK_0(OpenLayer::playGameCallback,this)),
	NULL
	)
	);
    return true;
}

//实现OpenLayer类中的下一个菜单的回调方法
void OpenLayer::playGameCallback()
{
	  man->toBeginLayer();
}
