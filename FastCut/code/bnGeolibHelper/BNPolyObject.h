#ifndef __BNPolyObject_H__
#define __BNPolyObject_H__

#include "cocos2d.h"
#include "../geolib/GeoLib.h"

using namespace cocos2d;

class BNPolyObject
{
  public:
	//�����þ���
	Sprite* sp;
	//�����ü��ýڵ�
	ClippingNode* clipper;
	//�����Լ���״�Ķ����
	C2DPolygon* cp;
	std::vector<Point> pointData;//��������
	//���캯��
	BNPolyObject(std::string pic,float* data,int count,Layer* layer);
	BNPolyObject(std::string pic,C2DPolygon* cpIn,Layer* layer);
	bool JudgeIsContian(Point p1, Point p2);//�ж��߶��Ƿ��ڶ���εķ���
};
#endif
