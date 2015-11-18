#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"

//用于创建场景的类
class GameSceneManager
{
public:
	//创建场景对象的方法
    static cocos2d::Scene* createScene();
    //切换到帮助场景的方法
    void toHelpLayer();
    //切换到主场景的方法
    void toBeginLayer();
    //切换到选关场景的方法
    void toChooseLayer();
    //切换到得分记录场景方法
    void toAchieveLayer();
    //切换到游戏场景的方法
    void toGameLayer();
};

#endif
