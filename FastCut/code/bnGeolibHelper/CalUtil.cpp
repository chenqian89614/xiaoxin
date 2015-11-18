#include "CalUtil.h"

float CalUtil::xmin=0;
float CalUtil::xmax=540;
float CalUtil::ymin=0;
float CalUtil::ymax=960;

float* CalUtil::makeArray(float x,float y)
{
	float* fa=new float[2];
	fa[0]=x;
	fa[1]=y;
	return fa;
}

vector<C2DPolygon> CalUtil::calParts(float sx,float sy,float ex,float ey)
{
	// 0[xmin,ymin]----------3[xmax,ymin]
	// |                              | 
	// |                              |
	// 1[xmin,ymax]----------2[xmax,ymax]

	int currIndex=0;
	vector<float*> al;
	al.push_back(makeArray(xmin,ymin));
	currIndex++;
	int jd1Index=-1;
	int jd2Index=-1;
	
	//��0-1�߶��봫���и��ߵĽ��� X=xmin
	float t=(xmin-sx)/(ex-sx);
	float y=(ey-sy)*t+sy;
	if(y>ymin&&y<ymax)
	{
		jd1Index=currIndex;
		al.push_back(makeArray(xmin,y)); 
		currIndex++;
	}
	al.push_back(makeArray(xmin,ymax));
	currIndex++;
	
	//��1-2�߶δ����и��ߵĽ��� y=ymax
	t=(ymax-sy)/(ey-sy);
	float x=(ex-sx)*t+sx;
	if(x>xmin&&x<xmax)
	{
		if(jd1Index==-1)
		{
			jd1Index=currIndex;
		}
		else
		{
			jd2Index=currIndex;
		}
		
		al.push_back(makeArray(x,ymax));
		currIndex++;
	}
	
	al.push_back(makeArray(xmax,ymax));
	currIndex++;
	
	//��2-3�߶δ����и��ߵĽ��� x=xmax
	t=(xmax-sx)/(ex-sx);
	y=(ey-sy)*t+sy;
	if(y>ymin&&y<ymax)
	{
		if(jd1Index==-1)
		{
			jd1Index=currIndex;
		}
		else
		{
			jd2Index=currIndex;
		}
		al.push_back(makeArray(xmax,y));
		currIndex++;
	}
	
	al.push_back(makeArray(xmax,ymin));
	currIndex++;
	
	//��3--0�߶δ����и��ߵĽ��� y=ymin
	t=(ymin-sy)/(ey-sy);
	x=(ex-sx)*t+sx;
	if(x>xmin&&x<xmax)
	{
		if(jd1Index==-1)
		{
			jd1Index=currIndex;
		}
		else
		{
			jd2Index=currIndex;
		}
		
		al.push_back(makeArray(x,ymin));
		currIndex++;
	}
	
	//���Ƶ�һ�������
	C2DPointSet  p1;
	int startIndex=jd1Index;
	while(true)
	{
		float* tempp=al.at(startIndex);
		p1.AddCopy(tempp[0],tempp[1]);
		if(startIndex==jd2Index)
		{
			break;
		}			
		startIndex=(startIndex+1)%al.size();
	}
	
	//���Ƶڶ��������
	C2DPointSet  p2;
	startIndex=jd2Index;
	while(true)
	{
		float* tempp=al.at(startIndex);
		p2.AddCopy(tempp[0],tempp[1]);
		if(startIndex==jd1Index)
		{
			break;
		}			
		startIndex=(startIndex+1)%al.size();
	}
	
	vector<C2DPolygon> result;
	C2DPolygon cp1;
	cp1.Create(p1,true);
	result.push_back(cp1);
	C2DPolygon cp2;
	cp2.Create(p2,true);
	result.push_back(cp2);
	return result;
}
