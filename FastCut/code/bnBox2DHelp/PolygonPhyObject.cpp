#include "PhyObject.h"

#include <string.h>

//data�Ǹ�������,��λΪ����
//���ڶ����  0-x 1-y 2-count 3...-xyxyxyxy
PolygonPhyObject:: PolygonPhyObject
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
	int vcount=((int)data[2]);
	//b2Vec2 verteics[vcount];
//	for(int i=0;i<vcount;i++)
//	{
//		verteics[i].Set(data[i*2+3]/pixToMeter,data[i*2+4]/pixToMeter);
//	}
	int32 count=vcount;

	b2PolygonShape dynamicBox;
//	dynamicBox.Set(verteics, count);

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
	dSp->setAnchorPoint(Point(0, 0));
}
