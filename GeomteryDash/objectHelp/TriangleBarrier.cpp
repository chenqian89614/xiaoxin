#include "Barrier.h"
#include "../hellocpp/GameLayer.h"
#include "../hellocpp/FlyLayer.h"
TriangleBarrier::TriangleBarrier
(
		std::string* stTemp,
		Layer* layer,
		Rect recta,
		float spLocationX,
		float spLocationY,
		float spLengthX,
		float spLengthY,
		int localZOrder
):Barrier(stTemp, layer, recta, spLocationX, spLocationY, spLengthX, spLengthY, localZOrder)
{
	idChar = 'T';

	sp = Sprite::createWithTexture(((GameLayer*)(layer))->sh->batchNode->getTexture(),recta);//��������
	sp->setAnchorPoint(Point(0.5f,0.5f));//���þ����ê��   ��Ϊ���ĵ�
	sp->setPosition(Point(spLocationX,spLocationY));//���þ����λ��
	Size size=sp->getContentSize();//��ȡ����ĳߴ�
	float scaleX=spLengthX/size.width;//���������X�������ű�
	float scaleY=spLengthY/size.height;//���������Y�������ű�
	sp->setScaleX(scaleX);//���þ���X�������ű�
	sp->setScaleY(scaleY);//���þ���Y�������ű�
//	layer->addChild(sp,localZOrder);//��������ӵ�������
	if(layer->getTag() == INDEX_GRAMLAYER)
	{
		((GameLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//��������ӵ�������
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		((FlyLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//��������ӵ�������
	}

	this->p = sp->getPosition();//��¼�ϰ��ﵱǰλ��
}

bool TriangleBarrier::collision(JumpCube* jc)
{
	Point point(jc->sp->getPosition().x-this->sp->getPosition().x,jc->sp->getPosition().y-this->sp->getPosition().y);
	float distance = point.getLength();//��������ĵ������������ĵ� ֮��ľ���
	float length = jc->lengthX/2+this->lengthX/2;//������ٽ����
	if(distance<=length)//ʵ�ʼ�¼�Ƿ�С�ڵ����ٽ����
	{
		jc->explode();//���÷���ı�ը����
		return true;
	}
	else
	{
		return false;
	}
}
bool TriangleBarrier::collisionFo(FlyObject* fo)
{
	if (fo->sp->boundingBox().intersectsRect(sp->boundingBox()))//�жϷ��������ϰ����Ƿ��н���
	{
		fo->explode();//���÷������ı�ը����
		return true;
	}
	else
	{
		return false;
	}
}
