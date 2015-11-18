#include "BNPolyObject.h"

BNPolyObject::BNPolyObject(std::string pic,C2DPolygon* cpIn,Layer* layer)
{
	//创建多边形，去除影响
	cp=cpIn;
	C2DPointSet pointCopyL;
	cp->GetPointsCopy(pointCopyL);
	cp=new C2DPolygon();
	cp->Create(pointCopyL,true);

	//获取顶点的数量
	int tempC11=pointCopyL.size();
	pointData.clear();
	for(int j=0;j<tempC11;j++)
	{
		C2DPoint* tempCP=pointCopyL.GetAt(j);
		pointData.push_back(Point(tempCP->x,tempCP->y));
	}

	//创建显示精灵
	sp = Sprite::create(pic);
	sp->setPosition(Point(0,0));
	sp->setAnchorPoint(Point(0,0));
	//创建剪裁用DrawNode
	DrawNode* shape = DrawNode::create();

	//创建凸拆分
	cp->ClearConvexSubAreas();
	cp->CreateConvexSubAreas();
	//用于获取凸拆分的
	C2DPolygonSet cps;
	//获取凸拆分区域
	cp->GetConvexSubAreas(cps);
	//获取凸拆分区域的数量
	int tcount=cps.size();

	//遍历所有凸拆分区域
	for(int i=0;i<tcount;i++)
	{
		//获取一个凸拆分区域
		C2DPolygon* cpTemp=cps.GetAt(i);
		//获取此凸拆分的顶点序列
		C2DPointSet pointCopy;
		cpTemp->GetPointsCopy(pointCopy);
		//获取顶点的数量
		int tempC=pointCopy.size();
		//创建绘制用顶点数组
		Point* pArray=new Point[tempC];
		for(int j=0;j<tempC;j++)
		{
			C2DPoint* tempCP=pointCopy.GetAt(j);
			pArray[j]=Point(tempCP->x,tempCP->y);
		}
		//绘制形状
		Color4F green(0, 1, 0, 0);
		Color4F red(1, 0, 0, 0.5f);
		shape->drawPolygon(pArray,tempC, green, 2, red);
	}

	//创建剪裁节点
	clipper=ClippingNode::create();
	//设置剪裁模板
	clipper->setStencil(shape);
	//设置被剪裁节点
	clipper->addChild(sp,0);
	clipper->setPosition(Point(0,0));
	//将被剪裁节点放置到层中
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

	//创建多边形顶点序列
	C2DPoint* points=new C2DPoint[count];
	for(int i=0;i<count;i++)
	{
		points[i]=C2DPoint(data[i*2],data[i*2+1]);
	}
	//根据顶点数据创建多边形
	cp=new C2DPolygon(points,(unsigned int)count,true);

	//创建显示精灵
	sp = Sprite::create(pic);
	sp->setPosition(Point(0,0));
	sp->setAnchorPoint(Point(0,0));
	//创建剪裁用DrawNode
	DrawNode* shape = DrawNode::create();

	//创建凸拆分
	cp->CreateConvexSubAreas();
	//用于获取凸拆分的
	C2DPolygonSet cps;
	//获取凸拆分区域
	cp->GetConvexSubAreas(cps);
	//获取凸拆分区域的数量
	int tcount=cps.size();

	//遍历所有凸拆分区域
	for(int i=0;i<tcount;i++)
	{
		//获取一个凸拆分区域
		C2DPolygon* cpTemp=cps.GetAt(i);
		//获取此凸拆分的顶点序列
		C2DPointSet pointCopy;
		cpTemp->GetPointsCopy(pointCopy);
		//获取顶点的数量
		int tempC=pointCopy.size();
		//创建绘制用顶点数组
		Point* pArray=new Point[tempC];
		for(int j=0;j<tempC;j++)
		{
			C2DPoint* tempCP=pointCopy.GetAt(j);
			pArray[j]=Point(tempCP->x,tempCP->y);
		}
		//绘制形状
		Color4F green(0, 1, 0, 1);
		Color4F red(1, 0, 0, 1);
		shape->drawPolygon(pArray,tempC, green, 2, red);
	}
	//创建剪裁节点
	ClippingNode* clipper=ClippingNode::create();
	//设置剪裁模板
	clipper->setStencil(shape);
	//设置被剪裁节点
	clipper->addChild(sp,0);
	clipper->setPosition(Point(0,0));
	//将被剪裁节点放置到层中
	layer->addChild(clipper, 0);
}
bool BNPolyObject::JudgeIsContian(Point pointFrom, Point pointTo)//判断线段是否在多边形的方法
{
	bool flagFrom = false;	//起点是否传入的标志位
	bool flagTo = false;	//终点是否传入的标志位
	std::vector<Point>::iterator iter = pointData.begin();
	for(;iter!=pointData.end();iter++)//遍历所有顶点
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
