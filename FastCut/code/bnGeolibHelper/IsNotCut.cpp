#include "IsNotCut.h"

bool IsNotCut::canCut=true;
IsNotCut::IsNotCut(float x,float y,float a,float b,float* coorData,int lengthCoorData)
{
	jiaoDian.clear();
	int count=0;//�е��ıߵ���������
	int j=0;
	for(int i=0;i<lengthCoorData-2;i=i+2)
	{
		if(Point::isSegmentIntersect(Point(x,y), Point(a,b),Point(coorData[i],coorData[i+1]), Point(coorData[i+2],coorData[i+3])))
		{
			this->jiaoDian.push_back(Point::getIntersectPoint(Point(x,y), Point(a,b),Point(coorData[i],coorData[i+1]), Point(coorData[i+2],coorData[i+3])));
			count++;
		}
		j=j+2;

	}
	if(j==lengthCoorData-2)
	{
		if(Point::isSegmentIntersect(Point(x,y), Point(a,b),Point(coorData[0],coorData[1]), Point(coorData[j],coorData[j+1])))
		{
			this->jiaoDian.push_back(Point::getIntersectPoint(Point(x,y), Point(a,b),Point(coorData[0],coorData[1]), Point(coorData[j],coorData[j+1])));
			count++;
		}
	}
	if(count%2==0&&count!=0)//����е��ıߵ�����Ϊż�������е��ıߵ�������Ϊ0
	{
		this->canCut = true;//������
		this->pointSize = count;
	}
	else
	{
		this->canCut = false;
	}
}
