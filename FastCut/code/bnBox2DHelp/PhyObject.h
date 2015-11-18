#ifndef  _PhyObject_H_
#define  _PhyObject_H_
#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

//�������ص���1��
#define pixToMeter 5

//����ͻ��Ʒ�װ�����
class PhyObject
{
	public:
	 //�������id
	 std::string* poId;
	 //���Ƹ����õľ���
     Sprite* dSp;
     //�����Ӧ�ĸ���
     b2Body* body;
     PhyObject
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
    );
    virtual void refresh();
};


//����ͻ��Ʒ�װ�ࡪ������
class RectPhyObject:public PhyObject
{
  public:
	RectPhyObject
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
    );
};

//����ͻ��Ʒ�װ�ࡪ��Բ��
class CirclePhyObject:public PhyObject
{
  public:
	CirclePhyObject
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
    );
};

//����ͻ��Ʒ�װ�ࡪ�������
class PolygonPhyObject:public PhyObject
{
  public:
	PolygonPhyObject
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
    );
};

//����ͻ��Ʒ�װ�ࡪ���߶�����
class EdgePhyObject:public PhyObject
{
  public:
	EdgePhyObject
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
    );
	void refresh();
  private:
	b2Rot r;
};
#endif
