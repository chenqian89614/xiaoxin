#include "Barrier.h"

Barrier::Barrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder)
{
	this->st = stTemp;//��¼�ϰ���id
	this->lengthX = spLengthX;//��¼����Ŀ��
	this->lengthY = spLengthY;//��¼����ĸ߶�

	this->timeCount = 0;//ʱ�����������
}
Barrier::~Barrier()
{
	delete st;//ɾ���ϰ���id
}
bool Barrier::collision(JumpCube* jc){}
bool Barrier::collisionFo(FlyObject* fo){}
void Barrier::reflesh()
{
	timeCount++;//ʱ���������һ
	sp->setPosition(Point(p.x - V * timeCount * INTERVAL , p.y));//�����ϰ����λ��     ��timeCount * INTERVALΪ������ʱ��
}
