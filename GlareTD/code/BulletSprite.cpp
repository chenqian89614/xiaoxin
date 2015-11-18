#include "BulletSprite.h"
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

//���캯��
BulletSprite::BulletSprite(){}

//�����ӵ��ķ���
BulletSprite* BulletSprite::create(const char* pic,int id)
{
	//����һ��ָ���ӵ���ָ��temp
	BulletSprite* temp = new BulletSprite();
	//��ʼ���ӵ��������
	temp->initWithFile(pic);
	//�Զ��ͷ�
	temp->autorelease();
	//�õ��ӵ���id
	temp->id = id;
	//���ó�ʼ�ĽǶ�
	temp->angle=0;

	return temp;
}

//�����ӵ��ķ���
BulletSprite* BulletSprite::create(const char* pic,int hurt,int target)
{
	//����ָ���ӵ���ָ��
	BulletSprite* temp = new BulletSprite();
	//��ʼ���ӵ��������
	temp->initWithFile(pic);
	//�Զ��ͷ�
	temp->autorelease();
	//�õ��ӵ����˺�ֵ
	temp->hurt = hurt;
	//�õ���ǰ��Ŀ��Ұ��
	temp->target = target;
	//���÷����ӵ��ĽǶ�
	temp->angle=0;

	return temp;
}
