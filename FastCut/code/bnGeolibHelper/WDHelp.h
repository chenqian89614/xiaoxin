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
	std::vector<C2DPolygon> allCP;//���ж����
	const C2DPolygon* onlyOneCP = NULL;
	C2DPointSet pointCopy;//��¼��ǰ�ĵ�����   ���¼����
	int numsAllCP;//�ж��ٸ������
	std::vector<C2DPolygon> noFlyCP;//��Ҫ���ߵĶ����
	std::vector<C2DPolygon> flyCP;//��Ҫ���ߵĶ����

	WDHelp(C2DPolygon qfy, BNPolyObject* bpoCurrMain);//allPoint::����������ĵ�   numsPoint����������		 Point* allPoint, int numsPoint
	void Separate(IsNotCut* inc, C2DPointSet pointCopy);
	void Zuhe(Point* pArray1,int numsCpTemp);
};

#endif
