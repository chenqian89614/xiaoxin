#ifndef __BNPolyObject_H__
#define __BNPolyObject_H__

#include "cocos2d.h"
#include "../geolib/GeoLib.h"

using namespace cocos2d;

class BNPolyObject
{
  public:
	//绘制用精灵
	Sprite* sp;
	//绘制用剪裁节点
	ClippingNode* clipper;
	//代表自己形状的多边形
	C2DPolygon* cp;
	std::vector<Point> pointData;//顶点数据
	//构造函数
	BNPolyObject(std::string pic,float* data,int count,Layer* layer);
	BNPolyObject(std::string pic,C2DPolygon* cpIn,Layer* layer);
	bool JudgeIsContian(Point p1, Point p2);//判断线段是否在多边形的方法
};
#endif
