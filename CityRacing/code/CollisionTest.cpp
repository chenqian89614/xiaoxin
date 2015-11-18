#include "CollisionTest.h"
#include "cocos2d.h"

using namespace cocos2d;

bool CollisionTest::isCollision(float x1,float y1,int w1,int h1,float x2,float y2,int w2,int h2)
{
	//����A-------xy�����С
	float xAMin = x1 - 0.5*w1;
	float xAMax = x1 + 0.5*w1;
	float yAMin = y1 - 0.5*h1;
	float yAMax = y1 + 0.5*h1;

	//����B-------xy�����С
	float xBMin = x2 - 0.5*w2;
	float xBMax = x2 + 0.5*w2;
	float yBMin = y2 - 0.5*h2;
	float yBMax = y2 + 0.5*h2;

	//�ص�xy
	float xOverlap=0;
	float yOverlap=0;
	float impacetArea=0;
	//A��B��
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
	//B��A��
	else if(xBMin>=xAMin&&xBMax<=xAMax)
	{
		xOverlap = fabs(xBMax - xBMin);
		if(yBMax<=yAMax&&yAMin>=yBMin&&yBMax>=yAMin)
		{
			yOverlap = fabs(yBMax - yAMin);
		}
		else if(yAMin<=yBMin&&yAMax<=yBMax&&yBMin<=yAMax)	//�ϲർ�������ɻ�
		{
			yOverlap = fabs(yAMax - yBMin);
		}
		else
		{
			yOverlap=0;
		}
	}
	//B��A�Ҳ� ������ײ
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
	//B��A�����ײ
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

	//����ص����
	impacetArea = fabs(xOverlap*yOverlap);
	if(impacetArea>=500)
	{
		return true;
	}else{
		return false;
	}
}
