#ifndef _WDHelp_h_
#define _WDHelp_h_

#include "../bnGeolibHelper/BNPolyObject.h"
//#include "../geolib/GeoLib.h"
#include "IsNotCut.h"
#include "cocos2d.h"

using namespace cocos2d;

class WDHelp
{
public:
	std::vector<C2DPolygon> allCP;//所有多边形
	const C2DPolygon* onlyOneCP = NULL;
	C2DPointSet pointCopy;//记录当前的点数据   起记录作用
	int numsAllCP;//有多少个多边形
	std::vector<C2DPolygon> noFlyCP;//不要飞走的多边形
	std::vector<C2DPolygon> flyCP;//需要飞走的多边形

	WDHelp(C2DPolygon qfy, BNPolyObject* bpoCurrMain);//allPoint::所有球的中心点   numsPoint：：几个球		 Point* allPoint, int numsPoint
	void Separate(IsNotCut* inc, C2DPointSet pointCopy);
	void Zuhe(Point* pArray1,int numsCpTemp);
};

#endif
