#include "GDData.h"
#include "GameLayer.h"
#include "FlyLayer.h"

void GDData::createFlyData()
{
	FlyLayer* layer1 = (FlyLayer*)(layer);
	if(layer1->timeCount == 0)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 50)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 100)
	{
		createEightTriangle1(layer1);

		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+80,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 130)
	{
		createEightTriangle2(layer1);
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 180)
	{
		createEightTriangle1(layer1);
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX,LENGTHSJY*5, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 250)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 300)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+75,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 350)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+17,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 400)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+96,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 500)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 550)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+230,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 600)
	{
		createEightTriangle1(layer1);
		createEightTriangle2(layer1);
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 650)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 700)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+150,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 800)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 850)
	{
		createEightTriangle1(layer1);

		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+80,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 900)
	{
		createEightTriangle2(layer1);
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 950)
	{
		createEightTriangle1(layer1);
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX,LENGTHSJY*5, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1000)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1050)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+75,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1100)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+17,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1150)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+96,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1200)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1250)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+230,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1300)
	{
		createEightTriangle1(layer1);
		createEightTriangle2(layer1);
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1350)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1400)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+150,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1450)
	{
		//长矩形
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}

}

GDData::GDData(Layer* layerIn)
{
	this->layer = layerIn;
}
void GDData::createEightTriangle1(Layer* layer2)
{
	FlyLayer* layer1 = (FlyLayer*)(layer2);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*2,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*3,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*4,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*5,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*6,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*7,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*8,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
}
void GDData::createEightTriangle2(Layer* layer2)
{
	FlyLayer* layer1 = (FlyLayer*)(layer2);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*2,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*3,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*4,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*5,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*6,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*7,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
	//三角形障碍物id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*8,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//创建三角形
	layer1->barrierVector.push_back(tb);
}

void GDData::createData()
{
	GameLayer* layer1 = (GameLayer*)(layer);

	if(layer1->timeCount == 0)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 50)
	{
//		layer1->timeCount = 1149;

		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 100)
	{
		//一个三角形2个矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 130)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 180)
	{
		//长矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 250)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 300)
	{
		//三个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 350)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 400)
	{
		//三连跳
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);

		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 500)
	{
		//1个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 550)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 600)
	{
		//三个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 650)
	{
		//一个三角形一个矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 700)
	{
		//三个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//1个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 800)
	{
		//三连跳
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);

		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 950)
	{
		//一个三角形2个矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 1000)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1050)
	{
		//长矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1100)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1150)
	{
//		//三个连着的三角形
//		//三角形障碍物id
//		ids = new std::string("T1");
//		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
//		layer1->barrierVector.push_back(tb);
//		//三角形障碍物id
//		ids = new std::string("T1");
//		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
//		layer1->barrierVector.push_back(tb);
//		//三角形障碍物id
//		ids = new std::string("T1");
//		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
//		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1200)
	{
		//三连跳
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}

}
void GDData::createData3()
{
	GameLayer* layer1 = (GameLayer*)(layer);

	if(layer1->timeCount == 0)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 50)
	{
		layer1->timeCount = 1149;

		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 100)
	{
		//一个三角形2个矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 130)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 180)
	{
		//长矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 250)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 300)
	{
		//三个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 350)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 400)
	{
		//三连跳
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);

		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 500)
	{
		//1个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 550)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 600)
	{
		//三个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 650)
	{
		//一个三角形一个矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 700)
	{
		//三个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//1个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 800)
	{
		//三连跳
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建矩形
		layer1->barrierVector.push_back(tb);

		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 950)
	{
		//一个三角形2个矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 1000)
	{
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1050)
	{
		//长矩形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//矩形形障碍物id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//创建矩形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1100)
	{
		//两个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1150)
	{
		//三个连着的三角形
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1200)
	{
		//三连跳
		//三角形障碍物id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//创建三角形
		layer1->barrierVector.push_back(tb);
	}

}
