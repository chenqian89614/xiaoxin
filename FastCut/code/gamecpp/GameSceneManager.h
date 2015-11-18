#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"

using namespace cocos2d;

//用于创建场景的类
class GameSceneManager
{
public:
	Scene* welcomeScene;//欢迎界面场景指针
	Scene* gameScene;//游戏场景指针
	Scene* choiceScene;//选项场景指针
	Scene* HelpScene;//帮助场景指针
	Scene* Round2Scene;//第二关场景指针
	Scene* Round3Scene;//第三关场景指针
	Scene* Round4Scene;//第四关场景指针
	Scene* Round5Scene;//第五关场景指针
	Scene* Round6Scene;//第六关场景指针
	Scene* levelScene;//选关场景指针；

	Scene* setScene;//系列场景指针
//	//创建场景对象的方法
//    static cocos2d::Scene* createScene();
	//创建场景对象的方法
	void createScene();

    void gogameScene();//去游戏场景的方法

    void reStart();//第一关重新开始的方法
    void reStart2();//第二关重新开始的方法
    void reStart3();//第三关重新开始的方法
    void reStart4();//第四关重新开始的方法
    void reStart5();//第五关重新开始的方法
    void reStart6();//第六关重新开始的方法
    void goChoiceScene();//去选项场景的方法
    void goWelcomeScene();//回欢迎场景的方法
    void goRound2Scene();//去第二关场景
    void goRound3Scene();//去第三关场景
    void goRound4Scene();//去第四关场景
    void goRound5Scene();//去第五关场景
    void goRound6Scene();//去第六关场景
    void goLevelScene();//去选关场景

    void goSetScene();//去系列场景

    void goHelpScene();//去帮助场景

};

#endif
