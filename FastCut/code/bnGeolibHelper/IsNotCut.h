#ifndef _IsNotCut_H_
#define _IsNotCut_H_

#include "cocos2d.h"
using namespace cocos2d;
class IsNotCut
{
public :
	std::vector<Point> jiaoDian;
	int pointSize;
	static bool canCut;//true表示能切割  false表示不能切割
	IsNotCut(float x,float y,float a,float b,float* coorData,int lengthCoorData);//判断能否切割的方法
};
#endif
