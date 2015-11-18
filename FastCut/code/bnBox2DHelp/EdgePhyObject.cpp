#include "PhyObject.h"

//data�Ǹ�������,��λΪ����
//data[0],[1] һ�����������  [2],[3] ��һ�����������
EdgePhyObject::EdgePhyObject
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
	float positionX=(data[0]+data[2])/2;//�����������λ�õ�X����
	float positionY=(data[1]+data[3])/2;//�����������λ�õ�Y����
	//���ø���λ��
	bodyDef.position.Set(positionX/pixToMeter,positionY/pixToMeter);
	//�����������
	body = world->CreateBody(&bodyDef);
	//�ڸ����м�¼��Ӧ�İ�װ����ָ��
	body->SetUserData(id);

	//�����������������
	b2EdgeShape shape;
	//����λ��
	shape.Set(b2Vec2((data[0]-positionX)/pixToMeter,(data[1]-positionY)/pixToMeter), b2Vec2((data[2]-positionX)/pixToMeter,(data[3]-positionY)/pixToMeter));

	if(!isStaticIn)
	{
		//����������������
		b2FixtureDef fixtureDef;
		//������״
		fixtureDef.shape = &shape;
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
		body->CreateFixture(&shape, 0.0f);
	}

	dSp = Sprite::create(pic);
	//��������ӵ�������
	layer->addChild(dSp, 1);
	//��ȡ����ĳߴ�
	Size size=dSp->getContentSize();
	
	b2Vec2 v1=shape.m_vertex1;//v1��ֵΪ���ε�һ������
	b2Vec2 v2=shape.m_vertex2;//v2��ֵΪ���εڶ�������
	b2Vec2 v3=v2-v1;	
	
	//���������X�������ű�
	float scaleX=v3.Length()*pixToMeter/size.width;
	//���������Y�������ű�
	float scaleY=3/size.height;
	//���þ���X�������ű�
	dSp->setScaleX(scaleX);
	//���þ���Y�������ű�
	dSp->setScaleY(scaleY);
	r.s=(v2.y-v1.y)/v3.Length();
	r.c=(v2.x-v1.x)/v3.Length();
}


void EdgePhyObject::refresh()
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
	dSp->setRotation(-angle*180.0/b2_pi-r.GetAngle()*180.0/b2_pi);
}
