#ifndef _Barrier_H_
#define _Barrier_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"
#include "JumpCube.h"
#include "../objectHelp/FlyObject.h"

using namespace cocos2d;

class Barrier
{
public:
	Sprite* sp;//障碍物精灵
	std::string* st;//障碍物id
	float lengthX;//表示精灵的宽度
	float lengthY;//表示精灵的高度
	char idChar;//char类型的障碍物id
	int timeCount;//时间计数器
	Point p;//表示障碍物位置
	Barrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder);//构造函数
	~Barrier();//析构函数
	virtual bool collision(JumpCube* jc);//障碍物与方块精灵的碰撞检测方法
	virtual bool collisionFo(FlyObject* fo);//障碍物与飞行器的碰撞检测方法
	void reflesh();//更新障碍物的位置方法
};

class TriangleBarrier : public Barrier
{
public:
	TriangleBarrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder);//构造函数
	bool collision(JumpCube* jc);//障碍物与方块精灵的碰撞检测方法
	bool collisionFo(FlyObject* fo);//障碍物与飞行器的碰撞检测方法
};

class RectBarrier : public Barrier
{
public:
	RectBarrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder);//构造函数
	bool collision(JumpCube* jc);//障碍物与方块精灵的碰撞检测方法
	bool collisionFo(FlyObject* fo);//障碍物与飞行器的碰撞检测方法
};

#endif
