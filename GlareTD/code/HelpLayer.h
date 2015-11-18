#ifndef  _HelpLayer_H_
#define  _HelpLayer_H_
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;
//自定义的布景类
class HelpLayer : public cocos2d::Layer
{
public:
	GameSceneManager *man;
	Menu* pMenu;
	Sprite* helpSprite;
	Sprite* help[9];
	//索引
	int currPicIndex=0;
	//初始化的方法
    virtual bool init();
    void initIntroPic();
    void menuCallBack0(Object* pSende);
    void menuCallBack1(Object* pSende);
    void menuCallBack2(Object* pSende);

    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(HelpLayer);
};

#endif
