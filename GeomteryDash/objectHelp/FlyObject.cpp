#include "FlyObject.h"
#include "../frameHelp/MusicManager.h"
#include "../hellocpp/FlyLayer.h"

FlyObject::FlyObject(std::string* stTemp, Layer* layer,
			Rect recta, float spLocationX, float spLocationY, float spLengthX, float spLengthY,
			Rect recta1, float sp1LocationX, float sp1LocationY, float sp1LengthX, float sp1LengthY,
			int localZOrder)
{
	this->layer = layer;
	this->st = stTemp;//������ id

	this->lengthX = spLengthX;
	this->lengthY = sp1LengthX/2+sp1LocationY;

	sp = Sprite::create();
	sp->setContentSize(Size(spLengthX,sp1LengthX/2+sp1LocationY));
	sp->setPosition(Point(JCX,JCY));//���þ����λ��
	layer->addChild(sp,1);//��������ӵ�������

	p = sp->getPosition();
	r = sp->getRotation();

	sp2 = Sprite::createWithTexture(((FlyLayer*)(layer))->sh->batchNode->getTexture(),recta);//��������
	sp2->setAnchorPoint(Point(0.5f,0.5f));//���þ����ê��   ��Ϊ���ĵ�
	sp2->setPosition(Point(spLocationX,spLocationY));//���þ����λ��
	Size size=sp2->getContentSize();//��ȡ����ĳߴ�
	float scaleX=spLengthX/size.width;//���������X�������ű�
	float scaleY=spLengthY/size.height;//���������Y�������ű�
	sp2->setScaleX(scaleX);//���þ���X�������ű�
	sp2->setScaleY(scaleY);//���þ���Y�������ű�
	sp2->setColor(Color3B(102,204,35));
	sp->addChild(sp2,localZOrder);//��������ӵ�������

	sp1 = Sprite::createWithTexture(((FlyLayer*)(layer))->sh->batchNode->getTexture(),recta1);//��������
	sp1->setAnchorPoint(Point(0.5f,0.5f));//���þ����ê��   ��Ϊ���ĵ�
	sp1->setPosition(Point(sp1LocationX,sp1LocationY));//���þ����λ��
	size=sp1->getContentSize();//��ȡ����ĳߴ�
	scaleX=sp1LengthX/size.width;//���������X�������ű�
	scaleY=sp1LengthY/size.height;//���������Y�������ű�
	sp1->setScaleX(scaleX);//���þ���X�������ű�
	sp1->setScaleY(scaleY);//���þ���Y�������ű�
	sp1->setColor(Color3B(102,204,35));
	sp->addChild(sp1,localZOrder);//��������ӵ�������


	heightUp = HEIGHT - HEIGHT_EDGE;
	heightDown = HEIGHT_EDGE;

	updataData();


	psh = new ParticleSystemHelp();
	layer->addChild(psh->psq1, BatchNodeZOrder-1);//��������Ч��ӵ�layer��
	psh->psq2->retain();
	psh->psq1->setVisible(false);
	psh->isPsq1 = false;

	psh->psq1->setSourcePosition(Point(minX , minY/2+maxY/2-5));
	psh->psq1->resetSystem();
	psh->psq1->setVisible(true);
	psh->isPsq1 = true;

	psh->psq1->retain();

}

FlyObject::~FlyObject()
{
	delete st;
}
void FlyObject::updata()
{
	psh->psq1->setSourcePosition(Point(minX , minY/2+maxY/2-5));//���û�������ϵͳ��λ��
	updataData();//���ø������ݵķ���
	if(((FlyLayer*)(layer))->isTouch == true)//�ж���ָ�Ƿ񴥿ص�����Ļ
	{
		up();//������������
	}
	else
	{
		down();//�����½�����
	}
}
void FlyObject::up()
{
	if(p.y+lengthY/2 > heightUp-1)//�жϷ��������ϱ��Ƿ񵽴�����
	{
		if(r<0)//�жϵ�ǰ��ת���Ƿ�С��0
		{
			sp->setRotation(r + vRotationJump * 0.8f * INTERVALJC);//���÷���������ת��
			r = sp->getRotation();//��¼��ǰ��ת��
		}
		else
		{
			sp->setRotation(0);//���÷���������ת��
			r = sp->getRotation();//��¼��ǰ��ת��
		}
	}
	else
	{
		sp->setPosition(Point(p.x, p.y + vJump * INTERVALJC));//���÷�������λ��
		p = sp->getPosition();//��¼��������ǰλ��
		if(r>-20)//�жϵ�ǰ��ת���Ƿ����һ������
		{
			sp->setRotation(r - vRotationJump * INTERVALJC);//���÷���������ת��
			r = sp->getRotation();//��¼��ǰ��ת��
		}
	}
}

void FlyObject::down()
{
	if(p.y-lengthY/2  < heightDown+1 )//�жϷ��������±��Ƿ񵽴�����   ���Ҵ�ʱ��������б״̬
	{
		if(r>0)//�жϵ�ǰ��ת���Ƿ�С��0
		{
			sp->setRotation(r - vRotationJump * INTERVALJC);//���÷���������ת��
			r = sp->getRotation();//��¼��ǰ��ת��
		}
		else
		{
			sp->setRotation(0);//���÷���������ת��
			r = sp->getRotation();//��¼��ǰ��ת��
		}
	}
	else
	{
		sp->setPosition(Point(p.x, p.y - vJump * 0.8f * INTERVALJC));//���÷�������λ��
		p = sp->getPosition();//��¼��������ǰλ��
		if(r<20)//�жϵ�ǰ��ת���Ƿ�С��һ������
		{
			sp->setRotation(r + vRotationJump * INTERVALJC);//���÷���������ת��
			r = sp->getRotation();//��¼��ǰ��ת��
		}
	}
}
void FlyObject::updataData()
{
	Rect rect = sp->getBoundingBox();//��ȡ���鵱ǰ�İ�Χ������
	minX = rect.origin.x;//��ȡ������������Xֵ
	maxX = minX + rect.size.width;//��ȡ���������Ҳ��Xֵ
	minY = rect.origin.y;//��ȡ�������±ߵĸ߶�ֵ
	maxY = minY + rect.size.height;//��ȡ�������ϱߵĸ߶�ֵ
}
void FlyObject::explode()
{
	sp1->setVisible(false);
	sp->setVisible(false);//���÷��龫�鲻�ɼ�

	psh->psq1->stopSystem();
	layer->addChild(psh->psq2,BatchNodeZOrder-1);//��ӱ�ըЧ��

	psh->psq2->setSourcePosition(Point(minX/2+maxX/2-150 , minY/2+maxY/2-70));
	psh->psq2->resetSystem();
	psh->psq1->setVisible(true);


	MusicManager::playExplosionEffect();
}
