#include "CollisionTest.h"
#include "cocos2d.h"

using namespace cocos2d;

bool CollisionTest::isCollision(float x1,float y1,int w1,int h1,float x2,float y2,int w2,int h2)
{
	//物体A-------xy最大最小
	float xAMin = x1 - 0.5*w1;
	float xAMax = x1 + 0.5*w1;
	float yAMin = y1 - 0.5*h1;
	float yAMax = y1 + 0.5*h1;

	//物体B-------xy最大最小
	float xBMin = x2 - 0.5*w2;
	float xBMax = x2 + 0.5*w2;
	float yBMin = y2 - 0.5*h2;
	float yBMax = y2 + 0.5*h2;

	//重叠xy
	float xOverlap=0;
	float yOverlap=0;
	float impacetArea=0;
	//A被B包
	if(xAMax<=xBMax&&xAMin>=xBMin)
	{
		xOverlap = fabs(xAMax - xAMin);
		if(yAMax<=yBMax&&yAMin<=yBMin&&yBMin<=yAMax)
		{
			yOverlap = fabs(yAMax - yBMin);
		}
		else if(yAMax>=yBMax&&yBMin<=yAMin&&yBMax>=yAMin)
		{
			yOverlap = fabs(yBMax-yAMin);
		}
		else
		{
			yOverlap=0;
		}
	}
	//B被A包
	else if(xBMin>=xAMin&&xBMax<=xAMax)
	{
		xOverlap = fabs(xBMax - xBMin);
		if(yBMax<=yAMax&&yAMin>=yBMin&&yBMax>=yAMin)
		{
			yOverlap = fabs(yBMax - yAMin);
		}
		else if(yAMin<=yBMin&&yAMax<=yBMax&&yBMin<=yAMax)	//上侧导弹包含飞机
		{
			yOverlap = fabs(yAMax - yBMin);
		}
		else
		{
			yOverlap=0;
		}
	}
	//B在A右侧 进行碰撞
	else if(xAMax<=xBMax&&xAMin<=xBMin&&xAMax>=xBMin)
	{
		xOverlap = fabs(xAMax - xBMin);
		if(yAMax<=yBMax&&yAMin<=yBMin&&yAMax>=yBMin)
		{
			yOverlap = fabs(yAMax - yBMin);
		}
		else if(yAMax>=yBMax&&yAMin>=yBMin&&yBMax>=yAMin)
		{
			yOverlap = fabs(yBMax - yAMin);
		}
		else
		{
			yOverlap=0;
		}
	}
	//B在A左侧相撞
	else if(xAMin>=xBMin&&xAMax>=xBMax&&xAMin<=xBMax)
	{
		xOverlap = fabs(xBMax-xAMin);
		if(yAMax<=yBMax&&yAMin<=yBMin&&yAMax>=yBMin)
		{
			yOverlap = fabs(yAMax - yBMin);
		}
		else if(yAMax>=yBMax&&yAMin>=yBMin&&yBMax>=yAMin)
		{
			yOverlap = fabs(yBMax-yAMin);
		}
		else
		{
			yOverlap=0;
		}
	}

	//求出重叠面积
	impacetArea = fabs(xOverlap*yOverlap);
	if(impacetArea>=500)
	{
		return true;
	}else{
		return false;
	}
}
