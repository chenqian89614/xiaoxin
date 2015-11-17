#include "GDData.h"
#include "GameLayer.h"
#include "FlyLayer.h"

void GDData::createFlyData()
{
	FlyLayer* layer1 = (FlyLayer*)(layer);
	if(layer1->timeCount == 0)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 50)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 100)
	{
		createEightTriangle1(layer1);

		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+80,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 130)
	{
		createEightTriangle2(layer1);
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 180)
	{
		createEightTriangle1(layer1);
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX,LENGTHSJY*5, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 250)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 300)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+75,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 350)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+17,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 400)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+96,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 500)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 550)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+230,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 600)
	{
		createEightTriangle1(layer1);
		createEightTriangle2(layer1);
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 650)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 700)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+150,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 800)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 850)
	{
		createEightTriangle1(layer1);

		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+80,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 900)
	{
		createEightTriangle2(layer1);
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 950)
	{
		createEightTriangle1(layer1);
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX,LENGTHSJY*5, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1000)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1050)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+75,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1100)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+17,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1150)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+96,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1200)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+200,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1250)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+230,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1300)
	{
		createEightTriangle1(layer1);
		createEightTriangle2(layer1);
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1350)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1400)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+150,LENGTHSJX * 5,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1450)
	{
		//������
		tb = new RectBarrier(NULL,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2,HEIGHT_EDGE+LENGTHSJY+100,LENGTHSJX * 5,LENGTHSJY, 2);//��������
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
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*2,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*3,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*4,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*5,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*6,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*7,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*8,HEIGHT-HEIGHT_EDGE-LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	tb->sp->setFlippedX(true);
	tb->sp->setFlippedY(true);
	layer1->barrierVector.push_back(tb);
}
void GDData::createEightTriangle2(Layer* layer2)
{
	FlyLayer* layer1 = (FlyLayer*)(layer2);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*2,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*3,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*4,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*5,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*6,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*7,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
	//�������ϰ���id
	tb = new TriangleBarrier(NULL,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX*8,HEIGHT_EDGE+LENGTHSJY/2,LENGTHSJX,LENGTHSJY,2);//����������
	layer1->barrierVector.push_back(tb);
}

void GDData::createData()
{
	GameLayer* layer1 = (GameLayer*)(layer);

	if(layer1->timeCount == 0)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 50)
	{
//		layer1->timeCount = 1149;

		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 100)
	{
		//һ��������2������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 130)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 180)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 250)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 300)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 350)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 400)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);

		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 500)
	{
		//1�����ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 550)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 600)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 650)
	{
		//һ��������һ������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 700)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//1�����ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 800)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);

		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 950)
	{
		//һ��������2������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 1000)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1050)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1100)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1150)
	{
//		//�������ŵ�������
//		//�������ϰ���id
//		ids = new std::string("T1");
//		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
//		layer1->barrierVector.push_back(tb);
//		//�������ϰ���id
//		ids = new std::string("T1");
//		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
//		layer1->barrierVector.push_back(tb);
//		//�������ϰ���id
//		ids = new std::string("T1");
//		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
//		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1200)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}

}
void GDData::createData3()
{
	GameLayer* layer1 = (GameLayer*)(layer);

	if(layer1->timeCount == 0)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 50)
	{
		layer1->timeCount = 1149;

		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 100)
	{
		//һ��������2������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 130)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 180)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 250)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 300)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 350)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 400)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);

		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 500)
	{
		//1�����ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 550)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 600)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 650)
	{
		//һ��������һ������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 700)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 750)
	{
		//1�����ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 800)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//��������
		layer1->barrierVector.push_back(tb);

		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*3+160,SJXY+LENGTHSJY/2,LENGTHSJX,LENGTHSJY*2, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*4+160*2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY*3, 2);//��������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 950)
	{
		//һ��������2������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX*2,SJXY,LENGTHSJX,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);

	}
	else if(layer1->timeCount == 1000)
	{
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1050)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		float length = LENGTHSJX * 6;
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new RectBarrier(ids,layer1,Rect(469,101,498-469,130-101),SJXX+LENGTHSJX/2+length/2,SJXY,length,LENGTHSJY, 2);//��������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX/2+length/2,SJXY+LENGTHSJY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1100)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1150)
	{
		//�������ŵ�������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-5,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX+LENGTHSJX-10+LENGTHSJX,SJXY,LENGTHSJX-5,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}
	else if(layer1->timeCount == 1200)
	{
		//������
		//�������ϰ���id
		ids = new std::string("T1");
		tb = new TriangleBarrier(ids,layer1,Rect(500,106,528-500,132-106),SJXX,SJXY,LENGTHSJX,LENGTHSJY,2);//����������
		layer1->barrierVector.push_back(tb);
	}

}
