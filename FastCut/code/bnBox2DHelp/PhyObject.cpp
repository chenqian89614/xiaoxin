#include "PhyObject.h"

//data�Ǹ�������,��λΪ����
PhyObject:: PhyObject
(
		std::string* idIn,
    	bool isStaticIn,
    	Layer* layer,
    	b2World* world,
    	std::string pic,
    	float* data,
    	float density,
    	float friction,
    	float restitution
)
{
	this->poId=idIn;
}

//���¾���λ�á���̬��Ϣ�ķ���
void PhyObject::refresh()
{
    //��ȡ�ɼ�����ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	Point origin = Director::getInstance()->getVisibleOrigin();
	//��ȡ�����Ӧ�ĸ���λ��
	b2Vec2 position=body->GetPosition();
	//��ȡ�����Ӧ�ĸ�����̬��
	float angle=body->GetAngle();
	//���þ����λ��
	dSp->setPosition
	(
		Point
		(
			origin.x+visibleSize.width/2+position.x*pixToMeter,
			origin.y+visibleSize.height/2+position.y*pixToMeter
		)
	);
	//���þ������̬
	dSp->setRotation(-angle*180.0/b2_pi);
}
