#ifndef _FlyObject_H_
#define _FlyObject_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"
#include "../frameHelp/ParticleSystemHelp.h"

using namespace cocos2d;

class FlyObject
{
public:
	Sprite* sp2;//飞行底座的精灵
	Sprite* sp1;//方块精灵
	Sprite* sp;//方块精灵
	std::string* st;//自身的id

	Point p;
	float r;

	float vJump = 450.0f;//上下移动的速度
	float vRotationJump = 320.0f;//旋转时的速度

	ParticleSystemHelp* psh;

	Layer* layer;

	// p1---p2
	// |    |
	// p3---p4
	float maxY;
	float minY;
	float maxX;
	float minX;
	float lengthX;
	float lengthY;

	float heightUp;
	float heightDown;

	FlyObject(std::string* stTemp, Layer* layer,
			Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY,
			Rect recta1, float sp1LocationX, float sp1LocationY, float sp1LengthX, float sp1LengthY,
			int localZOrder);
	~FlyObject();

	void updata();
	void up();
	void down();
	void updataData();
	void explode();
};

#endif
