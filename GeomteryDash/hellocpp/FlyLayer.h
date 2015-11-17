#ifndef _FlyLayer_H_
#define _FlyLayer_H_

#include "GameSceneManager.h"
#include "cocos2d.h"
#include <vector>
#include "../objectHelp/FlyObject.h"
#include "../objectHelp/Barrier.h"
#include "../frameHelp/SpriteManager.h"
#include "../frameHelp/PauseCode.h"
#include "GDData.h"

using namespace cocos2d;


class FlyLayer : public cocos2d::Layer
{
public:

	GameSceneManager *gsm;
	Director* director;
	Size visibleSize;
	Point origin;

//	MusicHelp* mh;//声音帮助类 指针
	SpriteManager* sh;//精灵管理类  指针
	PauseCode* pc;//暂停代码指针
	GDData* gdData;
	FlyObject* fo;
	std::string* ids;

	bool isUpdateAll = true;//是否进行UpdateAll方法的回调


	Barrier* tb;
//	Barrier* zh;
	std::vector<Barrier*>::iterator iter;
	std::vector<Barrier*> barrierVector;//存障碍物的vector

	std::map<std::string,Sprite*> spMap;



	int timeCountCollision = 0;//碰撞时间计数器
	int timeCount = 0;




	bool isTouch=false;

    virtual bool init();//初始化的方法


	//开始触控事件的处理方法
	bool myOnTouchBegan(Touch *touch, Event *event);
	//触控移动事件的处理方法
	void myOnTouchMoved(Touch *touch, Event *event);
	//触控结束事件的处理方法
	void myOnTouchEnded(Touch *touch, Event *event);
	//触控终止事件的处理方法
	void myOnTouchCancelled(Touch *touch, Event *event);

	void updateAll();//更新所有的方法
	void updateBarrier();
	void collisionDetection();
	void deleteBarrier();//删除 出屏幕的 障碍物  的方法

    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(FlyLayer);
};

#endif
