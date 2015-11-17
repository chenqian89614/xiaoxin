#ifndef _GameLayer_H_
#define _GameLayer_H_

#include "GameSceneManager.h"
#include "cocos2d.h"
#include <vector>
#include "../objectHelp/Barrier.h"
#include "../objectHelp/JumpCube.h"
#include "../frameHelp/SpriteManager.h"
#include "../frameHelp/PauseCode.h"
#include "GDData.h"

using namespace cocos2d;


class GameLayer : public cocos2d::Layer
{
public:

	GameSceneManager *gsm;
	Director* director;
	Size visibleSize;
	Point origin;

	SpriteManager* sh;//精灵管理类  指针
	PauseCode* pc;//暂停代码指针
	GDData* gdData;

	bool isUpdateAll = true;//是否进行UpdateAll方法的回调

	int indexGK;

	JumpCube* jc;
	std::string* ids;
	Barrier* tb;
	Barrier* zh;
	std::vector<Barrier*>::iterator iter;

	std::map<std::string,Sprite*> spMap;

	std::vector<Barrier*> barrierVector;//存障碍物的vector

	int timeCountCollision = 0;//碰撞时间计数器
	int timeCount = 0;




	bool isTouch=false;

    virtual bool init();//初始化的方法


	//开始触控事件的处理方法
	bool myOnTouchBegan(Touch *touch, Event *event);
	//触控移动事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event);
	//触控结束事件的处理方法ew
	void myOnTouchEnded(Touch *touch, Event *event);
	//触控终止事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event);

	void updateAll();//更新所有的方法
	void deleteBarrier();//删除 出屏幕的 障碍物  的方法
	void collisionDetection();//碰撞检测方法
	void initObjectOrSprite();//初始化 背景 、  地面物体  和  跳跃的方块
	void refleshJumpCube();
	void updateBarrier();

    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(GameLayer);
};

#endif
