#ifndef  _AchieveLayer_H_
#define  _AchieveLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "AppMacros.h"
#include <String>

using namespace cocos2d;
using namespace std;

//自定义的布景类
class AchieveLayer : public cocos2d::Layer
{
public:
	string glareScore[3];
	Label* labels;
	//声明背景精灵
	Sprite *backSprite;
    //Manager 对象的引用
    GameSceneManager *man;
    Menu* pMenu;
	//初始化的方法
    virtual bool init();
    void readScore();
    void saveScore(int);
    void menuCallBack(Object* pSende);

    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(AchieveLayer);
};

#endif
