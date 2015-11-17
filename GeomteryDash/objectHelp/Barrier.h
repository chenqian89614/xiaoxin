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
	Sprite* sp;//�ϰ��ﾫ��
	std::string* st;//�ϰ���id
	float lengthX;//��ʾ����Ŀ��
	float lengthY;//��ʾ����ĸ߶�
	char idChar;//char���͵��ϰ���id
	int timeCount;//ʱ�������
	Point p;//��ʾ�ϰ���λ��
	Barrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder);//���캯��
	~Barrier();//��������
	virtual bool collision(JumpCube* jc);//�ϰ����뷽�龫�����ײ��ⷽ��
	virtual bool collisionFo(FlyObject* fo);//�ϰ��������������ײ��ⷽ��
	void reflesh();//�����ϰ����λ�÷���
};

class TriangleBarrier : public Barrier
{
public:
	TriangleBarrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder);//���캯��
	bool collision(JumpCube* jc);//�ϰ����뷽�龫�����ײ��ⷽ��
	bool collisionFo(FlyObject* fo);//�ϰ��������������ײ��ⷽ��
};

class RectBarrier : public Barrier
{
public:
	RectBarrier(std::string* stTemp, Layer* layer, Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY, int localZOrder);//���캯��
	bool collision(JumpCube* jc);//�ϰ����뷽�龫�����ײ��ⷽ��
	bool collisionFo(FlyObject* fo);//�ϰ��������������ײ��ⷽ��
};

#endif
