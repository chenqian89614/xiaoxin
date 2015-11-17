#ifndef _ParticleSystemHelp_H_
#define _ParticleSystemHelp_H_

#include "cocos2d.h"
#include "../hellocpp/Constant.h"

using namespace cocos2d;

class ParticleSystemHelp
{
public :
	ParticleSystemHelp(){
	}
	void createSnow()
	{
		psq3 = ParticleSnow::create();			//������ѩ����ϵͳЧ��
		psq3->retain();										//��������
		psq3->setTexture( Director::getInstance()->getTextureCache()->addImage("pic/snow.png") );	//Ϊ����ϵͳ����ͼƬ
		psq3->setPosition( Point(WIDTH/2, HEIGHT) );						//��������ϵͳ������
		psq3->setLife(3);										//��������ϵͳ������ֵ
		psq3->setLifeVar(1);   								//��������ϵͳ�������仯ֵ
		psq3->setGravity(Point(0,-10));							//��������ϵͳ����������
		psq3->setSpeed(130);									//��������ϵͳ���ٶ�ֵ
		psq3->setSpeedVar(30);    							//��������ϵͳ���ٶȱ仯ֵ
		psq3->setStartColor((Color4F){0.9,0.9,0.9,1});				//��������ϵͳ�Ŀ�ʼ��ɫֵ
		psq3->setStartColorVar((Color4F){0,0,0.1,1});				//��������ϵͳ�Ŀ�ʼ��ɫ�仯ֵ
		psq3->setEmissionRate(psq3->getTotalParticles()/psq3->getLife());	//��������ϵͳ�ķ�������
//		this->addChild(psq3, 0);								//������ϵͳ��ӵ�������
	}


public :
	ParticleSystemQuad* psq1 = ParticleSystemQuad::create("pic/GC/dragEffect.plist");//�ڵ��滬�е�ʱ��    ����������Ч
	bool isPsq1 = false;
	ParticleSystemQuad* psq2 = ParticleSystemQuad::create("pic/GC/explodeEffect.plist");//ײ����  ���鱬ը����Ч
	ParticleSystemQuad* psq3;


};

#endif
