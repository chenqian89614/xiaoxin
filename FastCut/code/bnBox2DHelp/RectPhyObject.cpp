#include "PhyObject.h"

#include <string.h>


//data�Ǹ�������,��λΪ����
//���ھ��� 0-x 1-y 2-w/2 3-h/2
RectPhyObject:: RectPhyObject
(
		std::string* id,
    	bool isStaticIn,
    	Layer* layer,
    	b2World* world,
    	std::string pic,
    	float* data,
    	float density,
    	float friction,
    	float restitution
):PhyObject(id,isStaticIn,layer,world,pic,data,density,friction,restitution)
{
	//������������
	b2BodyDef bodyDef;
	//����Ϊ���˶�����
	if(!isStaticIn)
	{
		bodyDef.type = b2_dynamicBody;
	}
	//���ø���λ��
	bodyDef.position.Set(data[0]/pixToMeter,data[1]/pixToMeter);
	//��������
	body = world->CreateBody(&bodyDef);
	//�ڸ����м�¼��Ӧ�İ�װ����ָ��
	body->SetUserData(id);

	//���������˶��ĸ������״
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(data[2]/pixToMeter, data[3]/pixToMeter);

	if(!isStaticIn)
	{
		//����������������
		b2FixtureDef fixtureDef;
		//������״
		fixtureDef.shape = &dynamicBox;
		//�����ܶ�
		fixtureDef.density = density;
		//����Ħ��ϵ��
		fixtureDef.friction = friction;
		//���ûָ�ϵ��
		fixtureDef.restitution=restitution;
		//�����������������
		body->CreateFixture(&fixtureDef);
	}
	else
	{
		//����״�������
		body->CreateFixture(&dynamicBox, 0.0f);
	}

	dSp = Sprite::create(pic);
	//��������ӵ�������
	layer->addChild(dSp, 1);
	//��ȡ����ĳߴ�
	Size size=dSp->getContentSize();
	//���������ʱ��Ҫ�ľ�����
	float pw=data[2]*2;
	//���������ʱ��Ҫ�ľ���߶�
	float ph=data[3]*2;
	//���������X�������ű�
	float scaleX=pw/size.width;
	//���������Y�������ű�
	float scaleY=ph/size.height;
	//���þ���X�������ű�
	dSp->setScaleX(scaleX);
	//���þ���Y�������ű�
	dSp->setScaleY(scaleY);
}
