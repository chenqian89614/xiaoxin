#include "BNPolyObject.h"

BNPolyObject::BNPolyObject(std::string pic,C2DPolygon* cpIn,Layer* layer)
{
	//��������Σ�ȥ��Ӱ��
	cp=cpIn;
	C2DPointSet pointCopyL;
	cp->GetPointsCopy(pointCopyL);
	cp=new C2DPolygon();
	cp->Create(pointCopyL,true);

	//��ȡ���������
	int tempC11=pointCopyL.size();
	pointData.clear();
	for(int j=0;j<tempC11;j++)
	{
		C2DPoint* tempCP=pointCopyL.GetAt(j);
		pointData.push_back(Point(tempCP->x,tempCP->y));
	}

	//������ʾ����
	sp = Sprite::create(pic);
	sp->setPosition(Point(0,0));
	sp->setAnchorPoint(Point(0,0));
	//����������DrawNode
	DrawNode* shape = DrawNode::create();

	//����͹���
	cp->ClearConvexSubAreas();
	cp->CreateConvexSubAreas();
	//���ڻ�ȡ͹��ֵ�
	C2DPolygonSet cps;
	//��ȡ͹�������
	cp->GetConvexSubAreas(cps);
	//��ȡ͹������������
	int tcount=cps.size();

	//��������͹�������
	for(int i=0;i<tcount;i++)
	{
		//��ȡһ��͹�������
		C2DPolygon* cpTemp=cps.GetAt(i);
		//��ȡ��͹��ֵĶ�������
		C2DPointSet pointCopy;
		cpTemp->GetPointsCopy(pointCopy);
		//��ȡ���������
		int tempC=pointCopy.size();
		//���������ö�������
		Point* pArray=new Point[tempC];
		for(int j=0;j<tempC;j++)
		{
			C2DPoint* tempCP=pointCopy.GetAt(j);
			pArray[j]=Point(tempCP->x,tempCP->y);
		}
		//������״
		Color4F green(0, 1, 0, 0);
		Color4F red(1, 0, 0, 0.5f);
		shape->drawPolygon(pArray,tempC, green, 2, red);
	}

	//�������ýڵ�
	clipper=ClippingNode::create();
	//���ü���ģ��
	clipper->setStencil(shape);
	//���ñ����ýڵ�
	clipper->addChild(sp,0);
	clipper->setPosition(Point(0,0));
	//�������ýڵ���õ�����
	layer->addChild(clipper, 0);
}

BNPolyObject::BNPolyObject(std::string pic,float* data,int count,Layer* layer)
{
	int idata=0;
	pointData.clear();
	for(int ii=0;ii<count;ii++)
	{
		pointData.push_back(Point(data[idata],data[idata+1]));
		idata=idata+2;
	}

	//��������ζ�������
	C2DPoint* points=new C2DPoint[count];
	for(int i=0;i<count;i++)
	{
		points[i]=C2DPoint(data[i*2],data[i*2+1]);
	}
	//���ݶ������ݴ��������
	cp=new C2DPolygon(points,(unsigned int)count,true);

	//������ʾ����
	sp = Sprite::create(pic);
	sp->setPosition(Point(0,0));
	sp->setAnchorPoint(Point(0,0));
	//����������DrawNode
	DrawNode* shape = DrawNode::create();

	//����͹���
	cp->CreateConvexSubAreas();
	//���ڻ�ȡ͹��ֵ�
	C2DPolygonSet cps;
	//��ȡ͹�������
	cp->GetConvexSubAreas(cps);
	//��ȡ͹������������
	int tcount=cps.size();

	//��������͹�������
	for(int i=0;i<tcount;i++)
	{
		//��ȡһ��͹�������
		C2DPolygon* cpTemp=cps.GetAt(i);
		//��ȡ��͹��ֵĶ�������
		C2DPointSet pointCopy;
		cpTemp->GetPointsCopy(pointCopy);
		//��ȡ���������
		int tempC=pointCopy.size();
		//���������ö�������
		Point* pArray=new Point[tempC];
		for(int j=0;j<tempC;j++)
		{
			C2DPoint* tempCP=pointCopy.GetAt(j);
			pArray[j]=Point(tempCP->x,tempCP->y);
		}
		//������״
		Color4F green(0, 1, 0, 1);
		Color4F red(1, 0, 0, 1);
		shape->drawPolygon(pArray,tempC, green, 2, red);
	}
	//�������ýڵ�
	ClippingNode* clipper=ClippingNode::create();
	//���ü���ģ��
	clipper->setStencil(shape);
	//���ñ����ýڵ�
	clipper->addChild(sp,0);
	clipper->setPosition(Point(0,0));
	//�������ýڵ���õ�����
	layer->addChild(clipper, 0);
}
bool BNPolyObject::JudgeIsContian(Point pointFrom, Point pointTo)//�ж��߶��Ƿ��ڶ���εķ���
{
	bool flagFrom = false;	//����Ƿ���ı�־λ
	bool flagTo = false;	//�յ��Ƿ���ı�־λ
	std::vector<Point>::iterator iter = pointData.begin();
	for(;iter!=pointData.end();iter++)//�������ж���
	{
		if((*iter)==pointFrom)
		{
			flagFrom = true;
		}
		if((*iter)==pointTo)
		{
			flagTo = true;
		}
	}
	if(flagFrom == true && flagTo == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
