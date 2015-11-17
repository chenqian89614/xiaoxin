#include "Barrier.h"
#include "../hellocpp/GameLayer.h"
#include "../hellocpp/MenuLayer.h"
#include "../hellocpp/FlyLayer.h"
#include "../hellocpp/ChoiceCubeLayer.h"
#include "../hellocpp/MusicLayer.h"


RectBarrier::RectBarrier
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
	idChar = 'R';//���þ����ϰ���id
	sp = Sprite::createWithTexture(((GameLayer*)(layer))->sh->batchNode->getTexture(),recta);//�����������
//	sp = Sprite::create(pic);//��������
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
	else if(layer->getTag() == INDEX_MENULAYER)
	{
		((MenuLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//��������ӵ�������
	}
	else if(layer->getTag() == INDEX_FLYLAYER)
	{
		((FlyLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//��������ӵ�������
	}
	else if(layer->getTag() == INDEX_CHOICECUBELAYER)
	{
		((ChoiceCubeLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//��������ӵ�������
	}
	else if(layer->getTag() == INDEX_MUSICLAYER)
	{
		((MusicLayer*)(layer))->sh->batchNode->addChild(sp,localZOrder);//��������ӵ�������
	}


	this->p = sp->getPosition();//��¼�ϰ��ﵱǰλ��
}
//��Ծ�������߶�  С�ڵ���   �ϰ�����ұ�  ����   ��Ծ������ұ߶�  ���ڵ���   �ϰ�������    ʱ   ������ײ���
bool RectBarrier::collision(JumpCube* jc)
{
	float jcBottom = jc->sp->getPosition().y - jc->lengthY/2;//��Ծ������±߶�
	float rbTop = this->sp->getPosition().y + this->lengthY/2;//�ϰ�����ϱ߶�

	float jcZ = jc->sp->getPosition().x-jc->lengthX/2;//��Ծ��������
	float jcY = jc->sp->getPosition().x+jc->lengthX/2;//��Ծ������ұ�
	float rbZ = this->sp->getPosition().x - this->lengthX/2;//�ϰ������߶�
	float rbY = this->sp->getPosition().x + this->lengthX/2;//�ϰ������߶�

	if(jc->sp->getPosition().x<rbZ && jcY>=rbZ)//��Ծ������е�x����  С�� �ϰ������� && ��Ծ������ұ�  ���ڵ���   �ϰ������߶�
	{
		if(jcBottom<rbTop)//��Ծ������±߶�  С�� �ϰ�����ϱ߶�
		{
			jc->explode();//���÷���ı�ը����
			return true;
		}
		else//��Ծ������±߶�  ���ڵ���  �ϰ�����ϱ߶�
		{
			if(jcBottom <= rbTop)//��Ծ������±߶�  С�ڵ���  �ϰ�����ϱ߶�
			{
				jc->refleshAngleAndPosition(rbTop + jc->lengthY/2);//���ø��·�����̬�ķ���
			}
			return false;
		}
	}
	else//��Ծ������е�x����  ����   �ϰ�������    ���Ҵ�ʱ��jcBottom�Ѿ����ڵ���rbTop��
	{
		if(jcBottom <= rbTop)//��Ծ������±߶�  С�ڵ���  �ϰ�����ϱ߶�
		{
			jc->refleshAngleAndPosition(rbTop + jc->lengthY/2);//���ø��·�����̬�ķ���
		}
		return false;
	}
}
bool RectBarrier::collisionFo(FlyObject* fo)
{
	float rbTop = this->sp->getPosition().y + this->lengthY/2;//�ϰ�����ϱ߶�
	float rbBottom = this->sp->getPosition().y - this->lengthY/2;//�ϰ�����±߶�
	float rbZ = this->sp->getPosition().x - this->lengthX/2;//�ϰ������߶�
	float rbY = this->sp->getPosition().x + this->lengthX/2;//�ϰ�����ұ߶�

	if(fo->maxX>=rbZ && fo->minY>=rbTop && fo->minX<=rbY)//���������ұ� ���� �ϰ�������   ���������±ߴ��ڵ����ϰ�����ϱ�  �����������С�ڵ����ϰ�����ұ�
	{
		if(rbTop>fo->heightDown)//�ϰ�����ϱ߶����ڷ������ķ�������
		{
			fo->heightDown = rbTop;//���÷������ķ�������
		}
		return false;
	}
	if(fo->maxX>=rbZ && fo->maxY<=rbBottom && fo->minX<=rbY)//���������ұ� ���� �ϰ�������   ���������ϱ�С�ڵ����ϰ�����±�  �����������С�ڵ����ϰ�����ұ�
	{
		if(rbBottom<fo->heightUp)//�ϰ�����±߶�С�ڷ������ķ�������
		{
			fo->heightUp = rbBottom;//���÷������ķ�������
		}
		return false;
	}
	if(fo->minX>rbY)//����������ߴ����ϰ�����ұ�
	{
		if(rbTop == fo->heightDown)//�ϰ�����ϱ߶� ���� �������ķ�������
		{
			fo->heightDown = HEIGHT_EDGE;//���÷������ķ�������
		}
		if(rbBottom == fo->heightUp)//�ϰ�����±߶� ���� �������ķ�������
		{
			fo->heightUp = HEIGHT - HEIGHT_EDGE;//���÷������ķ�������
		}
		return false;
	}
	if(fo->minX<rbZ && fo->maxX>rbZ)//���������ұ� С�� �ϰ�������   ����������� ���� �ϰ�����ұ�
	{
		if(fo->maxY<rbBottom || fo->minY>rbTop)//���������ϱ�  С�� �ϰ�����±�     ����      ���������±�  ���� �ϰ�����ϱ�
		{
			return false;
		}

		if (fo->sp->boundingBox().intersectsRect(sp->boundingBox()))//�жϷ��������ϰ���֮���Ƿ���ڽ���//�жϷ��������ڵİ�Χ�����ϰ������ڵİ�Χ���Ƿ��н���
		{
			fo->explode();//���÷������ı�ը����
			return true;
		}
		else
		{
			return false;
		}
	}
}
