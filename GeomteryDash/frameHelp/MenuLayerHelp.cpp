#include "MenuLayerHelp.h"
#include "../hellocpp/MenuLayer.h"
#include "SpriteManager.h"
#include "../hellocpp/Constant.h"
#include "../objectHelp/Barrier.h"

MenuLayerHelp::MenuLayerHelp(Layer* layerIn)
{
	this->layer = layerIn;
	sh = ((MenuLayer*)(layer))->sh;
}

void MenuLayerHelp::initCreateSprite()
{
	//���Ͻ� �ķ��ؼ���ť
	sh->allSp[7] = sh->createSprite(NULL, Rect(832,150,869-832,180-150), sh->batchNode, 0.5f, 0.5f, 45, 540-37, 63, 55, GoBackZOrder);
	sh->allSp[7]->setRotation(-90.0f);
	sh->AddEventListenerSprite(sh->allSp[7]);

	//�м��  ����LevelLayer�İ�ť
	sh->allSp[20] = sh->createSprite(NULL, Rect(307,644,413-307,750-644), sh->batchNode, 0.5f, 0.5f, WIDTH/2, HEIGHT/2, 179, 179, GroundZOrder+1);
	sh->AddEventListenerSprite(sh->allSp[20]);

	//����  ����  ѡ����Ծ����  �İ�ť
	sh->allSp[21] = sh->createSprite(NULL, Rect(590,339,66,66), sh->batchNode, 0.5f, 0.5f, 293, HEIGHT/2, 114, 114, GroundZOrder+1);
	sh->AddEventListenerSprite(sh->allSp[21]);

	//�Ҳ��  ����   ����  �İ�ť
	sh->allSp[22] = sh->createSprite(NULL, Rect(390,384,66,66), sh->batchNode, 0.5f, 0.5f, 666, HEIGHT/2, 114, 114, GroundZOrder+1);
	sh->AddEventListenerSprite(sh->allSp[22]);

	sh->createSiJiao();//�������ܵ�ͼƬ

	//��Ծ�ϰ��� ����ͼƬ
	sh->createSprite(NULL, Rect(383,574,616-383,631-574), sh->batchNode, 0.5f, 0.5f, WIDTH/2, (HEIGHT/2+80+HEIGHT)/2, 510, 120, GroundZOrder+1);
	//���ɿƼ� ����ͼƬ
	sh->createSprite(NULL, Rect(36,225,269-36,281-225), sh->batchNode, 0.5f, 0.5f, WIDTH/4+50, HEIGHT/8, 250, 60, GroundZOrder+1);
	//��Ȩ���� ����ͼƬ
	sh->createSprite(NULL, Rect(40,284,276-40,343-284), sh->batchNode, 0.5f, 0.5f, WIDTH/4*3-50, HEIGHT/8, 250, 60, GroundZOrder+1);

	sh->createGround();//����������沢�����Զ������ƶ�
	//����  �����ƶ�
	sh->backgroundRoll();

}

bool MenuLayerHelp::JudgeSp(Sprite* sp)
{
	if(sp == sh->allSp[20])//�������� ���ǽ���LevelLayer�İ�ť
	{
		((MenuLayer*)(layer))->gsm->goLevelLayer();
		return true;
	}
	else if(sp == sh->allSp[21])//�������� ���ǽ���  ѡ����Ծ����  �İ�ť
	{
		((MenuLayer*)(layer))->gsm->goChoiceCubeLayer();
		return true;
	}
	else if(sp == sh->allSp[22])//�������� ���ǽ���   ����  �İ�ť
	{
		((MenuLayer*)(layer))->gsm->goMusicLayer();
		return true;
	}
	else if(sp == sh->allSp[7])//�������� ���ǽ���   ����  �İ�ť
	{
		Director::getInstance()->end();
		return true;
	}
	else
		return false;
}
