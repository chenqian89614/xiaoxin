#ifndef _IsNotCut_H_
#define _IsNotCut_H_

#include "cocos2d.h"
using namespace cocos2d;
class IsNotCut
{
public :
	std::vector<Point> jiaoDian;
	int pointSize;
	static bool canCut;//true��ʾ���и�  false��ʾ�����и�
	IsNotCut(float x,float y,float a,float b,float* coorData,int lengthCoorData);//�ж��ܷ��и�ķ���
};
#endif
