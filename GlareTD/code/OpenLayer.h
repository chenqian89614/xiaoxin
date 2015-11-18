#ifndef  _OpenLayer_H_
#define  _OpenLayer_H_
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "BeginLayer.h"
#include "AppMacros.h"

using namespace cocos2d;

//自定义的布景类
class OpenLayer : public cocos2d::Layer
{
public:
    //Manager 对象的引用
    GameSceneManager *man;
	//初始化的方法
    virtual bool init();
    //执行特效菜单的回调方法
    void playGameCallback();

    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(OpenLayer);
};

#endif
