#ifndef _BNJoyStick_H_
#define _BNJoyStick_H_

#include "cocos2d.h"
using namespace cocos2d;

class BNJoyStick : public Sprite
{
  public:
	//构造函数
	BNJoyStick(void);
	//析构函数
    virtual ~BNJoyStick(void);

    //限制摇杆移动事件的时间
    int yhCount=0;

    //触控标志位
    bool touchFlag=false;

    //中心摇杆精灵
    Sprite* centerPoint;
    //方向盘半径
    float rRange;
    //摇杆移动的横坐标
    float vx;
    //摇杆移动的纵坐标
    float vy;

    //获取矩形区域
    Rect getRect();
    //判断触摸点位置的方法
    bool containsTouchLocation(Touch* touch);
    //设置中心摇杆位置及获取半径
    void calCenter();
    //计算摇杆中心在纹理图的坐标方法
    void calCenterPosition(float tx,float ty);

    //每次精灵进入时被回调
    virtual void onEnter();
    //每次精灵退出时被回调
    virtual void onExit();
    //开始触控事件的处理方法
    bool onTouchBegan(Touch* touch, Event* event);
    //触控移动事件的处理方法
	void onTouchMoved(Touch* touch, Event* event);
	//触控结束事件的处理方法
	void onTouchEnded(Touch* touch, Event* event);

	//创建游戏摇杆方法
    static BNJoyStick* create(const std::string& basefilename,const std::string& centerfilename);
};


#endif
