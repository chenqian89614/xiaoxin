#include "MusicLayerHelp.h"
#include "../hellocpp/MusicLayer.h"
#include "SpriteManager.h"
#include "MusicManager.h"
#include "../hellocpp/Constant.h"
#include "../objectHelp/Barrier.h"
#include "ParticleSystemHelp.h"

MusicLayerHelp::MusicLayerHelp(Layer* layerIn)
{
	this->layer = layerIn;
	sh = ((MusicLayer*)(layer))->sh;
}

void MusicLayerHelp::initCreateSprite()
{
	ParticleSystemHelp* psh = new ParticleSystemHelp();
	psh->createSnow();
	((MusicLayer*)(layer))->addChild(psh->psq3, 10);

	//	����  �����ƶ�
	sh->backgroundRoll();
	sh->createSiJiao();//�������ܵ�ͼƬ
	sh->createGround();//����������沢�����Զ������ƶ�

	//���Ͻ� �ķ��ؼ���ť
	sh->allSp[1] = sh->createSprite(NULL, Rect(832,150,869-832,180-150), sh->batchNode, 0.5f, 0.5f, 45, 540-37, 63, 55, GoBackZOrder);
	sh->allSp[1]->setRotation(-90.0f);
	sh->AddEventListenerSprite(sh->allSp[1]);

	//��Ч ����ͼƬ
	sh->createSprite(NULL, Rect(903,638,1015-903,696-638), sh->batchNode, 0.5f, 0.5f,  420, 320, 150, 60, GroundZOrder+5);
	Rect recta;
	if(MusicManager::onEffect == true)
	{
		recta = Rect(196,187,233-196,225-187);//��Ч����״̬   ��ͼƬ
	}
	else
	{
		recta = Rect(234,188,271-234,224-188);//��Ч�ر�״̬   ��ͼƬ
	}
	//��Ч��ť
	sh->allSp[2] = sh->createSprite(NULL, recta, sh->batchNode, 0.5f, 0.5f, 590, 320, 70, 70, GoBackZOrder);
	sh->AddEventListenerSprite(sh->allSp[2]);

	//���� ����ͼƬ
	sh->createSprite(NULL, Rect(731,640,842-731,696-640), sh->batchNode, 0.5f, 0.5f, 420, 240, 150, 60, GroundZOrder+5);
	if(MusicManager::onSound == true)
	{
		recta = Rect(0,184,38,38);//��ͣ  �����ֿ���״̬   ��ͼƬ
	}
	else
	{
		recta = Rect(40,186,76-40,225-186);//��ͣ  �����ֹر�״̬   ��ͼƬ
	}
	//���ְ�ť
	sh->allSp[3] = sh->createSprite(NULL, recta, sh->batchNode, 0.5f, 0.5f, 590, 240, 70, 70, GoBackZOrder);
	sh->AddEventListenerSprite(sh->allSp[3]);

	//�ؿ�ͼƬ����
	sh->createSprite(NULL, Rect(649, 508,1004-649,637-508), sh->batchNode, 0.5f, 0.5f, WIDTH/2, 270, 600, 250, GoBackZOrder-1);

	//���ɿƼ� ����ͼƬ
	sh->createSprite(NULL, Rect(36,224,269-36,281-224), sh->batchNode, 0.5f, 0.5f, WIDTH/4+50, HEIGHT/8, 250, 60, GroundZOrder+1);
	//��Ȩ���� ����ͼƬ
	sh->createSprite(NULL, Rect(40,284,276-40,343-284), sh->batchNode, 0.5f, 0.5f, WIDTH/4*3-50, HEIGHT/8, 250, 60, GroundZOrder+1);
	//��������Ч ����ͼƬ
	sh->createSprite(NULL, Rect(732,640,1015-732,696-640), sh->batchNode, 0.5f, 0.5f, WIDTH/2, HEIGHT-60, 450, 80, GroundZOrder+1);



}

bool MusicLayerHelp::JudgeSp(Sprite* sp)
{
	if(sp == sh->allSp[1])//�������� ���Ƿ��صİ�ť
	{
		((MusicLayer*)(layer))->gsm->goMenuLayer();
		return true;
	}
	if(sp == sh->allSp[2])//�������� ����   �İ�ť
	{
		if(MusicManager::onEffect == true)
		{
			MusicManager::onEffect = false;
			UserDefault::getInstance()->setBoolForKey("5", MusicManager::onEffect);
			UserDefault::getInstance()->flush();
		}
		else
		{
			MusicManager::onEffect = true;
			UserDefault::getInstance()->setBoolForKey("5", MusicManager::onEffect);
			UserDefault::getInstance()->flush();
		}
		sh->batchNode->removeChild(sh->allSp[2],true);
		Rect recta;
		if(MusicManager::onEffect == true)
		{
			recta = Rect(196,187,233-196,225-187);//��Ч����״̬   ��ͼƬ
		}
		else
		{
			recta = Rect(234,188,271-234,224-188);//��Ч�ر�״̬   ��ͼƬ
		}
		//��Ч��ť
		sh->allSp[2] = sh->createSprite(NULL, recta, sh->batchNode, 0.5f, 0.5f, 590, 320, 70, 70, GoBackZOrder);
		sh->AddEventListenerSprite(sh->allSp[2]);

		return true;
	}
	if(sp == sh->allSp[3])//�������� ����   �İ�ť
	{
		if(MusicManager::onSound == true)
		{
			MusicManager::pauseBackgroundMusic();
		}
		else
		{
			if(MusicManager::noPlaySound == true)
			{
				MusicManager::onSound = true;
				UserDefault::getInstance()->setBoolForKey("6", MusicManager::onSound);
				UserDefault::getInstance()->flush();
				MusicManager::playMenuLayerMusic();
				MusicManager::noPlaySound = false;
			}
			else
			{
				MusicManager::resumeBackgroundMusic();
			}
		}
		sh->batchNode->removeChild(sh->allSp[3],true);
		Rect recta;
		if(MusicManager::onSound == true)
		{
			recta = Rect(0,184,38,38);//��ͣ  �����ֿ���״̬   ��ͼƬ
		}
		else
		{
			recta = Rect(40,186,76-40,225-186);//��ͣ  �����ֹر�״̬   ��ͼƬ
		}
		//���ְ�ť
		sh->allSp[3] = sh->createSprite(NULL, recta, sh->batchNode, 0.5f, 0.5f, 590, 240, 70, 70, GoBackZOrder);
		sh->AddEventListenerSprite(sh->allSp[3]);
		return true;
	}
	else
		return false;
}
