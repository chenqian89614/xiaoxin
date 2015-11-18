#ifndef  _ChooseLayer_H_
#define  _ChooseLayer_H_
#include "GameSceneManager.h"
#include "AppMacros.h"

#include "cocos2d.h"
using namespace cocos2d;

//自定义的布景类
class ChooseLayer : public cocos2d::Layer
{
public:
	//声明菜单对象
	Menu* pMenu;
	//声明场景所属管理者
	GameSceneManager *man;
	//声明一个切换关卡用到的全局变量
	static int modeLevel;
	//初始化的方法
    virtual bool init();

    //点击关卡1-5的回调方法
    void oneMode(Object* pSender);
    void twoMode(Object* pSender);
    void threeMode(Object* pSender);
    void fourMode(Object* pSender);
    void fiveMode(Object* pSender);
    //返回按钮点击回调方法
    void sixMode(Object* pSender);

    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(ChooseLayer);
};

#endif
