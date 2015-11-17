#include "Barrier.h"

Barrier::Barrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder)
{
	this->st = stTemp;//记录障碍物id
	this->lengthX = spLengthX;//记录精灵的宽度
	this->lengthY = spLengthY;//记录精灵的高度

	this->timeCount = 0;//时间计数器置零
}
Barrier::~Barrier()
{
	delete st;//删除障碍物id
}
bool Barrier::collision(JumpCube* jc){}
bool Barrier::collisionFo(FlyObject* fo){}
void Barrier::reflesh()
{
	timeCount++;//时间计数器加一
	sp->setPosition(Point(p.x - V * timeCount * INTERVAL , p.y));//设置障碍物的位置     、timeCount * INTERVAL为真正的时间
}
