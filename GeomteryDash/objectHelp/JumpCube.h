#ifndef _JumpCube_H_
#define _JumpCube_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"
#include "../frameHelp/ParticleSystemHelp.h"

using namespace cocos2d;

class JumpCube
{
public:
	Sprite* sp;//自身的精灵
	std::string* st;//自身的id

	Point p;
	float r;
	float lengthX;//精灵的长
	float lengthY;//精灵的宽

	//关于跳跃的各项物理参数
	float vJump = JCJH / timeJump;//(timeJump * INTERVALJC);//上升时的速度
	float vRotationJump = 90.0f / timeJump;//(timeJump * INTERVALJC);//上升过程中 旋转的角速度
	bool isJump=false;//是否处于跳跃状态

	//关于下落的各项物理参数
	float vDown = vJump * 1.0;//下落时的速度  是上升时的速度的1.2倍
	bool isDown = false;

	int timeCount = 0;//时间记录器

	ParticleSystemHelp* psh;

	Layer* layer;

	JumpCube(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLength, int localZOrder);
	~JumpCube();
	void reflesh(float maxH);

	void Jump();
	void Down();
	void refleshAngleAndPosition(float y);
	void explode();
};

#endif
